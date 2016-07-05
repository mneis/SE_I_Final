#include <asf.h>

#define INIT5BAUD 0

#define	ISO9141 0
#define	KWP2000 1
#define	CAN 2


typedef struct data_struct
{
	uint8_t* data;
	uint8_t bytes;
}data_struct;


//============== General Functions ==================================== 

void initPIDs();


uint8_t requestService(uint8_t service, uint8_t PID, uint8_t protocol);

uint8_t sendRequest(uint8_t protocol, uint8_t bytes, uint8_t service, uint8_t PID);

uint8_t receiveData(uint8_t data[], uint8_t bytes, uint8_t protocol, uint8_t PID);

uint8_t init5BAUD();

uint8_t fastInit();

data_struct* getPIDTable();