import face_recognition as fr
import cv2
from scipy import spatial
import torch
import os
import numpy as np

testnum = 0
datasets_path = "FERET/" #根据实际情况修改地址
types_name = os.listdir(datasets_path)
types_name = sorted(types_name)

list_file = open('embeddings.txt', 'w')
for cls_id, type_name in enumerate(types_name):
    photos_path = os.path.join(datasets_path, type_name)
    if not os.path.isdir(photos_path):
        continue
    photos_name = os.listdir(photos_path)
    photos_name = sorted(photos_name)
    for photo_name in photos_name:
        photo_path = os.path.join(photos_path, photo_name)
        if(photo_name == 'Thumbs.db'):
            break
        img = cv2.imread(photo_path)
        face_embedding = fr.face_encodings(img) # 形式：[array([])]，可能为空[]，也有可能有好几个
        if face_embedding: 
            # print(type(face_embedding[0])) #有机会加一个进度条
            list_file.write(str(cls_id)) #第一列代表人的id
            print(str(cls_id) + " " + str(testnum))
            testnum += 1
            for x in face_embedding[0]:
                list_file.write(" " + str(round(x,8)))
            list_file.write('\n')
            # np.savetxt(list_file,face_embedding[0],fmt='%.8f')            
list_file.close()
