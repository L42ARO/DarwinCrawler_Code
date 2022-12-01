import cv2
import urllib.request
import numpy as np
 
def nothing(x):
    pass
 
url='http://172.20.10.2/cam-lo.jpg'
url2 = 'http://172.20.10.4'
##'''cam.bmp / cam-lo.jpg /cam-hi.jpg / cam.mjpeg '''
cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)
 
l_h, l_s, l_v = 0, 59, 118
u_h, u_s, u_v = 49, 255, 255
 
while True:
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    frame=cv2.imdecode(imgnp,-1)
    #_, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
 
    l_b = np.array([l_h, l_s, l_v])
    u_b = np.array([u_h, u_s, u_v])
    
    mask = cv2.inRange(hsv, l_b, u_b)
 
    cnts, _ = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    try:
        ch_c = cnts[0]
        max_area = cv2.contourArea(ch_c)
        for c in cnts:
            area=cv2.contourArea(c)
            if area>max_area:
                ch_c=c
                max_area=area
        cv2.drawContours(frame,[ch_c],-1,(255,0,0),3)
        M=cv2.moments(ch_c)
        cx=int(M["m10"]/M["m00"])
        cy=int(M["m01"]/M["m00"])
        gridSquare = np.array([-1,-1])
        gridSquareHeight = frame.shape[0] / 3
        gridSquareWidth = frame.shape[1] / 3
        for i in range(3):
            for j in range(3):
                if (cy > gridSquareHeight * i and cy < gridSquareHeight * (i + 1)) and (cx > gridSquareWidth * j and cx < gridSquareWidth * (j + 1)):
                    gridSquare = np.array([i,j])
        if(gridSquare[0] != -1 and gridSquare[1] != -1):
            cv2.putText(frame,"("+str(gridSquare[0])+","+str(gridSquare[1])+")",(cx,cy),cv2.FONT_HERSHEY_SIMPLEX,1,(0,0,255),2)
            if ((gridSquare[0] == 0 or gridSquare[0]==1) and gridSquare[1] == 0):
                res = urllib.request.urlopen(url2 + '/fishForwardLeft')
            elif (gridSquare[0] == 0 and gridSquare[1] == 1):
                res = urllib.request.urlopen(url2 + '/fishForward')
            elif ((gridSquare[0] == 0 or gridSquare[0]==1) and gridSquare[1] == 2):
                res= urllib.request.urlopen(url2 + '/fishForwardRight')
            elif (gridSquare[0] == 2 and gridSquare[1] == 0):
                res=urllib.request.urlopen(url2 + '/fishBackLeft')
            elif (gridSquare[0] == 2 and gridSquare[1] == 1):
                res=urllib.request.urlopen(url2 + '/fishBackward')
            elif (gridSquare[0] == 2 and gridSquare[1] == 2):
                res=urllib.request.urlopen(url2 + '/fishBackwardRight')
            elif (gridSquare[0] == 1 and gridSquare[1] == 1):
                res=urllib.request.urlopen(url2 + '/fishStop')
        cv2.circle(frame,(cx,cy),7,(255,255,255),-1)
        cv2.putText(frame,"fish",(cx-20, cy-20),cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255),2)
    except Exception as e:
        print(e)

        
    res = cv2.bitwise_and(frame, frame, mask=mask)
 
    cv2.imshow("live transmission", frame)
    cv2.imshow("mask", mask)
    cv2.imshow("res", res)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break
    
 
cv2.destroyAllWindows()