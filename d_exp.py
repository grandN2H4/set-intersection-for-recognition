import torch
import os
import numpy as np
import sys
import random
import matplotlib.pyplot as plt
import math
import scipy.interpolate, scipy.optimize

# embedding的长度
DIM = 128
# 量化
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
    slotData = np.zeros((d,DIM))
    i = 0
    # 使用切片方法在循环中按照指定步长递增
    for x in sortedData[::slotNum]: 
        slotData[i] = x
        i += 1
    
    # 对每一个embedding，量化它。将slot数组转置更方便迭代
    print("step5")
    quanData = np.zeros((data.shape[0],DIM), dtype=int)
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

# 二值化并映射到集合    
def vector2set(d,m):
    
    allData = sort_And_divide(d) #量化后的数据
    data = allData[:,1:]
    list_id = allData[:,0:1]
    list_set = list()

    # 二值化
    for x in data:
        feature = ''
        a = set()
        for y in x:
            feature += bin(int(pow(2,y)-1))[2:].zfill(m-1) #LSSC
            # feature += bin(int(y))[2:].zfill(m) #DBR

        # 把idx作为集合元素
        for i,j in enumerate(feature):
            if j == '1':
                a.add(i)        
        list_set.append(a)

    return list_id, list_set

# 通过随机比较来评估
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

# 通过两两比较来评估
def evaluate(d, m, t):
    
    faceid, faceset= vector2set(d, m)

    n = len(faceid)
    far = 0
    frr = 0
    same = 0
    notsame = 0
    for i in range(n-1):
        for j in range(i+1,n):
            num = len(set.intersection(faceset[i],faceset[j]))
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

# 做每一维度关于d的实验
def exp_d(Dim):

    # allData = sort_And_divide(d) # 量化后的数据
    # 量化
    min_d = 2
    max_d = 32+1
    quanData = list()
    for d in range(min_d, max_d):
        quanData.append(sort_And_divide(d))
    faceid = quanData[0][:, 0:1]    
    print("quan Done.")
    ans_d = list()
    # 对每一维度的数据
    for dim in range(100,105):
        print("dim: ", dim)

        # 找到最好的d
        best_d = 0
        best_eer = 1.0
        for d in range(min_d, max_d):
            print("d: ", d, end = ' ')
            allData = quanData[d-min_d]
            Far = []
            Frr = []                        
            m = d
            # 二值化并映射到集合
            faceset = list()
            data = allData[:,dim+1:dim+2] #取一维数据（第一列是id） 
            print(data)
            for x in data:
                feature = bin(int(pow(2,x)-1))[2:].zfill(m) #LSSC
                a = set()    
                for i,j in enumerate(feature):
                    if j == '1':
                        a.add(i)        
                faceset.append(a)
    
            # 评估计算FAR、FRR
            n = len(faceid)

            for t in range(0, m+1):
                far = 0
                frr = 0
                same = 0
                notsame = 0
                for i in range(n-1):
                    for j in range(i+1, n):
                        num = len(set.intersection(faceset[i],faceset[j]))
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
                Frr.append(frr/same)
                Far.append(far/notsame)
            print("plot")
            plt.plot(Far,'b')
            plt.plot(Frr,'r')
            plt.savefig("pics/dim"+str(dim)+"_d"+str(d)+"_plot.png")
            # 计算EER
            idx = 0
            for t in range (0,m):
                if(Frr[t] >= Far[t]):
                    y1 = np.linspace(Frr[t-1], Frr[t], 50)
                    y2 = np.linspace(Far[t-1], Far[t], 50)
                    idx = np.argwhere(np.isclose(y1, y2, atol=0.01)).reshape(-1)          
                    eer = y2[idx][0]
                    print("eer: ", eer, "idx: ", idx)
                    break 
            if eer < best_eer:
                best_eer = eer
                best_d   = d
        print("best_eer: ", best_eer, "best_d: ", best_d)
        ans_d.append(best_d)
    print("ans_d: ", ans_d)
    return ans_d

exp_d(5) 