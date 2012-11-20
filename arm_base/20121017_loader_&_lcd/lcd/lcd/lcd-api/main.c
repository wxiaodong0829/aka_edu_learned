#include "lcd.h"

int c_entry(void)
{
	lcd_init();
	
	lcd_clear_screen(0x000000);	// black	
	
	lcd_draw_hline(272/2, 100, 480-100, 0xffffff);	// white
	
	lcd_draw_vline(480/2, 50, 272-50, 0xffffff);	// white
	
	#define POS	50
	#define HALF	20
	lcd_draw_cross(POS, POS, HALF);
	lcd_draw_cross(POS, 480-POS, HALF);
	
	lcd_draw_cross(272-POS, POS, HALF);
	lcd_draw_cross(272-POS, 480-POS, HALF);
	
	while (1);
		
	return 0;
}
