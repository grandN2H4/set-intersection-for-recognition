from evaluate import *
d = 16
m = d
list_id, list_set = vector2set(d,m)

file = open("faceSet.txt","w")
n = len(list_id)
for i in range(n):
    file.write(str(list_id[i][0]))
    for j in list_set[i]:
        file.write(" "+str(j))
    file.write("\n")
file.close()