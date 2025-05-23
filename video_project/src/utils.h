#ifndef UTILS_H
#define UTILS_H

#include "game.h"

// Utility functions
void printNames();
void stringToImage(std::string msg, int startX, int startY);
void stringToImageNames(std::string msg, int startX, int startY);
void generateRandomEnemyOrder();
void shuffleArray(int arr[], int size);
void loadSprites();
void typeDamage(character *a, character *b);
int countTimes();
void timedDamage(character *a, int timeDamage);
void randomDamage(character *a);

// Interrupt functions
int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr);
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
void BTN_Intr_Handler(void *InstancePtr);

//extern XGpio BTNInst;
//extern XScuGic INTCInst;
//extern int btn_value;
//extern int btnFlag;
//extern int btnInterruptTime;
//extern XTime btnFirstTime;


#endif
