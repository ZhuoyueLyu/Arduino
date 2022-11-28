# Face tracker using OpenCV and Arduino
# by Shubham Santosh

import cv2
import serial, time

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
# Change cv2.VideoCapture(1) to cv2.VideoCapture(0). It is a MacOS bug for Coaca applications
# https://github.com/Classical-machine-learning/invisiblityCloak/issues/3
cap = cv2.VideoCapture(0)
# fourcc= cv2.VideoWriter_fourcc(*'XVID')
ArduinoSerial = serial.Serial('/dev/cu.usbserial-120', 9600, timeout=0.1)
# out= cv2.VideoWriter('face detection4.avi',fourcc,20.0,(640,480))
time.sleep(1)

while cap.isOpened():
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)  # mirror the image
    # print(frame.shape)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6)  # detect the face
    for x, y, w, h in faces:
        # number of faces
        print("num faces: " + str(len(faces)))
        # sending coordinates to Arduino
        # string = 'X{0:d}Y{1:d}'.format((x + w // 2), (y + h // 2))
        # print(string)
        string = 'N{0:d}'.format(len(faces))
        print(string)

        ArduinoSerial.write(string.encode('utf-8'))
        # plot the center of the face
        cv2.circle(frame, (x + w // 2, y + h // 2), 2, (0, 255, 0), 2)
        # plot the roi
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)
    # plot the squared region in the center of the screen
    cv2.rectangle(frame, (640 // 2 - 30, 480 // 2 - 30),
                  (640 // 2 + 30, 480 // 2 + 30),
                  (255, 255, 255), 3)
    cv2.imshow('img', frame)
    # press q to Quit
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
