#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

bool alarm = true;

const int buzzer = 11;
const int led = 12;

//const long int one = 16724175;
const long int two = 16718055;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);

}

void loop() {
  if (alarm){
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(250);
  }

  if (irrecv.decode(&results)){
    if (results.value == two){
      alarm = !alarm;
      Serial.println("Toggle");
    }
    irrecv.resume();
  } 
  Serial.println(alarm);
}
