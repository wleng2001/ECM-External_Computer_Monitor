#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

String tekst="Tak bedzie widoczny twoj tekst po wpisaniu w COM, nie ustawilem jeszcze komend, ktore beda mogly zmieniac wielkosc tekstu ani tez obslugi polskich znakow. Postaram sie to jednak zmienic w przyszlosci a jesli czas i sprzet pozwoli to dodam to i do zegarka.";

void testscrolltext(String tekst) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(tekst);
  display.display();
}

String odbior_danych(){
  String dane="";
  if(Serial.available() > 0) { //Czy Arduino odebrało dane
    dane=Serial.readStringUntil('\n'); //Jeśli tak, to odczytaj je do znaku końca linii i zapisz w zmiennej odebraneDane
    Serial.println("użytkownik: "+dane);
    
  }
  return dane;
}

void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  delay(5000);
  Serial.println("dzialam!");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  testscrolltext(tekst);
  
  String tymczasowy_tekst=odbior_danych();
  if(tymczasowy_tekst!=""){
    tekst=tymczasowy_tekst;
  }
}
