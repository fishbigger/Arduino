int bounces = 0;
int pin = 13;
int oldOut;

void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  if (oldOut == 1 && !oldOut == digitalRead(pin)) {
    bounces++; 
    Serial.println(bounces);
    
  }
  oldOut = digitalRead(pin);
  delay(10);
  
}
