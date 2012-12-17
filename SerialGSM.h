#ifndef _SerialGSM_H
#define _SerialGSM_H
#include "Arduino.h"
#include <SoftwareSerial.h>

#define SERIALTIMEOUT 2000
#define PHONESIZE 13
#define MAXMSGLEN 160

class SerialGSM : public SoftwareSerial {
public:
  SerialGSM(int rxpin,int txpin);
  void FwdSMS2Serial();
  void SendSMS();
  void SendSMS(char * cellnumber,char * outmsg);
  void DeleteAllSMS();
  void Reset();
  void EndSMS();
  void StartSMS();
  int ReadLine();
  int ReceiveSMS();
  void Verbose(boolean var1);
  boolean Verbose();
  void Sender(char * var1);
  char * Sender();
  void Rcpt(char * var1);
  char * Rcpt();
  void Message(char * var1);
  char * Message();
  void Boot();

  boolean verbose;
  char sendernumber[PHONESIZE + 1];
  char rcpt[PHONESIZE + 1];
  char outmessage[160];
  char inmessage[160];
  
protected:
  unsigned long lastrec;
  
};

#endif /* not defined _SerialGSM_H */

