#ifndef LCD_H_
#define LCD_H_

extern u8g_t u8g;

extern uint8_t draw_state;



void u8g_prepare(void);
void u8g_box_frame(uint8_t a);
void u8g_string(uint8_t a);
void u8g_line(uint8_t a);
void u8g_ascii_1(void);
void u8g_ascii_2(void);
void draw(void);
void temperature_screen(void);
void draw_thermometer(void);


struct lcd_object {
	char *object_address;
	uint8_t pos_x;
	uint8_t pos_y;
	uint8_t height;
	uint8_t width;
	uint8_t font_size;
	u8g_fntpgm_uint8_t font;
};



//struct lcd_object lcd_page_objects[2][2];






//struct lcd_page


#endif
