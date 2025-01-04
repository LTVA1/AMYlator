#include "amy.h"

AMY* amy_create()
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
    amy->reg_a = data;
}

void amy_write_reg_b(AMY* amy, uint8_t data)
{
    amy->reg_b = data;
}

void amy_write_reg_c(AMY* amy, uint8_t data)
{
    amy->reg_c = data;
}

void amy_write_reg_command(AMY* amy, uint8_t data)
{
    if((data & AMY_FREQ_ENV_BREAKPOINT_CMD_MASK) == AMY_FREQ_ENV_BREAKPOINT_CMD_CODE)
    {
        return;
    }
    if((data & AMY_VOICE_TYPE_CMD_MASK) == AMY_VOICE_TYPE_CMD_CODE)
    {
        return;
    }
    if((data & AMY_READ_CURR_FREQ_CMD_MASK) == AMY_READ_CURR_FREQ_CMD_CODE)
    {
        return;
    }
    if((data & AMY_SYSTEM_OPTIONS_CMD_MASK) == AMY_SYSTEM_OPTIONS_CMD_CODE)
    {
        return;
    }
    if((data & AMY_CONTROL_CMD_MASK) == AMY_CONTROL_CMD_CODE)
    {
        return;
    }
    if((data & AMY_VOL_ENV_BREAKPOINT_CMD_MASK) == AMY_VOL_ENV_BREAKPOINT_CMD_CODE)
    {
        return;
    }
    if((data & AMY_HARM_PAIR_NOISE_RAM_CMD_MASK) == AMY_HARM_PAIR_NOISE_RAM_CMD_CODE)
    {
        return;
    }
    if((data & AMY_READ_CURR_VOL_ENV_CMD_MASK) == AMY_READ_CURR_VOL_ENV_CMD_CODE)
    {
        return;
    }
}

uint8_t amy_read_reg_a(AMY* amy)
{
    return amy->reg_a;
}

uint8_t amy_read_reg_b(AMY* amy)
{
    return amy->reg_b;
}

uint8_t amy_read_reg_c(AMY* amy)
{
    return amy->reg_c;
}

void amy_clock(AMY* amy) //one sound sample
{

}

void amy_fill_buffer(AMY* amy, int16_t* buffer, uint32_t length)
{

}

void amy_set_is_muted(AMY* amy, uint8_t ch, bool mute)
{
    amy->muted[ch] = mute;
}