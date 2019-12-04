#define PUMP_PIN 2
#define MOISTURE_SENSOR_PIN A0
#define MOISTURE_POWER_PIN 3
#define PUMP_RATE 0.01 //mL of fluid pumped per millisecond
#define DRY_LEVEL 520
#define WET_LEVEL 300
#define FIELD_CAPACITY 50 //field capacity of the soil
#define MSEC_IN_DAY (unsigned long)86400000

void water(int milliliters){
  unsigned long started_watering = millis();
  while(millis()-started_watering>(PUMP_RATE*milliliters)){
    digitalWrite(PUMP_PIN, HIGH);
    delay(100);
  }
}

int soil_moisture(){
  //Returns an int % of soil saturation (assumes linear response, which is a terrible idea)
  digitalWrite(MOISTURE_POWER_PIN, HIGH);
  delay(100);
  int level = analogRead(MOISTURE_SENSOR_PIN);
  digitalWrite(MOISTURE_POWER_PIN, LOW);
  level = 100 - 100*(level - WET_LEVEL)/(DRY_LEVEL-WET_LEVEL);
  if(level<0){level=0;}
  if(level>100){level=100;}
  return level;
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(MOISTURE_POWER_PIN,OUTPUT);
}

void loop(){
  int value = soil_moisture();
  Serial.println(value);
  
}

// the loop function runs over and over again forever
//void loop() {
// unsigned long begin_time =  millis();
// while(soil_moisture()<FIELD_CAPACITY){
//  //water
//  delay(300000);
// }
//  delay(MSEC_IN_DAY - begin_time);
//}
