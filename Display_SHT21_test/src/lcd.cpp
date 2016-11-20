#include <u8g_arm.h>
#include "lcd.h"
#include <stdlib.h>

uint8_t draw_state = 0;

u8g_t u8g;

struct lcd_screen lcd_screens[2];

void init_screens(void) {
	lcd_screens[HOMESCREEN].screen_objects = (lcd_object*)malloc(3 * sizeof(lcd_object));
}


//Thermometer bitmap (source: https://github.com/basvdijk/arduino-weather/blob/master/arduino-weather.ino)
#define temperature_width 18
#define temperature_height 47
static unsigned char temperature_bits[] U8G_PROGMEM = {
   0xc0, 0x0f, 0x00, 0xe0, 0x1f, 0x00, 0x70, 0x38, 0x00, 0x30, 0x30, 0x00,
   0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,
   0x30, 0x30, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x30, 0x30, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00,
   0xb0, 0x37, 0x00, 0xb0, 0x37, 0x00, 0x98, 0x67, 0x00, 0x8c, 0xc7, 0x00,
   0xc6, 0x8f, 0x01, 0xe2, 0x1f, 0x01, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03,
   0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03, 0xf3, 0x3f, 0x03,
   0xf3, 0x3f, 0x03, 0xe6, 0x9f, 0x01, 0xc6, 0x8f, 0x01, 0x0c, 0xc0, 0x00,
   0x38, 0x70, 0x00, 0xf0, 0x3f, 0x00, 0xc0, 0x0f, 0x00 };



void u8g_prepare(void) {
  u8g_SetFont(&u8g, u8g_font_6x10);
  u8g_SetFontRefHeightExtendedText(&u8g);
  u8g_SetDefaultForegroundColor(&u8g);
  u8g_SetFontPosTop(&u8g);
}

void u8g_box_frame(uint8_t a) {
  u8g_DrawStr(&u8g, 0, 0, "drawBox");
  u8g_DrawBox(&u8g, 5,10,20,10);
  u8g_DrawBox(&u8g, 10+a,15,30,7);
  u8g_DrawStr(&u8g, 0, 30, "drawFrame");
  u8g_DrawFrame(&u8g, 5,10+30,20,10);
  u8g_DrawFrame(&u8g, 10+a,15+30,30,7);
}

void u8g_string(uint8_t a) {
  u8g_DrawStr(&u8g, 30+a,31, " 0");
  u8g_DrawStr90(&u8g, 30,31+a, " 90");
  u8g_DrawStr180(&u8g, 30-a,31, " 180");
  u8g_DrawStr270(&u8g, 30,31-a, " 270");
}

void u8g_line(uint8_t a) {
  u8g_DrawStr(&u8g, 0, 0, "drawLine");
  u8g_DrawLine(&u8g, 7+a, 10, 40, 55);
  u8g_DrawLine(&u8g, 7+a*2, 10, 60, 55);
  u8g_DrawLine(&u8g, 7+a*3, 10, 80, 55);
  u8g_DrawLine(&u8g, 7+a*4, 10, 100, 55);
}

void u8g_ascii_1(void) {
  char s[2] = " ";
  uint8_t x, y;
  u8g_DrawStr(&u8g, 0, 0, "ASCII page 1");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 32;
      u8g_DrawStr(&u8g, x*7, y*10+10, s);
    }
  }
}

void u8g_ascii_2(void) {
  char s[2] = " ";
  uint8_t x, y;
  u8g_DrawStr(&u8g, 0, 0, "ASCII page 2");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      u8g_DrawStr(&u8g, x*7, y*10+10, s);
    }
  }
}


void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_string(draw_state&7); break;
    case 2: u8g_line(draw_state&7); break;
    case 3: u8g_ascii_1(); break;
    case 4: u8g_ascii_2(); break;
  }
}

void temperature_screen(void){
	u8g_DrawXBMP(&u8g, 100, 8, temperature_width, temperature_height, temperature_bits);
	u8g_SetFont(&u8g, u8g_font_osb18);
	u8g_DrawStr(&u8g, 0, 20, "ABC");
}


// draw Thermometer icon
void draw_thermometer(void){
	u8g_DrawXBMP(&u8g, 100, 8, temperature_width, temperature_height, temperature_bits);

}


void draw_screen(void){
	lcd_screens[HOMESCREEN].screen_objects->object_active = true;
}


