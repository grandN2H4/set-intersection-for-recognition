from asyncio.format_helpers import _format_callback_source
import torch
import os
import numpy as np
import sys
import random
import matplotlib.pyplot as plt
import math

dim = 128 # embedding的长度

def sort_And_divide(d):
    # d是量化槽的数量
       
    # 取数据
    print("step1")
    allData = np.loadtxt("embeddings.txt")
    data = allData[:,1:] 
    
    # 对每一列进行排序
    print("step2")
    sortedData = np.sort(data, axis=0)

    # 每个槽中的数量
    print("step3")
    slotNum = data.shape[0]//d
    if (data.shape[0] % d) != 0 :
        slotNum += 1

    # 把每个槽的分割代表数字提出来
    print("step4")
    slotData = np.zeros((d,dim))
    i = 0
    # 使用切片方法在循环中按照指定步长递增
    for x in sortedData[::slotNum]: 
        slotData[i] = x
        i += 1
    
    # 对每一个embedding，量化它。将slot数组转置更方便迭代
    print("step5")
    quanData = np.zeros((data.shape[0],dim), dtype=int)
    T = slotData.T
    for idx,embedding in enumerate(data):
        for jdx, val in enumerate(embedding):
            for i in range(d):
                if i == d - 1:
                    quanData[idx][jdx] = i                
                elif val >= T[jdx][i] and val <= T[jdx][i+1]:
                    quanData[idx][jdx] = i
                    break
                    # print(T[jdx][i],quanData[idx][jdx])
    # print(quanData.shape)
    # print(data.shape)            
    print("step6")
    newData = np.hstack((allData[:,0:1].astype(int),quanData))
    return newData
    
def vector2set(d,m):
    
    allData = sort_And_divide(d)
    data = allData[:,1:]
    list_set = list()
    for x in data:
        feature = ''
        a = set()
        for y in x:
            feature += bin(int(pow(2,y)-1))[2:].zfill(m-1) #LSSC
            # feature += bin(int(y))[2:].zfill(m) #DBR
        # print(bin(int(pow(2,y)-1))[2:].zfill(m))
        for i,j in enumerate(feature):
            if j == '1':
                a.add(i)     
        # print(a)   
        list_set.append(a)
    list_id = allData[:,0:1]
    return list_id, list_set

def random_evaluate(faceid, faceset, t, times):

    n = len(faceid)
    far = 0
    frr = 0
    same = 0
    notsame = 0
    for idx in range(times):
        i = random.randint(0,n-1)
        j = random.randint(0,n-1)  
        num = len(set.intersection(faceset[i],faceset[j]))
        # print(num)
        # print(i, j, faceid[i], faceid[j])
        if(faceid[i] == faceid[j]):    #计算自己和自己比的总次数
            same += 1
        else:           #计算自己和别人比的总次数
            notsame += 1
        # 认假
        if(faceid[i] != faceid[j] and num > t):
            far += 1
        # 拒真
        if(faceid[i] == faceid[j] and num < t):
            frr += 1

    return far, frr, notsame, same

def evaluate(faceid, faceset, t):
    
    n = len(faceid)
    far = 0
    frr = 0
    same = 0
    notsame = 0
    i = 0
    j = 0
    iddx = list()

    while(i < n):
        if(i == 0 or faceid[i-1] != faceid[i]):
            iddx.append(i)
            iddx.append(i+1)
            iddx.append(i+2)
        i += 1
    m = len(iddx)
    print("m: ",m)
    for i in range(n-1):
        for j in range(i+1,n):
            # i = iddx[k]
            # j = iddx[s]
            # print(i," ",j)
            num = len(set.intersection(faceset[i],faceset[j]))
            # print(num)
            # print(i, j, faceid[i], faceid[j])
            if(faceid[i] == faceid[j]):    #计算自己和自己比的总次数
                same += 1
            else:           #计算自己和别人比的总次数
                notsame += 1
            # 认假
            if(faceid[i] != faceid[j] and num > t):
                far += 1
            # 拒真
            if(faceid[i] == faceid[j] and num < t):
                frr += 1
    return far, frr, notsame, same

def regi_veri(faceid, faceset, t):

    n_all = len(faceid)
    far = 0
    frr = 0
    same = 0
    notsame = 0
    i = 0
    j = 0
    registerid = list()
    registerset = list()
    verifyid = list()
    verifyset = list()
    while(i < n_all):
        if(i == 0 or faceid[i-1] != faceid[i]):
            verifyset.append(faceset[i])
            verifyid.append(faceid[i])
            registerid.append(faceid[i])
            i += 1
        a = set()
        while(i < n_all and faceid[i-1] == faceid[i]):
            a = a | faceset[i]
            i += 1
        registerset.append(a)
    m = len(registerid)
    n = len(verifyid)

    return registerset, verifyset

    # for i in range(0, m):
    #     for j in range(0, n):
    #         num = len(set.intersection(registerset[i],verifyset[j]))
    #         # print("num: ", num)
    #         if(registerid[i] == verifyid[j]):    #计算自己和自己比的总次数
    #             same += 1
    #         else:           #计算自己和别人比的总次数
    #             notsame += 1
    #         # 认假
    #         if(registerid[i] != verifyid[j] and num > t):
    #             far += 1
    #         # 拒真
    #         if(registerid[i] == verifyid[j] and num < t):
    #             frr += 1
    # return far, frr, notsame, same
    
# d = 20 # d是量化槽的数量
# m = d # 量化的位数 m与d相关
# t = 850 # 比较的阈值
times = 400000

# faceid, faceset= vector2set(d, m)

def test_t(d, faceid, faceset, A, B, t, step):
    FAR = []
    FRR = [] 
    if(t == 2):
        Far = 0
        Frr = 0
        flag = 0
        best_t = -2
    else:
        Far = -1
        Frr = -1
        flag = 1
        best_t = 0
    for epoch in range(A, B):
        print("epoch: " + str(epoch))
        # far, frr, notsame, same = random_evaluate(faceid, faceset, t, times)
        # far, frr, notsame, same = evaluate(faceid, faceset, t)
        far, frr, notsame, same = regi_veri(faceid, faceset, t)
        if(same == 0 or notsame == 0):
            print(same, notsame);
        else:
            FRR.append(frr/same)
            FAR.append(far/notsame)   
            print("d: ", d)
            print("t: ", t, "FRR: ",frr,"/",same,"=",frr/same)
            print("FAR: ",far,"/",notsame,"=",far/notsame)
            if(best_t == -2 and frr/same > far/notsame):
                best_t = t-step
            if(Far == -1 and far/notsame < 0.005):
                Far = far/notsame
                Frr = frr/same
                best_t = t
        t += step

    plt.plot(FAR,'b')
    plt.plot(FRR,'r')
    plt.savefig('rv_t'+str(t)+'-'+str(t + step*50)+'_d'+str(d)+'_FAR&FRR_plot.png')
    plt.close()
    if(flag == 0):
        return best_t
    else:
        return Far, Frr, best_t

def test_d():
    for d in range(2,32):
        m = d
        faceid, faceset = vector2set(d, m)
        Init_Epoch      = 0
        Interval_Epoch  = 50
        Epoch = 100
        step1 = 50
        step2 = 1
        t = test_t(d, faceid, faceset, Init_Epoch, Interval_Epoch, 2, step1)
        Far, Frr, best_t = test_t(d, faceid, faceset, Interval_Epoch, Epoch, t, step2)

# test_d()