# from https://stackoverflow.com/questions/36219687/python-serial-to-arduino-speed-test

import time
import serial
import sys

ser = serial.Serial(
    port=sys.argv[1],
    baudrate=115200,
    timeout=1
)

i = 0;

#wait until bootloader finished
time.sleep(2)

try:
    t0 = time.time()
    while i < 1000:
        ser.write(b'U')
        ser.flush()
        while ser.in_waiting <= 0:
            pass
        ret = ser.read(1)
        if ret != b'U':
            print("Error received: %s" % ret)
        i += 1
    t1 = time.time()
except KeyboardInterrupt:
    ser.close()
    exit(1)

ser.close()
print("%.3f" % ((t1-t0) / 1000))
