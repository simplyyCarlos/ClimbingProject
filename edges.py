from __future__ import print_function
import cv2
import numpy as np



cap = cv2.VideoCapture(0)

while cap.isOpened():
    success, src = cap.read()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      break

    
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (3, 3), 0)

    edged = cv2.Canny(blurred, 10, 100)

    cv2.imshow("Original image", src)
    cv2.imshow("Edged image", edged)

    cv2.waitKey(0)
    if cv2.waitKey(5) & 0xFF == 27:
      break
cap.release()
