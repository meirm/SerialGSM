SerialSMS by Meir Michanie 
meirm@riunx.com
Released under GPL3


SerialSMS is a library for arduino to be used with a GPRS/GSM shield.

The library allows you to send/receive SMS with simple OOP methods.
The library also allows you to receive or make phone calls.

Install:
========

	* Create a folder named "SerialGSM" under libraries.
	* Copy the content of this repository into it.




Samples:
========
Sample program to receive SMS for parsing:

//############### ReceiveSMS ############


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

//#######################################


Sample program demostrating how to send a SMS.


//############### SendSMS ################

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

//####################################
