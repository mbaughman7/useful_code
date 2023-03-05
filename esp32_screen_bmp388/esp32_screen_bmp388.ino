#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  // Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
  Wire.begin(5, 4);
  Serial.println("print temp to screen with bmp388 sketch");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  if (!bmp.begin_I2C()) {  // hardware I2C mode, can pass in address & alt Wire
                           //if (! bmp.begin_SPI(BMP_CS)) {  // hardware SPI mode
                           //if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  delay(2000);  // Pause for 2 seconds

  // Clear the buffer.
  display.clearDisplay();
  startupText();
  // Draw bitmap on the screen
  display.display();
}


void loop() {
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();

  printTemp();

  delay(2000);
}



void startupText() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // Start at top-left corner
  display.println(F("ESP32 Temp"));
  display.println(F("Sketch"));
  display.display();
  delay(3000);
}

void printTemp() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // Start at top-left corner
  display.print(F("Temp:"));
  display.println((bmp.temperature));
  display.print((bmp.readAltitude(SEALEVELPRESSURE_HPA)));
  display.display();
  delay(3000);
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);       // Normal 1:1 pixel scale
  display.setTextColor(WHITE);  // Draw white text
  display.setCursor(0, 0);      // Start at top-left corner
  display.println(F("Hello, world!"));

  display.display();
  delay(2000);
}