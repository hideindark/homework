import os
from pylab import *
import numpy as np
import random
import cv2
from skimage import feature as skft
#将图片以灰度读取并作处理后返回矩阵
def imageload(i,p):
    Datadir= 'face'+'/'+str(i)+'/'
    data=[]
    for i in p:
        filename=Datadir + 'testimg' + str(i) +'.jpg'
        img = cv2.imread(filename,0)
        data += lbp(img)
    data = pca(data)
    return data
def lbp(img):
    lbpimg=skft.local_binary_pattern(img,3,24)
    rows,cols= lbpimg.shape
    imgVector = zeros((1,rows*cols))
    imgVector = reshape(lbpimg,(1,rows*cols))
    return imgVector
    
def pca(data):
    data=np.mat(data)
    x=data - np.mean(data)#零均值化
    rows,cols=x.shape
    C=x*x.T/(rows*cols)
    D,V=np.linalg.eig(C)#求特征值D和特征向量V
    W=V[:,0:10]#取前10个特征向量
    x1=W.T*x#特征变换
    return x1

if __name__ == '__main__':
    name = ["张锦伦","刘昕","刘梦虎","孔飞","胡进垒","陈小羽"]
    train = []
    for i = xrange(7):
        train[i] = imageload(i,range(1,5)) 
    test = [random.randint(0,6),5]
    print "test:"+name[test[0]]
    test=imageload(test[0],5)#读取测试图片，并经过lbp,pca处理之后转为列向量
    distance=[]
    for i in xrange(7):#计算图片到各个类型的距离
        result=np.linalg.slove(train[i],test)
        distance+=np.linalg.norm(result)
    print "find："+name[distance.index(min(distance))]