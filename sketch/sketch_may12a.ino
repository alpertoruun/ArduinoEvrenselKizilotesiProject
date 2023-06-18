#include <IRremote.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); 


#define IR_RECEIVE_PIN 2
#define IR_BUTTON_1 69
#define IR_BUTTON_2 70
#define IR_BUTTON_3 71
#define IR_BUTTON_4 68
#define SOL_OK 8
#define SAG_OK 90
#define OK 28
#define SERVO_PIN 8
#define RED_LED_PIN 5
#define GREEN_LED_PIN 6
#define BLUE_LED_PIN 7
#define buzzer 10  // Set the buzzer pin

#define tempo 120 // Set the tempo (in BPM)

int notes[] = {262, 349, 330, 294, 247, 294};

int durations[] = {40, 400, 400, 400, 400, 400};
Servo myservo; // create a servo object

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(buzzer, OUTPUT); // Set the buzzer pin as output
  Serial.begin(9600);
  BTSerial.begin(9600);
  // Set pins for RGB LEDs to output mode
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Attach servo to pin 9
  myservo.attach(SERVO_PIN);
}

void loop() {
  if (BTSerial.available()) {
    char data = BTSerial.read();
    // Do something with the received data here
  }

  if(Serial.available()>0){
    char veri=Serial.read();
    if(veri=='k'){
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      
    }else if(veri=='y'){
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
    }else if(veri=='m'){
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
    }else if(veri=='l'){
      myservo.write(180);
    }else if(veri=='r'){
      myservo.write(180);
      myservo.write(0);
    }else if(veri=='z'){
      playMelody();
      Serial.println("devam");
      setup();
    }
  }

  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    switch (command) {
      case IR_BUTTON_1: {
        Serial.println("Pressed on button 1");
        // Turn on red LED and turn off green and blue LEDs
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(BLUE_LED_PIN, LOW);
        break;
      }
      case IR_BUTTON_2: {
        Serial.println("Pressed on button 2");
        // Turn on green LED and turn off red and blue LEDs
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(BLUE_LED_PIN, LOW);
        break;
      }
      case IR_BUTTON_3: {
        Serial.println("Pressed on button 3");
        // Turn on blue LED and turn off red and green LEDs
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(BLUE_LED_PIN, HIGH);
        break;
      }
      case SOL_OK: {
        Serial.println("Pressed on sol ok");
        // Make servo motor spin clockwise
        myservo.write(180); // set the servo position to 180 degrees
        break;
      }
      case SAG_OK: {
        Serial.println("Pressed on sag ok");
        // Make servo motor spin clockwise
        myservo.write(180); // set the servo position to 180 degrees
        myservo.write(0); // set the servo position to 0 degrees
        break;
      }
      case OK :{
        Serial.println("Pressed on OK button");
        playMelody();
         Serial.println("dewam");
         setup();
      }
      default: {
        Serial.println("Button not recognized");
        // Turn off all LEDs if button not recognized
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(BLUE_LED_PIN, LOW);
      }
    }
  }
}


void playMelody() {
  for (int i = 0; i < 6; i++) {
    int duration = 6000 / (tempo * durations[i]); // Calculate the duration of each note based on the tempo
    tone(buzzer, notes[i], duration); // Play the note
    delay(200); // Add a slight delay between notes
  }
  noTone(buzzer); // Stop playing the tone
}