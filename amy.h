#ifndef AMY_H
#define AMY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define AMY_NUM_CHANNELS 8
#define AMY_NUM_HARMONIC_OSCILLATORS 64
#define AMY_NUM_NOISE_GENERATORS 2

#define AMY_NUM_REGISTERS 4

#define AMY_SIN_ROM_SIZE 4096
#define AMY_EXP_ROM_SIZE 4096

#define AMY_FREQ_ENV_BREAKPOINT_CMD_CODE 0b00001000
#define AMY_VOICE_TYPE_CMD_CODE 0b00010000
#define AMY_READ_CURR_FREQ_CMD_CODE 0b00011000
#define AMY_SYSTEM_OPTIONS_CMD_CODE 0b00100000
#define AMY_CONTROL_CMD_CODE 0b00110000
#define AMY_VOL_ENV_BREAKPOINT_CMD_CODE 0b01000000
#define AMY_HARM_PAIR_NOISE_RAM_CMD_CODE 0b10000000
#define AMY_READ_CURR_VOL_ENV_CMD_CODE 0b11000000

#define AMY_FREQ_ENV_BREAKPOINT_CMD_MASK 0b11111000
#define AMY_VOICE_TYPE_CMD_MASK 0b11111000
#define AMY_READ_CURR_FREQ_CMD_MASK 0b11111000
#define AMY_SYSTEM_OPTIONS_CMD_MASK 0b11110000
#define AMY_CONTROL_CMD_MASK 0b11110000
#define AMY_VOL_ENV_BREAKPOINT_CMD_MASK 0b11000000
#define AMY_HARM_PAIR_NOISE_RAM_CMD_MASK 0b11000000
#define AMY_READ_CURR_VOL_ENV_CMD_MASK 0b11000000

typedef struct
{
    uint8_t slope;
    uint8_t destination;
    uint16_t curr_val;
    bool running;
    uint8_t counter;
} amy_volume_envelope;

typedef struct
{
    amy_volume_envelope env;
    uint32_t curr_phase;
} amy_harmonic_oscillator;

typedef struct
{
    uint8_t slope;
    uint16_t destination;
    uint32_t curr_val;
    bool running;
    uint8_t counter;
} amy_freq_envelope;

typedef struct
{
    amy_freq_envelope env;
    uint8_t type;
} amy_channel;

typedef struct
{
    uint16_t lfsr;
    uint16_t freq; //up-down counter?
    uint16_t noise_val; //noise value bits?
    uint16_t shift_control; //shift control bits?
} amy_noise_generator;

typedef struct
{
    uint16_t sin_rom[AMY_SIN_ROM_SIZE];
    uint16_t exp_rom[AMY_EXP_ROM_SIZE];

    amy_noise_generator noise_gen[AMY_NUM_NOISE_GENERATORS];
    amy_channel chan[AMY_NUM_CHANNELS];
    amy_harmonic_oscillator harm_osc[AMY_NUM_HARMONIC_OSCILLATORS];
    uint32_t harmonic_pair_flags;
    uint8_t reg_a;
    uint8_t reg_b;
    uint8_t reg_c;
    bool forty_harm; //system options register
    bool individual_mode;
    bool int_mode;
    bool ale_mode;
    bool nzinit; //system control register
    bool seq_reset;

    // debug/emulation/Furnace tracker helpers:
    int16_t channel_output[AMY_NUM_CHANNELS];
    bool muted[AMY_NUM_CHANNELS];
    int16_t output;
} AMY;

AMY* amy_create();
void amy_reset(AMY* amy);
void amy_free(AMY* amy);

void amy_write_reg_a(AMY* amy, uint8_t data);
void amy_write_reg_b(AMY* amy, uint8_t data);
void amy_write_reg_c(AMY* amy, uint8_t data);
void amy_write_reg_command(AMY* amy, uint8_t data);

uint8_t amy_read_reg_a(AMY* amy);
uint8_t amy_read_reg_b(AMY* amy);
uint8_t amy_read_reg_c(AMY* amy);

void amy_clock(AMY* amy); //one sound sample
void amy_fill_buffer(AMY* amy, int16_t* buffer, uint32_t length);

// debug/emulation/Furnace tracker helpers:
void amy_set_is_muted(AMY* amy, uint8_t ch, bool mute);

#ifdef __cplusplus
};
#endif
#endif
