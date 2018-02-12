#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/glpng.h>

#define WINDOW_WIDTH  (IMG_SIZE * (MAP_DISP_X_RANGE - 1))
#define WINDOW_HEIGHT (IMG_SIZE * (MAP_DISP_Y_RANGE - 1))

#define IMG_SIZE 48

#define MAP_ALL_X_RANGE 21
#define MAP_ALL_Y_RANGE 21

#define MAP_DISP_X_RANGE 13
#define MAP_DISP_Y_RANGE 13

#define ROAD_WIDTH 1
#define WALL_THICKNESS 1

#define RANDOM_CREATE_ROAD_TRY 4

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

Map gameMap;

//
//callback.c
//
void display(void);
void reshape(int, int);
void timer(int);

//
//img.c
//
void loadImg(char*, Img*);
void putImg(Img*, int, int);
void loadMapImage(Map*);
void putMap(Map*, int, int);

//
//map.c
//
void initMap(Map*);

//
//game.c
//
void initGame(void);
