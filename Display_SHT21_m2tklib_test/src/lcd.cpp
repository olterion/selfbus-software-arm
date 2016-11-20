#include <stdlib.h>
#include <string.h>
#include <u8g_arm.h>
#include <M2tk.h>
#include <m2ghu8g.h>
#include "lcd.h"
#include <sblib/core.h>
#include <sblib/timeout.h>
#include "params.h"

uint8_t draw_state = 0;

u8g_t u8g;

struct lcd_home_screen window_ventilation;

//ohne dieses lässt es sich nicht kompilieren....?!
void u8g_box_frame(uint8_t a) {
  u8g_DrawBox(&u8g, 5,10,20,10);
  u8g_DrawStr(&u8g, 0, 30, "drawFrame");
  u8g_DrawFrame(&u8g, 10+a,15+30,30,7);
}


void initLCD(void) {
	u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_hw_spi, u8g_com_hw_spi_fn);

	u8g_SetDefaultForegroundColor(&u8g);

	/* 2. Setup m2 */
//	m2_Init(&top_el_x2l_menu, m2_es_arduino, m2_eh_4bs, m2_gh_u8g_bfs);
	/* connect u8glib with m2tklib */
	m2_SetU8g(&u8g, m2_u8g_box_icon);

	/* assign u8g font to index 0 */
	m2.setFont(0, u8g_font_6x13);

	// Setup keys
	m2.setPin(M2_KEY_SELECT, uiKeySelectPin);
	m2.setPin(M2_KEY_PREV, uiKeyUpPin);
	m2.setPin(M2_KEY_NEXT, uiKeyDownPin);
	m2.setPin(M2_KEY_EXIT, uiKeyExitPin);
}





//=================================================
// Forward declaration of the toplevel element
M2_EXTERN_ALIGN(top_el_x2l_menu);



/*=== number entry ===*/

uint8_t u8num = 0;
uint32_t u32num = 0;

void fn_num_zero(m2_el_fnarg_p fnarg) {
  u8num = 0;
  u32num = 0;
}

M2_LABEL(el_num_label1, NULL, "U8:");
M2_U8NUM(el_num_1, NULL, 0, 255, &u8num);	//das wollen wir!!

M2_LABEL(el_num_label2, NULL, "U32:");
M2_U32NUM(el_num_2, "c5", &u32num);

M2_BUTTON(el_num_zero, "f4", " zero ", fn_num_zero);
M2_ROOT(el_num_goto_top, "f4", " back ", &top_el_x2l_menu);

M2_LIST(num_list) = {
    &el_num_label1, &el_num_1,
    &el_num_label2, &el_num_2,
    &el_num_zero, &el_num_goto_top
};
M2_GRIDLIST(el_num_menu_grid, "c2", num_list);
M2_ALIGN(el_top_num_menu, "-1|1W64H64", &el_num_menu_grid);



uint8_t global_value = 0;

uint8_t u8_cb(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
    global_value = val;
  return global_value;
}

M2_U8NUMFN(el_u8_cb, NULL, 0, 10, u8_cb);


//=================================================
// this is the overall menu structure for the X2L Menu

m2_xmenu_entry xmenu_data[] =
{
  { "Numbers ", &el_top_num_menu },
  { "Menu 2", NULL, NULL },
  { ". Solltemp", NULL, &el_u8_cb },
  { NULL, NULL, NULL },
};

//=================================================
// This is the main menu dialog box

// The first visible line and the total number of visible lines.
// Both values are written by M2_X2LMENU and read by M2_VSB
uint8_t el_x2l_first = 0;
uint8_t el_x2l_cnt = 3;

// M2_X2LMENU definition
// Option l4 = four visible lines
// Option e15 = first column has a width of 15 pixel
// Option W43 = second column has a width of 43/64 of the display width
// Option F3 = select font 3 for the extra column (icons)

M2_X2LMENU(el_x2l_strlist, "l4e15W43F3", &el_x2l_first, &el_x2l_cnt, xmenu_data, 65,102,'\0');
M2_SPACE(el_x2l_space, "W1h1");
M2_VSB(el_x2l_vsb, "l4W2r1", &el_x2l_first, &el_x2l_cnt);
M2_LIST(list_x2l) = { &el_x2l_strlist, &el_x2l_space, &el_x2l_vsb };
M2_HLIST(el_x2l_hlist, NULL, list_x2l);
M2_ALIGN(top_el_x2l_menu, "-1|1W64H64", &el_x2l_hlist);


//=================================================
// m2 object and constructor
M2tk m2(&top_el_x2l_menu, m2_es_arduino, m2_eh_4bs, m2_gh_u8g_ffs);






//================================================================
// low level graphics

uint32_t homescreen_update_time = 0;

// will return none-zero if an update is required
uint8_t update_home_screen(void) {
  if ( homescreen_update_time < millis() ) {
    homescreen_update_time = millis();
    homescreen_update_time += 300;
    return 1;
  }
  return 0;
}

void draw_home_screen(void) {
  u8g_SetDefaultForegroundColor(&u8g);
  u8g_DrawXBMP(&u8g, 100, 8, luefter_width, luefter_height, luefter_bits);
  u8g_DrawXBMP(&u8g, 0, 8, snowflake_width, snowflake_height, snowflake_bits);
}


//================================================================
// high level draw and update procedures

void draw_graphics(void) {
  // show the graphics depending on the current toplevel element

//  if ( m2.getRoot() == &el_combine ) {
//      // combine is active, do add the rectangle
//      // menu is on the right, put the rectangle to the left
////      draw_rectangle(0,y);
//  }

  if ( m2.getRoot() == &m2_null_element ) {
      // all menus are gone, show the rectangle
      draw_home_screen();
  }
}

// update graphics, will return none-zero if an update is required
uint8_t update_graphics(uint8_t handleKeyResult) {
  if ( m2.getRoot() == &top_el_x2l_menu ) {
      // switch to home screen after a while
	  if(!timeout[LCD_HOME_SCREEN].started()){
		  timeout[LCD_HOME_SCREEN].start(RETURNTIME_HOMESCREEN);
	  }
	  if ( handleKeyResult ){ //a key input was made
		  timeout[LCD_HOME_SCREEN].start(RETURNTIME_HOMESCREEN);
	  }

	  if(timeout[LCD_HOME_SCREEN].expired()){	//if some time there was no key input
		  m2.setRoot(&m2_null_element);
	  }

      return handleKeyResult; //give back the result of handleKey
  }

  if ( m2.getRoot() == &m2_null_element ) {
      // check for any keys and assign a suitable menu again
      if ( m2.getKey() != M2_KEY_NONE ){
    	  m2.setRoot(&top_el_x2l_menu);
      }

      // all menus are gone, do a update or process the key input
      return update_home_screen() || handleKeyResult;
  }

  // no update for the graphics required
  return 0;
}

//================================================================
// overall draw procedure for u8glib
void draw_menu(void) {
	draw_graphics();
	m2.draw();
}
