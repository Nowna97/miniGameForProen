#include "commonHeader.h"

Block blockData[BLOCK_CNT];
BlockDataCnt testBlock = test;

//
//画像を読み込む関数
//
void loadImg(char* imgName, Img* setTo)
{
	setTo->img = pngBind(imgName, PNG_NOMIPMAP, PNG_ALPHA,
								 &setTo->imgInfo, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	if(setTo->img <= 0)
	{
		printf("\"%s\" is not found\n", imgName);
	}
	if(setTo->imgInfo.Width != IMG_SIZE)
	{
		printf("width of \"%s\" is not 48 pixel\n");
	}
	if(setTo->imgInfo.Height != IMG_SIZE)
	{
		printf("height of \"%s\" is not 48 pixel\n");
	}
}

//
//画像を表示する関数
//
void putImg(Img *imgToDisp, int x, int y)
{
  int w, h;  //  テクスチャの幅と高さ

  w = IMG_SIZE;   //  テクスチャの幅と高さを取得する
  h = IMG_SIZE;

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, imgToDisp->img);
  glColor4ub(255, 255, 255, 255);

  glBegin(GL_QUADS);  //  幅w, 高さhの四角形

  glTexCoord2i(0, 0);
  glVertex2i(x, y);

  glTexCoord2i(0, 1);
  glVertex2i(x, y + h);

  glTexCoord2i(1, 1);
  glVertex2i(x + w, y + h);

  glTexCoord2i(1, 0);
  glVertex2i(x + w, y);

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

//
//ブロックの三面の画像を読み込む関数
//
void loadBlock(char* blockName, Block *setTo)
{
	char imgName[32];
	sprintf(imgName, "./resource/%s_over.png", blockName);
	loadImg(imgName, &setTo->over);
	sprintf(imgName, "./resource/%s_left.png", blockName);
	loadImg(imgName, &setTo->left);
	sprintf(imgName, "./resource/%s_right.png", blockName);
	loadImg(imgName, &setTo->right);
}

//
//すべてのブロックの画像を読み込む関数
//
void loadAllBlockData()
{
	loadBlock("test", &blockData[testBlock]);
}

//
//ブロックを表示する関数
//
void putBlock(Block *blockToDisp, int x, int y, int whichSurfaceIsDisp)
{
	if((whichSurfaceIsDisp & DISP_OVER) != 0)
	{
		putImg(&blockToDisp->over, x, y);
	}
	if((whichSurfaceIsDisp & DISP_LEFT) != 0)
	{
		putImg(&blockToDisp->left, x, y);
	}
	if((whichSurfaceIsDisp & DISP_RIGHT) != 0)
	{
		putImg(&blockToDisp->right, x, y);
	}
}
