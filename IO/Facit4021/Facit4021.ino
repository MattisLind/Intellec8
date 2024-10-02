/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define AC PA15
#define AO PB3
#define AM1 PB4
#define AM2 PB5
#define SC PB6
#define SO PB7
#define P PA8

void soInterrupt() {
  if (digitalRead(SO)==HIGH) {
    Serial.println("SO=1");
  } else {
    Serial.println("SO=0");
  }
}

void scInterrupt () {
  int data = GPIOB->regs->IDR >> 8;
  int error =  digitalRead(SO);
  if (error==1) {
    if (digitalRead(SC)==HIGH) {
      //Serial.print("SC=1 D=");
      Serial.write(data);
      digitalWrite(AC, 0);
    } else {
      //Serial.print("SC=0 D=");
      digitalWrite(AC, 1);
    }
  }
}



void pInterrupt () {
  if (digitalRead(P)==HIGH) {
    Serial.println("P=1");
  } else {
    Serial.println("P=0");
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(AC, OUTPUT);
  pinMode(AO, OUTPUT);
  pinMode(AM1, OUTPUT);
  pinMode(AM2, OUTPUT);
  pinMode(SO, INPUT);
  pinMode(SC, INPUT);
  pinMode(P, INPUT);
  GPIOB->regs->CRH = 0x88888888; // SET INPUT W/ PUPD on PB15-PB8
  //attachInterrupt(SO, soInterrupt, CHANGE);
  //attachInterrupt(SC, scInterrupt, CHANGE);
  //attachInterrupt(P, pInterrupt, CHANGE);
  while (!Serial);
  Serial.begin(9600);
  Serial.println();
  Serial.println("FACIT 4021 Exerciser");
  Serial.print(">");
  digitalWrite(AM2, LOW);
  digitalWrite(AM1, LOW);
  digitalWrite(AO, HIGH);
  digitalWrite(AC, LOW);
  //digitalWrite(AC, HIGH);
}

int am1=0, am2=0, ac=0, ao=0,sc, so;


// the loop function runs over and over again forever
void loop() {
  int ch;
  int firstCharRead = 0;
  /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  */
  // wait for a 
  if (Serial.available()) {
    ch = Serial.read();
    switch(ch) {
      case '1':
        am1 ^= 1;
        Serial.println("1");
        digitalWrite(AM1, am1);
        Serial.print("AM1=");
        Serial.print(am1);
        Serial.println();
        Serial.print(">");
        break;
      case '2':
        am2 ^= 1;
        Serial.println("2");
        digitalWrite(AM2, am2);
        Serial.print("AM2=");
        Serial.print(am2);
        Serial.println();
        Serial.print(">");
        break;
      case 'c':
      case 'C':
        ac ^= 1;
        Serial.println("C");
        Serial.print("AC=");
        Serial.print(ac);
        Serial.println();
        Serial.print(">");
        digitalWrite(AC, ac);
        break;
      case 'o':
      case 'O':
        Serial.println("O");
        ao ^= 1;
        Serial.print("AO=");
        Serial.print(ao);
        Serial.println();
        Serial.print(">");
        digitalWrite(AO, ao);
        break;
      case 's':
      case 'S':
        Serial.println("S");
        Serial.print("SO=");
        Serial.print(digitalRead(SO));
        Serial.print(" SC=");
        Serial.print(digitalRead(SC));
        Serial.print(" P=");
        Serial.println(digitalRead(P));
        Serial.print(">");
        break;
      case 'r':
      case 'R':
        do {        
          digitalWrite(AC, HIGH);  
          //Serial.println(digitalRead(SO));
          while (digitalRead(SC) != HIGH) {            
            if ((digitalRead(SO) == LOW) && (firstCharRead == 1)) break;
          };
          firstCharRead = 1;
          //Serial.println(digitalRead(SO));
          if (digitalRead(SO) == LOW) break;
          Serial.write(GPIOB->regs->IDR >> 8);
          digitalWrite(AC, LOW);
          if (digitalRead(SO) == LOW) break;
          while (digitalRead(SC) != LOW) {
            if (digitalRead(SO) == LOW) break;
          };
          //Serial.println(digitalRead(SO));
          if (digitalRead(SO) == LOW) break;
        } while (true);
        break;
      default:
        Serial.println();
        Serial.print(">");
        break;
        
    }
  }
}
