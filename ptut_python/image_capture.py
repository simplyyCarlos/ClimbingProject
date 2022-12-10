import cv2
import sys


def __main__() :
        if (len(sys.argv) !=9):
            sys.exit("Not enough args")
        arg_one = sys.argv[0]
        print(float(arg_one))
        
        filename="savedImage.jpg"
        cap = cv2.VideoCapture(0)
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
        image = cv2.flip(image,1)
        cv2.imwrite("frame.jpg",image)
        cap.release()
        

if __name__ == '__main__':
       __main__()