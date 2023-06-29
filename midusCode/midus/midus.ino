#include <Wire.h>
#include <LSM6.h>
#include <Encoder.h>

#define neoPixelBus 6

#define I2CData 8
#define I2CScl 9

#define motorSleep 7

#define motor1Phase 0
#define motor1EN 1
#define motor1EncA 4
#define motor1EncB 5
#define PWMChannelMotor1 0

#define motor2Phase 2
#define motor2EN 3
#define motor2EncA 18
#define motor2EncB 19
#define PWMChannelMotor2 1

#define MotorPWMFreq 100

LSM6 imu;

Encoder motor1Enc(motor1EncA, motor1EncB);
Encoder motor2Enc(motor2EncA, motor2EncB);

long positionLeft  = -999;
long positionRight = -999;


void setup() {
  Serial.begin(115200);
  //Wire.begin(I2CData, I2CScl);  

  // if (!imu.init())
  // {
  //   Serial.println("Failed to detect and initialize IMU!");
  //   while (1);
  // }
  // imu.enableDefault();
  neopixelWrite(neoPixelBus, 0, 128, 0); //Janky code, need to use a real library, but the shift reg nature of the neoPixels means this is a later problem!


  // *** Motor Defs ***
  pinMode(motorSleep, OUTPUT);

  pinMode(motor1Phase, OUTPUT);
  ledcSetup(PWMChannelMotor1, MotorPWMFreq, 4); // channel(0-7), freq, resolution (8bit)
  ledcAttachPin(motor1EN, PWMChannelMotor1);
  
  pinMode(motor2Phase, OUTPUT);
  ledcSetup(PWMChannelMotor2, MotorPWMFreq, 4); // channel(0-7), freq, resolution (8bit)
  //ledcAttachPin(motor2EN, PWMChannelMotor2);
  pinMode(motor1EN, OUTPUT);
  // *** end of Motor Defs ***

  // *** Bringup tests ***
  neopixelWrite(neoPixelBus, 128, 0, 0); //Janky code, need to use a real library, but the shift reg nature of the neoPixels means this is a later problem!
  neopixelWrite(neoPixelBus, 128, 0, 0);


  digitalWrite(motorSleep, 1); //wake up motor controllers
  digitalWrite(motor1Phase, 0); //setting motor direction
  digitalWrite(motor2Phase, 0);

  digitalWrite(motor1EN, 1); // run first motor (128 = 255/2, 255 is 8bit max, so running at half speed)
  delay(1500);
  // ledcWrite(motor1EN, 0); // disable first motor
  // delay(10);
  // ledcWrite(motor2EN, 128);  //run second motor
  // delay(1500);
  // ledcWrite(motor2EN, 0);  //disable second motor

  //digitalWrite(motorSleep, 1); //wake up motor controllers


  neopixelWrite(neoPixelBus, 0, 128, 0);

  // *** end Bringup tests ***








}

void loop() {
  digitalWrite(1, 1); // run first motor (128 = 255/2, 255 is 8bit max, so running at half speed)
  delay(100);
  digitalWrite(1, 0); // run first motor (128 = 255/2, 255 is 8bit max, so running at half speed)
  delay(100);

  // put your main code here, to run repeatedly:
  // //neopixelWrite(neoPixelBus, 0, 128, 0);
  //   neopixelWrite(neoPixelBus, 128, 0, 0);

  // long newLeft, newRight;
  // newLeft = motor1Enc.read();
  // newRight = motor2Enc.read();
  // if (newLeft != positionLeft || newRight != positionRight) {
  //   Serial.print("Enc1 = ");
  //   Serial.print(newLeft);
  //   Serial.print(", Enc2 = ");
  //   Serial.print(newRight);
  //   Serial.println();
  //   positionLeft = newLeft;
  //   positionRight = newRight;
  // }
  // // if a character is sent from the serial monitor,
  // // reset both back to zero.
  // if (Serial.available()) {
  //   Serial.read();
  //   Serial.println("Reset both knobs to zero");
  //   motor1Enc.write(0);
  //   motor2Enc.write(0);
  // }
}
