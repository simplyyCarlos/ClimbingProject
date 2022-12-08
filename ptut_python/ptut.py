import cv2
import mediapipe as mp
from mediapipe.framework.formats import landmark_pb2

mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_pose = mp.solutions.pose

def __main__() :
    cap = cv2.VideoCapture(0)
    with mp_pose.Pose(
        min_detection_confidence=0.7,
        min_tracking_confidence=0.7) as pose:
        
        while cap.isOpened():
            success, image = cap.read()
            if not success:
                print("Ignoring empty camera frame.")
            # If loading a video, use 'break' instead of 'continue'.
                break
            
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
                    x=data_point.x * 640
                    y=data_point.y * 480
                    cpt+=1
                    if(cpt %2 == 0):
                        cv2.circle(image,(int(x),int(y)),10,(255,0,0),-1)
                    else:
                        cv2.circle(image,(int(x),int(y)),10,(0,0,255),-1)
            # Flip the image horizontally for a selfie-view display.
            cv2.imshow('MediaPipe Pose', cv2.flip(image, 1))
            if cv2.waitKey(5) & 0xFF == 27:
                break
        cap.release()
        

if __name__ == '__main__':
       __main__()