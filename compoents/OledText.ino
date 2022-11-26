#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);
 
int number = 0;

void setup()   {
  OLED.begin();
  OLED.clearDisplay();

  //Add stuff into the 'display buffer'
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.println("Mr Screen");

  OLED.display(); //output 'display buffer' to screen  
  OLED.startscrollleft(0x00, 0x0F); //make display scroll 
} 
 
void loop() {
  delay(5000);
  OLED.clearDisplay();
  OLED.setCursor(0,0);
  OLED.print("count with me! " +number);
  OLED.display();
  number++;
}