/*
  Water Sensor V2

  Makes a buzzer chirp periodically when contact is broken from a water level probe.

  The circuit:
  - Buzzer attached from pin 12 to ground
  - NPN (2N2222) transistor biased with 4.7k resistor from emitter to ground,
    and 1k resistor from collector to +5V, and emitter attached to pin 2.
  - Water sensor + probe attached to +5V
  - Water sensor - probe attached to transistor base

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13. This will be used as an indicator to test the sensor.

  created 2022
  by Schaner Designs <http://www.schanerdesigns.com>
  modified 6 December, 2022
  by Dan Schaner

  This example code is in the public domain.
  
*/

// constants won't change. They're used here to set pin numbers:
const int sensorPin = 2;     // the number of the pushbutton pin
const int buzzerPin =  12;      // the number of the LED pin
const int indicatorPin = 13;

// variables will change:
int sensorState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the buzzer and indicator pins as output:
  pinMode(buzzerPin, OUTPUT);
  pinMode(indicatorPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(sensorPin, INPUT);

}

void loop() {
  // read the state of the sensor value:
  sensorState = digitalRead(sensorPin);
  int inc = 1;

  // check if the sensor is making contact. If it is, the sensorState is HIGH:
  if (sensorState == LOW) {
    // turn buzzer on periodically:
    while(digitalRead(buttonPin) == LOW) {
      digitalWrite(indicatorPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(15);  // when on, the buzzer sounds for 15 ms
      digitalWrite(buzzerPin, LOW);

      // set delay for 15 seconds (150 x 100 = 15000 ms = 15 s)
      // by using the 100 ms delay and looping 150 times, we get a 15 s delay
      // that can be interrupted/reset if contact and remade and broken again (non-blocking code)
      while((digitalRead(sensorPin) == LOW) && (inc <= 150)) {
        delay(100);
        inc++;
      }
      inc = 1;  // reset the inc counter
    }
  } else {
    // turn buzzer and indicator LED off:
    digitalWrite(buzzerPin, LOW);
    digitalWrite(indicatorPin, LOW);
  }
}
