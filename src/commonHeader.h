#include <stdio.h>
#include <GL/glut.h>
#include <GL/glpng.h>

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 540

#define IMG_SIZE 48

#define MAP_ALL_X_RANGE 10
#define MAP_ALL_Y_RANGE 10

#define MAP_DISP_X_RANGE 10
#define MAP_DISP_Y_RANGE 10

#define DISP_OVER  0b100
#define DISP_LEFT  0b010
#define DISP_RIGHT 0b001

#define BLOCK_CNT 1

typedef enum
{
	test
}BlockDataCnt;
extern BlockDataCnt testBlock;

typedef struct
{
	GLuint img;
	pngInfo imgInfo;
}Img;

typedef struct
{
	Img over, left, right;
}Block;

typedef struct
{
	Block block;
	int height;
}Cell;

typedef struct
{
	Cell cell[MAP_ALL_Y_RANGE][MAP_ALL_X_RANGE];
}Map;

extern Block blockData[BLOCK_CNT];
extern BlockDataCnt testBlock;

//
//callback.c
//
void display(void);
void reshape(int, int);
void timer(int);

//
//img.c
//
void loadImage(char*, Img*);
void putImg(Img*, int, int);
void loadBlock(char*, Block*);
void loadAllBlockData(void);
void putBlock(Block*, int, int, int);
