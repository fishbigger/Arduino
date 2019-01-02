#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int val = 0;
float NewVal = 0;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  

  delay(10);
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  //val = analogRead(0);     // read the input pin
  //NewVal = map(val, 0, 1021, SERVOMIN, SERVOMAX);
  //Serial.println(NewVal);
  
  // Drive each servo one at a time
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
   pwm.setPWM(0, 0, pulselen);
  }

  delay(100);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
   pwm.setPWM(0, 0, pulselen);
  }
  

  delay(100);
  //pwm.setPWM(0, 0, SERVOMAX);
}
