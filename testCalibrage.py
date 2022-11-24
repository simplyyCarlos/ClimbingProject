from __future__ import print_function
import cv2
import numpy as np
import argparse
from matplotlib import pyplot as plt

cap = cv2.VideoCapture(0)

while cap.isOpened():
    success, src = cap.read()
    src_copy = src.copy()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      break

    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    estimatedThreshold, thresholdImage=cv2.threshold(gray,30,30,cv2.THRESH_BINARY)
    ## DETERMINE CONTOURS AND FILTER THEM
    
    cnts=cv2.findContours(thresholdImage, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if len(cnts) == 2 else cnts[1]
    for c in cnts:
        x,y,w,h = cv2.boundingRect(c)
        cv2.rectangle(src, (x, y), (x + w, y + h), (36,255,12), 2)
    cv2.imshow('Image', src)
    cv2.waitKey(0)

cap.release()
