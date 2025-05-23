#ifndef CONFIG_H
#define CONFIG_H

#include "xparameters.h"
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xtmrctr.h"
#include "xil_io.h"
#include "xil_cache.h"
#include "xtime_l.h"
#include "xil_mmu.h"
#include "xpseudo_asm.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sleep.h>
#include <string>


// Multicore
#define COMM_VAL 		(*(volatile unsigned long *)(0xFFFF000))
#define STATE1          (*(volatile bool*)(0xFFFF004))
#define STATE2         	(*(volatile bool*)(0xFFFF005))
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

// Parameter definitions
#define INTC_DEVICE_ID         XPAR_PS7_SCUGIC_0_DEVICE_ID
#define BTNS_DEVICE_ID         XPAR_AXI_GPIO_1_DEVICE_ID
#define INTC_GPIO_INTERRUPT_ID XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR
#define BTN_INT                XGPIO_IR_CH1_MASK
#define LFSR_ADDR 			   0x43C10000
extern volatile uint32_t *lfsr_ptr;
#define COUNTER_ADDR 		   0x43C20000
extern volatile uint32_t* counter_ptr;

// Button parameters
#define CLOCKSPEED         200000000
#define DEBOUNCE_WAIT_TIME 1000

// Display Buffer Values
const int NUM_BYTES_BUFFER = 5242880;  // 1280 * 1024 * 4 bytes
extern int * image_buffer_pointer;
const int displayWidth = 1280;
const int displayHeight = 1024;
const int barOffset = 0;
const int barWidth = 256;

// Game constants
const int numEnemies = 6;
const int baseDamage = 32;
extern int numHeals;
extern float typeEffectiveness[numEnemies][numEnemies];
extern int playerSprite;
extern int enemySprite;

// Menu constants
const int TEXT_BASE_HEIGHT = 123;
const int TEXT_BASE_WIDTH = 20;
const int TEXT_ADD_HEIGHT = TEXT_BASE_HEIGHT + 15;
const int TEXT_ADD_WIDTH = TEXT_BASE_WIDTH + 100;

extern XGpio BTNInst;
extern XScuGic INTCInst;
extern int btn_value;
extern int btnFlag;
extern int btnInterruptTime;
extern XTime btnFirstTime;


#endif
