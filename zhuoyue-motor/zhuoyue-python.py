import cv2
import numpy as np
import requests
import serial, time
from scipy import ndimage

# ESP32 URL
URL = "http://192.168.4.1"
AWB = True

# Face recognition and opencv setup
cap = cv2.VideoCapture(URL + ":81/stream")
is_detecting_side_face = True
if is_detecting_side_face:
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_profileface.xml')
else:
    # front face detection
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# ArduinoSerial = serial.Serial('/dev/cu.usbserial-0001', 9600, timeout=0.1)
ArduinoSerial = serial.Serial('/dev/cu.usbserial-0001', 115200, timeout=0.1)
curr_num_faces = 0


def count_num_faces(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6)  # detect the face
    for x, y, w, h in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)
    # cv2.imshow('img', frame)
    return len(faces)


def set_resolution(url: str, index: int = 1, verbose: bool = False):
    try:
        if verbose:
            resolutions = "10: UXGA(1600x1200)\n9: SXGA(1280x1024)\n8: XGA(1024x768)\n7: SVGA(800x600)\n6: VGA(640x480)\n5: CIF(400x296)\n4: QVGA(320x240)\n3: HQVGA(240x176)\n0: QQVGA(160x120)"
            print("available resolutions\n{}".format(resolutions))

        if index in [10, 9, 8, 7, 6, 5, 4, 3, 0]:
            requests.get(url + "/control?var=framesize&val={}".format(index))
        else:
            print("Wrong index")
    except:
        print("SET_RESOLUTION: something went wrong")


def set_quality(url: str, value: int = 1, verbose: bool = False):
    try:
        if value >= 10 and value <= 63:
            requests.get(url + "/control?var=quality&val={}".format(value))
    except:
        print("SET_QUALITY: something went wrong")


def set_awb(url: str, awb: int = 1):
    try:
        awb = not awb
        requests.get(url + "/control?var=awb&val={}".format(1 if awb else 0))
    except:
        print("SET_QUALITY: something went wrong")
    return awb


if __name__ == '__main__':
    set_resolution(URL, index=8)
    counter_for_faces = 0
    while True:
        if cap.isOpened():
            ret, frame = cap.read()
            frame = cv2.rotate(frame, cv2.ROTATE_180)  # rotate image by 180
            num_faces = count_num_faces(frame)
            if is_detecting_side_face:
                frame = cv2.flip(frame, 1)  # mirror the image
                num_faces += count_num_faces(frame)
            string = '{0:d}'.format(num_faces)
            if num_faces != curr_num_faces:
                counter_for_faces += 1
                if counter_for_faces >= 3:  # only update the number of faces when that's the case for three frames
                    ArduinoSerial.write(string.encode('utf-8'))
                    print(string)
                    curr_num_faces = num_faces
                    counter_for_faces = 0
            # string = 'M{0:d}H{1:d}'.format(2100, 2100)
            cv2.imshow("frame", frame)

            key = cv2.waitKey(1)

            if key == ord('r'):
                idx = int(input("Select resolution index: "))
                set_resolution(URL, index=idx, verbose=True)

            elif key == ord('q'):
                val = int(input("Set quality (10 - 63): "))
                set_quality(URL, value=val)

            elif key == ord('a'):
                AWB = set_awb(URL, AWB)

            elif key == 27:
                break

    cv2.destroyAllWindows()
    cap.release()
