# Face tracker using OpenCV and Arduino
# by Shubham Santosh

import cv2
import serial, time

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
# Change cv2.VideoCapture(1) to cv2.VideoCapture(0). It is a MacOS bug for Coaca applications
# https://github.com/Classical-machine-learning/invisiblityCloak/issues/3
cap = cv2.VideoCapture(0)
ArduinoSerial = serial.Serial('/dev/cu.usbserial-120', 9600, timeout=0.1)
curr_num_faces = 0

while cap.isOpened():
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)  # mirror the image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6)  # detect the face
    num_faces = len(faces)
    string = '{0:d}'.format(num_faces)
    print(string)
    if num_faces != curr_num_faces:
        ArduinoSerial.write(string.encode('utf-8'))
        curr_num_faces = num_faces
    for x, y, w, h in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)
    cv2.imshow('img', frame)
    # press q to Quit
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
