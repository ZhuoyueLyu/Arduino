import serial, time
ArduinoSerial = serial.Serial('/dev/cu.usbserial-0001', 9600, timeout=0.1)
# string='H{0:d}M{1:d}'.format(25200, 25200)
string='H{0:d}M{1:d}'.format(2100, 2100)
ArduinoSerial.write(string.encode('utf-8'))