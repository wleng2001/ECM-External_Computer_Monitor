#include "eo_graphics.h"

//EXTRA_FUNCTIONS-------------------------------------------------------------------
byte fps_display;
byte fps;
unsigned long frame_start;
unsigned long measure_frame;
unsigned long if_time;

#define if_fps_counter 1
#define fraps_height display.height()-7
#define fraps_width 0
#define display_fraps 1
#define refresh 500 

void fps_counter(){
  if(if_fps_counter==1 and millis()-refresh<if_time){
    fps=fps+1;
  }else{
    fps_display=fps*1000/refresh;
    fps=0;
    if_time=millis();
  }
}

int frame_time(unsigned long frame_start){
  return millis()-frame_start;
}

void fraps(bool frame_time){
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(fraps_width, fraps_height);
  display.print(fps_display);
  display.print(" ");
  if(frame_time==1){
    display.println(measure_frame);  
  }
}

void load_display(){
  if(display_fraps==1){
    fraps(1);
  }
  display.display();
  fps_counter();
  measure_frame=frame_time(frame_start);
}

void clear_Display(){
  display.clearDisplay();
  frame_start=millis();
}

//progress bar
void progress_bar(uint8_t postep, uint8_t wys, uint8_t szer){
  display.drawBitmap(szer, wys, bitmap_progress_bar, 110, 5, 1);//draw bitmap, which it is boundary of progress bar
  uint8_t i=0;
  uint8_t k=0;
  if(postep>0){
    display.drawPixel(szer+1,wys+2, SSD1306_WHITE);
    while(i<=int(postep*1.06)){
      while(k<3){
        display.drawPixel((szer+2+i),(wys+1+k), SSD1306_WHITE);
        k=k+1;
      }
      if(k==3){
        k=0;
      }
      i=i+1;
    }
  }
  if(postep==100){
    display.drawPixel((szer+108),(wys+2), SSD1306_WHITE);
  }
}
//baterry charging
void baterry_charge(byte height, byte width, byte precente){
  if(precente>100){
    precente=0;
  }
  display.drawBitmap(width, height, bitmap_0_baterry, O_baterry_width, O_baterry_height, SSD1306_WHITE);
  for(byte i=0; i<=precente/10; i++){
    for(byte j=0; j<=4; j++){
      display.drawPixel(width+O_baterry_width-1-i,height+1+j,SSD1306_WHITE);
    }
  }
}
//wifi range
void wifi_range(byte height, byte width, byte range){
  if(range>90){
    display.drawBitmap(width,height,bitmap_wifi_big_range,big_range_width,big_range_height,1);    
  }
  if(range>50){
    display.drawBitmap(width,height+2,bitmap_wifi_medium_range,medium_range_width,medium_range_height,1);    
  }
  if(range>20){
    display.drawBitmap(width,height+4,bitmap_wifi_small_range,small_range_width,small_range_height,1);
  }
  display.drawPixel(width,height+6,SSD1306_WHITE);
}
//button
void button(bool if_choice, uint8_t polozenie_wys, uint8_t polozenie_szer, String inscription){
  if(if_choice==true){
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  }else{
    display.setTextColor(SSD1306_WHITE);
  }
  uint8_t szer_przycisku=inscription.length()*6+3;
  uint8_t wys_przycisku=11;
  display.drawLine( polozenie_szer, polozenie_wys, polozenie_szer+szer_przycisku, polozenie_wys, SSD1306_WHITE);//poziom góra
  display.drawLine( polozenie_szer, polozenie_wys, polozenie_szer, polozenie_wys+wys_przycisku, SSD1306_WHITE);//pion lewo
  display.drawLine( polozenie_szer, polozenie_wys+wys_przycisku, polozenie_szer+szer_przycisku, polozenie_wys+wys_przycisku, SSD1306_WHITE);//poziom dół
  display.drawLine( polozenie_szer+szer_przycisku, polozenie_wys, polozenie_szer+szer_przycisku, polozenie_wys+wys_przycisku, SSD1306_WHITE);//pion prawo

  display.setTextSize(1);
  display.setCursor(polozenie_szer+2,polozenie_wys+2);
  display.println(inscription); //wstaw F!
}
//LIST_ITEM-----------------------------------
//list item on or of
#define margin 4

void list_item_true(bool if_choice,byte height, String description, bool if_on){
  height=height+1;
  if(if_choice==0){
   display.setTextColor(SSD1306_WHITE); 
  }else{
    display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
  }
  display.setTextSize(1);
  display.setCursor(1,height);
  display.println(description);
  if(if_on==1){
    display.drawBitmap(display.width()-margin-switch_on_width, height-1, bitmap_switch_on, switch_on_width, switch_on_height,SSD1306_WHITE);
  }else{
    display.drawBitmap(display.width()-margin-switch_off_width, height-1, bitmap_switch_off, switch_off_width, switch_off_height,SSD1306_WHITE);
  }
}
//list item  String
void list_item_string(bool if_choice, byte height, String description, String value){
  if(if_choice==0){
   display.setTextColor(SSD1306_WHITE); 
  }else{
    display.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
  }
  display.setTextSize(1);
  display.setCursor(1,height);
  display.println(description);
  display.setCursor(display.width()-value.length()*7-margin,height);
  display.println(value);
}
//PLOT_BAR---------------------------------
//horizontal bar
void h_bar(byte height, byte width, byte bar_h, byte length, byte percent){
  display.drawLine(width, height, width, height+bar_h, SSD1306_WHITE);
  byte len_percent=length*percent/100;
  byte max_h=height+1;
  byte min_h=height+bar_h-1;
  if(max_h>=min_h){
    max_h=min_h;
  }
  for(byte i=width+1;i<=width+len_percent;i++){
    for(byte j=max_h;j<=min_h;j++){
      display.drawPixel(i,j,SSD1306_WHITE);
    }
  }
  display.drawLine(width+length, height, width+length, height+bar_h, SSD1306_WHITE);
}
