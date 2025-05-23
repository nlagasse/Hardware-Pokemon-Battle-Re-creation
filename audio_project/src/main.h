/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

/* ---------------------------------------------------------------------------- *
 * 								Header Files									*
 * ---------------------------------------------------------------------------- */
#include <stdio.h>
#include <xil_io.h>
#include <sleep.h>
#include "xiicps.h"
#include <xil_printf.h>
#include <xparameters.h>
#include "xgpio.h"
#include "xuartps.h"
#include "stdlib.h"
#include "xtime_l.h"
#include "xil_mmu.h"
#include <stdbool.h>

/* ---------------------------------------------------------------------------- *
 * 							Custom IP Header Files								*
 * ---------------------------------------------------------------------------- */
#include "audio.h"
#include "interrupts.h"
#include "sdcard.h"
/* ---------------------------------------------------------------------------- *
 * 							Prototype Functions									*
 * ---------------------------------------------------------------------------- */
void menu();
void tonal_noise();
void audio_stream();
void lms_filter();
unsigned char gpio_init();
void nco_init(void *InstancePtr);

void BTN_Intr_Handler(void *baseaddr_p);
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr);
/* ---------------------------------------------------------------------------- *
 * 						Redefinitions from xparameters.h 						*
 * ---------------------------------------------------------------------------- */

#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR

#define BUTTON_SWITCH_BASE XPAR_GPIO_1_BASEADDR
//#define LED_BASE XPAR_LED_CONTROLLER_0_S00_AXI_BASEADDR
#define BUTTON_SWITCH_ID XPAR_GPIO_1_DEVICE_ID

/* ---------------------------------------------------------------------------- *
 * 							Define GPIO Channels								*
 * ---------------------------------------------------------------------------- */
#define BUTTON_CHANNEL 1
//#define SWITCH_CHANNEL 2

/* ---------------------------------------------------------------------------- *
 * 							Audio Scaling Factor								*
 * ---------------------------------------------------------------------------- */
#define SCALE 6

/* ---------------------------------------------------------------------------- *
 * 							Global Variables									*
 * ---------------------------------------------------------------------------- */
XIicPs Iic;
XGpio Gpio; // Gpio instance for buttons and switches
XGpio BTNInst;
XScuGic INTCInst;

#define CPU_CLOCK_FREQ 200000000

#define LFSR_ADDR 0x43C10000

#define sev() __asm__("sev")
#define ARM1_STARTADDR 0xFFFFFFF0
#define ARM1_BASEADDR 0x10080000
#define COMM_VAL (*(volatile unsigned long *)(0xFFFF000))
#define STATE1          (*(volatile bool*)(0xFFFF004))
#define STATE2         (*(volatile bool*)(0xFFFF005))
#define MOVE            (*(volatile bool*)(0xFFFF006))
#define ERROR           (*(volatile bool*)(0xFFFF007))
#define SELECT          (*(volatile bool*)(0xFFFF008))
#define DESELECT        (*(volatile bool*)(0xFFFF009))
#define HEAL            (*(volatile bool*)(0xFFFF00A))
#define NOTEFFECTIVE    (*(volatile bool*)(0xFFFF00B))
#define EFFECTIVE       (*(volatile bool*)(0xFFFF00C))
#define SUPEREFFECTIVE  (*(volatile bool*)(0xFFFF00D))
#define VOLUME 			(*(volatile int*)(0xFFFF00E))
//#define IPC_INTERRUPT (*(volatile uint8_t*)(0xFFFF004))

#endif /* ADVENTURES_WITH_IP_H_ */
