# Face tracker using OpenCV and Arduino
# by Shubham Santosh

import cv2
import serial, time

# side face detection (indeed...only works with side face, but it actually only works with one side)
# but we can flip the image to detect the other direction.
# image = cv2.flip(image, 1)
is_detecting_side_face = True
if is_detecting_side_face:
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_profileface.xml')
else:
    # front face detection
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# pathZ= '/Library/Frameworks/Python.framework/Versions/3.9/lib/python3.9/site-packages/cv2/data/haarcascade_frontalface_default.xml'
# Change cv2.VideoCapture(1) to cv2.VideoCapture(0). It is a MacOS bug for Coaca applications
# https://github.com/Classical-machine-learning/invisiblityCloak/issues/3
cap = cv2.VideoCapture(0)
# ArduinoSerial = serial.Serial('/dev/cu.usbserial-120', 9600, timeout=0.1)
curr_num_faces = 0


def count_num_faces(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6)  # detect the face
    for x, y, w, h in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)
    cv2.imshow('img', frame)
    return len(faces)


while cap.isOpened():
    ret, frame = cap.read()
    num_faces = count_num_faces(frame)
    if is_detecting_side_face:
        frame = cv2.flip(frame, 1)  # mirror the image
        num_faces += count_num_faces(frame)
    string = '{0:d}'.format(num_faces)
    print(string)
    if num_faces != curr_num_faces:
        # ArduinoSerial.write(string.encode('utf-8'))
        curr_num_faces = num_faces

    # press q to Quit
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
