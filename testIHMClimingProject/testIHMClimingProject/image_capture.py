

import cv2
import sys

print("image_capture loaded")
   
def main():
    
    filename="savedImage.jpg"
    cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920/2)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080/2)
    while cap.isOpened():
        success, image = cap.read(0)
        if not success:
            print("Ignoring empty camera frame.")
        # If loading a video, use 'break' instead of 'continue'.
            break
            
        # To improve performance, optionally mark the image as not writeable to
        # pass by reference.
        image.flags.writeable = False
            
        # Flip the image horizontally for a selfie-view display.
        cv2.imshow('MediaPipe Pose', cv2.flip(image, 1))
        image.flags.writeable = True
        if cv2.waitKey(5) & 0xFF == 27:
            break
    sucess, image=cap.read(0)
    cv2.imwrite(filename,image)
    cap.release()
        
main()