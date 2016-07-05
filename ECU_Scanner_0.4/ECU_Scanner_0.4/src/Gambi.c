#include <stdarg.h>
#include <asf.h>
#include "OBDII-std.h"
#include "PID_interpreter.h"
#include "Gambi.h"
#include "conf_at25dfx.h"

uint8_t dataReceived;


struct usart_module uart_com;
struct usart_module uart_OBD;

uint8_t flashMemWrited = 0xAB;

data_struct** PIDTable;

uint16_t timingShift = 0;

struct spi_module at25dfx_spi;
struct at25dfx_chip_module at25dfx_chip;
	


//======================== UART functions ========================================================= 


void uartSend(uint8_t data){
  while (usart_write_wait(&uart_OBD, data) != STATUS_OK) {
  }
}

uint8_t uartReceive(uint8_t* received)
{
  if (usart_read_wait(&uart_OBD, received) != STATUS_OK) return 1; 
  else return 0;
}

void uartClear()
{
  while(usart_read_wait(&uart_OBD, &dataReceived) != STATUS_BUSY){} // Clear all data of buffers
}

void uartInit()
{
  struct usart_config config_usart;
  usart_get_config_defaults(&config_usart);
  config_usart.baudrate    = UART_OBD_BAUDRATE;
  config_usart.mux_setting = UART_OBD_MUX_SETTING;
  config_usart.pinmux_pad0 = UART_OBD_PINMUX_PAD0;
  config_usart.pinmux_pad1 = UART_OBD_PINMUX_PAD1;
  config_usart.pinmux_pad2 = UART_OBD_PINMUX_PAD2;
  config_usart.pinmux_pad3 = UART_OBD_PINMUX_PAD3;
  while (usart_init(&uart_OBD, UART_OBD_MODULE, &config_usart) != STATUS_OK) {
  }
  usart_enable(&uart_OBD);
}

void uartSetTXasDigital()     // This function is very especific.
{                             // Preferably this pin should already set high.
  usart_disable(&uart_OBD);     // Disable the UART_OBD

  struct port_config config_port_pin;
  port_get_config_defaults(&config_port_pin);
  config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
  config_port_pin.input_pull = PORT_PIN_PULL_UP;
  port_pin_set_config(PIN_TX, &config_port_pin);  // Set the PIN_TX of uart_OBD to output

  port_pin_set_output_level(PIN_TX, true);        // Set High to PIN_TX
}

//========================== PIN functions ========================================================


void pinOutCtrl(uint8_t gpio_pin, uint8_t state)
{
  if(state) port_pin_set_output_level(gpio_pin, true);        // Set PIN High
  else port_pin_set_output_level(gpio_pin, false);            // Set PIN low
}



//========================== IHM functions ========================================================

void printIHM ( const char * format, ... )
{
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);
	comSendString(buffer);
}


void comInit()
{
  struct usart_config config_usart;
  usart_get_config_defaults(&config_usart);
  config_usart.baudrate    = UART_COM_BAUDRATE;
  config_usart.mux_setting = UART_COM_MUX_SETTING;
  config_usart.pinmux_pad0 = UART_COM_PINMUX_PAD0;
  config_usart.pinmux_pad1 = UART_COM_PINMUX_PAD1;
  config_usart.pinmux_pad2 = UART_COM_PINMUX_PAD2;
  config_usart.pinmux_pad3 = UART_COM_PINMUX_PAD3;
  while (usart_init(&uart_com, UART_COM_MODULE, &config_usart) != STATUS_OK) {
  }
  usart_enable(&uart_com);
}

void comSend(uint8_t data){
  while (usart_write_wait(&uart_com, data) != STATUS_OK) {
  }
}

void comSendString(char buffer[])
{
	uint16_t loop=0;
	do
	{
		comSend(buffer[loop]);
		loop++;
	}while(buffer[loop] != '\0');
}

uint8_t comReceive(uint8_t* received)
{
  if (usart_read_wait(&uart_com, received) != STATUS_OK) return 1; 
  else return 0;
}

void comClear()
{
  while(usart_read_wait(&uart_com, &dataReceived) != STATUS_BUSY){} // Clear all data of buffers
}

//========================== Flash Memory Functions ================================================


static void at25dfx_init(void)
{
	struct at25dfx_chip_config at25dfx_chip_config;
	struct spi_config at25dfx_spi_config;	

	at25dfx_spi_get_config_defaults(&at25dfx_spi_config);
	at25dfx_spi_config.mode_specific.master.baudrate = AT25DFX_CLOCK_SPEED;
	at25dfx_spi_config.mux_setting = AT25DFX_SPI_PINMUX_SETTING;
	at25dfx_spi_config.pinmux_pad0 = AT25DFX_SPI_PINMUX_PAD0;
	at25dfx_spi_config.pinmux_pad1 = AT25DFX_SPI_PINMUX_PAD1;
	at25dfx_spi_config.pinmux_pad2 = AT25DFX_SPI_PINMUX_PAD2;
	at25dfx_spi_config.pinmux_pad3 = AT25DFX_SPI_PINMUX_PAD3;

	spi_init(&at25dfx_spi, AT25DFX_SPI, &at25dfx_spi_config);
	spi_enable(&at25dfx_spi);
		

	at25dfx_chip_config.type = AT25DFX_MEM_TYPE;
	at25dfx_chip_config.cs_pin = AT25DFX_CS;

	at25dfx_chip_init(&at25dfx_chip, &at25dfx_spi, &at25dfx_chip_config);
}

void writeFlashMemory(const void *data, at25dfx_datalen_t length, at25dfx_address_t address)
{
	at25dfx_chip_wake(&at25dfx_chip);
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);
	
	at25dfx_chip_erase_block(&at25dfx_chip, address, AT25DFX_BLOCK_SIZE_4KB);
	at25dfx_chip_write_buffer(&at25dfx_chip, address, data, length);
	
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, true);
	at25dfx_chip_sleep(&at25dfx_chip);	
}

void readFlashMemory(const void *data, at25dfx_datalen_t length, at25dfx_address_t address)
{
	at25dfx_chip_wake(&at25dfx_chip);
	at25dfx_chip_read_buffer(&at25dfx_chip, address, data, length);
	at25dfx_chip_sleep(&at25dfx_chip);	
}

void clearFlashMemory()
{
	int loop;
	at25dfx_chip_wake(&at25dfx_chip);
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, false);
	for (loop=0; loop<16; loop++)
	{
		at25dfx_chip_erase_block(&at25dfx_chip, BLOCK_SIZE*16*loop, AT25DFX_BLOCK_SIZE_64KB);
	}
	at25dfx_chip_set_global_sector_protect(&at25dfx_chip, true);
	at25dfx_chip_sleep(&at25dfx_chip);	
}

//========================== MAIN functions ========================================================



uint8_t shift_light(bool *lightShift, bool *shiftLight, uint16_t RPM_Salvo)
{
	float A = PIDTable[0x0C]->data[0];
	float B = PIDTable[0x0C]->data[1];

	A = (256*A + B)/4;
	
	if ((uint16_t) A < RPM_Salvo)
	{
		printIHM("\n                               Engine RPM: %d RPM\n", (int) A);
		*shiftLight = false;
	}
	else
	{
		timingShift++;
		if (timingShift == SHIFTPERIOD)
			timingShift = 0;
		
		*shiftLight = true;
		if (timingShift < (SHIFTPERIOD/2)) *lightShift = false;
		else *lightShift = true;
		
		if (*lightShift == true) printIHM("\n****************************** Engine RPM: %d RPM  ******************************\n", (int) A);
		else printIHM("\n############################## Engine RPM: %d RPM  ##############################\n", (int) A);
	}
}

void setDefaultValues()
{
	
	printIHM("\nLimpando dados da memoria:\n");
	
	clearFlashMemory();
	
	printIHM("\n\nA memoria flash teve seus dados totalmente excluidos. Aperte qualquer tecla para reiniciar.\n");
	
	while(comReceive(&dataReceived)){}      // Enquanto não receber dados da COM

}


void initialize(uint16_t *RPM_Salvo, improveSpeed *moreSpeed)
{
	comInit();
	comSend(CLEAR_TERMINAL);
	printIHM("\nECU Scanner\n");
	printIHM("Iniciando...");
	delay_ms(2000);

	at25dfx_init();
	
	at25dfx_chip_wake(&at25dfx_chip);
	
	if (at25dfx_chip_check_presence(&at25dfx_chip) != STATUS_OK) {
		printIHM("\nProblemas na inicializacao da flash\n");
	}
	else printIHM("\n\nFlash ok\n");
	
	uint8_t readFlash;
	readFlashMemory(&readFlash, sizeof(uint8_t), FLASH_ADDR_INIT);
	
	if (readFlash == flashMemWrited)
	{
		printIHM("\nJa existem dados salvos\n");	
		
		readFlashMemory(RPM_Salvo, sizeof(uint16_t), RPM_ADDR_FLASH_MEM);
		readFlashMemory(moreSpeed, sizeof(improveSpeed), MORESPEED_ADDR_FLASH_MEM);
	}
	else
	{
		printIHM("\nNao existem dados salvos\n");
		
		writeFlashMemory(&flashMemWrited, sizeof(uint8_t), FLASH_ADDR_INIT);
		
		writeFlashMemory(RPM_Salvo, sizeof(uint16_t), RPM_ADDR_FLASH_MEM);
		
		writeFlashMemory(moreSpeed, sizeof(improveSpeed), MORESPEED_ADDR_FLASH_MEM);
	}
	
	initPIDs();

	PIDTable = getPIDTable();
}