#include <string.h>
#include "OBDII-std.h"
#include "Gambi.h"

data_struct* PIDtable[0x80];

uint8_t keyBytes[2];

uint8_t dataReceived;

// 0 -> PIDs suportados -> de 1 a 20
uint8_t PID00_data[4];
data_struct PID00_struct = {PID00_data, 4};


// 1 -> Monitor status since DTCs cleared -> 4 bytes 
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
//      C7 : EGR system montoring supported : EGR_SUP -> YES | NO
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
uint8_t PID01_data[4];
data_struct PID01_struct = {PID01_data, 4};


// 3 -> Fuel System Status 1 and 2 -> 2 bytes
//    A = System 1
//    B = System 2
//    Results:
//      1 : Open loop due to insufficient engine temperature
//      2 : Closed loop, using oxygen feedback to determine fuel mix
//      4 : Open loop due to engine load OR fuel cut due to deceleration
//      8 : Open loop due to system failure
//      16 : Closed loop, using at least one oxygen sensor but there is a fault in the feedback system.
//      other : Unknown response 
uint8_t PID03_data[2];
data_struct PID03_struct = {PID03_data, 2};


// 4 -> Calculated LOAD Value -> 1 byte
//  A*100/255 0 -> 100 %
uint8_t PID04_data[1];
data_struct PID04_struct = {PID04_data, 1};


// 5 -> Engine coolant temperature -> 1 byte
//  A-40    -40 -> 215 °C
uint8_t PID05_data[1];
data_struct PID05_struct = {PID05_data, 1};


// 6 -> Short Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID06_data[1];
data_struct PID06_struct = {PID06_data, 1};


// 7 -> Long Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID07_data[1];
data_struct PID07_struct = {PID07_data, 1};


// B -> Intake Manifold Absolute Pressure -> 1 byte
//  A       0 kPa -> 255 kPa
uint8_t PID0B_data[1];
data_struct PID0B_struct = {PID0B_data, 1};


// C -> Engine RPM -> 2 bytes
//  (256*A + B)/4   0 RPM -> 16383.75
uint8_t PID0C_data[2];
data_struct PID0C_struct = {PID0C_data, 2};


// D -> Vehicle speed -> 1 byte 
uint8_t PID0D_data[1];
data_struct PID0D_struct = {PID0D_data, 1};


// E -> Timing Advanced -> 1 byte
//  (A/2) - 64    -64 -> 63.5 ° before TDC (ponto máximo do pistão)
uint8_t PID0E_data[1];
data_struct PID0E_struct = {PID0E_data, 1};


// F -> Intake air temperature  -> 1 byte
//  A-40        -40 -> 215 °C
uint8_t PID0F_data[1];
data_struct PID0F_struct = {PID0F_data, 1};


// 11 -> Throttle position -> 1 byte
//  A*100/255   0 -> 100%
uint8_t PID11_data[1];
data_struct PID11_struct = {PID11_data, 1};


// 13 -> Oxygen sensors present -> 1 Byte
//  Bits [0-3] -> sensors 1-4 -> Bank1
//  Bits [4-7] -> sensors 5-8 -> Bank2
uint8_t PID13_data[1];
data_struct PID13_struct = {PID13_data, 1};


// 15 -> Oxygen Sensor 2 -> 2 bytes
//    A : voltage   A/200   0 -> 1.275 V
//    B : Short term fuel trim (B*100/128)-100
uint8_t PID15_data[2];
data_struct PID15_struct = {PID15_data, 2};


// 1C -> OBD standards this vehicle conforms to -> 1 byte
uint8_t PID1C_data[1];
data_struct PID1C_struct = {PID1C_data, 1};


// #20 -> PIDs suportados -> de 21 a 40
uint8_t PID20_data[4];
data_struct PID20_struct = {PID20_data, 4};


// 21 -> Distance traveled with malfunction indicator lamp (MIL) on -> 2 bytes
//  256*A + B     0 -> 65535 Km
uint8_t PID21_data[2];
data_struct PID21_struct = {PID21_data, 2};


// 34 -> Oxygen Sensor 1 -> 4 bytes
//    A B : (256A+B)*2/65536    0 -> <2
//    C D : C - 128 + D/256
uint8_t PID34_data[4];
data_struct PID34_struct = {PID34_data, 4};



//============== General Functions ====================================

void initPIDs()
{
  uint8_t loop;
  for(loop=0; loop<0x80;loop++)   // Initializes the vector with NULL
    PIDtable[loop] = (data_struct *) NULL;

  PIDtable[0x00] = &PID00_struct;
  PIDtable[0x01] = &PID01_struct;
  PIDtable[0x03] = &PID03_struct;
  PIDtable[0x04] = &PID04_struct;
  PIDtable[0x05] = &PID05_struct;
  PIDtable[0x06] = &PID06_struct;
  PIDtable[0x07] = &PID07_struct;
  PIDtable[0x0B] = &PID0B_struct;
  PIDtable[0x0C] = &PID0C_struct;
  PIDtable[0x0D] = &PID0D_struct;
  PIDtable[0x0E] = &PID0E_struct;
  PIDtable[0x0F] = &PID0F_struct;
  PIDtable[0x11] = &PID11_struct;
  PIDtable[0x13] = &PID13_struct;
  PIDtable[0x15] = &PID15_struct;
  PIDtable[0x1C] = &PID1C_struct;
  PIDtable[0x20] = &PID20_struct;
  PIDtable[0x21] = &PID21_struct;
  PIDtable[0x34] = &PID34_struct;
}



uint8_t requestService(uint8_t service, uint8_t PID, uint8_t protocol)
{
  if (service == 0x01)
  {
    if (sendRequest(protocol, PIDtable[PID]->bytes, service, PID))
      return -1;                           // if an error occour, report with -1
    return receiveData(PIDtable[PID]->data, PIDtable[PID]->bytes, protocol, PID);   // Call the function receiveData with respectives parameters to receive the response of ECU.
  }
  return -1;

}

uint8_t sendRequest(uint8_t protocol, uint8_t bytes, uint8_t service, uint8_t PID)
{
  if (protocol == ISO9141)
  {
    uartSend(0x68);   // Send the data sequence according to protocol
    uartSend(0x6A);
    uartSend(0xF1);
    uartSend(service);
    uartSend(PID);
    uint8_t checkSum = 0x68 + 0x6A + 0xF1 + service + PID;
    uartSend(checkSum);
    return 0;
  }else
  {
    return -1;
  }
}

uint8_t receiveData(uint8_t data[], uint8_t bytes, uint8_t protocol, uint8_t PID)
{
  if (protocol == ISO9141)
  {
    uint8_t timing, loop, checkSum = 0, dataAux[bytes+6];
    uartClear();      // Clear the input stream
	delay_ms(10);
    for (loop=0; loop<bytes+6; loop++)
    {
      timing = 0;
      while (uartReceive(&dataReceived))
      {
        if (timing == 50) return 1; // if more then 50 ms pass and ECU not respond, returns 1 to indicate that the transmition terminate with time-out.
        delay_ms(1); // waits 1ms to attempt receive again
        timing++;
      }
      dataAux[loop] = dataReceived;      
      if (loop < bytes + 5) checkSum += dataAux[loop];  // Sum all data receive without checkSum.
    }
    if (checkSum != dataAux[bytes+5]) return -1; // if any error has found, return -1;
    else
    {
      for (loop=0; loop<bytes; loop++)
        data[loop] = dataAux[loop+5];   // With success on transmition, save the data received.
      return 0;
    }
  }
  else
  {
    return -1;
  }
}

uint8_t init5BAUD()
{
  uint8_t loop, data;
  uint16_t  timing=0;

  uartSetTXasDigital();

  pinOutCtrl(PIN_TX, LOW);  // Sends the startbit
  delay_ms(198);  

  pinOutCtrl(PIN_TX, HIGH); // Initiates the transmition of byte 0x33 at 5 bauds
  delay_ms(397);

  pinOutCtrl(PIN_TX, LOW);
  delay_ms(397);

  pinOutCtrl(PIN_TX, HIGH);
  delay_ms(397);

  pinOutCtrl(PIN_TX, LOW);
  delay_ms(397);

  pinOutCtrl(PIN_TX, HIGH);
  delay_ms(199);


  uartInit();    // Configure uart to communicate with OBDII
	
	delay_ms(20);
  uartClear();      // Clear the input stream
  for (loop=0; loop<3; loop++)
  {
    timing=0;
    while (uartReceive(&dataReceived))
    {
      if (timing == 100) return 1; // if more then 50 ms pass and ECU not respond, returns 1 to indicate that the transmition terminate with time-out.
      delay_ms(1); // waits 10ms to attempt receive again
      timing++;
    }
	
    data = dataReceived;
    if ((loop == 0) && (data != 0x55)) return -1;
    else if (loop == 1) keyBytes[0] = data;
    else keyBytes[1] = data;
  }
  uartSend(~keyBytes[1]); // Send key byte 2 in one's complement
  
  uartClear();
  
  timing=0;
  while (uartReceive(&dataReceived))
  {
    if (timing == 100) return 1;  // if more then 500 ms pass and ECU not respond, returns 1 to indicate that the transmition terminate with time-out.
    delay_ms(10); // waits 10ms to attempt receive again
    timing++;
  }

  
  if (dataReceived != 0xCC) return -1;  // If the ECU returns a different message that ~0x33 (0x33 in one's complement) an error has occurred

  return 0;
}

uint8_t fastInit()
{
  return -1;
}

data_struct* getPIDTable()
{
	return PIDtable;
}