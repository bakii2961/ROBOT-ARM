#include <AccelStepper.h>

// Motor pin bağlantıları
#define MOTOR1_STEP_PIN 2
#define MOTOR1_DIR_PIN 3
#define MOTOR2_STEP_PIN 4
#define MOTOR2_DIR_PIN 5
#define MOTOR3_STEP_PIN 6
#define MOTOR3_DIR_PIN 7
#define MOTOR4_STEP_PIN 8
#define MOTOR4_DIR_PIN 9
#define MOTOR5_STEP_PIN 10
#define MOTOR5_DIR_PIN 11
#define MOTOR6_STEP_PIN 12
#define MOTOR6_DIR_PIN 13
#define button 52
#define ena_pin 53

// Motor sürücü ayarları
#define STEPS_PER_REV 200
#define SPEED 1000
#define ACCELERATION 500

int ali = 1 ;
int ahmet = 0;
int i ;
int A;
// AccelStepper nesneleri oluşturun
AccelStepper stepper1(AccelStepper::DRIVER, MOTOR1_STEP_PIN, MOTOR1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR2_STEP_PIN, MOTOR2_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, MOTOR3_STEP_PIN, MOTOR3_DIR_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, MOTOR4_STEP_PIN, MOTOR4_DIR_PIN);
AccelStepper stepper5(AccelStepper::DRIVER, MOTOR5_STEP_PIN, MOTOR5_DIR_PIN);
AccelStepper stepper6(AccelStepper::DRIVER, MOTOR6_STEP_PIN, MOTOR6_DIR_PIN);

void setup() {

  Serial.begin(9600);  // USB üzerinden seri haberleşmeyi başlat

  // Motor ayarları
  stepper1.setMaxSpeed(SPEED);
  stepper1.setAcceleration(ACCELERATION);

  stepper2.setMaxSpeed(SPEED);
  stepper2.setAcceleration(ACCELERATION);

  stepper3.setMaxSpeed(SPEED);
  stepper3.setAcceleration(ACCELERATION);

  stepper4.setMaxSpeed(SPEED);
  stepper4.setAcceleration(ACCELERATION);

  stepper5.setMaxSpeed(SPEED);
  stepper5.setAcceleration(ACCELERATION);

  stepper6.setMaxSpeed(SPEED);
  stepper6.setAcceleration(ACCELERATION);
  pinMode(button,INPUT);
  pinMode(ena_pin,OUTPUT);

  Serial.println("Serial Monitor Temizlendi.");
}

void loop() {

  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    
    processReceivedData(data);
   
  }

 
  // Her motorun hareketini bağımsız olarak kontrol et
  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
  stepper5.run();
  stepper6.run();
}

void processReceivedData(String data) {
  int values[6];
  int index = 0;

  Serial.print("Gelen Veri: ");
  Serial.println(data);

  while (data.length() > 0) {
    int commaPos = data.indexOf(',');
    if (commaPos != -1) {
      values[index] = data.substring(0, commaPos).toInt();
      data = data.substring(commaPos + 1);
    } else {
      values[index] = data.toInt();
      data = "";
    }

    index++;
  }

  // Her motorun hedef konumunu ayarlayın
  stepper1.moveTo(values[0]*100);
  stepper2.moveTo(values[1]*100);
  stepper3.moveTo(values[2]);
  stepper4.moveTo(values[3]);
  stepper5.moveTo(values[4]);
  stepper6.moveTo(values[5]);
}
