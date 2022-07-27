import numpy as np
import matplotlib.pyplot as plt
Data = np.loadtxt("data.txt")
cnt = Data[:,0:1]
num = Data[:,1:2]
# t = 800
# k = 3
same = 100
notsame = 9900
def FarFrr(k,t):
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

line_s = ["-", "--", "-.", ":"]
for k in range(2,6):
    
    FAR = []
    FRR = []
    for t in range(5,1000,5):
        Frr, Far = FarFrr(k,t)
        FRR.append(Frr)
        FAR.append(Far)
        
    plt.plot(FRR,FAR,linestyle=line_s[k-2], linewidth=3, label=r'$t_1$'+"="+str(k))

    font1 = {'family' : 'Arial',
    'weight' : 'normal',
    'size'   : 12,
    }
    plt.legend(loc='upper right')  
    plt.grid(color="k", linestyle=":") #网格
    plt.xlabel('False  Rejection  Rate', font1)
    plt.ylabel('False  Acceptance  Rate', font1)
    plt.title("DET Curve", fontsize=15)

    pathr = 'pics/DET.png'
    plt.savefig(pathr)
    
    # file= open("dataForPics.txt","w")
    # file.write(str(k)+"\n")
    # file.write("FRR: " + str(FRR) + "\n")
    # file.write("FAR: " + str(FAR) + "\n")

plt.close()
