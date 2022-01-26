#include <Arduino.h>
#include <Vector.h>

const int buttonPin = 6;                 // the number of the pushbutton pin
const int ledPin = 3;                    // the number of the LED pin
const int ledPin2 = 8;                   // the number of the LED pin
const int lightSensor = A3;              // the number of the light sensor pin
const int lightModeTransitionValue = 50; //transition threshold
const int ELEMENT_COUNT_MAX = 5;         //vector init value
const int numberOfModes = 7;             //number of modes
int ledState = HIGH;                     // the current state of the output pin
int ledState2 = HIGH;                    // the current state of the output pin
int buttonState;                         // the current reading from the input pin
int lastButtonState = LOW;               // the previous reading from the input pin
int counter = 0;                         //button press counter
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long currentMillis = 0;
unsigned long currentMillis2 = 0;
//mean of values read by phototransistor, default big number so as not to turn the LED on accidentally
int mean = 1000;
int lightLevel; //light level
int storage_array[ELEMENT_COUNT_MAX];
Vector<int> lightValues(storage_array); //vector of light values

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

//prototypes
void blinkTwoLEDsSimultaneously(unsigned long);
void blinkTwoLEDsSeparately(unsigned long);
void controlLedWithPhototransistor(bool willBlink);

void setup()
{
  //set button pin as input
  pinMode(buttonPin, INPUT);
  //set LED pins as output
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // set initial LEDs state
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
  //init serial
  Serial.begin(9600);
}

void loop()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  // read value of light sensor
  lightLevel = analogRead(lightSensor);
  // store light value to a vector
  lightValues.push_back(lightLevel);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      //if button was pressed
      if (buttonState == HIGH)
      {
        //if button was pressed 7 times, reset counter
        //7 is the amount of available modes
        counter >= numberOfModes ? counter = 1 : counter++;
      }
    }
  }

  currentMillis = millis();
  currentMillis2 = millis();

  //choose appropriate mode
  switch (counter)
  {
  case 1:
    //turn on both LEDs, don't blink them
    digitalWrite(ledPin, HIGH);
    controlLedWithPhototransistor(false);
    break;
  case 2:
    //blink two LEDs slowly
    blinkTwoLEDsSimultaneously(1000);
    break;
  case 3:
    //blink two LEDs moderate quickly
    blinkTwoLEDsSimultaneously(500);
    break;
  case 4:
    //blink two LEDs quickly
    blinkTwoLEDsSimultaneously(200);
    break;
  case 5:
    //blink two LEDs asynchronously
    blinkTwoLEDsSeparately(1000);
    break;
  case 6:
  default:
    //turn off the LEDs
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    break;
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

/**
 * @brief Blink two LEDs in a synchronized manner.
 * 
 * @param interval expectancy time between blinking
 */
void blinkTwoLEDsSimultaneously(unsigned long interval)
{
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    ledState == LOW ? ledState = HIGH : ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    controlLedWithPhototransistor(true);
  }
}

/**
 * @brief Blink two LEDs in a asynchronous manner
 * 
 * @param interval expectancy time between blinking
 */
void blinkTwoLEDsSeparately(unsigned long interval)
{
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
    {
      ledState = HIGH;
      ledState2 = LOW;
    }
    else
    {
      ledState = LOW;
      ledState2 = HIGH;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    digitalWrite(ledPin2, ledState2);
  }
}
/**
 * @brief Control LED2 according to light values
 * 
 * @param willBlink if LED2 blinks in current mode or not
 */
void controlLedWithPhototransistor(bool willBlink)
{
  unsigned int waitTime = 5000; //time to wait between switching, time to collect light data

  if (currentMillis2 - previousMillis2 >= waitTime)
  {
    previousMillis2 = currentMillis2;
    //calculate mean value of light data collected within waitTime
    mean = 0;
    int n = 0;
    int sum = 0;
    for (auto x : lightValues)
    {
      sum += x;
      n++;
      Serial.println(x);
    }
    mean = sum / n;
    Serial.println(mean);
    //empty contents of lightValues vector
    lightValues.clear();
  }

  if (willBlink)
  {
    mean < lightModeTransitionValue ? digitalWrite(ledPin2, ledState) : digitalWrite(ledPin2, LOW);
  }
  else
  {
    mean < lightModeTransitionValue ? digitalWrite(ledPin2, HIGH) : digitalWrite(ledPin2, LOW);
  }
}
