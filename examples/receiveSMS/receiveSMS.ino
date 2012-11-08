#include <SerialGSM.h>
#include <SoftwareSerial.h>
SerialGSM cell(2,3);

boolean sendonce=true;
void setup(){  
  Serial.begin(9600);
  cell.begin(9600);
  cell.Verbose(true);
  cell.Boot();
  cell.DeleteAllSMS();
  cell.FwdSMS2Serial();
 }


void loop(){
  if (cell.ReceiveSMS()){
	 Serial.print("Sender: ");
	 Serial.println(cell.Sender());
	 Serial.print("message: ");
	 Serial.println(cell.Message());
	 cell.DeleteAllSMS();
  }
}

