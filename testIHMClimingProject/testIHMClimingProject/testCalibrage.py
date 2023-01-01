import cv2 
import numpy as np 
import mmap




def main():
    try:
        img = cv2.imread("./img/charucoboard.jpeg", cv2.IMREAD_GRAYSCALE) 
        cap = cv2.VideoCapture(0,cv2.CAP_DSHOW) 
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1024)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 576)
        sift = cv2.SIFT_create() 
        kp_image, desc_image =sift.detectAndCompute(img, None) 
        index_params = dict(algorithm = 1, trees = 5) 
        search_params = dict(checks=50) 
        flann = cv2.FlannBasedMatcher(index_params, search_params)
        charucoboardDetected = False
        while (charucoboardDetected == False) :
            try :
                _, frame = cap.read() 
                grayframe = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) 
                kp_grayframe, desc_grayframe = sift.detectAndCompute(grayframe, None) 
                matches= flann.knnMatch(desc_image, desc_grayframe, k=2) 
                good_points=[] 
                for m, n in matches: 
                
                    if(m.distance < 0.7*n.distance): 
                        good_points.append(m) 
                query_pts = np.float32([kp_image[m.queryIdx] 
                                .pt for m in good_points]).reshape(-1, 1, 2) 
            
                train_pts = np.float32([kp_grayframe[m.trainIdx] 
                                .pt for m in good_points]).reshape(-1, 1, 2) 
            
                matrix, mask = cv2.findHomography(query_pts, train_pts, cv2.RANSAC, 5.0)
                matrixRet = np.linalg.inv(matrix)
                charucoboardDetected = True 
                print (matrixRet)
                """
                h, w = img.shape
                pts = np.float32([[0, 0], [0, h - 1], [w - 1, h - 1], [w - 1, 0]]).reshape(-1, 1, 2)
                dst = cv2.perspectiveTransform(pts, matrix)
                homography = cv2.polylines(frame, [np.int32(dst)], True, (255, 0, 0), 3) 
                image = cv2.circle(homography,(400,200), 3, (0,0,255), -1)
                print(image.shape)
                pts2 = np.array([[[400,200]]], dtype = "float32")

                dst2 = cv2.perspectiveTransform(pts2, matrixRet)
                print (dst2[0, 0, 0])
                resized = cv2.resize(cv2.imread("./img/charucoboard.jpeg"), (np.int(1920/2),np.int(1080/2)), interpolation = cv2.INTER_AREA)
                image2 = cv2.circle(resized,(np.int(dst2[0, 0, 0]/2),np.int(dst2[0, 0, 1]/2)), 3, (0,0,255), -1)

                cv2.imshow("img",image)
                cv2.imshow("img2",image2)
                cv2.waitKey(0)
                """
            except :
                continue
        
        shmem = mmap.mmap(-1, 72 ,"shm", access=mmap.ACCESS_WRITE)
        res = np.zeros(shape=9)
        for i in range (3):
            for y in range (3):
                res[(i*3+y)]=np.double(matrixRet[i][y])
        i=0
        for value in res:
                shmem.seek(i)
                shmem.write((value).tobytes())
                i+=8
        shmem.close()
        cap.release()
    except:
        return
