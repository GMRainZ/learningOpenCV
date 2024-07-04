import cv2

import os

img=cv2.imread('imagesDir/lena.png')

# 定义一个空列表classNames
classNames=[]
# 定义一个字符串变量classFile，表示配置文件路径
classFile='Config/coco.names'

# 使用with语句和open()函数打开文件，并读取文件内容
with open(classFile,'rt') as f:
    # 将文件内容按行读取，并去除每行末尾的换行符，然后将每行分割成列表
    classNames=f.read().rstrip('\n').split('\n')

print(classNames)

configPath='Config/ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt'
weightsPath='Config/frozen_inference_graph.pb'

# 创建一个基于COCO模型的检测模型
net=cv2.dnn_DetectionModel(weightsPath,configPath)
# 设置输入尺寸
net.setInputSize(320,320)
# 设置输入比例
net.setInputScale(1.0/ 127.5)
# 设置输入均值
net.setInputMean((127.5, 127.5, 127.5))
# 设置输入图像的BGR顺序是否交换
net.setInputSwapRB(True)

cap=cv2.VideoCapture("imagesDir/Road_traffic_video2.mp4")
# cap=cv2.VideoCapture(0)
cap.set(3,880)
cap.set(4,720)


if cap.isOpened()==False:
    print("Error opening video stream or file")
    exit(1)
while True:
    success,img=cap.read()
    classIds, confs, bbox = net.detect(img, confThreshold=0.5)
    if len(classIds) != 0:
        # 遍历classIds、confs、bbox
        for classId, confidence, bbox in zip(classIds.flatten(),confs.flatten(),bbox):
            # 在图片上绘制矩形框
            cv2.rectangle(img,bbox,(255,0,255),2)
            # 在矩形框下方添加类别名称

            print(classId-1)

            if classId <= 80:
                cv2.putText(img,classNames[classIds[0]-1].upper(),(bbox[0]+10,bbox[1]+30),cv2.FONT_HERSHEY_COMPLEX,1,(0,255,0),2)
        
    cv2.imshow("Output",img)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()