#include "OBDII-std.h"
#include "Gambi.h"
#include "PID_interpreter.h"


// 0 -> PIDs suportados -> de 1 a 20
uint8_t PID00_funct(data_struct* data)
{
  uint8_t aux;
  // Data A
  aux = data->data[0];
  if(aux & 0x80) printIHM("PID01 = YES\n");  // Test if the MSB is 1
  else printIHM("PID01 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID02 = YES\n");  // Test if the MSB is 1
  else printIHM("PID02 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID03 = YES\n");  // Test if the MSB is 1
  else printIHM("PID03 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID04 = YES\n");  // Test if the MSB is 1
  else printIHM("PID04 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID05 = YES\n");  // Test if the MSB is 1
  else printIHM("PID05 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID06 = YES\n");  // Test if the MSB is 1
  else printIHM("PID06 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID07 = YES\n");  // Test if the MSB is 1
  else printIHM("PID07 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID08 = YES\n");  // Test if the MSB is 1
  else printIHM("PID08 = NO\n");


  // Data B
  aux = data->data[1];
  if(aux & 0x80) printIHM("PID09 = YES\n");  // Test if the MSB is 1
  else printIHM("PID09 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0A = YES\n");  // Test if the MSB is 1
  else printIHM("PID0A = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0B = YES\n");  // Test if the MSB is 1
  else printIHM("PID0B = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0C = YES\n");  // Test if the MSB is 1
  else printIHM("PID0C = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0D = YES\n");  // Test if the MSB is 1
  else printIHM("PID0D = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0E = YES\n");  // Test if the MSB is 1
  else printIHM("PID0E = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID0F = YES\n");  // Test if the MSB is 1
  else printIHM("PID0F = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID10 = YES\n");  // Test if the MSB is 1
  else printIHM("PID10 = NO\n");


  // Data C
  aux = data->data[2];
  if(aux & 0x80) printIHM("PID11 = YES\n");  // Test if the MSB is 1
  else printIHM("PID11 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID12 = YES\n");  // Test if the MSB is 1
  else printIHM("PID12 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID13 = YES\n");  // Test if the MSB is 1
  else printIHM("PID13 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID14 = YES\n");  // Test if the MSB is 1
  else printIHM("PID14 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID15 = YES\n");  // Test if the MSB is 1
  else printIHM("PID15 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID16 = YES\n");  // Test if the MSB is 1
  else printIHM("PID16 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID17 = YES\n");  // Test if the MSB is 1
  else printIHM("PID17 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID18 = YES\n");  // Test if the MSB is 1
  else printIHM("PID18 = NO\n");


  // Data D
  aux = data->data[3];
  if(aux & 0x80) printIHM("PID19 = YES\n");  // Test if the MSB is 1
  else printIHM("PID19 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1A = YES\n");  // Test if the MSB is 1
  else printIHM("PID1A = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1B = YES\n");  // Test if the MSB is 1
  else printIHM("PID1B = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1C = YES\n");  // Test if the MSB is 1
  else printIHM("PID1C = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1D = YES\n");  // Test if the MSB is 1
  else printIHM("PID1D = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1E = YES\n");  // Test if the MSB is 1
  else printIHM("PID1E = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID1F = YES\n");  // Test if the MSB is 1
  else printIHM("PID1F = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID20 = YES\n");  // Test if the MSB is 1
  else printIHM("PID20 = NO\n");

  return 0;
}


// 1 -> Monitor status since DTCs cleared -> 4 bytes
//	The bits in this PID shall report two pieces of information for each monitor: 
//	⎯ monitor status since DTCs were last cleared, saved in NVRAM or Keep Alive RAM; and 
//	⎯ monitors supported on this vehicle. 
//
//    A : 
//      A7 : MIL -> ON | OFF
//      A6 - A0 : DTC_CNT -> vlr

//    B:
//      B7 : 0
//      B6 : Comprehensive component monitoring ready : CCM_RDY -> YES | NO
//      B5 : Fuel system monitoring ready : FUEL_RDY -> YES | NO
//      B4 : Misfire monitoring ready : MIS_RDY -> YES | NO
//      B3 : 0
//      B2 : Comprehensive component monitoring supported : CCM_SUP -> YES | NO
//      B1 : Fuel system monitoring supported
//      B0 : Misfire monitoring supported: MIS_SUP -> YES | NO

//    C:
//      C7 : EGR system monitoring supported : EGR_SUP -> YES | NO
//      C6 : Oxygen sensor heater monitoring supported : HTR_SUP ->  YES | NO
//      C5 : Oxygen sensor monitoring supported : 02S_SUP -> YES | NO
//      C4 : A/C system refrigerant monitoring supported : ACRF_SUP -> YES | NO
//      C3 : Secondary air system monitoring supported : AIR_SUP -> YES | NO
//      C2 : Evaporative system monitoring supported : EVAP_SUP -> YES | NO
//      C1 : Heated catalyst monitoring supported : HCAT_SUP -> YES | NO
//      C0 : Catalyst monitoring supported : CAT_SUP -> YES | NO

//    D:
//      D7 : EGR system montoring ready : EGR_RDY -> YES | NO
//      D6 : Oxygen sensor heater monitoring ready : HTR_RDY ->  YES | NO
//      D5 : Oxygen sensor monitoring ready : 02S_RDY -> YES | NO
//      D4 : A/C system refrigerant monitoring ready : ACRF_RDY -> YES | NO
//      D3 : Secondary air system monitoring ready : AIR_RDY -> YES | NO
//      D2 : Evaporative system monitoring ready : EVAP_RDY -> YES | NO
//      D1 : Heated catalyst monitoring ready : HCAT_RDY -> YES | NO
//      D0 : Catalyst monitoring ready : CAT_RDY -> YES | NO
uint8_t PID01_funct(data_struct* data)
{
	uint8_t aux;
	aux = data->data[0];	// Take the byte "A"
	if (aux & 0x80) printIHM("Malfunction Indicator Lamp (MIL) is ON\n");
	else printIHM("Malfunction Indicator Lamp (MIL) is OFF\n");
	
	aux &= 0x7F;		// Take only 6-0 bits
	printIHM("Diagnostic Trouble Codes on the memory of ECU: %d\n", aux);
	
	printIHM("\nMonitors supported:\n");
	aux = data->data[1];
	if(aux & 0x01)	printIHM("YES:  \tMisfire monitoring supported\n");
	else printIHM("NO:  \tMisfire monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tFuel system monitoring supported\n");
	else printIHM("NO:  \tFuel system monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tComprehensive component monitoring supported\n");
	else printIHM("NO:  \tComprehensive component monitoring supported\n");
	
	aux = data->data[2];
	if(aux & 0x01)	printIHM("YES:  \tCatalyst monitoring supported\n");
	else printIHM("NO:  \tCatalyst monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tHeated catalyst monitoring supported\n");
	else printIHM("NO:  \tHeated catalyst monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tEvaporative system monitoring supported\n");
	else printIHM("NO:  \tEvaporative system monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tSecondary air system monitoring supported\n");
	else printIHM("NO:  \tSecondary air system monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tA/C system refrigerant monitoring supported\n");
	else printIHM("NO:  \tA/C system refrigerant monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tOxygen sensor monitoring supported\n");
	else printIHM("NO:  \tOxygen sensor monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tOxygen sensor heater monitoring supported\n");
	else printIHM("NO:  \tOxygen sensor heater monitoring supported\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tEGR system monitoring supported\n");
	else printIHM("NO:  \tEGR system monitoring supported\n");

	printIHM("\nMonitors ready:\n");
	aux = data->data[1];
	aux = aux >> 4;		// shift bit 4 to LSB
	if(aux & 0x01)	printIHM("YES:  \tMisfire monitoring ready\n");
	else printIHM("NO:  \tMisfire monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:	\tFuel system monitoring ready\n");
	else printIHM("NO:  \tFuel system monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:	\tComprehensive component monitoring ready\n");
	else printIHM("NO:  \tComprehensive component monitoring ready\n");
	
	aux = data->data[3];
	if(aux & 0x01)	printIHM("YES:  \tCatalyst monitoring ready\n");
	else printIHM("NO:  \tCatalyst monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tHeated catalyst monitoring ready\n");
	else printIHM("NO:  \tHeated catalyst monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tEvaporative system monitoring ready\n");
	else printIHM("NO:  \tEvaporative system monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tSecondary air system monitoring ready\n");
	else printIHM("NO:  \tSecondary air system monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tA/C system refrigerant monitoring ready\n");
	else printIHM("NO:  \tA/C system refrigerant monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tOxygen sensor monitoring ready\n");
	else printIHM("NO:  \tOxygen sensor monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tOxygen sensor heater monitoring ready\n");
	else printIHM("NO:  \tOxygen sensor heater monitoring ready\n");
	aux = aux >> 1;
	if(aux & 0x01)	printIHM("YES:  \tEGR system monitoring ready\n");
	else printIHM("NO:  \tEGR system monitoring ready\n");

	return 0;
}


// 3 -> Fuel System Status 1 and 2 -> 2 bytes
//    A = System 1
//    B = System 2
//    Results:
//	Bit:
//	0	Open loop - has not yet satisfied conditions to go closed loop
//	1	Closed loop - using oxygen sensor(s) as feedback for fuel control
//	2	Open loop due to driving conditions (e.g. power enrichment, deceleration enleanment)
//	3	Open loop - due to detected system fault OL-Fault
//	4	Closed loop, but fault with at least one oxygen sensor - may be using single oxygen sensor for fuel control
//	5-7	ISO/SAE reserved (bits shall be reported as ‘0’)
// Only one bit by bank can be set one
// If all bit of bank are '0' then the bank don't exists on system

uint8_t PID03_funct(data_struct* data)
{
	uint8_t aux;
	aux = data->data[0];
	printIHM("Fuel system 1: (if more than 1 response, an error occoured)\n");
	if(aux)
	{
		if(aux & 0x80) printIHM("\tUnkdown response bit[7]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tUnkdown response bit[6]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tUnkdown response bit[5]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tClosed loop, but fault with at least one oxygen sensor - may be using single oxygen sensor for fuel control\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop - due to detected system fault\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop due to driving conditions (e.g. power enrichment, deceleration enleanment)\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tClosed loop - using oxygen sensor(s) as feedback for fuel control\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop - has not yet satisfied conditions to go closed loop\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
	}
	else printIHM("\tFuel system 1 is not present\n");
	
	aux = data->data[1];
	printIHM("Fuel system 2: (if more than 1 response, an error occoured)\n");
	if(aux)
	{
		if(aux & 0x80) printIHM("\tUnkdown response bit[7]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tUnkdown response bit[6]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tUnkdown response bit[5]\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tClosed loop, but fault with at least one oxygen sensor - may be using single oxygen sensor for fuel control\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop - due to detected system fault\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop due to driving conditions (e.g. power enrichment, deceleration enleanment)\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tClosed loop - using oxygen sensor(s) as feedback for fuel control\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
		if(aux & 0x80) printIHM("\tOpen loop - has not yet satisfied conditions to go closed loop\n");  // Test if the MSB is 1
		aux = aux << 1;     // Shift one bit to left
	}
	else printIHM("\tFuel system 2 is not present\n");
	
	return 0;
}


// 4 -> Calculated LOAD Value -> 1 byte
//  A*100/255 0 -> 100 %
uint8_t PID04_funct(data_struct* data)
{
  float A = data->data[0];
  A = (A*100)/255;
  printIHM("Engine Load: %d %%\n", (int)A);

  return 0;
}


// 5 -> Engine coolant temperature -> 1 byte
//  A-40    -40 -> 215 °C
uint8_t PID05_funct(data_struct* data)
{
  int16_t A = data->data[0];
  A = (A-40);
  printIHM("Engine coolant temperature: %d °C\n", A);

  return 0;
}


// 6 -> Short Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID06_funct(data_struct* data)
{
  float A = data->data[0];
  A = ((A*100)/128)-100;
  printIHM("Short Term Fuel Trim: %d %%\n", (int)A);

  return 0;
}


// 7 -> Long Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID07_funct(data_struct* data)
{
  float A = data->data[0];
  A = ((A*100)/128)-100;

  printIHM("Long Term Fuel Trim: %d %%\n", (int)A);

  return 0;
}


// B -> Intake Manifold Absolute Pressure -> 1 byte
//  A       0 kPa -> 255 kPa
uint8_t PID0B_funct(data_struct* data)
{
  printIHM("Intake Manifold Absolute Pressure: %d kPa\n", data->data[0]);

  return 0;
}


// C -> Engine RPM -> 2 bytes
//  (256*A + B)/4   0 RPM -> 16383.75
uint8_t PID0C_funct(data_struct* data)
{
  float A = data->data[0];
  float B = data->data[1];

  A = (256*A + B)/4;

  printIHM("Engine RPM: %d RPM\n", (int) A);

  return 0;
}


// D -> Vehicle speed -> 1 byte 
uint8_t PID0D_funct(data_struct* data)
{
  printIHM("Speed: %d km/h\n", (data->data[0]));

  return 0;
}


// E -> Timing Advanced -> 1 byte
//  (A/2) - 64    -64 -> 63.5 ° before TDC (ponto máximo do pistão)
uint8_t PID0E_funct(data_struct* data)
{
  float A = data->data[0];
  A = (A/2)-64;
  printIHM("Timing Advanced: %d °\n", (int)A);

  return 0;
}


// F -> Intake air temperature  -> 1 byte
//  A-40        -40 -> 215 °C
uint8_t PID0F_funct(data_struct* data)
{
  int16_t A = data->data[0];
  A = (A-40);
  printIHM("Intake air temperature: %d °C\n", A);

  return 0;
}


// 11 -> Throttle position -> 1 byte
//  A*100/255   0 -> 100%
uint8_t PID11_funct(data_struct* data)
{
  float A = data->data[0];
  A = (A*100)/255;

  printIHM("Throttle position: %d %%\n", (int) A);

  return 0;
}


// 13 -> Oxygen sensors present -> 1 Byte
//  Bits [0-3] -> sensors 1-4 -> Bank1
//  Bits [4-7] -> sensors 5-8 -> Bank2
uint8_t PID13_funct(data_struct* data)
{
  uint8_t aux;
  // Data A
  aux = data->data[0];
  printIHM("Oxygen sensors:\nBank2\n");
  if(aux & 0x80) printIHM("8 = YES\n");  // Test if the MSB is 1
  else printIHM("8 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("7 = YES\n");  // Test if the MSB is 1
  else printIHM("7 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("6 = YES\n");  // Test if the MSB is 1
  else printIHM("6 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("5 = YES\n");  // Test if the MSB is 1
  else printIHM("5 = NO\n");

  printIHM("Bank1\n");
  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("4 = YES\n");  // Test if the MSB is 1
  else printIHM("4 = NO\n");
  
  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("3 = YES\n");  // Test if the MSB is 1
  else printIHM("3 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("2 = YES\n");  // Test if the MSB is 1
  else printIHM("2 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("1 = YES\n");  // Test if the MSB is 1
  else printIHM("1 = NO\n");

  return 0;
}


// 15 -> Oxygen Sensor 2 -> 2 bytes
//    A : voltage   A/200   0 -> 1.275 V
//    B : Short term fuel trim (B*100/128)-100
uint8_t PID15_funct(data_struct* data)
{
  float A, B;
  A = data->data[0];
  A = (A*10)/2000;

  B = data->data[1];
  B = ((B*100)/128)-100;

  printIHM("Oxygen sensor 2: %d V(x1000)  %d %%\n", (int) A*1000, (int) B);

  return 0;
}


// 1C -> OBD standards this vehicle conforms to -> 1 byte
uint8_t PID1C_funct(data_struct* data)
{
  printIHM("PID1C nao implementado\n");

  return 0;
}


// #20 -> PIDs suportados -> de 21 a 40
uint8_t PID20_funct(data_struct* data)
{
  uint8_t aux;
  // Data A
  aux = data->data[0];
  if(aux & 0x80) printIHM("PID21 = YES\n");  // Test if the MSB is 1
  else printIHM("PID21 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID22 = YES\n");  // Test if the MSB is 1
  else printIHM("PID22 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID23 = YES\n");  // Test if the MSB is 1
  else printIHM("PID23 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID24 = YES\n");  // Test if the MSB is 1
  else printIHM("PID24 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID25 = YES\n");  // Test if the MSB is 1
  else printIHM("PID25 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID26 = YES\n");  // Test if the MSB is 1
  else printIHM("PID26 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID27 = YES\n");  // Test if the MSB is 1
  else printIHM("PID27 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID28 = YES\n");  // Test if the MSB is 1
  else printIHM("PID28 = NO\n");


  // Data B
  aux = data->data[1];
  if(aux & 0x80) printIHM("PID29 = YES\n");  // Test if the MSB is 1
  else printIHM("PID29 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2A = YES\n");  // Test if the MSB is 1
  else printIHM("PID2A = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2B = YES\n");  // Test if the MSB is 1
  else printIHM("PID2B = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2C = YES\n");  // Test if the MSB is 1
  else printIHM("PID2C = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2D = YES\n");  // Test if the MSB is 1
  else printIHM("PID2D = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2E = YES\n");  // Test if the MSB is 1
  else printIHM("PID2E = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID2F = YES\n");  // Test if the MSB is 1
  else printIHM("PID2F = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID30 = YES\n");  // Test if the MSB is 1
  else printIHM("PID30 = NO\n");


  // Data C
  aux = data->data[2];
  if(aux & 0x80) printIHM("PID31 = YES\n");  // Test if the MSB is 1
  else printIHM("PID31 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID32 = YES\n");  // Test if the MSB is 1
  else printIHM("PID32 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID33 = YES\n");  // Test if the MSB is 1
  else printIHM("PID33 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID34 = YES\n");  // Test if the MSB is 1
  else printIHM("PID34 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID35 = YES\n");  // Test if the MSB is 1
  else printIHM("PID35 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID36 = YES\n");  // Test if the MSB is 1
  else printIHM("PID36 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID37 = YES\n");  // Test if the MSB is 1
  else printIHM("PID37 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID38 = YES\n");  // Test if the MSB is 1
  else printIHM("PID38 = NO\n");


  // Data D
  aux = data->data[3];
  if(aux & 0x80) printIHM("PID39 = YES\n");  // Test if the MSB is 1
  else printIHM("PID39 = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3A = YES\n");  // Test if the MSB is 1
  else printIHM("PID3A = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3B = YES\n");  // Test if the MSB is 1
  else printIHM("PID3B = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3C = YES\n");  // Test if the MSB is 1
  else printIHM("PID3C = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3D = YES\n");  // Test if the MSB is 1
  else printIHM("PID3D = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3E = YES\n");  // Test if the MSB is 1
  else printIHM("PID3E = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID3F = YES\n");  // Test if the MSB is 1
  else printIHM("PID3F = NO\n");

  aux = aux << 1;     // Shift one bit to left
  if(aux & 0x80) printIHM("PID40 = YES\n");  // Test if the MSB is 1
  else printIHM("PID40 = NO\n");

  return 0;
}


// 21 -> Distance traveled with malfunction indicator lamp (MIL) on -> 2 bytes
//  256*A + B     0 -> 65535 Km
uint8_t PID21_funct(data_struct* data)
{
  uint16_t A = data->data[0];
  uint16_t B = data->data[1];
  A = (256*A)+B;

  printIHM("Distance traveled with MIL: %d km\n", A);

  return 0;
}


// 34 -> Oxygen Sensor 1 -> 4 bytes
//    A B : (256A+B)*2/65536    0 -> <2 Fuel-Air Equivalence Ratio 
//    C D : C - 128 + D/256   -128 -> 128 mA
uint8_t PID34_funct(data_struct* data)
{
  float A = data->data[0];
  float B = data->data[1];
  float C = data->data[2];
  float D = data->data[3];

  A = (256*A+B)*(2000/65536);
  C = (C-128+(D/256));

  printIHM("Oxygen sensor 1: \n\t Fuel-Air ratio: %d (x1000) \n\tSensor Current %d mA\n", (int) A*1000, (int) C);

  return 0;
}

uint8_t PIDfunctionFinder(data_struct* dataTable[], uint8_t PID)
{
  if (PID == 0x00)  PID00_funct(dataTable[0x00]);

  else if (PID == 0x01) PID01_funct(dataTable[0x01]);
          
  else if (PID == 0x03) PID03_funct(dataTable[0x03]);

  else if (PID == 0x04) PID04_funct(dataTable[0x04]);

  else if (PID == 0x05) PID05_funct(dataTable[0x05]);

  else if (PID == 0x06) PID06_funct(dataTable[0x06]);

  else if (PID == 0x07) PID07_funct(dataTable[0x07]);

  else if (PID == 0x0B) PID0B_funct(dataTable[0x0B]);

  else if (PID == 0x0C) PID0C_funct(dataTable[0x0C]);

  else if (PID == 0x0D) PID0D_funct(dataTable[0x0D]);

  else if (PID == 0x0E) PID0E_funct(dataTable[0x0E]);

  else if (PID == 0x0F) PID0F_funct(dataTable[0x0F]);

  else if (PID == 0x11) PID11_funct(dataTable[0x11]);

  else if (PID == 0x13) PID13_funct(dataTable[0x13]);

  else if (PID == 0x15) PID15_funct(dataTable[0x15]);

  else if (PID == 0x1C) PID1C_funct(dataTable[0x1C]);

  else if (PID == 0x20) PID20_funct(dataTable[0x20]);

  else if (PID == 0x21) PID21_funct(dataTable[0x21]);

  else if (PID == 0x34) PID34_funct(dataTable[0x34]);

  else  
  {
    printIHM("PID desconhecido. \n");
    return -1;
  }

  return 0;
}