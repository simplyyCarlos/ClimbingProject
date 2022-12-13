import cv2 
import numpy as np 
import mmap



def main():
    try:
        img = cv2.imread("charucoboard.jpeg", cv2.IMREAD_GRAYSCALE) 
        cap = cv2.VideoCapture(0,cv2.CAP_DSHOW) 
        sift = cv2.SIFT_create() 
        kp_image, desc_image =sift.detectAndCompute(img, None) 
        index_params = dict(algorithm = 1, trees = 5) 
        search_params = dict(checks=50) 
        flann = cv2.FlannBasedMatcher(index_params, search_params)
        charucoboardDetected = False
        while (charucoboardDetected!=True) :
            try :
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
                charucoboardDetected = True 
            except :
                continue
        
        shmem = mmap.mmap(-1, 72 ,"shm", access=mmap.ACCESS_WRITE)
        res = np.zeros(shape=9)
        for i in range (3):
            for y in range (3):
                res[(i*3+y)]=np.double(matrix[i][y])
        i=0
        for value in res:
                shmem.seek(i)
                shmem.write((value).tobytes())
                i+=8
        shmem.close()
        cap.release()
    except:
        return
    
    