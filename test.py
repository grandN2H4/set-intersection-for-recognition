import numpy as np
import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)
x1 = [1,2,3,4,5,6,7,8]
y1 = [20,100,50,120,55,240,50,25]
x2 = [3,4,5,6,7,8,9]
y2 = [25,35,14,67,88,44,120]
ax.plot(x1, y1, color='lightblue',linewidth=3)
ax.plot(x2, y2, color='darkgreen', marker='^')
# Plot the cross point
x3 = np.linspace(6, 7, 1000)       
#  # (6, 7) intersection range
y1_new = np.linspace(240, 50, 1000) 
# # (6, 7) corresponding to (240, 50) in y1
y2_new = np.linspace(67, 88, 1000)  
# # (6, 7) corresponding to (67, 88) in y2
idx = np.argwhere(np.isclose(y1_new, y2_new, atol=0.1)).reshape(-1)
ax.plot(x3[idx], y2_new[idx], 'ro')
print(y2_new[idx])
plt.savefig('test.png')