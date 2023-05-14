import serial # library for serial communication
import pyautogui # library for interacting with GUI

# connecting to the bluetooth interface by passing port name and baud rate 
print('[Connecting via bluetooth ...]')
bluetooth = serial.Serial("com9", 9600, timeout=1)
print("[Connected.]")
# continuously reading the data from communication port
while True:
    try:
        # reading a line from bluetooth 
        line = bluetooth.readline()
        if line != b'':
            # decoding and processing the data received from bluetooth
            line = line.decode("utf-8").strip().split(',')
            x, y, l, r = map(lambda x: int(x), line)
            # handling the left click
            if l == 1:
                pyautogui.click()
                print(f"Left Click: {x}, {y}, ({l}, {r})")
            # handling the right click
            elif r == 1:
                pyautogui.click(button="right")
                print(f"Right Click: {x}, {y}, ({l}, {r})")
            # handling the cursor movement
            elif l == 0 and r == 0:
                pyautogui.moveTo(x, y)
                print(f"Cursor Movement: {x}, {y}, ({l}, {r})")
    except Exception as e:
        print('Error: ' + str(e))
