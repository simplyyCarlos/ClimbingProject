import cv2
import mediapipe as mp
import mmap
import sys
from mediapipe.framework.formats import landmark_pb2





mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_pose = mp.solutions.pose
IMAGE_HEIGHT = 480
IMAGE_WIDTH = 640

def __main__() :
    shmem = mmap.mmap(-1, 16*4 ,"shm", access=mmap.ACCESS_WRITE)
    cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)
    with mp_pose.Pose(
        min_detection_confidence=0.7,
        min_tracking_confidence=0.9) as pose:
        tab = [[0]*8,[0]*8]
        
        while cap.isOpened():
            success, image = cap.read(0)
            if not success:
                print("Ignoring empty camera frame.")
            # If loading a video, use 'break' instead of 'continue'.
                continue
            
            # To improve performance, optionally mark the image as not writeable to
            # pass by reference.
            image.flags.writeable = False
            image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            results = pose.process(image)
            if (results.pose_landmarks):
                landmark_subset = landmark_pb2.NormalizedLandmarkList(
                    landmark = [
                        results.pose_landmarks.landmark[15],
                        results.pose_landmarks.landmark[16],
                        results.pose_landmarks.landmark[17],
                        results.pose_landmarks.landmark[18],
                        results.pose_landmarks.landmark[19],
                        results.pose_landmarks.landmark[20],
                        results.pose_landmarks.landmark[21],
                        results.pose_landmarks.landmark[22]
                    ]
                )
            
                # Draw the pose annotation on the image.
                image.flags.writeable = True
                image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
                poses=landmark_subset.landmark
                cpt = 0
                
                for data_point in poses:
                    x=data_point.x * IMAGE_WIDTH
                    y=data_point.y * IMAGE_HEIGHT
                    if(x >=0 and y>=0):
                        tab[0][cpt] = int(data_point.x*10**8)
                        tab[1][cpt] = int(data_point.y*10**8)
                        
                    
                    
                    if(cpt %2 == 0):
                        cv2.circle(image,(tab[0][cpt],tab[1][cpt]),10,(255,0,0),1)
                    else:
                        cv2.circle(image,(tab[0][cpt],tab[1][cpt]),10,(0,0,255),1)
                    
                    cpt+=1
                cpt = 0
                
                for op in tab:
                    for data in op:
                        shmem.seek(cpt)
                        shmem.write((data).to_bytes(4,"little"))
                        cpt += 4 
                
                

            # Flip the image horizontally for a selfie-view display.
            cv2.imshow('MediaPipe Pose', cv2.flip(image, 1))
            if cv2.waitKey(5) & 0xFF == 27:
                break
        cap.release()
    
        

if __name__ == '__main__':
       __main__()
