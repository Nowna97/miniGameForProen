#include "commonHeader.h"

//
//画像を読み込む関数
//
void loadImg(char* imgName, Img* loadTo)
{
  loadTo->img = pngBind(imgName, PNG_NOMIPMAP, PNG_ALPHA,
                 &loadTo->imgInfo, GL_CLAMP, GL_NEAREST, GL_NEAREST);
  if(loadTo->img == 0)
  {
    printf("\"%s\" is not found\n", imgName);
  }
  if(loadTo->imgInfo.Width != IMG_SIZE)
  {
    printf("width of \"%s\" is not %d pixel\n", imgName, IMG_SIZE);
  }
  if(loadTo->imgInfo.Height != IMG_SIZE)
  {
    printf("height of \"%s\" is not %d pixel\n", imgName, IMG_SIZE);
  }
}

//
//画像を表示する関数
//
void putImg(Img* imgToPut, int x, int y)
{
  int w, h;  //  テクスチャの幅と高さ

  w = IMG_SIZE;   //  テクスチャの幅と高さを取得する
  h = IMG_SIZE;

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, imgToPut->img);
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

void loadMapImage(Map* loadTo)
{
  int i, j;

  for(i = 0; i < MAP_ALL_X_RANGE; i ++)
  {
    for(j = 0; j < MAP_ALL_Y_RANGE; j ++)
    {
      if(loadTo->cell[i][j].isWall == 1)
      {
        loadImg("./resource/wall.png", &loadTo->cell[i][j].img);
      }
      else
      {
        loadImg("./resource/floor.png", &loadTo->cell[i][j].img);
      }
    }
  }
}

//
//指定した場所周辺のマップを表示する関数
//
void putMap(Map* mapToPut, int centerX, int centerY)
{
  int i, j;

  for(i = 0; i < MAP_DISP_X_RANGE; i ++)
  {
    for(j = 0; j < MAP_DISP_Y_RANGE; j ++)
    {
      if(centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2 >= 0 && centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2 < MAP_ALL_X_RANGE
        && centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2 >= 0 && centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2 < MAP_ALL_Y_RANGE)
      {
        putImg(&mapToPut->cell[centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2][centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2].img
          , i * IMG_SIZE - centerX % IMG_SIZE, j * IMG_SIZE - centerY % IMG_SIZE);
      }
    }
  }
}
