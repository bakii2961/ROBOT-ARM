#include <AccelStepper.h>
#define MOTOR1_STEP_PIN 2
#define MOTOR1_DIR_PIN 3
#define BUTTON1_PIN A1


#define MOTOR2_STEP_PIN 4
#define MOTOR2_DIR_PIN 5
#define BUTTON2_PIN A2

#define MOTOR3_STEP_PIN 6
#define MOTOR3_DIR_PIN 7
#define BUTTON3_PIN A3


#define MOTOR4_STEP_PIN 8
#define MOTOR4_DIR_PIN 9
#define BUTTON4_PIN A4

#define MOTOR5_STEP_PIN 10
#define MOTOR5_DIR_PIN 11
#define BUTTON5_PIN A5


#define MOTOR6_STEP_PIN 12
#define MOTOR6_DIR_PIN 13
#define BUTTON6_PIN A6

//AccelStepper stepper(1, STEP_PIN, DIR_PIN);


AccelStepper stepper1(AccelStepper::DRIVER, MOTOR1_STEP_PIN, MOTOR1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, MOTOR2_STEP_PIN, MOTOR2_DIR_PIN);
AccelStepper stepper3(AccelStepper::DRIVER, MOTOR3_STEP_PIN, MOTOR3_DIR_PIN);
AccelStepper stepper4(AccelStepper::DRIVER, MOTOR4_STEP_PIN, MOTOR4_DIR_PIN);
AccelStepper stepper5(AccelStepper::DRIVER, MOTOR5_STEP_PIN, MOTOR5_DIR_PIN);
AccelStepper stepper6(AccelStepper::DRIVER, MOTOR6_STEP_PIN, MOTOR6_DIR_PIN);


int targetPosition = 0; // Başlangıç konumu
int currentPosition = 0; // Mevcut konumu saklamak için değişken


bool loopRunning1 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState1 = HIGH; // Buton durumu
bool lastButtonState1 = HIGH; // Önceki buton durumu
bool buttonPressed1 = false; // Buton basıldı mı?
unsigned long lastDebounceTime1 = 0; // Son debounce süresi
unsigned long debounceDelay1 = 50; // Titreme süresi


bool loopRunning2 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState2 = HIGH; // Buton durumu
bool lastButtonState2 = HIGH; // Önceki buton durumu
bool buttonPressed2 = false; // Buton basıldı mı?
unsigned long lastDebounceTime2 = 0; // Son debounce süresi
unsigned long debounceDelay2 = 50; // Titreme süresi



bool loopRunning3 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState3 = HIGH; // Buton durumu
bool lastButtonState3 = HIGH; // Önceki buton durumu
bool buttonPressed3 = false; // Buton basıldı mı?
unsigned long lastDebounceTime3 = 0; // Son debounce süresi
unsigned long debounceDelay3 = 50; // Titreme süresi


bool loopRunning4 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState4 = HIGH; // Buton durumu
bool lastButtonState4 = HIGH; // Önceki buton durumu
bool buttonPressed4 = false; // Buton basıldı mı?
unsigned long lastDebounceTime4 = 0; // Son debounce süresi
unsigned long debounceDelay4 = 50; // Titreme süresi




bool loopRunning5 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState5 = HIGH; // Buton durumu
bool lastButtonState5 = HIGH; // Önceki buton durumu
bool buttonPressed5 = false; // Buton basıldı mı?
unsigned long lastDebounceTime5 = 0; // Son debounce süresi
unsigned long debounceDelay5 = 50; // Titreme süresi



bool loopRunning6 = true; // Döngünün çalışma durumunu takip etmek için flag
bool buttonState6 = HIGH; // Buton durumu
bool lastButtonState6 = HIGH; // Önceki buton durumu
bool buttonPressed6 = false; // Buton basıldı mı?
unsigned long lastDebounceTime6 = 0; // Son debounce süresi
unsigned long debounceDelay6 = 50; // Titreme süresi



void setup() {
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(1000);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500);
  stepper3.setMaxSpeed(1000);
  stepper3.setAcceleration(500);
  stepper4.setMaxSpeed(1000);
  stepper4.setAcceleration(500);
  stepper5.setMaxSpeed(1000);
  stepper5.setAcceleration(500);
  stepper6.setMaxSpeed(1000);
  stepper6.setAcceleration(500);
  Serial.begin(9600);
  pinMode(BUTTON1_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
  pinMode(BUTTON2_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
  pinMode(BUTTON3_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
  pinMode(BUTTON4_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
  pinMode(BUTTON5_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
  pinMode(BUTTON6_PIN, INPUT_PULLUP); // Buton pinini giriş olarak ayarla ve dahili pull-up direncini etkinleştir
}

void loop() {
 
 motor1();
 motor2();
 motor3();
 motor4();
 motor5();
 motor6();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor1(){
  if (loopRunning1) {
    for (int i = 0; ; i++) {
      stepper1.moveTo(i);
      
      int reading1 = digitalRead(BUTTON1_PIN); // Buton durumunu oku

      if (reading1 != lastButtonState1) { // Buton durumu değişti mi?
        lastDebounceTime1 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime1) > debounceDelay1) {
        if (reading1 != buttonState1) {
          buttonState1 = reading1;
          if (buttonState1 == LOW) {
            buttonPressed1 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed1) {
              currentPosition = stepper1.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper1.stop();
              loopRunning1 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState1 = reading1; // Buton durumunu kaydet
      
      stepper1.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps1 = currentPosition - 200; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps1);
    stepper1.moveTo(backSteps1);
    stepper1.runToPosition();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor2(){
  if (loopRunning2) {
   
    for (int i = 0; ; i++) {
      stepper2.moveTo(i);
      
      
      int reading2 = digitalRead(BUTTON2_PIN); // Buton durumunu oku

      if (reading2 != lastButtonState2) { // Buton durumu değişti mi?
        lastDebounceTime2 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime2) > debounceDelay2) {
        if (reading2 != buttonState2) {
          buttonState2 = reading2;
          if (buttonState2 == LOW) {
            buttonPressed2 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed2) {
              currentPosition = stepper2.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper2.stop();
              loopRunning2 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState2 = reading2; // Buton durumunu kaydet
      
      stepper2.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps2 = currentPosition - 400; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps2);
    stepper2.moveTo(backSteps2);
    stepper2.runToPosition();
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor3(){

  if (loopRunning3) {
   
    for (int i = 0; ; i++) {
      stepper3.moveTo(i);
      
      
      int reading3 = digitalRead(BUTTON3_PIN); // Buton durumunu oku

      if (reading3 != lastButtonState3) { // Buton durumu değişti mi?
        lastDebounceTime3 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime3) > debounceDelay3) {
        if (reading3 != buttonState3) {
          buttonState3 = reading3;
          if (buttonState3 == LOW) {
            buttonPressed3 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed3) {
              currentPosition = stepper3.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper3.stop();
              loopRunning3 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState3 = reading3; // Buton durumunu kaydet
      
      stepper3.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps3 = currentPosition - 100; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps3);
    stepper3.moveTo(backSteps3);
    stepper3.runToPosition();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor4(){

  if (loopRunning4) {
   
    for (int i = 0; ; i++) {
      stepper4.moveTo(i);
      
      
      int reading4 = digitalRead(BUTTON4_PIN); // Buton durumunu oku

      if (reading4 != lastButtonState4) { // Buton durumu değişti mi?
        lastDebounceTime4 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime4) > debounceDelay4) {
        if (reading4 != buttonState4) {
          buttonState4 = reading4;
          if (buttonState4 == LOW) {
            buttonPressed4 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed4) {
              currentPosition = stepper4.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper4.stop();
              loopRunning4 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState4 = reading4; // Buton durumunu kaydet
      
      stepper4.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps4 = currentPosition - 100; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps4);
    stepper4.moveTo(backSteps4);
    stepper4.runToPosition();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor5(){

  if (loopRunning5) {
   
    for (int i = 0; ; i++) {
      stepper5.moveTo(i);
      
      
      int reading5 = digitalRead(BUTTON5_PIN); // Buton durumunu oku

      if (reading5 != lastButtonState5) { // Buton durumu değişti mi?
        lastDebounceTime5 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime5) > debounceDelay5) {
        if (reading5 != buttonState5) {
          buttonState5 = reading5;
          if (buttonState5 == LOW) {
            buttonPressed5 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed5) {
              currentPosition = stepper5.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper5.stop();
              loopRunning5 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState5 = reading5; // Buton durumunu kaydet
      
      stepper5.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps5 = currentPosition - 100; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps5);
    stepper5.moveTo(backSteps5);
    stepper5.runToPosition();
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void motor6(){
  if (loopRunning6) {
   
    for (int i = 0; ; i++) {
      stepper6.moveTo(i);
      
      
      int reading6 = digitalRead(BUTTON6_PIN); // Buton durumunu oku

      if (reading6 != lastButtonState6) { // Buton durumu değişti mi?
        lastDebounceTime6 = millis(); // Titreme süresini güncelle
      }

      if ((millis() - lastDebounceTime6) > debounceDelay3) {
        if (reading6 != buttonState6) {
          buttonState6 = reading6;
          if (buttonState6 == LOW) {
            buttonPressed6 = true; // Buton basıldı olarak işaretle
          } else {
            if (buttonPressed6) {
              currentPosition = stepper6.currentPosition();
              Serial.print("Mevcut Konum: ");
              Serial.println(currentPosition);
              stepper6.stop();
              loopRunning6 = false; // Döngünün bir daha çalışmaması için flag'i false yap
              break;
            }
          }
        }
      }
      lastButtonState6 = reading6; // Buton durumunu kaydet
      
      stepper6.run();
      //delay(10);
    }
    
    // For döngüsü bittiğinde motorun geri gitmesini sağla
    int backSteps6 = currentPosition - 100; // Mevcut konumdan 200 geri git
    Serial.print("Geri gitme adım sayısı: ");
    Serial.println(backSteps6);
    stepper6.moveTo(backSteps6);
    stepper6.runToPosition();
  }
}