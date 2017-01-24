//Intermitente derecho
//intermitente Izdo
//Boton Derecho
//Boton Izdo
//Acelerometro
//Posición
//Freno

// constants won't change. Used here to set a pin number :
const int ledPinIzda =  2;      // the number of the LED pin intermitente Derecha
const int ledPinDcha =  3;      // the number of the LED pin intermitente Izda
const int ledPinPosi =  4;      // the number of the LED pin freno
const int ledPinFren =  5;      // the number of the LED pin
const int buttonPinIzda = 6;    // pulsador izda
const int buttonPinDcha = 7;    // pulsador Dcha

// Variables will change :
int ledStateIzda = LOW;             // ledState used to set the LED Iza apagado
int ledStateDcha = LOW;
int ledStatePosi = LOW;
int ledStateFren = LOW;
int boolButtonIzda = 0;
int boolButtonDcha = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPinIzda, OUTPUT);
}

void loop() {

  //Lee el boton
  if (digitalRead(buttonPinIzda)== HIGH) {
    int boolButtonIzda = 1;
  }  
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledStateIzda == LOW) {
      ledStateIzda = HIGH;
    } else {
      ledStateIzda = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPinIzda, ledStateIzda);
  }
}

