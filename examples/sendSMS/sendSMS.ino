#include <SerialGSM.h>
#include <SoftwareSerial.h>
SerialGSM cell(2,3);
void setup(){  
 Serial.begin(9600); 
 cell.begin(9600);
  cell.Verbose(true);
  cell.Boot(); 
  cell.FwdSMS2Serial();
  cell.Rcpt("+972123456789");
  cell.Message("hello world");
  cell.SendSMS();
}


void loop(){
  if (cell.ReceiveSMS()){
    Serial.println(cell.Message());
    cell.DeleteAllSMS();
  }

}

