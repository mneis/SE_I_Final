/**
 * \file
 *
 * \brief Matheus Neis e Michel Duarte
 *
 */

#include <math.h>
#include <asf.h>
#include "OBDII-std.h"
#include "Gambi.h"
#include "PID_interpreter.h"
#include "pt.h"

uint8_t dataReceived, PID, fastest, softError, service;
uint16_t RPM_Salvo = 6000, loop;	
int8_t errorInit=0, error=0, restart=0, refresh=0;
uint8_t PIDmonitor[30];

bool lightShift = false, shiftLight = false;

data_struct** PIDTable;

improveSpeed moreSpeed = {.first = 0, .last = 0, .empty = 1};

struct pt pt1, pt2, pt3, pt4;

uint8_t PIDmonitorDisplay[30] = {0x04, 0x05, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x11, 0x00};
// 0x04 -> Engine load
// 0x05 -> Engine temperature
// 0x0B -> Intake Manifold Absolute Pressure
// 0x0C -> RPM
// 0x0D -> Vehicle Speed
// 0x0E -> timing advance
// 0x0F -> Intake air temperature
// 0x11 -> Throttle position


// Argumentos / Retornos para thread receiveString_pt
formatos_retorno arg_receiveString_pt;
uint16_t result_receiveString_pt;
char string_receiveString_pt[256];

// Argumentos / Retornos para thread OBD_std_pt
uint8_t service_OBD_std_pt, protocolo_OBD_std_pt, pid_OBD_std_pt;


// Variaveis para thread manager_pt
uint8_t aux_current_state;

// Flags para ProtoThreads
bool manager_flag, display_flag, OBD_std_flag, receiveString_flag;
uint8_t current_state, op = idle;

static int OBD_std_pt(struct pt *pt)	// Espera receber como parametro service_OBD_std_pt, protocolo_OBD_std_pt e pid_OBD_std_pt;
{										// Retorna apenas um valor em error ou errorInit se solicitado
	PT_BEGIN(pt);

	while(1)
	{
		OBD_std_flag = false;
		PT_WAIT_UNTIL(pt, OBD_std_flag);
		softError =0;
		error = 0;
		if (service_OBD_std_pt == INIT5BAUD)
			errorInit = init5BAUD();
		else
		{
			while(1)
			{
				error = requestService(service_OBD_std_pt, pid_OBD_std_pt, protocolo_OBD_std_pt);
				if (error)
				{
					softError++;
					if (softError >= 10)
					{
						printIHM("Reiniciando comunicacao: \n");
						
						aux_current_state = current_state;
						current_state = error;
						display_flag = true;
						PT_WAIT_WHILE(pt, display_flag);
						
						error = init5BAUD();
						if (error)
						{
							break;
						}
						else
						{
							current_state = aux_current_state;
							display_flag = true;
							PT_WAIT_WHILE(pt, display_flag);
							softError = 0;
						}
					}
				}
				else
				{
					errorInit = 0;
					break;
				}
			}
		}
	}
	PT_END(pt);
}

static int receiveString_pt(struct pt *pt)	// Espera receber como parâmetro o tipo de conversão na variavel arg_receiveString_pt;
{											// Retorna se inteiro em result_receiveString_pt e se string em string_receiveString_pt;
	PT_BEGIN(pt);
	while(1)
	{
		receiveString_flag = false;
		PT_WAIT_UNTIL(pt, receiveString_flag);
		
		for(loop=0; ;loop++)      // Receive the string that finalize with \n
		{
			while(comReceive(&dataReceived))		// Wait a new character from COM
			{
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				if (op != idle) break;				// If when waiting characters, the display initiates a function, change to place that display is.
			}
			if (op != idle) break;
		
			if ((dataReceived == '\r') || (dataReceived == '\n'))	// Caso seja retorno de carro ou nova linha, sai do loop
			{
				printIHM("%c", dataReceived);		// Mostra na tela o número escrito
				break;
			}
			else if (dataReceived == 127)		// Caso seja dado um backspace (no caso o computador envia "del")
			{
				if (loop)
				{
					loop -= 2;
					printIHM("%c", dataReceived);		// Mostra na tela o número escrito
				}
				else loop--;
			}
			else
			{
				printIHM("%c", dataReceived);		// Mostra na tela o número escrito
				string_receiveString_pt[loop] = dataReceived;
			}
		}
	
		if ((arg_receiveString_pt == STR) && (op == idle))		// If the return is spected how string
		{
			string_receiveString_pt[loop] = '\0';
		}
		else if (((arg_receiveString_pt == DEC)||(arg_receiveString_pt == HEX)) && (op == idle))
		{
			uint8_t loop2;

			for(loop2=0; loop2<loop; loop2++)      // Converts each character to a hex number
			{
				if ((string_receiveString_pt[loop2]>=48)&&(string_receiveString_pt[loop2]<=57))
				{
					string_receiveString_pt[loop2] = string_receiveString_pt[loop2] - 48;
				}
				else if ((string_receiveString_pt[loop2]>=65)&&(string_receiveString_pt[loop2]<=70))
				{
					string_receiveString_pt[loop2] = string_receiveString_pt[loop2] - 55;
				}
				else if ((string_receiveString_pt[loop2]>=97)&&(string_receiveString_pt[loop2]<=102))
				{
					string_receiveString_pt[loop2] = string_receiveString_pt[loop2] - 87;
				}
			}

			uint16_t result=0;

			for (loop2=0; loop2 < loop; loop2++)   // Converts each algarism Hex to a number Hex
			{
				if (arg_receiveString_pt == HEX)	result += string_receiveString_pt[loop-(loop2+1)]*((uint16_t) pow((double)16, (double)(loop2)));
				else result += string_receiveString_pt[loop-(loop2+1)]*((uint16_t) pow((double)10, (double)(loop2)));
			}
			
			result_receiveString_pt = result;
		}
	}
	PT_END(pt);
}

static int display_pt(struct pt *pt)
{
	PT_BEGIN(pt);
	while(1)
	{
		display_flag = false;
		PT_WAIT_UNTIL(pt, display_flag);
	}
	
	PT_END(pt);
}

static int manager_pt(struct pt *pt)
{
	PT_BEGIN(pt);
	
	current_state = working;	
	display_flag = true;
	PT_WAIT_WHILE(pt, display_flag);
	
	initialize(&RPM_Salvo, &moreSpeed);
	
	while(1)
	{

		service_OBD_std_pt = INIT5BAUD;			// Inicializa comunicacao
		OBD_std_flag = true;
		PT_WAIT_WHILE(pt, OBD_std_flag);

		while(1)
		{
			restart = 0;
			comClear();
			comSend(CLEAR_TERMINAL);     // Command to clear terminal

			printIHM("\nECU Scanner\n");
			printIHM("Escolha a sua opcao:\n");
			printIHM("\t1 : Monitor\n");
			printIHM("\t2 : Requisicao de PID\n");
			printIHM("\t3 : Shift-light\n");
			printIHM("\t4 : Monitor de velocidade\n");
			printIHM("\t5 : Velocidades salvas\n");
			printIHM("\tR : Reinicia comunicacao\n");
			printIHM("\tC : Limpa Memoria\n");

			if (errorInit > 0){
				printIHM("\nErro de timeout na inicializacao.\n");
				current_state = err;
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				delay_ms(1000);
			}
			else if (errorInit < 0){
				printIHM("\nErro geral na inicializacao.\n");
				current_state = err;
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				delay_ms(1000);
			}
			if (error > 0){
				printIHM("\nErro de timeout na execucao.\n");
				current_state = err;
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				delay_ms(1000);
			}
			else if (error < 0){
				printIHM("\nErro geral na execucao.\n");
				current_state = err;
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				delay_ms(1000);
			}
			while(1)
			{
				current_state = menu;
				display_flag = true;
				PT_WAIT_WHILE(pt, display_flag);
				
				uint8_t aux;
				restart = 0;
				refresh = 0;
				errorInit = 0;
				if(comReceive(&dataReceived) == 0)
				{
					aux = dataReceived;
				}
				else aux = NULL;
				
/*###########*/	if ((aux == '1') || (op == update_mon))
				{
					printIHM("\nOpcao Monitor escolhida\n");
					// Inform which are the PID that should be displayed on terminal
					PIDmonitor[0] = 0x03;	//  0x03 ->	Fuel System Status 1 and 2
					PIDmonitor[1] = 0x04;	//  0x04 -> Engine load
					PIDmonitor[2] = 0x05;	//  0x05 -> Engine temperature
					PIDmonitor[3] = 0x06;	//  0x06 -> Short Term Fuel Trim
					PIDmonitor[4] = 0x07;	//  0x07 -> Long Term Fuel Trim
					PIDmonitor[5] = 0x0B;	//  0x0B -> Intake Manifold Absolute Pressure
					PIDmonitor[6] = 0x0C;	//  0x0C -> RPM
					PIDmonitor[7] = 0x0D;	//  0x0D -> Vehicle Speed
					PIDmonitor[8] = 0x0E;	//  0x0E -> Timing advance
					PIDmonitor[9] = 0x0F;	//  0x0F -> Intake air temperature
					PIDmonitor[10] = 0x11;	//  0x11 -> Throttle position
					PIDmonitor[11] = 0x15;	//  0x15 -> Oxygen Sensor 2
					PIDmonitor[12] = 0x21;	//  0x21 -> Distance traveled with malfunction indicator lamp (MIL)
					PIDmonitor[13] = 0x00;
					
					op = update_mon;
					current_state = load_v1;
					
					while((comReceive(&dataReceived))&&(op == update_mon))      // Enquanto não receber dados da COM
					{
						for(loop=0; PIDmonitor[loop] != 0x00; loop++)
						{
							
							OBD_std_flag = true;
							service_OBD_std_pt = 1;
							protocolo_OBD_std_pt = ISO9141;
							pid_OBD_std_pt = PIDmonitor[loop];
							PT_WAIT_WHILE(pt, OBD_std_flag);

							if (error) break;
						}
						if (error) break;
						
						comSend(CLEAR_TERMINAL);    // Command to clear terminal

						printIHM("\n\nMonitor: (Envie qualquer mensagem para sair)\n");

						for(loop=0; PIDmonitor[loop] != 0x00; loop++)
							PIDfunctionFinder(PIDTable, PIDmonitor[loop]);
						
						display_flag = true;
						PT_WAIT_WHILE(pt, display_flag);

					}
					if (!error)
					{
						display_flag = true;
						current_state = menu;
						PT_WAIT_WHILE(pt, display_flag);
					}
					
					op = idle;
					comClear();
					refresh = 1;
				}
/*###########*/	else if ((aux == '2') || (op == update_pid))
				{
					comSend(CLEAR_TERMINAL);
					printIHM("\nRequisicao de PID: \n");
					printIHM("Informe o servico: 1");

					service = 1;
					//   service = receiveString(HEX);
					//
					//   printIHM("0x%02x \n", service);

					printIHM("\nInforme o PID: ");
					
					if (op != update_pid)		// se (op == update_pid) deve-se ignorar o recebimento de PIDs pois ja tem um PID solicitado
					{
						arg_receiveString_pt = HEX;
						receiveString_flag = true;
						PT_WAIT_WHILE(pt, receiveString_flag);
						
						if (op == idle) 
						{
							PID = result_receiveString_pt;
							op = update_pid;
						}
					}
					if (op == update_pid)
					{
						printIHM("0x%02x \n", PID);
						
						
						service_OBD_std_pt = service;
						pid_OBD_std_pt = PID;
						protocolo_OBD_std_pt = ISO9141;
						OBD_std_flag = true;
						
						PT_WAIT_WHILE(pt, OBD_std_flag);		// Request PIDTable update
						
						if (!error)
						{
							if (PID == 0x03) current_state = sel_PID0x03;
							else if (PID == 0x04) current_state = sel_PID0x04;
							else if (PID == 0x05) current_state = sel_PID0x05;
							else if (PID == 0x06) current_state = sel_PID0x06;
							else if (PID == 0x07) current_state = sel_PID0x07;
							else if (PID == 0x0B) current_state = sel_PID0x0B;
							else if (PID == 0x0C) current_state = sel_PID0x0C;
							else if (PID == 0x0D) current_state = sel_PID0x0D;
							else if (PID == 0x0E) current_state = sel_PID0x0E;
							else if (PID == 0x0F) current_state = sel_PID0x0F;
							else if (PID == 0x11) current_state = sel_PID0x11;
							else if (PID == 0x13) current_state = sel_PID0x13;
							else if (PID == 0x15) current_state = sel_PID0x15;
							else if (PID == 0x21) current_state = sel_PID0x21;
							else current_state = working;
							
							display_flag = true;
							PT_WAIT_WHILE(pt, display_flag);

							PIDfunctionFinder(PIDTable, PID);

							printIHM("\n\n(Envie qualquer mensagem para sair)\n");
							while(comReceive(&dataReceived)&&(op == update_pid))
							{
								if(current_state != working)
								{
									display_flag = true;
									PT_WAIT_WHILE(pt, display_flag);
								}
							}
							display_flag = true;
							current_state = menu;
							PT_WAIT_WHILE(pt, display_flag);
						}
					}
					
					op = idle;
					comClear();
					refresh = 1;
				}
/*###########*/	else if ((aux == '3') || (op == update_shift))
				{					
					printIHM("\nSetar Shift-light: (anteriormente escolhido %d)\n(apenas aperte enter caso nao queira trocar)\nNew threshold: ", RPM_Salvo);

					if (op != update_shift)		// se (op == update_shift) deve-se ignorar o recebimento de PIDs pois ja tem um PID solicitado
					{
						arg_receiveString_pt = DEC;
						receiveString_flag = true;
						PT_WAIT_WHILE(pt, receiveString_flag);
						
						if ((result_receiveString_pt != 0) || (op == update_shift))
						{
							RPM_Salvo = result_receiveString_pt;		// if a new number be choose, save it
							
							writeFlashMemory(&RPM_Salvo, sizeof(uint16_t), RPM_ADDR_FLASH_MEM);
							
							printIHM("\n\nNova RPM de referencia escolhida\n");
						}
						
						if (op != idle) break;
						else op = update_shift;
					}
					if (op == update_shift)
					{
						current_state = shift_mon;
					
						while((comReceive(&dataReceived))&&(op == update_shift))      // Enquanto não receber dados da COM
						{
							while(1)
							{
								service_OBD_std_pt = 1;
								pid_OBD_std_pt = 0x0C;
								protocolo_OBD_std_pt = ISO9141;
								OBD_std_flag = true;
								
								PT_WAIT_WHILE(pt, OBD_std_flag);		// Request PID of RPM
								
								break;
							}
							if (error) break;

							comSend(CLEAR_TERMINAL);    // Command to clear terminal

							printIHM("\nShift-light: (Envie qualquer mensagem para sair)\n");
						
							shift_light(&lightShift, &shiftLight, RPM_Salvo);
							
							display_flag = true;
							PT_WAIT_WHILE(pt, display_flag);
						}
						
						if (!error)
						{
							current_state = menu;
							display_flag = true;
							PT_WAIT_WHILE(pt, display_flag);
						}	
					}
					
					op = idle;
					comClear();
					refresh = 1;
				}
/*###########*/	else if ((aux == '4') || (op == update_vm))
				{
					fastest = 0;
					
					PIDmonitor[0] = 0x0D ;	// PID da velocidade
					PIDmonitor[1] = 0x05 ;	// PID temperatura
					PIDmonitor[3] = 0x00;	// Fim da requisição
					
					op = update_vm;
					current_state = save_vm;
					while((comReceive(&dataReceived))&&(op == update_vm))      // Enquanto não receber dados da COM
					{			
						PIDmonitor[2] = 0x0C ;	// PID RPM
									
						for(loop=0; PIDmonitor[loop] != 0x00; loop++){
							
							service_OBD_std_pt = 1;
							pid_OBD_std_pt = PIDmonitor[loop];
							protocolo_OBD_std_pt = ISO9141;
							OBD_std_flag = true;
							
							PT_WAIT_WHILE(pt, OBD_std_flag);		// Request PID of RPM
							
							if(error) break;
						}
						if (error) break;
						
						comSend(CLEAR_TERMINAL);    // Command to clear terminal

						printIHM("\nSpeed-Monitor: (Tecle S para salvar ou qualquer outra tecla para sair)\n");
						
						if (PIDTable[0x0D]->data[0] > fastest) fastest = PIDTable[0x0D]->data[0];		// If has a new larger speed save it!
						
						printIHM("Velocidade maxima: %d km/h\n", fastest);
						
						PIDmonitor[2] = 0x00;				// take out the RPM request
						
						for(loop=0; PIDmonitor[loop] != 0x00; loop++)		// Display the functions required
							PIDfunctionFinder(PIDTable, PIDmonitor[loop]);
						
						shift_light(&lightShift, &shiftLight, RPM_Salvo);
						
						display_flag = true;
						PT_WAIT_WHILE(pt, display_flag);

					}
					if(((dataReceived == 's')||(dataReceived == 'S')||(op == write_vm)) && (!error))
					{
						if((moreSpeed.last) == ((moreSpeed.first+1)%SIZE_VEC_SPEED))	// Caso não tenha mais espaço no vetor, perde a mais antiga velocidade salva
						moreSpeed.last = (moreSpeed.last+1)%SIZE_VEC_SPEED;
						
						if (!moreSpeed.empty) moreSpeed.first = (moreSpeed.first+1)%SIZE_VEC_SPEED; // if not empty, change the first position
						moreSpeed.speed[moreSpeed.first] = fastest;
						
						moreSpeed.empty = 0;
						
						writeFlashMemory(&moreSpeed, sizeof(improveSpeed), MORESPEED_ADDR_FLASH_MEM);
						
						printIHM("Nova velocidade salva %d", fastest);
						delay_ms(1000);
					}
					
					if (!error)
					{
						display_flag = true;
						current_state = menu;
						PT_WAIT_WHILE(pt, display_flag);
					}
					
					op = idle;
					comClear();
					refresh = 1;
				}
/*###########*/ else if ((aux == '5') || (op == update_vtable))
				{
					printIHM("\nVelocidades salvas: (Pressione 'C' para limpar a memoria)\n\n");
					if (moreSpeed.empty) printIHM("Nao ha dados salvos\n");
					else
					{
						uint16_t loop = moreSpeed.first;
						uint16_t loop2 = 1;
						do
						{
							printIHM("%d) %d km/h\n", loop2, moreSpeed.speed[loop]);
							loop2++;
							loop = (SIZE_VEC_SPEED-1) - (SIZE_VEC_SPEED-loop)%SIZE_VEC_SPEED;
							
						} while (loop != (SIZE_VEC_SPEED-1) - (SIZE_VEC_SPEED-moreSpeed.last)%SIZE_VEC_SPEED);
					}
					
					op = update_vtable;
					current_state = load_v1;
					while((comReceive(&dataReceived)&&(op != erase_vtable))&&((current_state == load_v1)||(current_state == load_v2)))     // Enquanto não receber dados da COM
					{
						display_flag = true;
						PT_WAIT_WHILE(pt, display_flag);
					}
					
					if((dataReceived == 'c')||(dataReceived == 'C')||(op == erase_vtable))
					{
						moreSpeed.first = 0;
						moreSpeed.last = 0;
						moreSpeed.empty = 1;
						
						writeFlashMemory(&moreSpeed, sizeof(improveSpeed), MORESPEED_ADDR_FLASH_MEM);
						
						printIHM("\nTodas velocidade salvas foram apagadas");
						delay_ms(1000);
					}
					
					current_state = menu;
					display_flag = true;
					PT_WAIT_WHILE(pt, display_flag);
					
					op = idle;
					comClear();
					refresh = 1;
				}
/*###########*/	else if ((aux == 'r')||(aux == 'R')||(op == reset))
				{
					current_state = working;
					display_flag = true;
					PT_WAIT_WHILE(pt, display_flag);
					
					printIHM("\nReiniciando comunicacao\n");
					op = idle;
					comClear();
					restart = 1;
					refresh = 1;
				}
/*###########*/	else if ((aux == 'c')||(aux == 'C'))
				{
					current_state = working;
					display_flag = true;
					PT_WAIT_WHILE(pt, display_flag);
					
					setDefaultValues();
					
					op = idle;
					comClear();				
					restart = 1;
					refresh = 1;
				}
/*###########*/	else if (aux == NULL) 
				{}
				else
				{
					printIHM("\nComando nao reconhecido\n");
					
					comClear();		
					delay_ms(1000);
				}
				if(refresh) break;			// Se uma funcao foi executada, atualiza o display
			}
			if (restart) break;			// Se o comando reset foi pedido, termina o laco e reinicia a comunicacao
		}
	}
	PT_END(pt);
}


void main(void)
{
	system_init();		// Initialize libraries and drivers
	
	PIDTable = getPIDTable();
	
	PT_INIT(&pt1);
	PT_INIT(&pt2);
	PT_INIT(&pt3);
	PT_INIT(&pt4);
	
	while(1)
	{
		OBD_std_pt(&pt1);
		receiveString_pt(&pt2);
		display_pt(&pt3);
		manager_pt(&pt4);
	}
}
