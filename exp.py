from asyncio.format_helpers import _format_callback_source
import torch
import os
import numpy as np
import sys
import random
import matplotlib.pyplot as plt
import math
from funcs import *

import pandas as pd
import seaborn as sns
import copy
import seaborn as sns
from itertools import combinations
from parameter import n



dim = 128 # embedding的长度
d = 16
m = d
# t = 882
# t = 800 #人脸阈值
# k = 3 #指纹阈值
faceid, faceset = vector2set(d, m)


def evaluation(bias,t,k):
    far = 0
    frr = 0
    flag = 0
    same = 0
    notsame = 0
    for I in range(1,101):  #每个人的
        for J in range(1,2):    #第1张 

            for I1 in range(1,101): #与每个人的
                cnt=0
                flag = 0  
                if(I == I1):    #计算自己和自己比的总次数
                    same += 1
                else:   #计算自己和别人比的总次数
                    notsame += 1
                
                # 指纹
                for J1 in range(2,9):   #第2~8张
                    # print(I,J,I1,J1)                
                        
                    if(I >= I1):    #调整文件名称
                        pathr = 'C:/wxj-Study/Forth-Term/GraduationProject/AAA/Codes/Data/dist-5-gon-translation-quan664/'+str(I1)+'_'+str(J)+'and'+str(I)+'_'+str(J1)+'.txt'
                    else:
                        pathr = 'C:/wxj-Study\Forth-Term/GraduationProject/AAA/Codes/Data/dist-5-gon-translation-quan664/'+str(I)+'_'+str(J)+'and'+str(I1)+'_'+str(J1)+'.txt'
                    # pathr = 'dist-5-gon-translation-quan664/8_2and9_5.txt'
                    
                    dist = np.loadtxt(pathr)
                    length = len(dist)
                    # print(dist.min())
                    for i in range(length):
                        if(dist[i] < 10):       #dist<30时认为是同一个点
                            # print(dist[i])
                            cnt += 1
                # 人脸
                registerset, verifyset = regi_veri(faceid, faceset)
                num = len(set.intersection(registerset[I+bias],verifyset[I1+bias]))
                
                if(cnt > k and num > t):                    #有cnt+1个相同点
                    flag = 1                    #判定为同一人
                if((I1 == I) and (flag == 0)):  #FRR
                    # print('frr: ',I,J,I1,J1,dist.min())
                    frr += 1
                if((I1 != I) and (flag == 1)):   #FAR
                    # print('far: ',I,J,I1,J1,dist.min())
                    far += 1
    print('FRR = ' + str(frr) + '/' + str(same) + ' = ' + str(frr/same*100) + '%')
    print('FAR = ' + str(far) + '/' + str(notsame) + ' = ' + str(far/notsame*100) + '%')
    return frr/same*100, far/notsame*100


def exp_bias():
    # bias:-1~99

    FAR = []
    FRR = []
    for bias in range(4,50,5):
        print('bias: ', bias)
        Frr, Far = evaluation(bias, 50, 3)
        FRR.append(Frr)
        FAR.append(Far)
    # plt.plot(FAR,'b')
    # plt.plot(FRR,'r')

    plt.plot(FAR,linewidth =2.0, label = r"FAR",color='tab:blue', linestyle='solid',marker='D') #画图，自变量x放前面
    plt.plot(FRR,linewidth =2.0, label = r"FRR",color='tab:red', linestyle='solid',marker='D') #画图，自变量x放前面

    #以下为图形设置参数
    # plt.legend(frameon=False,loc="upper left",fontsize='large') #设置图例无边框，将图例放在左上角
    # plt.rcParams['figure.figsize']=(6.0,4.0) #图形大小
    # plt.rcParams['savefig.dpi'] = 200 #图片像素
    # plt.rcParams['figure.dpi'] = 200 #分辨率
    # 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
    # 指定dpi=200，图片尺寸为 1200*800
    # 指定dpi=300，图片尺寸为 1800*1200
    # 设置figsize可以在不改变分辨率情况下改变比例

    font1 = {'family' : 'Arial',
    'weight' : 'normal',
    'size'   : 15,
    }

    plt.legend(loc='upper right')  
    plt.grid(color="k", linestyle=":") #网格

    plt.title("Multi-Validation", fontsize=15)

    plt.xlabel('Ten-Sets',font1) #x轴坐标名称及字体样式
    plt.ylabel('FAR/FRR(%)',font1) #y轴坐标名称及字体样式

    plt.xticks(fontsize=13) #x轴刻度字体大小
    plt.yticks(fontsize=13) #y轴刻度字体大小
    plt.xlim(0,9)#X轴范围
    plt.ylim(0,20)#显示y轴范围

    plt.savefig('pics/Multi-Validation_2.png')
    plt.close()

exp_bias()

def exp_t_and_k():
    
    file= open("data.txt","a")

    for k in range(2,4):
        FAR = []
        FRR = []
        for t in range(700,950,50):
            print('k: ', k)
            Frr, Far = evaluation(50, t, k)
            FRR.append(Frr)
            FAR.append(Far)
        plt.plot(FRR,FAR)
        file.writelines(str(k))
        file.write("FRR: ")
        file.writelines(FRR)
        file.write("FAR: ")
        file.writelines(FAR)    
        # plt.plot(FAR,'b')
        # plt.plot(FRR,'r')
    pathr = 'pics/DET_tk.png'
    plt.savefig(pathr)
    plt.close()
    file.close()

# exp_t_and_k()

def exp_t():
    
    FAR = []
    FRR = []
    for t in range(200,1000,100):
        print("t: ",t)
        Frr, Far = evaluation(24, t, 3)
        FRR.append(Frr)
        FAR.append(Far)
    plt.plot(FRR,FAR)
    # plt.plot(FRR,'r')
    pathr = 'pics/DET.png'
    plt.savefig(pathr)
    plt.close()

# exp_t()