# import numpy as np
# import matplotlib.pyplot as plt
# fig = plt.figure()
# ax = fig.add_subplot(111)
# x1 = [1,2,3,4,5,6,7,8,9,10]
# frr = [0.5,0.6,0.7,1,2,3,4,4,4,4]
# x2 = [1,2,3,4,5,6,7,8,9,10]
# far = [9,8,7,6,5,4,3,3,2,1]
# # y2 = [0.1717171717171717,0.2828282828282828,0.1616161616161616,0.26262626262626265,0.15151515151515152,0.18181818181818182,0.15151515151515152,0.1717171717171717,0.20202020202020202,0.1717171717171717]
# plt.plot(frr,far)
# # plt.plot(y1,linewidth =2.0, label = r"FAR",color='tab:blue', linestyle='solid',marker='D') #画图，自变量x放前面
# # plt.plot(y2,linewidth =2.0, label = r"FRR",color='tab:red', linestyle='solid',marker='D') #画图，自变量x放前面

# #以下为图形设置参数
# plt.legend(frameon=False,loc="upper left",fontsize='large') #设置图例无边框，将图例放在左上角
# # plt.rcParams['figure.figsize']=(6.0,4.0) #图形大小
# # plt.rcParams['savefig.dpi'] = 200 #图片像素
# # plt.rcParams['figure.dpi'] = 200 #分辨率
# # 默认的像素：[6.0,4.0]，分辨率为100，图片尺寸为 600&400
# # 指定dpi=200，图片尺寸为 1200*800
# # 指定dpi=300，图片尺寸为 1800*1200
# # 设置figsize可以在不改变分辨率情况下改变比例

# font1 = {'family' : 'Arial',
# 'weight' : 'normal',
# 'size'   : 15,
# }
# plt.xlabel('Ten-Fold',font1) #x轴坐标名称及字体样式
# plt.ylabel('FAR/FRR(%)',font1) #y轴坐标名称及字体样式
# #插入文本框
# # plt.text(-1, 30,'(a)',fontsize=18) #在图中添加文本

# plt.xticks(fontsize=13) #x轴刻度字体大小
# plt.yticks(fontsize=13) #y轴刻度字体大小
# # plt.xlim(0,10)#X轴范围
# # plt.ylim(0,0.3)#显示y轴范围
# plt.show()



# ax.plot(x1, y1, color='lightblue',linewidth=3)
# ax.plot(x2, y2, color='darkgreen', marker='^')
# # Plot the cross point
# x3 = np.linspace(6, 7, 1000)       
# #  # (6, 7) intersection range
# y1_new = np.linspace(240, 50, 1000) 
# # # (6, 7) corresponding to (240, 50) in y1
# y2_new = np.linspace(67, 88, 1000)  
# # # (6, 7) corresponding to (67, 88) in y2
# idx = np.argwhere(np.isclose(y1_new, y2_new, atol=0.1)).reshape(-1)
# ax.plot(x3[idx], y2_new[idx], 'ro')
# print(y2_new[idx])
# # plt.savefig('test.png')

# # -*- coding: utf-8 -*-

# # import numpy as np
# # import matplotlib.pyplot as plt
# # from sklearn import svm, datasets
# # from sklearn.metrics import roc_curve, auc  ###计算roc和auc
# # from sklearn.model_selection import train_test_split

# # # Import some data to play with
# # iris = datasets.load_iris()
# # X = iris.data
# # y = iris.target

# # ##变为2分类
# # X, y = X[y != 2], y[y != 2]

# # # Add noisy features to make the problem harder
# # random_state = np.random.RandomState(0)
# # n_samples, n_features = X.shape
# # X = np.c_[X, random_state.randn(n_samples, 200 * n_features)]

# # # shuffle and split training and test sets
# # X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.3, random_state=0)

# # # Learn to predict each class against the other
# # svm = svm.SVC(kernel='linear', probability=True,random_state=random_state)

# # ###通过decision_function()计算得到的y_score的值，用在roc_curve()函数中
# # y_score = svm.fit(X_train, y_train).decision_function(X_test)

# # # Compute ROC curve and ROC area for each class
# # fpr,tpr,threshold = roc_curve(y_test, y_score) ###计算真正率和假正率
# # roc_auc = auc(fpr,tpr) ###计算auc的值

# # plt.figure()
# # lw = 2
# # plt.figure(figsize=(10,10))
# # plt.plot(fpr, tpr, color='darkorange',
# #          lw=lw, label='ROC curve (area = %0.2f)' % roc_auc) ###假正率为横坐标，真正率为纵坐标做曲线
# # plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
# # plt.xlim([0.0, 1.0])
# # plt.ylim([0.0, 1.05])
# # plt.xlabel('False Positive Rate')
# # plt.ylabel('True Positive Rate')
# # plt.title('Receiver operating characteristic example')
# # plt.legend(loc="lower right")
# # plt.show()

# file= open("data.txt","a")
# for i in range(0,5):
#     for j in range(6,9):
#         file.write(str(i)+" "+str(j)+'\n')
# file.close()

# y = 4
# m = 16
# a = bin(int(pow(2,y-1)))[2:].zfill(m)
# print(a)

# def binary2gray(n):
#     # n = int(n, 2)
#     n = int(n)
#     return bin(n^(n>>1))[2:].zfill(16)
    
# binary = input('输入二进制码：')
# print('格雷码:', binary2gray(binary))

# import math
# print(math.log2(2))

import matplotlib.pyplot as plt
FRR = [4,4,4,4,4,4,4,4,4,4]
FAR = [0.0101010101010101,0.0,0.0,0.0,0.0,0.0202020202020202,0.0101010101010101,0.0,0.030303030303030304,0.0]
plt.plot(FAR,linewidth =2.0, label = r"FAR",color='tab:blue', linestyle='solid',marker='D') #画图，自变量x放前面
plt.plot(FRR,linewidth =2.0, label = r"FRR",color='tab:red', linestyle='solid',marker='D') #画图，自变量x放前面
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

plt.savefig('pics/Multi-Validation.png')
plt.close()