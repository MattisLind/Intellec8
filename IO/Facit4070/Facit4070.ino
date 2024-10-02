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

#define PI PA15 //OUTPUT
#define PR PB3  // INPUT
#define TP PB4  //INPUT
#define ERR1 PB5 //INPUT
#define P PB6 //INPUT
#define DIR PB7  //OUTPUT
#define TL PA8 // INPUT



// the setup function runs once when you press reset or power the board
void setup() {
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PI, OUTPUT);
  pinMode(PR, INPUT);
  pinMode(TP, INPUT);
  pinMode(ERR1, INPUT);
  pinMode(P, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(TL, INPUT);
  GPIOB->regs->CRH = 0x33333333;
  while (!Serial);
  Serial.begin(9600);
  Serial.println();
  Serial.println("FACIT 4070 Exerciser");
  Serial.print(">");
  digitalWrite(PI, LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(P, HIGH);
}

int data=0;

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()) {
    data = Serial.read();
    Serial.write(data);
    while(digitalRead(PR)==LOW);
    GPIOB->regs->ODR = (GPIOB->regs->ODR & 0x00ff) | ((data & 0xff) << 8);
    digitalWrite(PI, HIGH);
    while(digitalRead(PR)==HIGH);
    digitalWrite(PI, LOW);
  }

}
