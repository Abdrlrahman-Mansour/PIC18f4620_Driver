/* 
 * File:   ecu_seven_seg.h
 * Author: laphouse
 *
 * Created on July 1, 2024, 3:13 PM
 */
#include "ecu_seven_seg.h"
/**
 * 
 * @param seg
 * @return 
 */
Std_ReturnType seven_segment_init(const segment_t *seg){
Std_ReturnType ret = E_OK;
if(NULL == seg){
    ret = E_NOT_OK;
}
else {
    ret = gpio_pin_direction_init(&(seg->segment_pin[0]));
    ret = gpio_pin_write_logic(&(seg->segment_pin[0]), seg->segment_pin[0].logic);
    ret = gpio_pin_direction_init(&(seg->segment_pin[1]));
    ret = gpio_pin_write_logic(&(seg->segment_pin[1]), seg->segment_pin[1].logic);
    ret = gpio_pin_direction_init(&(seg->segment_pin[2]));
    ret = gpio_pin_write_logic(&(seg->segment_pin[2]), seg->segment_pin[2].logic);
    ret = gpio_pin_direction_init(&(seg->segment_pin[3]));
    ret = gpio_pin_write_logic(&(seg->segment_pin[3]), seg->segment_pin[3].logic);

}
return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return 
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
Std_ReturnType ret = E_OK;
if((NULL == seg) || (number > 9)){
    ret = E_NOT_OK;
}
else {
    ret = gpio_pin_write_logic(&(seg->segment_pin[0]),(number & 0x01));
    ret = gpio_pin_write_logic(&(seg->segment_pin[1]),((number >>1) & 0x01));
    ret = gpio_pin_write_logic(&(seg->segment_pin[2]),((number >>2) & 0x01));
    ret = gpio_pin_write_logic(&(seg->segment_pin[3]),((number >>3) & 0x01));
}
return ret;
}