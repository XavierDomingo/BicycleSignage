#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>


#define PIN            8
#define NUMPIXELS      15
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
//Intermitente derecho
//intermitente Izdo
//Boton Derecho
//Boton Izdo
//Acelerometro
//Posición Neopixel
//Freno Neopixel


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
boolean boolButtonIzda = 0;
boolean boolButtonDcha = 0;
boolean semaforo = 0;
boolean boolFrena = 0;
byte indiceIzda = 15;
byte indiceDcha = 0;
byte indicePosicion = 0;


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisNeoPixel = 0;

// constants won't change :
const int interval = 500;           // interval at which to blink (milliseconds)
const int intervalNeoPixel = 50;
/////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // set the digital pin as output:
  pinMode(ledPinIzda, OUTPUT);
  pinMode(ledPinDcha, OUTPUT);
  pinMode(ledPinPosi, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  //displaySetRange(ADXL345_RANGE_4_G);
    
}

void loop() {
   sensors_event_t event; 
   accel.getEvent(&event);
   if (event.acceleration.x<2)
   {
     boolFrena = 1; 
   }  
   else
   {
     boolFrena = 0;
   }
  
  
  unsigned long currentMillis = millis();
  
  //Lee el boton Izquierdo
  if ((digitalRead(buttonPinIzda)== HIGH) and (semaforo == 0) and (boolButtonIzda == 0)) {
     boolButtonIzda = 1; // quiero encender led
     semaforo = 1; //bloqueo hasta que no suelte el bonton
  }
  if ((digitalRead(buttonPinIzda)== HIGH) and (boolButtonIzda == 1) and (semaforo == 0)) {
     boolButtonIzda = 0;  // pi apriento el boton pero esta encendido, apago y libero
     semaforo = 1; //bloqueo hasta que no suelte el bonton
  }  
  if ((digitalRead(buttonPinIzda)== LOW) and (semaforo == 1)) {
     semaforo = 0; //si suelta el boton desbloqueo 
  }
  
  //Lee el boton Dcho
  if ((digitalRead(buttonPinDcha)== HIGH) and (semaforo == 0) and (boolButtonDcha == 0)) {
     boolButtonDcha = 1; // quiero encender led
     semaforo = 1; //bloqueo hasta que no suelte el bonton
  }
  if ((digitalRead(buttonPinDcha)== HIGH) and (boolButtonDcha == 1) and (semaforo == 0)) {
     boolButtonDcha = 0;  // pi apriento el boton pero esta encendido, apago y libero
     semaforo = 1; //bloqueo hasta que no suelte el bonton
  }  
  if ((digitalRead(buttonPinDcha)== LOW) and (semaforo == 1)) {
     semaforo = 0; //si suelta el boton desbloqueo 
  }
 

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
//blick intermitente izda
    if (boolButtonIzda == 1) {
        // if the LED is off turn it on and vice-versa:
      if (ledStateIzda == LOW) {
        ledStateIzda = HIGH;
      } else {
        ledStateIzda = LOW;
      }
        // set the LED with the ledState of the variable:
      digitalWrite(ledPinIzda, ledStateIzda);
    } //end led izda
//blick intermitente dcha
    if (boolButtonDcha == 1) {
        // if the LED is off turn it on and vice-versa:
      if (ledStateDcha == LOW) {
        ledStateDcha = HIGH;
      } else {
        ledStateDcha = LOW;
      }
        // set the LED with the ledState of the variable:
      digitalWrite(ledPinDcha, ledStateDcha);
    }//end ld dcha
    
  } //if currentmilins
  
  if (currentMillis - previousMillisNeoPixel >= intervalNeoPixel) {
    previousMillisNeoPixel = currentMillis;
    //si frena
        if ( boolFrena == 1 ) {
                pixels.setBrightness(250);
        	for(int i=0;i<NUMPIXELS;i++){
                    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.
                    }
                    pixels.show(); // This sends the updated pixel color to the hardware.
        } else if ( boolButtonDcha == 1) {
        //  señala Dcha en orange 255,165,0,250
	        pixels.setBrightness(160);
                for(int i=0;i<NUMPIXELS;i++){
                    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
                    }
                    pixels.setPixelColor(indiceDcha, pixels.Color(255,165,0));
                    indiceDcha++;
                    if (indiceDcha == NUMPIXELS ){
                    indiceDcha = 0;
                    }
                    pixels.show(); // This sends the updated pixel color to the hardware.
        } else if ( boolButtonIzda == 1) {
        // señala Izda en orange
	        pixels.setBrightness(160);
                for(int i=0;i<NUMPIXELS;i++){
                    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
                    }
                    pixels.setPixelColor(indiceIzda, pixels.Color(255,165,0));
                    indiceDcha--;
                    if (indiceDcha == 0 ){
                    indiceDcha = NUMPIXELS;
                    }
                    pixels.show(); // This sends the updated pixel color to the hardware.
        } else {
          pixels.setBrightness(160);
          //posicion coche fantastico;     
        indicePosicion = random(0, NUMPIXELS);
        pixels.setPixelColor(indicePosicion, pixels.Color(255,0,0));
        pixels.setPixelColor(6, pixels.Color(255,0,0));
        pixels.setPixelColor(7, pixels.Color(255,0,0));
        pixels.setPixelColor(8, pixels.Color(255,0,0));
        pixels.show();
        }  
  }//Final IfNeopixel
}//final de todo


