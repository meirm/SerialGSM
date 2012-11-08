// SerialGSM version 1.0
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
  this->println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  this->println("AT+CNMI=3,3,0,0"); // set module to send SMS data to serial out upon receipt 
  delay(200);
}

void SerialGSM::SendSMS(char * cellnumber,char * outmsg){
  this->Sender(cellnumber);
  this->Message(outmsg);
  if (verbose) Serial.println(rcpt);
  this->StartSMS();
  if (verbose) Serial.println(message);
  this->print(message);
  this->EndSMS();
}

void SerialGSM::SendSMS(){
  if (verbose) Serial.println(rcpt);
  this->StartSMS();
  if (verbose) Serial.println(message);
  this->print(message);
  this->EndSMS();
}

void SerialGSM::DeleteAllSMS(){
  this->println("AT+CMGD=1,4"); // delete all SMS
}

void SerialGSM::Reset(){
  this->println("AT+CFUN=1,1"); // Reset Modem
}


void SerialGSM::EndSMS(){
  this->print(char(26));  // ASCII equivalent of Ctrl-Z

  //delay(5 * 1000); // the SMS module needs time to return to OK status
}

void SerialGSM::StartSMS(){

  this->println("AT+CMGF=1"); // set SMS mode to text

  this->print("AT+CMGS=");

  this->print(char(34)); // ASCII equivalent of "

  this->print(rcpt);

  this->println(char(34));  // ASCII equivalent of "

  delay(500); // give the module some thinking time

}

int SerialGSM::ReadLine(){
  static int pos=0;
  char nc;
  if (this->available()){
    nc=this->read();
    if (nc == '\n' or (pos > MAXMSGLEN) or ((millis()> lastrec + SERIALTIMEOUT)and (pos > 0)) ){
      nc='\0';
      lastrec=millis();
      message[pos]=nc;
     pos=0;
     if (verbose) Serial.println(message);
      return 1;
    }
    else if (nc=='\r') {
      return 0;
    }
    else{
      message[pos++]=nc;
      lastrec=millis();
      return 0;
    }
  }
  return 0;
}


int SerialGSM::ReceiveSMS(){
  static boolean insms=0;
  if (this->ReadLine()){
  // Get the number of the sms sender in order to be able to reply
	if ( strstr(message, "CMT: ") != NULL ){
	    insms=1;
	    int sf=6;
	    if(strstr(message, "+CMT:")) sf++; 
		    for (int i=0;i < PHONESIZE;i++){
		      sendernumber[i]=message[sf+i];
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
	return message;
}


void SerialGSM::Sender(char * var1){
	sprintf(sendernumber,"%s",var1);
}


void SerialGSM::Rcpt(char * var1){
	sprintf(rcpt,"%s",var1);
}

void SerialGSM::Message(char * var1){
	sprintf(message,"%s",var1);
}

void SerialGSM::Boot(){
  int counter=0;
  while(counter++ < 15){
    if (verbose) Serial.print(".");
    delay(1000);
  }
  if (verbose) Serial.println();
  
}
