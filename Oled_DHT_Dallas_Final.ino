#include <SPI.h>  
 #include <Wire.h>  
 #include <Adafruit_GFX.h>  
 #include <Adafruit_SSD1306.h>  
 #include <SimpleDHT.h>
 #include <OneWire.h>
#include <DallasTemperature.h>
  
 //   for DHT11,   
 //   VCC: 5V or 3V  
 //   GND: GND  
 //   DATA: 2  
 int pinDHT11 = 8;  
 SimpleDHT11 dht11(pinDHT11); 
 #define ONE_WIRE_BUS 9 
 #define screen_width 128 // OLED display width, in pixels  
 #define screen_height 64 // OLED display height, in pixels  
 #define OLED_RESET 4  
 Adafruit_SSD1306 display(screen_width, screen_height);
 
 OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
  
 void setup ()  
 {  
  Serial.begin(9600);
  // Start up the library
  sensors.begin();  
   Serial.println("TEMPERATURE AND HUMIDITY");  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();  
 }  
 void loop ()  
 {  
  byte temperature = 0;  
  byte humidity = 0;  
  int err = SimpleDHTErrSuccess; 
  sensors.requestTemperatures();  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {  
   Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);  
   return;  
  }  
  Serial.print((int)temperature); Serial.print(" *C, ");   
  Serial.print((int)humidity); Serial.println(" H");  
  // DHT11 sampling rate is 1HZ.  
   display.clearDisplay();  
   display.setTextSize(1);  
   display.setTextColor(SSD1306_WHITE);  
   display.setCursor(0, 0);  
   display.print("  TEMP. & HUMIDITY");  
   display.setCursor(0, 15);  
   display.print(" TEMPERATURE : ");  
   display.setCursor(90, 15);  
   display.print((int)temperature);
   display.setCursor(110, 15);  
   display.print("C");  
   display.setCursor(0, 30);  
   display.print(" HUMIDITY  : ");  
   display.setCursor(90, 30);  
   display.print((int)humidity);
    display.setCursor(110, 30);  
   display.print("%");
    display.setCursor(0, 45);
   display.print("CelTEMPERATURE : ");
   display.setCursor(90, 45);  
   display.print(sensors.getTempCByIndex(0));
   display.setCursor(120, 45);  
   display.print("C");    
   display.display();  
 }  
