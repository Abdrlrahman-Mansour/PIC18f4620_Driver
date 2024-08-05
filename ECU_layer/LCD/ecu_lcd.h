/* 
 * File:   ecu_lcd.h
 * Author: laphouse
 *
 * Created on July 3, 2024, 9:35 AM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/*section :     Includes    */
#include "ecu_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"




/*section :     Macros Declarations    */
#define LCD_CLEAR                       0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF    0x04
#define LCD_ENTRY_MODE_DEC_SHIFT_ON     0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF    0x06
#define LCD_ENTRY_MODE_INC_SHIFT_ON     0x07
#define LCD_CURSOR_MOVE_SHIFT_LEFT      0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT     0x14
#define LCD_DISPLAY_SHIFT_LEFT          0x18
#define LCD_DISPLAY_SHIFT_RIGHT         0x1C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF     0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON      0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF      0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON       0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF                  0x08
#define LCD_8BIT_MODE_2_LINE         0x38
#define LCD_4BIT_MODE_2_LINE         0x28

#define _LCD_CGRAM_START             0x40
#define _LCD_DDRAM_START             0x80

#define ROW1    1
#define ROW2    2
#define ROW3    3
#define ROW4    4

/*section :     Macro Function Declarations    */


/*section :     Data Type Declarations    */
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;
/*section :      Function Declarations    */
Std_ReturnType lcd_4bit_init(const lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd,uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd,uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd,uint8 row,uint8 col,uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd,uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd,uint8 row,uint8 col,uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd,uint8 row,uint8 col ,const uint8 _char[],uint8 mem_pos);

Std_ReturnType lcd_8bit_init(const lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd,uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd,uint8 row,uint8 col,uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd,uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd,uint8 row,uint8 col,uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd,uint8 row,uint8 col ,const uint8 _char[],uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value, uint16 *str);
Std_ReturnType convert_int_to_string(uint32 value, uint32 *str);

#endif	/* ECU_LCD_H */

