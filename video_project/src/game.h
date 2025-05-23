#ifndef GAME_H
#define GAME_H

#include "config.h"

// Object structure (logical coordinates are in a 240×160 space)
struct object {
    int* image;   // pointer to sprite pixel data (logical dimensions)
    int width;    // logical width
    int height;   // logical height
    int posX;     // logical x position (0–239)
    int posY;     // logical y position (0–159)
    int zIndex;   // optional z-index for layering (lower drawn first)
    bool draw;	  // whether to draw or not, 0 no, 1 yes
    bool dead;    // only for enemy pokemon, 0 if alive, 1 if dead
};

// Global precomputed scaled background (1280×1024)
extern int* scaledBackground;
extern int* background;  // points to the current 240×160 background image

struct character{
	int type;
	int health;
};
extern character characters[numEnemies + 1]; // 0-5 are enemies, 6 is player
extern int cursorVal;
extern int currEnemy;
extern int ordering[numEnemies];
extern std::vector<object> objects;
extern std::vector<object> letters;
extern std::vector<object> renderQueue;
extern int gameState; // 0 = choosing pokemon, 1 = battling, 2 = end game
extern int hueShift; // hue of pokemon

// Screen functions
void renderScene(const std::vector<object>& objs);
void upscaleBackground(const int* src);
void updateAndRender();
void starterMenu();

// Animation functions
void playAnimation(int animNum/*, int repeat*/);
void playEnemyAnimation();
void animateTest();
void animateMove(const std::vector<object>& moveFrames);
void updateHealth();
void animatePlayerDamage();
void animateEnemyDamage();
void updateHealthHeal();
void animatePlayerDamageHeal();


#endif
