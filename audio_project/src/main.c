/*
 * Main source file. Contains main() and menu() functions.
 */
#include "main.h"

/* ---------------------------------------------------------------------------- *
 * 									main()										*
 * ---------------------------------------------------------------------------- *
 * Runs all initial setup functions to initialise the audio codec and IP
 * peripherals, before calling the interactive menu system.
 * ---------------------------------------------------------------------------- */

int main(void){
	xil_printf("Entering Main\r\n");
//    Xil_SetTlbAttributes((u32)(&COMM_VAL), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&STATE1), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&STATE2), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&MOVE), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&ERROR), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&SELECT), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&DESELECT), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&HEAL), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&NOTEFFECTIVE), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&EFFECTIVE), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&SUPEREFFECTIVE), NORM_NONCACHE);
	Xil_SetTlbAttributes((u32)(&VOLUME), NORM_NONCACHE);
	COMM_VAL = 0;
	STATE1 = false;
	STATE2 = false;
	MOVE = false;
	ERROR = false;
	SELECT = false;
	DESELECT = false;
	HEAL = false;
	NOTEFFECTIVE = false;
	EFFECTIVE = false;
	SUPEREFFECTIVE = false;
	VOLUME = 500;
//    Xil_SetTlbAttributes((u32)(&IPC_INTERRUPT), NORM_NONCACHE);
//    IPC_INTERRUPT = 0;
    Xil_SetTlbAttributes((u32)(0x00900000), NORM_NONCACHE);
    memset(0x00900000, 0, 5242880);
    memset(0x00900000, 0, 5242880);

	Xil_Out32(ARM1_STARTADDR, ARM1_BASEADDR);
	dmb();
	sev();

	int status;
	IicConfig(XPAR_XIICPS_0_DEVICE_ID); 				// Configure the IIC data structure
	AudioPllConfig(); 									// Configure the Audio Codec's PLL
	AudioConfigureJacks(); 								// Configure line in/out ports, configure HP jack
	gpio_init(); 										// Initialize GPIO peripherals
	status = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID);// Configure interrupt handlers and GPIO buttons
		if(status != XST_SUCCESS) return XST_FAILURE;
	XGpio_SetDataDirection(&BTNInst, 1, 0xFF);
	status = IntcInitFunction(INTC_DEVICE_ID, &BTNInst);// Initialize interrupt controller
		if(status != XST_SUCCESS) return XST_FAILURE;

	xil_printf("Finished setup\r\n");

	sd_card_initialization();

	COMM_VAL = 1;

//	xil_printf("1\r\n");
//	playWavFile(0);
//	xil_printf("2\r\n");
//	playWavFile(1);
//	xil_printf("3\r\n");
//	playWavFile(2);
//	xil_printf("4\r\n");
//	playWavFile(3);
//	xil_printf("5\r\n");
//	playWavFile(4);
//	xil_printf("6\r\n");
//	playWavFile(5);
//	xil_printf("7\r\n");
	menu();

    return 1;
}

/* ---------------------------------------------------------------------------- *
 * 									menu()										*
 * ---------------------------------------------------------------------------- */

void menu(){
	xil_printf("Into menu\r\n");
	u8 inp = 0x00;
	u32 CntrlRegister;

	/* Turn off all LEDs */
//	Xil_Out32(LED_BASE, 0);

	CntrlRegister = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_CR_OFFSET);

	XUartPs_WriteReg(UART_BASEADDR, XUARTPS_CR_OFFSET,
				  ((CntrlRegister & ~XUARTPS_CR_EN_DIS_MASK) |
				   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));




//	volatile uint32_t *lfsr_ptr = (volatile uint32_t *)LFSR_ADDR;
	while (!XUartPs_IsReceiveData(UART_BASEADDR)){
		// play audio files
		if(MOVE){
			playWavFile(4);
			xil_printf("MOVE\r\n");
			MOVE = false;
		}
		if(ERROR){
			playWavFile(9);
			xil_printf("ERROR\r\n");
			ERROR = false;
		}
		if(SELECT){
			playWavFile(5);
			xil_printf("SELECT\r\n");
			SELECT = false;
		}
		if(DESELECT){
			playWavFile(3);
			xil_printf("DESELECT\r\n");
			DESELECT = false;
		}
		if(HEAL){
			playWavFile(1);
			xil_printf("HEAL\r\n");
			HEAL = false;
		}
		if(NOTEFFECTIVE){
			playWavFile(7);
			xil_printf("NOTEFFECTIVE\r\n");
			NOTEFFECTIVE = false;
		}
		if(EFFECTIVE){
			playWavFile(6);
			xil_printf("EFFECTIVE\r\n");
			EFFECTIVE = false;
		}
		if(SUPEREFFECTIVE){
			playWavFile(8);
			xil_printf("SUPEREFFECTIVE\r\n");
			SUPEREFFECTIVE = false;
		}
		if(STATE2){
			playWavFile(2);
			xil_printf("VICTORY\r\n");
			STATE2 = false;
		}
	}


}


