import numpy as np
import matplotlib.pyplot as plt
fingerData = np.loadtxt("data.txt")
cnt = fingerData[:,0:1]

# t = 800
k = 3
same = 100
notsame = 9900
def FarFrr(num,k,t):
    frr = 0
    far = 0
    for i in range(0,100):
        for j in range(0,100):
            flag = 0
            if(cnt[i*100+j] > k and num[i*100+j] > t):                    #有cnt+1个相同点
                flag = 1                    #判定为同一人
            if((i == j) and (flag == 0)):  #FRR
                # print('frr: ',I,J,I1,J1,dist.min())
                frr += 1
            if((i != j) and (flag == 1)):   #FAR
                # print('far: ',I,J,I1,J1,dist.min())
                far += 1
    print('FRR = ' + str(frr) + '/' + str(same) + ' = ' + str(frr/same*100) + '%')
    print('FAR = ' + str(far) + '/' + str(notsame) + ' = ' + str(far/notsame*100) + '%')
    return frr/same, far/notsame


def det_d(Approach):
    D = [2,4,8,16]
    line_s = ["-", "--", "-.", ":"]
    for i,d in enumerate(D):
        faceData = np.loadtxt("dataPics/"+Approach+str(d)+".txt")
        num = faceData[:,0:1]
        FAR = []
        FRR = []
        for t in range(5,1000,5):
            Frr, Far = FarFrr(num,k,t)
            FRR.append(Frr)
            FAR.append(Far)            
        plt.plot(FRR,FAR,linestyle=line_s[i], linewidth=3, label="d="+str(d))

    font1 = {'family' : 'Arial',
    'weight' : 'normal',
    'size'   : 12,
    }
    plt.legend(loc='upper right')  
    plt.grid(color="k", linestyle=":") #网格
    plt.xlabel('False  Rejection  Rate', font1)
    plt.ylabel('False  Acceptance  Rate', font1)
    plt.title("DET Curve", fontsize=15)

    pathr = 'graph/'+Approach+'.png'
    plt.savefig(pathr)

    plt.close()

# det_d("OneHot"+"_d_")

def det_bin():
    Approach = ["DBR","BRGC","LSSC","OneHot"]
    line_s = ["-", "--", "-.", ":"]
    for i,approach in enumerate(Approach):
        faceData = np.loadtxt("dataPics/"+approach+"_d_16.txt")
        num = faceData[:,0:1]
        FAR = []
        FRR = []
        for t in range(5,1000,5):
            Frr, Far = FarFrr(num,k,t)
            FRR.append(Frr)
            FAR.append(Far)            
        plt.plot(FRR,FAR,linestyle=line_s[i], linewidth=3, label="Approach="+approach)

    font1 = {'family' : 'Arial',
    'weight' : 'normal',
    'size'   : 12,
    }
    plt.legend(loc='upper right')  
    plt.grid(color="k", linestyle=":") #网格
    plt.xlabel('False  Rejection  Rate', font1)
    plt.ylabel('False  Acceptance  Rate', font1)
    plt.title("DET Curve", fontsize=15)

    pathr = 'graph/Approach.png'
    plt.savefig(pathr)

    plt.close()

det_bin()