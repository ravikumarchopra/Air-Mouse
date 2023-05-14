#include <SoftwareSerial.h>

// tx and rx pins for bluetooth module (HC-05)
const int txpin = 5, rxpin = 6;
SoftwareSerial bluetooth(txpin, rxpin);
// Analog output pins for accelerometer 
const int x = A0;
const int y = A1;
// variables to store the accelerometer readings (x, y)
int x_raw, y_raw;
int xcord, ycord;
// pins connected to push buttons for left and right click
const int lclick = 2;
const int rclick = 3;
// variables to store left and right click state (i.e. for clicked it will be 1)
int lstate = 0;
int rstate = 0;
// led to indicate the click status
const int led = 13;
int debounceTime = 50; // debounce variable
volatile bool triggerClick = false; // flag for click trigger
long unsigned int lastPress; // last click time for handling the debouncing
int last_x_raw = 0; // last value of x value from accelerometer for filtering the noise
int last_y_raw = 0; // last value of y value from accelerometer for filtering the noise
float alpha = 0.5; // constant for used for filtering the noise
int T = 5; // threshold for x and y value from accelerometer
int S = 1; // sensitivity of the mouse pointer

void setup()
{
    // initializing pins
    pinMode(x, INPUT);
    pinMode(y, INPUT);
    pinMode(lclick, INPUT);
    pinMode(rclick, INPUT);
    pinMode(led, OUTPUT);
    // setting left/right click pins high
    digitalWrite(lclick, HIGH);
    digitalWrite(rclick, HIGH);
    // set up interrupts for left and right click
    attachInterrupt(digitalPinToInterrupt(lclick), ISR_Click, FALLING);
    attachInterrupt(digitalPinToInterrupt(rclick), ISR_Click, FALLING);
    // initializing communication port with a baud rate
    Serial.begin(9600);
    bluetooth.begin(9600);
}

void loop()
{
    // handling the left/right click
    if ((millis() - lastPress) > debounceTime && triggerClick)
    {
        // updating the last left/right click time
        lastPress = millis();
        // turn on led
        digitalWrite(led, HIGH);
        // reading the status of left/right click buttons
        lstate = digitalRead(lclick);
        rstate = digitalRead(rclick);
        // transmitting the x, y and left/right click status via bluetooth
        bluetooth.print(xcord);
        bluetooth.print(",");
        bluetooth.print(ycord);
        bluetooth.print(",");
        bluetooth.print(!lstate);
        bluetooth.print(",");
        bluetooth.print(!rstate);
        bluetooth.println();
        // turn off led after transmitting the data
        digitalWrite(led, LOW);
        // reseting the trigger flag
        triggerClick = false;
    }
    // handling the output from accelerometer
    else{
        x_raw = analogRead(x) * S;
        y_raw = analogRead(y) * S;

        // Apply low-pass filter to accelerometer readings
        x_raw = alpha * x_raw + (1 - alpha) * last_x_raw;
        y_raw = alpha * y_raw + (1 - alpha) * last_y_raw;        
        // processing the accelerometer output if it is greater than the threshold value T
        if (abs(last_x_raw - x_raw) > T || abs(last_y_raw - y_raw) > T)
        {
            last_x_raw = x_raw;
            last_y_raw = y_raw;
            // mapping the x, y values to the values we want
            xcord = map(x_raw, 286, 429, 0, 1920);
            ycord = map(y_raw, 282, 427, 0, 1080);
            // transmitting the x, y and left/right click status via bluetooth
            bluetooth.print(xcord);
            bluetooth.print(",");
            bluetooth.print(ycord);
            bluetooth.print(",");
            bluetooth.print(0);
            bluetooth.print(",");
            bluetooth.print(0);
            bluetooth.println();
        }      
    }
}

// interrupt service routine for left/right click
void ISR_Click()
{
    delay(50);
    triggerClick = true;
}