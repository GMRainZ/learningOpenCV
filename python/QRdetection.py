import numpy as np
import cv2

import pyzbar.pyzbar as pyzbar
  
# 创建一个VideoCapture对象，参数0表示使用默认的摄像头
cap=cv2.VideoCapture(0)
# 设置摄像头分辨率，参数3表示width，参数4表示height
cap.set(3,640)
cap.set(4,480)

# 设置摄像头参数
#cap.set(cv2.CAP_PROP_AUTO_EXPOSURE,0.25)
#cap.set(cv2.CAP_PROP_EXPOSURE,0.01)


# 进入一个无限循环
while True:
    # 使用cap.read()函数读取摄像头的画面，ret表示是否成功读取，frame表示读取到的画面
    ret,frame=cap.read()
    # 使用cv2.imshow()函数显示画面，参数'frame'表示窗口的名字，frame表示要显示的画面
    
    # 使用pyzbar.decode()函数解码画面中的二维码，参数frame表示要解码的画面对象
    # 返回一个包含所有解码信息的列表
    # 这里我们只关心第一个解码信息，即列表中的第一个元素
    for barcode in pyzbar.decode(frame):
        # 打印出解析出来的数据
        #print(barcode.data)
        myData=barcode.data.decode("utf-8")
        # 将解析出来的数据转换为字符串并打印出来
        print(myData)

        # 将barcode.polygon转换为np.array类型
        pts=np.array([barcode.polygon],np.int32)
        # 将pts转换为(n,1,2)形状
        pts=pts.reshape((-1,1,2))
        # 使用cv2.polylines在frame上绘制多边形，第三个参数True表示闭合路径，第四个参数(255,0,255)表示颜色，第五个参数5表示线宽
        cv2.polylines(frame,[pts],True,(255,0,255),5)


        pts2=barcode.rect
        # 使用cv2.putText在frame上绘制文本，参数依次为：画面对象，文本内容，文本位置，字体，字体大小，颜色，线宽
        cv2.putText(frame,myData,(pts2[0],pts2[1]),cv2.FONT_HERSHEY_SIMPLEX,0.9,(255,0,255),2)
    
    #print(barcode.type)
    cv2.imshow('frame',frame)
    # 使用cv2.waitKey()函数等待用户按下键盘上的键，参数1表示等待1毫秒，0xFF表示键的ASCII码
    if cv2.waitKey(1) & 0xFF == ord('q'):
        # 如果用户按下键'q'，则退出循环
        break



