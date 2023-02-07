import cv2
import mediapipe as mp
import numpy as np
from mediapipe.framework.formats import landmark_pb2
import mmap



mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_pose = mp.solutions.pose


def main() :
    cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1024)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 576)
    with mp_pose.Pose(
        min_detection_confidence=0.75,
        min_tracking_confidence=0.75) as pose:
        shmem = mmap.mmap(-1, 64 ,"positionMain", access=mmap.ACCESS_WRITE)
        file = open("ContinueMediapipe.txt")
        while cap.isOpened() and file.read()=="1":
            file.close()
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
                i = 0
                print(poses)
                for data_point in poses:
                    
                    shmem.seek(i)
                    shmem.write(np.float32(data_point.x).tobytes())
                    i+=4
                    shmem.seek(i)
                    shmem.write(np.float32(data_point.y).tobytes())
                    i+=4
            readable = False
            while(readable != True):
                try:
                    file = open("ContinueMediapipe.txt")
                    if(file.readable()==True):
                        readable = True
                except:
                    continue
                
            # Flip the image horizontally for a selfie-view display.
            """cv2.imshow('MediaPipe Pose', cv2.flip(image, 1))
            if cv2.waitKey(5) & 0xFF == 27:
                break"""
        cap.release()

main()