#define v_of_dev "wen82-182x64-g-w" //version of device, which read computer program, when first section means version of microcontroller second resolution of display, third that display is graphical or text, last section means that device have some additional function (button for example)

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "analyzer.h" //it's module which edit input to form acceptable by rest of program
#include "graphics.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//variables
const String wellcome="Device isn't connected";
String text=wellcome; //text, which will be displayed
String comm="";
String data="";

//functions
void display_text(String text) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}

String receive_data(){
  String data="";
  if(Serial.available() > 0) {
    data=Serial.readStringUntil('\n'); //read input to '\n' sign
  }
  return data;
}
//commands
void commands(String comm, String data){
  device_version(comm);
  source_monitor(comm);
  set_baudrate(comm, data);
}

void device_version(String comm){
  if(comm=="VERSION"){
    Serial.println(v_of_dev);
  }
}

void source_monitor(String comm){
  if(comm=="SM_M"){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(22,1);
    display.print(F("source monitor"));
    display.drawBitmap((display.width()-w_bitmap_source_monitor_48x48)/2, display.height()-h_bitmap_source_monitor_48x48, bitmap_source_monitor_48x48, w_bitmap_source_monitor_48x48, h_bitmap_source_monitor_48x48, 1);
    display.display();
    String data="";
    while(one_word_ret(data)!="EXIT"){
      if(data!=""){
        display_text(data); 
      }
      String temporary_data=receive_data();
      if(temporary_data!=""){
        data=temporary_data;
      }
    }
  }
}

void set_baudrate(String comm, String data){
  if(comm=="SERIAL"){
    Serial.begin(data.toInt());
    Serial.printf("Serial set to %d baudrate",data.toInt());
  }
}

//program
void setup() {
  Serial.begin(9600);
  device_version("VERSION");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  display_text(wellcome);
  display.clearDisplay();
}

void loop() {
  commands(comm, data);
  comm="";
  String temporary_text=receive_data();
  if(temporary_text!=""){
    text=temporary_text;
    data=delete_useless_spaces(text);
    comm=one_word_ret(data);
    data=ed_txt.rewrite_in_range(comm.length(),data.length(),data);
  }
  
}
