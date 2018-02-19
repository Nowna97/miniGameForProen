#include "commonHeader.h"

//
//画像データ読込関数
//
void loadImg(char* imgName, Img* loadTo)
{
  loadTo->img = pngBind(imgName, PNG_NOMIPMAP, PNG_ALPHA,
                 &loadTo->imgInfo, GL_CLAMP, GL_NEAREST, GL_NEAREST);
  if(loadTo->img == 0)
  {
    printf("\"%s\" is not found\n", imgName);
  }
}

//
//画像表示関数
//
void putImg(Img* imgToPut, int x, int y, int transparency)
{
  int w, h;

  w = imgToPut->imgInfo.Width;
  h = imgToPut->imgInfo.Height;

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, imgToPut->img);
  glColor4ub(255, 255, 255, transparency);

  glBegin(GL_QUADS);

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
//迷路全体の画像データ読込関数
//
void loadMapImage(Map* loadTo)
{
  int i, j;

  for(i = 0; i < MAP_ALL_X_RANGE; i ++)
  {
    for(j = 0; j < MAP_ALL_Y_RANGE; j ++)
    {
      if(loadTo->cell[i][j].isWall == 1 && (i != MAP_ALL_X_RANGE - 2 || j != MAP_ALL_Y_RANGE - 1))
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
//迷路の画像表示関数
//
void putMap(Map* mapToPut, int centerX, int centerY)
{
  int i, j;

  for(i = 0; i < MAP_DISP_X_RANGE + 1; i ++)
  {
    for(j = 0; j < MAP_DISP_Y_RANGE + 1; j ++)
    {
      if(centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2 >= 0 && centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2 < MAP_ALL_X_RANGE
        && centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2 >= 0 && centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2 < MAP_ALL_Y_RANGE)
      {
        putImg(&mapToPut->cell[centerX / IMG_SIZE + i - MAP_DISP_X_RANGE / 2][centerY / IMG_SIZE + j - MAP_DISP_Y_RANGE / 2].img
          , i * IMG_SIZE - centerX % IMG_SIZE, j * IMG_SIZE - centerY % IMG_SIZE, 255);
      }
    }
  }
}

//
//キャラクターの画像データ読込関数
//
void loadCharacterImage(char* characterName, Character* loadTo)
{
  char fileName[(int)strlen(characterName) + 21];

  sprintf(fileName, "./resource/%s_under.png", characterName);
  loadImg(fileName, &loadTo->img[0]);
  sprintf(fileName, "./resource/%s_left.png", characterName);
  loadImg(fileName, &loadTo->img[1]);
  sprintf(fileName, "./resource/%s_over.png", characterName);
  loadImg(fileName, &loadTo->img[2]);
  sprintf(fileName, "./resource/%s_right.png", characterName);
  loadImg(fileName, &loadTo->img[3]);
}

//
//キャラクターの画像表示関数
//
void putCharacter(Character* characterToPut, int centerX, int centerY)
{
  putImg(&characterToPut->img[characterToPut->direction]
    , MAP_DISP_X_RANGE / 2 * IMG_SIZE + characterToPut->x - centerX
    , MAP_DISP_X_RANGE / 2 * IMG_SIZE + characterToPut->y - centerY, 255);
}
//
//敵の画像表示関数
//
void putEnemy(Character* enemyToPut, int centerX, int centerY)
{
  int i;

  for(i = 0; i < ENEMY_NUM; i ++)
  {
    if(MAP_DISP_X_RANGE / 2 * IMG_SIZE + enemyToPut[i].x - centerX >= 0 - IMG_SIZE
      && MAP_DISP_X_RANGE / 2 * IMG_SIZE + enemyToPut[i].x - centerX < WINDOW_WIDTH
      && MAP_DISP_X_RANGE / 2 * IMG_SIZE + enemyToPut[i].y - centerY >= 0 - IMG_SIZE
      && MAP_DISP_X_RANGE / 2 * IMG_SIZE + enemyToPut[i].y - centerY < WINDOW_HEIGHT)
    {
      putCharacter(&enemyToPut[i], centerX, centerY);
    }
  }
}
