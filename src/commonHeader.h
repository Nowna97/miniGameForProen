#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glpng.h>

#define WINDOW_WIDTH  (IMG_SIZE * MAP_DISP_X_RANGE)
#define WINDOW_HEIGHT (IMG_SIZE * MAP_DISP_Y_RANGE)

#define IMG_SIZE 48

#define MAP_ALL_X_RANGE 21
#define MAP_ALL_Y_RANGE 21

#define MAP_DISP_X_RANGE 13
#define MAP_DISP_Y_RANGE 13

#define ROAD_WIDTH 1
#define WALL_THICKNESS 1

#define RANDOM_CREATE_ROAD_TRY 4

#define PLAYER_CHARACTER_STEP 4
#define ENEMY_STEP 4
#define MOVE_POSTPONEMENT 4
#define COLLISION_POSTPONEMENT (IMG_SIZE / 2)

#define ENEMY_NUM 7
#define FIELD_OF_VISION 5

typedef struct
{
  GLuint img;
  pngInfo imgInfo;
}Img;

typedef struct
{
  int isWall;
  Img img;
}Cell;

typedef struct
{
  Cell cell[MAP_ALL_X_RANGE][MAP_ALL_Y_RANGE];
}Map;

typedef struct
{
  int x;
  int y;
  int direction;
  int whereGoing;
  Img img[4];
}Character;

int mode;
Map gameMap;
Character playerCharacter;
Character enemyCharacter[ENEMY_NUM];
int pushingSpace;

//
//callback.c
//
void display(void);
void reshape(int, int);
void timer(int);
void keyboard(unsigned char, int, int);
void keyboardUp(unsigned char, int, int);

//
//img.c
//
void loadImg(char*, Img*);
void putImg(Img*, int, int);
void loadMapImage(Map*);
void putMap(Map*, int, int);
void loadCharacterImage(char*, Character*);
void putCharacter(Character*, int, int);
void putEnemy(Character*, int, int);

//
//game.c
//
void initGame(void);
void initMap(Map*);
void initPlayerCharacter(Character*);
void playerCharacterMove(Map*, Character*);
void initEnemy(Character*);
void enemyMove(int*, Character*, Character*);
int  isCollisioning(Character*, Character*);
int  getDistance(Character*, Character*);
