#include "amy.h"

AMY* amy_init()
{
    AMY* amy = (AMY*)malloc(sizeof(AMY));
    return amy;
}

void amy_reset(AMY* amy)
{
    memset((void*)amy, 0, sizeof(AMY));
}

void amy_free(AMY* amy)
{
    free(amy);
}

void amy_write_reg_a(AMY* amy, uint8_t data)
{

}

void amy_write_reg_b(AMY* amy, uint8_t data)
{

}

void amy_write_reg_c(AMY* amy, uint8_t data)
{

}

void amy_write_reg_command(AMY* amy, uint8_t data)
{

}

void amy_fill_buffer(AMY* amy, int16_t* buffer, uint32_t length)
{
    
}