# -*- coding: utf-8 -*-
import os
import numpy as np
import random
import cv2
import math
import time
#将图片以灰度读取并作pca处理后返回特征矩阵，降维后的数据，测试数据和每一行的均值
def imageload(k):
    choose = np.random.permutation(10)+1
    train_data=np.zeros((k*40,112*92))
    test_data=np.zeros(((10-k)*40,112*92))
    train_face_number = np.zeros(40*k)
    test_face_number = np.zeros(40*(10-k))
    for i in xrange(40):
        for j in xrange(10):
            filename='orl_faces/s' + str(i+1)+'/'  + str(choose[j]) +'.pgm'
            img = cv2.imread(filename,0)
            #img = cv2.resize(img,(40,120),interpolation=cv2.INTER_AREA)
            #img=lbp(img)#lbp算法加上pca之后会导致识别效果变差，应该是两者之间有冲突造成了干扰
            adjustface=img.flatten()
            Dir = 'testface/'+str(i*10+j)+'.jpg'
            #cv2.imwrite(Dir,img)
            if j<k:
                train_data[i*k+j,:] = adjustface
                train_face_number[i*k + j] =i
            else:
                test_data[i*(10-k)+j-k,:] = adjustface
                test_face_number[i*(10-k) + j-k] = i
    W,data_mean,data = pca(train_data,30)
    return W,data,test_data, data_mean,train_face_number,test_face_number
##LBP算法，提取人脸特征
def lbp(img,R=2,P=8):
    pi = math.pi  
    rows,cols = np.shape(img)  
    tempface = np.mat(np.zeros((rows,cols)))  
    for x in xrange(R,rows-R):  
        for y in xrange(R,cols-R):  
            repixel = ''  
            pixel=np.int(img[x,y])  
            #　圆形LBP算子  
            for p in [2,1,0,7,6,5,4,3]:  
                p = np.float(p)  
                xp = x + R* np.cos(2*pi*(p/P))  
                yp = y - R* np.sin(2*pi*(p/P))  
                if img[np.int(xp),np.int(yp)] > pixel:
                    repixel += '1'  
                else:  
                    repixel += '0'  
            tempface[x,y] = int(binaryro(repixel),base=2)  
    return tempface  
def binaryro(pixel):
    length = len(pixel)
    zero = ''
    for i in range(length)[ : :-1]:
        if pixel[i]=='0':
            pixel=pixel[:i]
            zero+='0'
        else:
            return zero+pixel
        if len(pixel) == 0:
            return '0'
    
def pca(data,k):
    data=np.float32(np.mat(data))
    rows,cols=data.shape
    data_mean = np.mean(data,0)#对各列求均值
    x=data - np.tile(data_mean,(rows,1))
    C=x*x.T
    D,V=np.linalg.eig(C)#求特征值D和特征向量V
    W=V[:,0:k]#取前k个特征向量
    W=x.T*W
    for i in xrange(k): #特征向量归一化
        L=np.linalg.norm(W[:,i])
        W[:,i]=W[:,i]/L
    x=x*W#降维后的数据
    return W,data_mean,x

if __name__ == "__main__":
    start= time.clock()
    pca_mat, train_data, test_data, train_data_mean, train_face_number,test_face_number = imageload(7) 
    num_train = train_data.shape[0]
    num_test =  test_data.shape[0]
    data_test_change =np.array( (test_data - np.tile(train_data_mean,(num_test,1)))*pca_mat )#将测试图像做pca处理
    train_data = np.array(train_data)
    distance = np.zeros(40*7)
    success_num =0;
    '''
    for i in xrange(num_test):#此时两个矩阵都处在同一坐标系统，由此求测试图片到各个训练图片的距离，并找出其中距离最近的一张作为识别结果
        test_face = data_test_change[i,:]
        diffmat = train_data - np.tile(test_face,(num_train,1))
        distances = np.sum(diffmat**2,axis=1)
        position = np.argsort(distances)[0]
        if train_face_number[position] == test_face_number [i] :
            success_num +=1
    '''
    for i in xrange(num_test):#利用最小二乘法得到训练人像到测试人像的表示系数，并算出距离
        test_face=data_test_change[i,:].T
        result = np.dot(np.dot(np.linalg.inv(np.dot(train_data,train_data.T)),train_data),test_face)
        for j in xrange(40*7):
            face = train_data[j,:]
            distance [j] = np.linalg.norm(test_face - face*result[j])
        position = np.argsort(distance)[0]
        if train_face_number[position] == test_face_number [i]:
            success_num += 1
    print 'timeuse:'+str(time.clock()-start)+'s'
    possible = np.float(success_num)/num_test
    print 'The classify accuracy is: %.2f%%'%(possible * 100)