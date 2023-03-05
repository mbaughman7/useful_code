
#include <SD.h>   
#include <dht.h>  


#define DHT11_PIN 7  //Sensor output pin is connected to pin 14.  This can be changed

dht DHT;  //instantiating the dht sensor and naming it DHT


void setup() {
  Serial.begin(9600);
  Serial.println("dec19 temphum sketch");
  Initialize_SDcard();  
  digitalWrite(33, HIGH);
}

void loop() {

  Write_SDcard();

  delay(15000);  //Wait for 15 seconds before writing the next data
}

void Write_SDcard() {
  int chk = DHT.read11(DHT11_PIN);

  int temp = DHT.temperature;

  int tempF = ((temp * (1.8)) + 32);


  File dataFile = SD.open("cLog.txt", FILE_WRITE);



  if (dataFile) {


    dataFile.print(millis());
    dataFile.print(",");

    dataFile.print(tempF);  //Store date on SD card
    dataFile.print(",");      //Move to next column using a ","


    dataFile.print(DHT.humidity);  //Store date on SD card
    dataFile.print(",");           //Move to next column using a ","


    dataFile.println();  //End of Row move to next row
    dataFile.close();    //Close the file

    Serial.print("Temp is: ");
    Serial.println(tempF);
    Serial.print("Humidity is: ");
    Serial.println(DHT.humidity);
  } else
    Serial.println("SD card writing failed");
}


void Initialize_SDcard() {
  // see if the card is present and can be initialized:
  if (!SD.begin(10)) {
    Serial.println("Card failed or not present");
    return;
  }

  File dataFile = SD.open("cLog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println("Time,Temperature,Humidity");  //Write the first row of the csv
    dataFile.close();
  }
}
