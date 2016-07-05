#include <asf.h>

// 0 -> PIDs suportados -> de 1 a 20
uint8_t PID00_funct(data_struct* data);


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
uint8_t PID01_funct(data_struct* data);


// 3 -> Fuel System Status 1 and 2 -> 2 bytes
//    A = System 1
//    B = System 2
//    Results:
//		0 : Fuel system X is not present
//      1 : Open loop due to insufficient engine temperature
//      2 : Closed loop, using oxygen feedback to determine fuel mix
//      4 : Open loop due to engine load OR fuel cut due to deceleration
//      8 : Open loop due to system failure
//      16 : Closed loop, using at least one oxygen sensor but there is a fault in the feedback system.
//      other : Unknown response 
uint8_t PID03_funct(data_struct* data);

// 4 -> Calculated LOAD Value -> 1 byte
//  A*100/255 0 -> 100 %
uint8_t PID04_funct(data_struct* data);

// 5 -> Engine coolant temperature -> 1 byte
//  A-40    -40 -> 215 °C
uint8_t PID05_funct(data_struct* data);


// 6 -> Short Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID06_funct(data_struct* data);


// 7 -> Long Term Fuel Trim -> 1 byte
//  A*100/128 - 100   -100 -> 99.2 %
uint8_t PID07_funct(data_struct* data);


// B -> Intake Manifold Absolute Pressure -> 1 byte
//  A       0 kPa -> 255 kPa
uint8_t PID0B_funct(data_struct* data);

// C -> Engine RPM -> 2 bytes
//  (256*A + B)/4   0 RPM -> 16383.75
uint8_t PID0C_funct(data_struct* data);

// D -> Vehicle speed -> 1 byte 
uint8_t PID0D_funct(data_struct* data);


// E -> Timing Advanced -> 1 byte
//  (A/2) - 64    -64 -> 63.5 ° before TDC (ponto máximo do pistão)
uint8_t PID0E_funct(data_struct* data);


// F -> Intake air temperature  -> 1 byte
//  A-40        -40 -> 215 °C
uint8_t PID0F_funct(data_struct* data);

// 11 -> Throttle position -> 1 byte
//  A*100/255   0 -> 100%
uint8_t PID11_funct(data_struct* data);

// 13 -> Oxygen sensors present -> 1 Byte
//  Bits [0-3] -> sensors 1-4 -> Bank1
//  Bits [4-7] -> sensors 5-8 -> Bank2
uint8_t PID13_funct(data_struct* data);


// 15 -> Oxygen Sensor 2 -> 2 bytes
//    A : voltage   A/200   0 -> 1.275 V
//    B : Short term fuel trim (B*100/128)-100 
uint8_t PID15_funct(data_struct* data);


// 1C -> OBD standards this vehicle conforms to -> 1 byte
uint8_t PID1C_funct(data_struct* data);


// #20 -> PIDs suportados -> de 21 a 40
uint8_t PID20_funct(data_struct* data);


// 21 -> Distance traveled with malfunction indicator lamp (MIL) on -> 2 bytes
//  256*A + B     0 -> 65535 Km
uint8_t PID21_funct(data_struct* data);


// 34 -> Oxygen Sensor 1 -> 4 bytes
//    A B : (256A+B)*2/65536    0 -> <2 Fuel-Air Equivalence Ratio
//    C D : C - 128 + D/256   -128 -> 128 mA
uint8_t PID34_funct(data_struct* data);

uint8_t PIDfunctionFinder(data_struct* dataTable[], uint8_t PID);