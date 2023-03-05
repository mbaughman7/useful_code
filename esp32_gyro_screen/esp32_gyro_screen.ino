#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  }
  Wire.begin(5, 4);
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("print gyro to screen sketch");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);

  display.clearDisplay();
  startupText();
  // Draw bitmap on the screen
  display.display();
}

void loop() {

  /* Get new sensor events with the readings */


  /* Print out the values */
  // Serial.print(a.acceleration.x);
  // Serial.print(",");
  // Serial.print(a.acceleration.y);
  // Serial.print(",");
  // Serial.print(a.acceleration.z);
  // Serial.print(", ");
  // Serial.print(g.gyro.x);
  // Serial.print(",");
  // Serial.print(g.gyro.y);
  // Serial.print(",");
  // Serial.print(g.gyro.z);
  // Serial.println("");
  printGyro();
  delay(100);
}

void printGyro() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // Start at top-left corner
  display.print(g.gyro.x);
  display.println(",");
  display.print(g.gyro.y);
  display.println(",");
  display.print(g.gyro.z);
  display.println("");
  display.display();
  delay(10);
}

void startupText() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);  // Start at top-left corner
  display.println(F("ESP32 Gyro"));
  display.println(F("Sketch"));
  display.display();
  delay(3000);
}