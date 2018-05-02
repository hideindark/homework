# 							                      			人脸识别系统

​											---基于线性表示的人脸识别系统	

​				作者:梁恺泉 		学号：2016060106012

​	引言：利用python将图片进行灰度处理后，利用LBP特征提取算法，PCA主成分分析算法和最小二乘法实现将基本的人脸识别，并分析LBP特征提取对PCA主成分后人脸识别成功率的影响

​	关键字  LBP，PCA，python，人脸识别，最小二乘法，线性表示

[TOC]

## 1.意义与目的

​	目前技术的发展使得识别技术的识别方式开始逐渐多样化，而人脸与指纹则是目前主流的几种办法之一，目前人脸识别与指纹识别的方案已经基本成熟，个人了解到的更多是对于信息获取方法的改进和对应的信息获取方法的调整，了解并应用人脸识别的方法可以增强我们对于线性代数的应用与图像识别的学习。

​	本次人脸识别的系统的目的主要在于以下几点：

1. 将图像进行灰度处理，主要通过PCA（主成分分析）完成对训练用人脸图像的特征提取，并将训练用人脸照片和测试用人脸照片统一在同一坐标系。
2. 利用线性回归计算测试人脸图像与哪张训练集人脸图像最近，得到结果。
3. 最后测试目标结果是否正确，并得到匹配正确率与运行时间。
4. 测试插入LBP算法对于结果的影响。

## 2.特征提取

​	这次设计的系统上的特征提取为先将图片作灰度处理，降低处理复杂度，以PCA（主成分分析）为主提取图像特征，最后测试是否使用LBP再进行图像特征提取对结果影响的测试。

​	LBP算法以提取局部特征作为判别依据，其优点在于可以降低对光照对于图片的影响，当然这次我并未测试欠曝图片与非欠曝图片对于LBP算法的影响，因为欠曝图片是缺少实际细节而较暗的照片仅仅是缺乏亮度，通过图像处理软件提高画面亮度后还是能够看到画面细节的。

​	LBP算法最初以单个像素点为中心的3x3邻域内将其他8个像素点与中心像素点比较，若大于中心像素则为1，否则为0，通过这样产生一串8位二进制数并以这个二进制数对应的值来反映该区域的纹理信息。之后产生了圆形LBP算子的算法来补正原来LBP算法不能满足不同尺寸和频率纹理的需求。

​	为了防止因为图片旋转导致圆形LBP算子不同的结果而产生了LBP等价模式，而这部分我目前也没看懂，进行特征提取时也仅以半径为2，取8个点进行计算以降低处理难度。

​	LBP实现代码:

```python
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
    
```

​	而主成分分析法，即PCA算法，简单而言就是一种降维的办法，而PCA算法最大的优点也在于降维。

​	PCA算法主要步骤简述为：

1. 先将数据集的均值归0。

2. 求协方差矩阵

3. 求数据集的特征值与特征向量。

4. 取由d个特征值对应的特征向量组成转置矩阵。

5. 对第4步产生的矩阵进行归一化。

6. 用原数据集与第5步的矩阵的转置相乘得到变化后的数据。

   其中第5步在图像处理上可以不做，因为每个像素（相当于不同属性）的取值范围是一样的[^1] ，最终可以得到的是变化后的数据，和第四或者第5步得到的用于进行特征变换的矩阵，用于匹配人脸。

   PCA实现代码：

   ```python
   def pca(data,k):
       data=np.float32(np.mat(data))
       rows,cols=data.shape
       data_mean = np.mean(data,0)#对各列求均值
       x=data - np.tile(data_mean,(rows,1))
       C=x*x.T
       D,V=np.linalg.eig(C)#求特征值D和特征向量V
       W=V[:,0:k]#取前20个特征向量
       W=x.T*W
       for i in xrange(k): #特征向量归一化
           L=np.linalg.norm(W[:,i])
           W[:,i]=W[:,i]/L
       x=x*W#降维后的数据
       return W,data_mean,x
   
   ```

   [^1]: https://blog.csdn.net/smartempire/article/details/22938315

##3.人脸分类

​	主要思路是将一张测试人脸由训练数据中每个人脸数据进行线性表示，以y为测试数据，$\beta_i$为第$i$个训练数据的表示系数，$X_i$为第$i$个训练数据，求$d_i=||y-X_i*\beta_i||$其中的最小值对应的下标$i$并找到其对应分类则表示该测试图像为该类。

​	线性表示代码：

```python
for i in xrange(num_test):
        test_face=data_test_change[i,:].T
        result = np.dot(np.dot(np.linalg.inv(np.dot(train_data,train_data.T)),train_data),test_face)
        for j in xrange(40*7):
            face = train_data[j,:]
            distance [j] = np.linalg.norm(test_face - face*result[j])
        position = np.argsort(distance)[0]
        if train_face_number[position] == test_face_number [i]:
            success_num += 1
```

​	当然我个人也试了一下另一种思路，利用经过PCA处理后两个集合的数据都处在同一坐标系下，求$di=||y-X_i||$其中$X_i$为第$i$行数据，同样是找出最小值对应下标，发现同样有效。

​	直接计算距离用代码：

```python
for i in xrange(num_test):#此时两个矩阵都处在同一坐标系统，由此求测试图片到各个训练图片的距离，并找出其中距离最近的一张作为识别结果
        test_face = data_test_change[i,:]
        diffmat = train_data - np.tile(test_face,(num_train,1))
        distances = np.sum(diffmat**2,axis=1)
        position = np.argsort(distances)[0]
        if train_face_number[position] == test_face_number [i] :
            success_num +=1
```

## 4.测试结果

​	在电脑配置为Inte i5-6300HQ，8G内存，使用电池供电的情况下，以orl人脸库共400张图测试，每组随机取7张图用作训练集，3张图为测试集的测试结果为：

1. 以PCA进行特征提取变换和线性表示的情况下，平均用时5s，准确率在80%左右，有时候会发生意外识别率只有50%。
2. 先将图片进行LBP特征提取，再进行PCA特征提取变化，利用线性表示的情况下，平均用时400s，识别率在50%左右。
3. 以PCA进行特征提取变换，用直接计算距离的情况下，平均用时0.5s，识别率在98%左右。
4. 先将图片进行LBP特征提取，再进行PCA特征提取变化，利用直接计算距离的情况下，平均用时400S+左右，波动在30S上下，识别率在60%到70%左右。

##5.总结

​	PCA特征提取的效果很好，LBP也可以正常使用，但是LBP与PCA不适合配合使用存在冲突，原因暂未分析出来，当然我这么做本身也是兴趣使然，想了解一下LBP与PCA结合之后的结果。

​	在进行图像分类时直接运算距离得到的结果测试下来比用线性表示的结果要好，无论是用orl人脸识别库还是同学们的人脸库最后直接运算距离都要高一点，但是使用同学们的人脸库的时候在每个人取3张做训练集，2张做测试集的情况下波动很大，这个和图片质量有关系就不提了，最后的结果是两者时候识别成功率相同，但是直接运算距离的话平均还是高10%左右。

​	总的来说这次人脸识别系统的学习让我学习了不少技术知识，了解到了图像处理方法，以后在一些比赛中说不定可以使用到其中的内容，可以说受益匪浅了。