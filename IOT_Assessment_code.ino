/* --- REFERENCES ------- */

/*
 SMS sender

 created 25 Feb 2012
 by Tom Igoe

 This example is in the public domain.

 http://www.arduino.cc/en/Tutorial/GSMExamplesSendSMS

*/

/* 
 *  Uses a PIR sensor to detect movement, buzzes a buzzer, And LED
 *  Creator Md. Jubayer Rahma
 *  If Need Help Contact : jrahman10@gmail.com
 *  Date : 13.04.2014
*/

// Include GSM library
#include <GSM.h>

#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

// char array of the telephone number to send SMS to
char remoteNumber[20]= "07450291064";  

// char array of the message being sent to phone number
char txtMsg[200]= "Movement has been detected! You have a visitor";

int ledPin = 8;                   // choose the pin for the LED
int pinSpeaker = 4;               // Set up a speaker on a PWM pin (digital 9, 10, or 11)
  
void setup() {
  pinMode(ledPin, OUTPUT);        // declare LED as output
  pinMode(pinSpeaker, OUTPUT);    // declare buzzer as output
  
  Serial.begin(9600);

  Serial.print("Motion Detecter |");
  Serial.println(" SMS Sender");

// connection state
  boolean notConnected = true;

// Start GSM shield
  while(notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)
      notConnected = false;
    else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");

  delay(2000);
  
  Serial.println("Starting program in 20 seconds");

  delay(20000);
}

void loop() {
  int inputPin = analogRead(A5);      // Reading the PIR Motion sensor value
  Serial.println(inputPin);
  
  if (inputPin >= 300) {              // check if the input is HIGH
    digitalWrite(ledPin, HIGH);       // turn LED ON
    playTone(300, 160);
    delay(150);

    sendSMS();
    
    delay(30000);
  }
  
  else {
      digitalWrite(ledPin, LOW);      // turn LED off & tone
      playTone(0, 0);
      delay(300);
  }
}

// Code from Md. Jubayer Rahma

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

// SMS Code
void sendSMS(){

  Serial.print("Message to mobile number: ");
  Serial.println(remoteNumber);

// sms text
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);

// send the message
  sms.beginSMS(remoteNumber);
  sms.print(txtMsg);
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");
}
