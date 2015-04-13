// SerialGSM version 1.1
// by Meir Michanie
// meirm@riunx.com





// error codes
// http://www.developershome.com/sms/resultCodes2.asp
#include <SerialGSM.h>

SerialGSM::SerialGSM(int rxpin,int txpin):
SoftwareSerial(rxpin,txpin)
{
 verbose=false;
}

void SerialGSM::FwdSMS2Serial(){
  Serial.println("AT+CMGF=1"); // set SMS mode to text
  this->println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  this->ReadLine();
  Serial.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt 
  this->println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt 
  delay(200);
  this->ReadLine();
}

void SerialGSM::SendSMS(char * cellnumber,char * outmsg){
  this->Rcpt(cellnumber);
  if (verbose) Serial.println(rcpt);
  this->StartSMS();
  this->Message(outmsg);
  Serial.print(outmessage);
  this->print(outmessage);
  this->EndSMS();
  delay(500);
  this->ReadLine();
}

void SerialGSM::SendSMS(){
  if (verbose) Serial.println(rcpt);
  if (verbose) Serial.println(outmessage);
  this->StartSMS();
  Serial.print(outmessage);
  this->print(outmessage);
  this->EndSMS();
  delay(500);
  this->ReadLine();
}

void SerialGSM::DeleteAllSMS(){
  Serial.println("AT+CMGD=1,4"); // delete all SMS
  this->println("AT+CMGD=1,4"); // delete all SMS
  delay(200);
  this->ReadLine();
}

void SerialGSM::Reset(){
  Serial.println("AT+CFUN=1,1"); // Reset Modem
  this->println("AT+CFUN=1,1"); // Reset Modem
  delay(200);
  this->ReadLine();
}


void SerialGSM::EndSMS(){
  this->print(char(26));  // ASCII equivalent of Ctrl-Z
  Serial.println();

  //delay(5 * 1000); // the SMS module needs time to return to OK status
}

void SerialGSM::StartSMS(){

  Serial.println("AT+CMGF=1"); // set SMS mode to text
  this->println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  this->ReadLine();

  Serial.print("AT+CMGS=");
  this->print("AT+CMGS=");

  this->print(char(34)); // ASCII equivalent of "

  Serial.print(rcpt);
  this->print(rcpt);

  this->println(char(34));  // ASCII equivalent of "

  delay(500); // give the module some thinking time
  this->ReadLine();

}

int SerialGSM::ReadLine(){
  static int pos=0;
  char nc;
  while (this->available()){
    nc=this->read();
    if (nc == '\n' or (pos > MAXMSGLEN) or ((millis()> lastrec + SERIALTIMEOUT)and (pos > 0)) ){
      nc='\0';
      lastrec=millis();
      inmessage[pos]=nc;
     pos=0;
     if (verbose) Serial.println(inmessage);
      return 1;
    }
    else if (nc=='\r') {
    }
    else{
      inmessage[pos++]=nc;
      lastrec=millis();
    }
  }
  return 0;
}


int SerialGSM::ReceiveSMS(){
  static boolean insms=0;
  if (this->ReadLine()){
  // Get the number of the sms sender in order to be able to reply
	if ( strstr(inmessage, "CMT: ") != NULL ){
	    insms=1;
	    int sf=6;
	    if(strstr(inmessage, "+CMT:")) sf++; 
		    for (int i=0;i < PHONESIZE;i++){
		      sendernumber[i]=inmessage[sf+i];
		    }
		sendernumber[PHONESIZE]='\0';
		return 0;
	 }else{ 
		if(insms) {
			insms=0;
			return 1;
		}
	}
  }
  return 0;
}


boolean SerialGSM::Verbose(){
	return verbose;
}

void SerialGSM::Verbose(boolean var1){
	verbose=var1;
}

char * SerialGSM::Sender(){
	return sendernumber;
}


char * SerialGSM::Rcpt(){
	return rcpt;
}

char * SerialGSM::Message(){
	return inmessage;
}


void SerialGSM::Sender(char * var1){
	sprintf(sendernumber,"%s",var1);
}


void SerialGSM::Rcpt(char * var1){
	sprintf(rcpt,"%s",var1);
}

void SerialGSM::Message(char * var1){
	sprintf(outmessage,"%s",var1);
}

void SerialGSM::Boot(){
  int counter=0;
  while(counter++ < 15){
    if (verbose) Serial.print(".");
    delay(1000);
  }
  if (verbose) Serial.println();
  
}
