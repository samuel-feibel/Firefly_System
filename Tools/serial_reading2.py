import serial
ser = serial.Serial('COM3', 115200, timeout=0)
ser.flushInput()

while True:
    try:
        data = []
        ser_bytes = ser.readline()
        # if ser_bytes == b'':
        #     break
        # while ser_bytes != b'\x00' and ser_bytes != b'':
        #     print('.')
        #     data.append(ser_bytes)
        #     ser_bytes = ser.readline()
        # decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        print(ser_bytes)
    except:
        print("Keyboard Interrupt")
        break