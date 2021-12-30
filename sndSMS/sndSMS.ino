/*
   This sketch will send a single SMS message upon booting.
   A Twilio account is required, as is a Twilio phone number.  The phone
   numbers are only a dollar or two per month, and messages/data are
   pay-as-you-go.  In order to use this sketch exactly as I use it, you
   will need to use a Twilio SuperSIM SIM card.  Other
   SIM cards may work for you, and results may vary.
   This sketch is intended to be used as a starting place for useful
   applications such as sending SMS messages upon input triggers like
   button mashing or analog input thresholds.
   I am using a DFRobot SIM7000A module, and I am in North America. 
*/

/* 
 This is what the beginning of the URL AT command should look like.  This isn't a real endpoint; I don't want my Twilio account
 getting blown up with your messages, but I'll leave this address here for formatting reference. 
 Note the '\' before the quotation marks internal to the message.  This is to 
 assign them as part of the text of the AT command and not as part of the code syntax.  Also note the
 '?' at the end.  That is to separate the URL resource path from the paramaters that will follow.
 In our case, the parameters that will follow are the From, To, and Body of the message.
*/
char url_header[] ="AT+HTTPPARA=\"URL\",\"http://sndSMS-9557.twil.io/sendMessage?";

/* 
 In the parameters, the '%20' represents a space.  https://www.fullhost.com/blog/what-does-20-mean-in-a-web-address/
 and %2b represents a '+' sign.  
 The From number is my Twilio phone number.
 You MUST use a Twilio phone number as your From number.  Twilio will not be able to route a message out using this
 method from a non-Twilio phone number, as far as I know.
 The numbers as they are shown in formatted for the United States.  The "%2b" is a +, and the first number after them is the country
 code of '1.'  So if your Twilio number is 555-234-5678, it would be formatted as seen below. The To number is to a United States number of
 555-876-5432.
*/
char from_arr[] = "From=%2b15552345678&";
char to_arr[] = "To=%2b15558765432&";
char body[] = "Body=Test%20Message\"\r";

unsigned char data = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);
  Serial.println(F("This is a sketch to send a single SMS message upon booting."));

  Serial.println("Hey!  Wake up!");
  Serial1.print("AT\r"); //Toggling this blank AT command elicits a response of "OK" from the
  //SIM module and helps to wake it up.  Anyone with more understanding of what is actually happening here,
  //please DM me your knowledge. 
  getResponse();
  Serial1.print("AT\r");
  getResponse();
  Serial1.print("AT\r");
  getResponse();
  Serial1.print("AT\r");
  getResponse();
  Serial1.print("AT\r");
  getResponse();
  
  //SIM MODULE SETUP
  Serial1.print("AT+CGDCONT=1,\"IP\",\"super\"\r");  //"super" is the key required to log onto the network using Twilio SuperSIM
  delay(500);
  getResponse();
  Serial1.print("AT+COPS=1,2,\"310410\"\r"); //310410 is AT&T's network code https://www.msisdn.net/mccmnc/310410/
  delay(5000);
  getResponse();
  Serial1.print("AT+CMGD=0,4\r"); //this line deletes any existing text messages to ensure
  //that the message space is empy and able to accept new messages
  delay(100);
  getResponse();
  Serial1.print("AT+CMGF=1\r");
  delay(100);
  getResponse();
  Serial1.print("AT+CNMI=2,2,0,0,0\r"); //
  delay(100);
  getResponse();
  //the sendSMS function takes four parameters.
  sendSMS(url_header, from_arr, to_arr, body);

}

void loop() {

}

void sendSMS(char pt1[], char pt2[], char pt3[], char pt4[])
{

  char finalURL[250] = "";

  strcpy(finalURL, pt1);
  strcat(finalURL, pt2);
  strcat(finalURL, pt3);
  strcat(finalURL, pt4);
  delay(500);
  Serial.println(finalURL);
  delay(20);
  Serial1.print("AT+HTTPTERM\r");
  delay(1000);
  getResponse();
  Serial1.print("AT+SAPBR=3,1,\"APN\",\"super\"\r");
  delay(300);
  getResponse();
  Serial1.print("AT+SAPBR=1,1\r");
  delay(1000);
  getResponse();
  Serial1.print("AT+HTTPINIT\r");
  delay(100);
  getResponse();
  Serial1.print("AT+HTTPPARA=\"CID\",1\r");
  delay(100);
  getResponse();
  Serial1.println(finalURL);
  delay(100);
  getResponse();
  Serial1.print("AT+HTTPACTION=1\r");
  delay(5000);
  getResponse();

}

void getResponse()
{
 
  if (Serial1.available())
  {
    while (Serial1.available())
    {
      data = Serial1.read();
      Serial.write(data);
    }
    data = 0;
  }
  delay(500);
}
