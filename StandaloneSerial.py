import serial
import time
import serial.tools.list_ports

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
time.sleep(3) #needed to give the arduino time to reboot after the serial port has been opened 
ports = [comport.device for comport in serial.tools.list_ports.comports()]
scramblestring = "U2 F' L B2 U2 B F L2"
scramblestring = "a6"
validCMDs = {"U": "U1", #standard moves
            "U'": "u1", 
            "U2": "U2", 
            "R": "R1", 
            "R'": "r1", 
            "R2": "R2", 
            "F": "F1", 
            "F'": "f1", 
            "F2": "F2", 
            "D": "D1", 
            "D'": "d1", 
            "D2": "D2", 
            "L": "L1", 
            "L'": "l1", 
            "L2": "L2", 
            "B": "B1", 
            "B'": "b1", 
            "B2": "B2",
            "Y0": "Y0", #axis open/close
            "y0": "y0", 
            "X0": "X0", 
            "x0": "x0", 
            "E1": "E1", #motor en/disable
            "E2": "E2",
            "A1": "A1", #single steps
            "a1": "a1", 
            "A2": "A2", 
            "a2": "a2", 
            "A3": "A3", 
            "a3": "a3",
            "A4": "A4", 
            "a4": "a4", 
            "A5": "A5", 
            "a5": "a5",
            "A6": "A6", 
            "a6": "a6",
            }
txCMDs = []
txList = scramblestring.split(" ")
for CMD in txList:
    CMD = validCMDs.get(CMD, lambda: None)
    txCMDs.append(CMD)


for num in txCMDs:
    
    # x = input("Enter a number: ") # Taking input from user
    arduino.write(bytes(num, 'utf-8'))
    # time.sleep(1)
    while arduino.in_waiting == 0:
        time.sleep(0.05)
    data = arduino.readline()
    if (data != b'K'):
        print('ACK was not received correctly')   
        #return -2
    print(data) # printing the value
    # time.sleep(1)