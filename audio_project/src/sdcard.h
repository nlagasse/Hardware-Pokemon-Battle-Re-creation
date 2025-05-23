#ifndef SDCARD_H_
#define SDCARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "platform.h"
#include "xil_printf.h"

#include "interrupts.h"

#include "xil_types.h"
#include "xstatus.h"
#include "xscugic.h"
#include "xparameters.h"
#include "ff.h"
#include "main.h"

void throwFatalError(const char *func,const char *msg);
extern void playWavFile(int num);
//void playAudio();
void loadWavFiles();
void loadImageFiles();
void sd_card_initialization();

#define MAX_FILES 32
#define MAX_FILENAME_LENGTH 32

extern char wavFiles[MAX_FILES][MAX_FILENAME_LENGTH];
extern int wavFileCount;

#define MAX_IMAGES 32
#define MAX_IMAGE_NAME_LENGTH 64

extern char imageFiles[MAX_IMAGES][MAX_IMAGE_NAME_LENGTH];
extern int imageFileCount;
extern u8 *imageBuffers[MAX_IMAGES];
extern size_t imageBufferSizes[MAX_IMAGES];
extern u32 *imageIntArrays[MAX_IMAGES];
extern size_t imageIntArraySizes[MAX_IMAGES];

extern u8 *buffers[MAX_FILES];
//extern fmtChunk_t fmtChunks[MAX_FILES];

#endif
