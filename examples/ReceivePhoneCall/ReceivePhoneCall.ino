#include <SerialGSM.h>
#include <SoftwareSerial.h>
SerialGSM cell(2, 3);
int ign = 0;
void setup() {
  Serial.begin(9600);
  cell.begin(9600);
  cell.Verbose(true);
  cell.Boot();
  cell.answer();
  delay(10000);
  cell.hangup();
  Serial.println("Done");
}


void loop() {
  
}

