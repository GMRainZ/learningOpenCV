import cv2
import face_recognition
import numpy as np


imgLinus=face_recognition.load_image_file('imagesDir/faces/linus1.jpg')
imgLinus=cv2.cvtColor(imgLinus,cv2.COLOR_BGR2RGB)
faceLoc=face_recognition.face_locations(imgLinus)[0]
encodeLinus=face_recognition.face_encodings(imgLinus)[0]
cv2.rectangle(imgLinus,(faceLoc[3],faceLoc[0]),(faceLoc[1],faceLoc[2]),(255,0,255),2)

cv2.imshow('Linus',imgLinus)
cv2.waitKey(0)
