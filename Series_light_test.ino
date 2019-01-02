#include <IRremote.h>
#include <stdlib.h>

const int SERIAL_BAUD = 9600;

const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

int pins12[] = {5, 12, 11, 10, 9, 8, 7, 4, 3, 2, A0, A1};
int pins8[] = {11, 10, 9, 8, 7, 4, 3, 2};
int leds, loops;
int x = 0;
int n;

const long int BUTTON_MIN = 16769055;
const long int BUTTON_PLUS = 16754775;

const int l12 = 12;
const int l8 = 8;

const int max_num_loops = 4;
const int min_num_loops = 2;

const int max_num_leds12 = max_num_loops * l12;
const int min_num_leds12 = min_num_loops * l12;
const int max_num_leds8 = max_num_loops * l8;
const int min_num_leds8 = min_num_loops * l8;

const int time_factor = 10;

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(true);

  Serial.begin(SERIAL_BAUD);
  
  for(int i = 0; i < l12; i++){
    pinMode(pins12[i], OUTPUT);
  }
  //Serial.println("hello world");
}

void loop() {
  if (irrecv.decode(&results)){
    
    Serial.println("hello world");
    
    if (results.value == BUTTON_MIN) {
    
      leds = rand() % (max_num_leds12 - min_num_leds12 + 1);
      leds += min_num_leds12 + 1;
      n = 1;
      for(int i = x; i < leds; i++){
        digitalWrite(pins12[i % l12], HIGH);
        digitalWrite(pins12[((i - 1) % l12)], LOW);
        delay(n * time_factor);
        n++;
        //Serial.println(i % l);
       }
       x = leds % l12;
    }
    if (results.value == BUTTON_PLUS) {
    
      leds = rand() % (max_num_leds8 - min_num_leds8 + 1);
      leds += min_num_leds8 + 1;
      n = 1;
      for(int i = x; i < leds; i++){
        digitalWrite(pins8[i % l8], HIGH);
        digitalWrite(pins8[((i - 1) % l8)], LOW);
        delay(n * time_factor);
        n++;
        //Serial.println(i % l);
       }
       x = leds % l8;
    }
    irrecv.resume(); 
  }
}
