#include <Arduino.h>
#include <ArduinoJson.h>

#define MOTOR_L_IN1         8
#define MOTOR_L_IN2         9
#define MOTOR_L_PWM         10
#define MOTOR_R_IN1         6
#define MOTOR_R_IN2         7
#define MOTOR_R_PWM         11


void set_driver(int in1_pin, int in2_pin, int pwm_pin, int speed) {
    if (speed > 0) {
        digitalWrite(in1_pin, HIGH);
        digitalWrite(in2_pin, LOW);
    } else {
        digitalWrite(in1_pin, LOW);
        digitalWrite(in2_pin, HIGH);
        speed *=-1;
    }
    analogWrite(pwm_pin, speed);
}

void move(int lw, int rw) {
    set_driver(MOTOR_L_IN1, MOTOR_L_IN2, MOTOR_L_PWM, lw);
    set_driver(MOTOR_R_IN1, MOTOR_R_IN2, MOTOR_R_PWM, rw);
}


void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_L_PWM, OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_R_PWM, OUTPUT);
}


String input_string = "";
bool string_complete = false;

void loop(){
  if (string_complete){
    StaticJsonDocument<50> doc;
    DeserializationError error = deserializeJson(doc, input_string);
    if (!error){
      int16_t left_motor = doc["motors"]["left"];
      int16_t right_motor = doc["motors"]["right"];
      move(left_motor, right_motor);
    }
    input_string = "";
    string_complete = false;
  }
}

void serialEvent(){
  while (Serial.available()){
    char in_char = (char)Serial.read();
    input_string += in_char;
    if (in_char == '\n'){
      string_complete = true;
    }
  }
  //Serial.println("ok");
}
