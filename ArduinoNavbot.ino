#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// gas variables

#define RL_VALUE 5.0
#define CALIBRATION_SAMPLE_TIMES 50
#define CALIBRATION_SAMPLE_INTERVAL 500
#define RO_CLEAN_AIR_FACTOR 9.83
#define READ_SAMPLE_TIMES 5
#define READ_SAMPLE_INTERVAL 50
#define GAS_LPG 0
#define GAS_CO 1
#define GAS_SMOKE 2


// Motor A
int enA = 11; // ENA → pin 11
int in1 = 12; // N1 → pin 12
int in2 = 10; // N2 → pin 10

// Motor B
int enB = 3;  // ENb → pin 3
int in3 = 9;  // N3 → pin 9
int in4 = 5;  // N4 → pin 5

#define DHTPIN A0  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

#define trigPin 7
#define echoPin 8
#define servoMainPin 6
#define BACKLIGHT_PIN  7
#define LED_ON  1

Servo servoMain;

// Define LCD parameters
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);
  servoMain.attach(servoMainPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
  delay(2000);
}

// Gas sensor curves
float LPGCurve[3] = {2.3, 0.21, -0.47};
float COCurve[3] = {2.3, 0.72, -0.34};
float SmokeCurve[3] = {2.3, 0.53, -0.44};

// Function to calculate MQ resistance
float MQResistanceCalculation(int raw_adc) {
  return ((float)RL_VALUE * (1023 - raw_adc) / raw_adc);
}

// Function for MQ sensor calibration
float MQCalibration(int mq_pin) {
  int i;
  float val = 0;

  for (i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) {
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val / CALIBRATION_SAMPLE_TIMES;

  val = val / RO_CLEAN_AIR_FACTOR;

  return val;
}

// Function to read MQ sensor value
float MQRead(int mq_pin) {
  int i;
  float rs = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs / READ_SAMPLE_TIMES;

  return rs;
}

// Function to get gas percentage based on MQ sensor type
int MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if (gas_id == GAS_LPG) {
    return MQGetPercentage(rs_ro_ratio, LPGCurve);
  } else if (gas_id == GAS_CO) {
    return MQGetPercentage(rs_ro_ratio, COCurve);
  } else if (gas_id == GAS_SMOKE) {
    return MQGetPercentage(rs_ro_ratio, SmokeCurve);
  }

  return 0;
}

// Function to calculate gas percentage
int MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10, (((log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));
}
// done gas 

unsigned long ping() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

//Function to move forward
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);

  delay(200);
  stop();
}

//Function to turn right
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);

  delay(200);
  stop();
}

//Function to turn left
void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);

  delay(200);
  stop();
}

//Function to move backwards
void back() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);
}

//Function to move stop
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(100);
}

void loop() {

  // Dsplay gas sensor data
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(GAS_LPG);
  // Move forward with a second delay to ensure a steady speed
  forward();
  delay(1000);

  // Read DHT sensor data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Display DHT data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Check if an obstacle is detected
  long distance = ping();
  if (distance < 15) { 
    // Stop the robot and move backwards
    stop();
    back();

    // Perform servo scan
    servoMain.write(90);
    delay(500);
    servoMain.write(0);
    delay(500);

    // Determine the direction with more space
    long leftDistance = ping();
    servoMain.write(180);
    delay(500);
    long rightDistance = ping();
    servoMain.write(90);
    delay(500);

    // Decide direction based on space after the turn
    if (leftDistance > rightDistance) {
      // Turn left
      left();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Turning Left");
    } else {
      // Turn right
      right();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Turning Right");
    }

    // Delay to stabilize the turn
    delay(500);
  }
}
