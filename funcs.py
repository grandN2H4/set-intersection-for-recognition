import numpy as np
import random
import matplotlib.pyplot as plt
import math

dim = 128 # embedding的长度
#数字变成1~d
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
                    quanData[idx][jdx] = i+1                
                elif val >= T[jdx][i] and val <= T[jdx][i+1]:
                    quanData[idx][jdx] = i+1
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
            # feature += bin(int(pow(2,y)-1))[2:].zfill(m) #LSSC
            # feature += bin(int(y))[2:].zfill(m)            #DBR
            # feature += bin(y^(y>>1))[2:].zfill(m)          #BRGC
            feature += bin(int(pow(2,y-1)))[2:].zfill(m)   #One-hot           
        for i,j in enumerate(feature):
            if j == '1':
                a.add(i)     
        # print(a)   
        list_set.append(a)
    list_id = allData[:,0:1]
    return list_id, list_set

def regi_veri(faceid, faceset):

    n_all = len(faceid)
    i = 0
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

    return registerset, verifyset

def evaluate(d, m, t, times):
    

    faceid, faceset= vector2set(d, m)

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
    total = n * (n - 1) / 2
    return far, frr, notsame, same


d = 4 # d是量化槽的数量
m = 10 # 量化的位数 m与d相关
t = 8 # 比较的阈值
times = 4000
step = 1
allnum = 40000
Init_Epoch      = 0
Interval_Epoch  = 12
Epoch = 20
FAR = []
FRR = [] 
for epoch in range(Init_Epoch, Interval_Epoch):
    print("epoch: " + str(epoch))
    far, frr, notsame, same = evaluate(d, m, t, times)
    if(same == 0 or notsame == 0):
        print(same, notsame);
    else:
        FRR.append(frr/same)
        FAR.append(far/notsame) 
        print("FRR: ",frr/same,"FAR: ",far/notsame)  
    # if d < allnum:
    #     d += step
    t += 1
    m = int(math.log(d,2))

plt.plot(FAR,'b')
plt.plot(FRR,'r')
plt.savefig('t2-22_d4_FAR&FRR_plot.png')


# print("far: " + str(far/notsame))
# print("frr: " + str(frr/same))