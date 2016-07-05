#include <asf.h>
//#include "conf_at25dfx.h"

#define HIGH 1
#define LOW 0
#define CLEAR_TERMINAL 12

#define SIZE_VEC_SPEED 10		// Define the lenght of vector that saves the speed tests

//======================== Shift-light defines =====================================================

#define SHIFTPERIOD 10

//======================== Flash Memory defines ====================================================

#define FLASH_ADDR_INIT 0x0000
#define BLOCK_SIZE 4096		// Size of the blocks of flash memory
#define RPM_ADDR_FLASH_MEM BLOCK_SIZE*1
#define MORESPEED_ADDR_FLASH_MEM BLOCK_SIZE*2

//======================== UART settings ===========================================================

//===== COM ============================================
#define UART_COM_BAUDRATE 250000;
#define UART_COM_MUX_SETTING EDBG_CDC_SERCOM_MUX_SETTING;
#define UART_COM_PINMUX_PAD0 EDBG_CDC_SERCOM_PINMUX_PAD0;
#define UART_COM_PINMUX_PAD1 EDBG_CDC_SERCOM_PINMUX_PAD1;
#define UART_COM_PINMUX_PAD2 EDBG_CDC_SERCOM_PINMUX_PAD2;
#define UART_COM_PINMUX_PAD3 EDBG_CDC_SERCOM_PINMUX_PAD3;
#define UART_COM_MODULE EDBG_CDC_MODULE

//===== OBD ============================================
// SERCOM4
#define PIN_TX PIN_PB08
#define UART_OBD_BAUDRATE 10400;
#define UART_OBD_MUX_SETTING EXT1_UART_SERCOM_MUX_SETTING;
#define UART_OBD_PINMUX_PAD0 EXT1_UART_SERCOM_PINMUX_PAD0;
#define UART_OBD_PINMUX_PAD1 EXT1_UART_SERCOM_PINMUX_PAD1;
#define UART_OBD_PINMUX_PAD2 EXT1_UART_SERCOM_PINMUX_PAD2;
#define UART_OBD_PINMUX_PAD3 EXT1_UART_SERCOM_PINMUX_PAD3;
#define UART_OBD_MODULE EXT1_UART_MODULE

// SERCOM4
// #define PIN_TX PIN_PB10
// #define UART_OBD_BAUDRATE 10400;
// #define UART_OBD_MUX_SETTING EXT2_UART_SERCOM_MUX_SETTING;
// #define UART_OBD_PINMUX_PAD0 EXT2_UART_SERCOM_PINMUX_PAD0;
// #define UART_OBD_PINMUX_PAD1 EXT2_UART_SERCOM_PINMUX_PAD1;
// #define UART_OBD_PINMUX_PAD2 EXT2_UART_SERCOM_PINMUX_PAD2;
// #define UART_OBD_PINMUX_PAD3 EXT2_UART_SERCOM_PINMUX_PAD3;
// #define UART_OBD_MODULE EXT2_UART_MODULE
// 
//SERCOM4
// #define PIN_TX PIN_PB10
// #define UART_OBD_BAUDRATE 10400;
// #define UART_OBD_MUX_SETTING EXT3_UART_SERCOM_MUX_SETTING;
// #define UART_OBD_PINMUX_PAD0 EXT3_UART_SERCOM_PINMUX_PAD0;
// #define UART_OBD_PINMUX_PAD1 EXT3_UART_SERCOM_PINMUX_PAD1;
// #define UART_OBD_PINMUX_PAD2 EXT3_UART_SERCOM_PINMUX_PAD2;
// #define UART_OBD_PINMUX_PAD3 EXT3_UART_SERCOM_PINMUX_PAD3;
// #define UART_OBD_MODULE EXT3_UART_MODULE


typedef enum formatos_retorno {HEX, DEC, STR}formatos_retorno;

typedef struct improveSpeed {
	uint16_t speed[SIZE_VEC_SPEED];
	uint16_t first;
	uint16_t last;
	uint16_t empty;
}improveSpeed;

enum
{
	working,
	err,
	menu,
	
	//func
	load,
	load_v1, load_v2,
	
	vm,
	save_vm,
	
	sl,
	shift_mon,
	
	pid,
	mon1, mon2, mon3,
	
	PID0x03, PID0x04, PID0x05, PID0x06,	PID0x07, PID0x0B, PID0x0C,
	PID0x0D, PID0x0E, PID0x0F, PID0x11, PID0x13, PID0x15, PID0x21,
	
	sel_PID0x03, sel_PID0x04, sel_PID0x05, sel_PID0x06,	sel_PID0x07, sel_PID0x0B, sel_PID0x0C,
	sel_PID0x0D, sel_PID0x0E, sel_PID0x0F, sel_PID0x11, sel_PID0x13, sel_PID0x15, sel_PID0x21,
};

enum
{
	idle,
	reset,
	update_vtable,
	update_vm,
	write_vm,
	update_shift,
	erase_vtable,
	update_mon,
	update_pid
};

//======================== UART functions =========================================================


void uartSend(uint8_t data);

uint8_t uartReceive(uint8_t* received);

void uartClear();

void uartInit();

void uartSetTXasDigital();

//========================== PIN functions ========================================================


void pinOutCtrl(uint8_t gpio_pin, uint8_t state);



//========================== IHM functions ========================================================

void printIHM ( const char * format, ... );

void comInit();

void comSend(uint8_t data);

void comSendString(char buffer[]);

uint8_t comReceive(uint8_t* received);

void comClear();

//========================== Flash Memory Functions ================================================


static void at25dfx_init(void);

void writeFlashMemory(const void *data, at25dfx_datalen_t length, at25dfx_address_t address);

void readFlashMemory(const void *data, at25dfx_datalen_t length, at25dfx_address_t address);

void clearFlashMemory();

//========================== MAIN functions ========================================================


uint8_t shift_light(bool *lightShift, bool *shiftLight, uint16_t RPM_Salvo);

void setDefaultValues();

void initialize(uint16_t *RPM_Salvo, improveSpeed *moreSpeed);