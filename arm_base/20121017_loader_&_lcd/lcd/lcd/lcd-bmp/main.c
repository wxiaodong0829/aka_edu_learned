#include "lcd.h"

#define BMP_ADDR	(0x22000000)

// before download this bin to 0x21000000, you should first "loadb 0x22000000" to load test.bmp file to 0x22000000
int c_entry(void)
{
	char * p = (char *)BMP_ADDR;
	char red, blue, green;
	int color;
	int i, j;
	
	lcd_init();
	
	lcd_clear_screen(0x000000);	// black	
	
	// read bmp file
	// bmp file header is 54 bytes
	p += 54;
	
	for (i = 0; i < 272; i++)
		for (j = 0; j < 480; j++)
		{
			blue = *p++;
			green = *p++;
			red = *p++;
		
			color = red << 16 | green << 8 | blue << 0;
			
			lcd_draw_pixel(271-i, j, color);
		}
		
	while (1);
		
	return 0;
}
