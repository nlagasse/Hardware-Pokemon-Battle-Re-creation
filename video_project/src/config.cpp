#include "config.h"

volatile uint32_t *lfsr_ptr = (volatile uint32_t *)LFSR_ADDR;

// Display Buffer Values
int * image_buffer_pointer = (int *)0x10980000;
volatile uint32_t* counter_ptr = (volatile uint32_t*)COUNTER_ADDR;


// Game constants
float typeEffectiveness[numEnemies][numEnemies] = {
    // 0    1    2    3    4    5
    {1,   2,  1,  1,  1,  0.5}, // Type 0 (Aggron)		(Blaziken)
    {0.5, 1,  2,  1,  1,  1},   // Type 1 (Armaldo) 	(Swampert)
    {1,   0.5,1,  2,  1,  1},   // Type 2 (Claydol) 	(Sceptile)
    {1,   1,  0.5,1,  2,  1},   // Type 3 (Cradily)
    {1,   1,  1,  0.5,1,  2},   // Type 4 (Metagross)
    {2,   1,  1,  1,  0.5,1}    // Type 5 (Skarmory)
};
int numHeals = 3;
int playerSprite = 0;
int enemySprite = 0;

XGpio BTNInst;
XScuGic INTCInst;
int btn_value = 0;
int btnFlag = 0;
int btnInterruptTime = 0;
XTime btnFirstTime;
