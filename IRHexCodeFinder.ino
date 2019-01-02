#include <Adafruit_PWMServoDriver.h>

#include <IRremote.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)

const long int plus = 16754775;
const long int minus = 16769055;
const int changeBy = 100;

int val = SERVOMIN;

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

  void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= 60;   // 60 Hz
    //Serial.print(pulselength); Serial.println(" us per period"); 
    pulselength /= 4096;  // 12 bits of resolution
    //Serial.print(pulselength); Serial.println(" us per bit"); 
    pulse *= 1000000;  // convert to us
    pulse /= pulselength;
    //Serial.println(pulse);
    pwm.setPWM(n, 0, pulse);
}

void loop(){
  if (irrecv.decode(&results)){
    Serial.println(results.value);
    if (results.value == plus && val + changeBy <= SERVOMAX){
      val += changeBy;
    } 
    if (results.value == minus && val - changeBy >= SERVOMIN){
      val -= changeBy;
    }    
    irrecv.resume();
  }
  Serial.println(val);
  
  pwm.setPWM(0, 0, val); 
  
}
