import serial, time

ArduinoSerial = serial.Serial('/dev/cu.usbserial-0001', 115200, timeout=0.1)
# string='H{0:d}M{1:d}'.format(25200, 25200)
num_faces = 2
string = '{0:d}'.format(num_faces)
# string='M{0:d}H{1:d}'.format(2100, 2100)
ArduinoSerial.write(string.encode('utf-8'))
