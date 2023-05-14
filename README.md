
# Wireless Air Mouse

The wireless air mouse operates on a straightforward concept, which involves utilizing an accelerometer to capture the acceleration values of hand gestures along the x and y-axis using Arduino. The accelerometer data is then transmitted to the computer using a Bluetooth Module which will be utilized by Python software drivers running on the computer to control the mouse cursor and execute specific actions.


## Pre-requisites

    1. Arduino Nano (any model)
    2. Accelerometer ADXL335 Module
    3. Bluetooth HC-05 Module
    4. Push buttons
    5. Python Installed computer

## Circuit Diagram

![Circuit Diagram](https://github.com/ravikumarchopra/Air-Mouse/assets/9302741/8fef4509-6d34-4db1-9ccd-297816760b62)

## How to Use/Run the code
`Step 1: Gather all the components required for the project as mentioned above.`

`Step 2:  Make all the connection according to the circuit diagram.`

`Step 3: Connect Arduino to a computer and upload the code inside 'mouse.c' to Arduino using Arduino IDE.`

`Step 4: Install python on your computer.`

`Step 5: Install the required libraries using the following commands:`

`pip install pyserial`

`pip install pyautogui`

`Step 6: Connect Arduino to a power source.`

`Step 7: Connect your computer to the bluetooth mouse (HC-05) by using the default pascode '1234'.`

`Step 8: After pairing to 'HC-05', check the port (e.g. com9) it's connected to and the the port in 'mouse.py' file at line number 14.`

`Step 9: execute the python file using the following command:`

`python mouse.py`

`Step 10: Enjoy playing with your Air Mouse by moving it into the air.`
