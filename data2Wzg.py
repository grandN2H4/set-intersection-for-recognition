from funcs import *
import math
D = [2,4,8,16]

for d in D:
    m = d # LSSC/One-hot
    # m = int(math.log2(d)) #DBR/BRGC
    list_id, list_set = vector2set(d,m)
    file = open("dataFace/OneHot_d_"+str(d)+".txt","w")
    n = len(list_id)
    for i in range(n):
        file.write(str(list_id[i][0]))
        for j in list_set[i]:
            file.write(" "+str(j))
        file.write("\n")
    file.close()