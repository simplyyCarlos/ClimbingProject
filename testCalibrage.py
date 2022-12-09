import cv2 
import numpy as np 


img = cv2.imread("img.jpg", cv2.IMREAD_GRAYSCALE) 
cap = cv2.VideoCapture(0) 
sift = cv2.xfeatures2d.SIFT_create() 
kp_image, desc_image =sift.detectAndCompute(img, None) 
index_params = dict(algorithm = 0, trees = 5) 
search_params = dict() 
flann = cv2.FlannBasedMatcher(index_params, search_params) 
_, frame = cap.read() 
 
grayframe = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) 
 
kp_grayframe, desc_grayframe = sift.detectAndCompute(grayframe, None) 
 
matches= flann.knnMatch(desc_image, desc_grayframe, k=2) 
  
good_points=[] 
 
for m, n in matches: 
     
    if(m.distance < 0.6*n.distance): 
        good_points.append(m) 
query_pts = np.float32([kp_image[m.queryIdx] 
                .pt for m in good_points]).reshape(-1, 1, 2) 
 
train_pts = np.float32([kp_grayframe[m.trainIdx] 
                .pt for m in good_points]).reshape(-1, 1, 2) 
 
matrix, mask = cv2.findHomography(query_pts, train_pts, cv2.RANSAC, 5.0) 
 
matches_mask = mask.ravel().tolist() 
 
h,w,d = img.shape
 
pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
 
dst = cv.perspectiveTransform(pts, matrix)
 
homography = cv2.polylines(frame, [np.int32(dst)], True, (255, 0, 0), 3) 
 
cv2.imshow("Homography", homography) 
