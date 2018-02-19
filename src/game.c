#include "commonHeader.h"

//
//迷路全体の初期化関数
//
void initMap(Map* init)
{
  int i, j;

  for(i = 0; i < MAP_ALL_X_RANGE; i ++)
  {
    for(j = 0; j < MAP_ALL_Y_RANGE; j ++)
    {
      init->cell[i][j].isWall = 1;
    }
  }

  int canCreateRoadPointXNum = (MAP_ALL_X_RANGE / (WALL_THICKNESS + ROAD_WIDTH) - (MAP_ALL_X_RANGE % (WALL_THICKNESS + ROAD_WIDTH) < WALL_THICKNESS ? 1 : 0));
  int canCreateRoadPointYNum = (MAP_ALL_Y_RANGE / (WALL_THICKNESS + ROAD_WIDTH) - (MAP_ALL_X_RANGE % (WALL_THICKNESS + ROAD_WIDTH) < WALL_THICKNESS ? 1 : 0));
  int canCreateRoadPointNum = canCreateRoadPointXNum * canCreateRoadPointYNum;
  int alreadyCreatedRoadNum;
  int alreadyCreatedRoadArray[canCreateRoadPointNum][3];
  int nowDigX, nowDigY;
  int nextDigX, nextDigY;
  int randomNum;
  int randomCreateRoadTryCnt;
  int randomCreateRoadTrySccessfulFlag;

  srandom(time(NULL));
  for(alreadyCreatedRoadNum = 0; alreadyCreatedRoadNum < canCreateRoadPointNum;)
  {
    if(alreadyCreatedRoadNum == 0)
    {
      nowDigX = random() % canCreateRoadPointXNum * (WALL_THICKNESS + ROAD_WIDTH) + WALL_THICKNESS;
      nowDigY = random() % canCreateRoadPointYNum * (WALL_THICKNESS + ROAD_WIDTH) + WALL_THICKNESS;
      init->cell[nowDigX][nowDigY].isWall = 0;
      alreadyCreatedRoadArray[alreadyCreatedRoadNum][0] = nowDigX;
      alreadyCreatedRoadArray[alreadyCreatedRoadNum][1] = nowDigY;
      alreadyCreatedRoadNum ++;
    }
    else
    {
      randomCreateRoadTryCnt = 0;
      randomCreateRoadTrySccessfulFlag = 0;

      while(randomCreateRoadTrySccessfulFlag == 0 && randomCreateRoadTryCnt < RANDOM_CREATE_ROAD_TRY)
      {
        randomNum = random() % 4;
        switch(randomNum)
        {
          case 0:
            nextDigX = nowDigX - (WALL_THICKNESS + ROAD_WIDTH);
            nextDigY = nowDigY;
            break;
          case 1:
            nextDigX = nowDigX;
            nextDigY = nowDigY - (WALL_THICKNESS + ROAD_WIDTH);
            break;
          case 2:
            nextDigX = nowDigX + (WALL_THICKNESS + ROAD_WIDTH);
            nextDigY = nowDigY;
            break;
          case 3:
            nextDigX = nowDigX;
            nextDigY = nowDigY + (WALL_THICKNESS + ROAD_WIDTH);
            break;
        }

        if(nextDigX >= WALL_THICKNESS && nextDigX < MAP_ALL_X_RANGE - WALL_THICKNESS
          && nextDigY >= WALL_THICKNESS && nextDigY < MAP_ALL_Y_RANGE - WALL_THICKNESS)
        {
          if(init->cell[nextDigX][nextDigY].isWall == 1)
          {
            for(i = ((nowDigX < nextDigX) ? nowDigX : nextDigX); i <= ((nowDigX < nextDigX) ? nextDigX + ROAD_WIDTH - 1 : nowDigX + ROAD_WIDTH - 1); i ++)
            {
              for(j = ((nowDigY < nextDigY) ? nowDigY : nextDigY); j <= ((nowDigY < nextDigY) ? nextDigY + ROAD_WIDTH - 1 : nowDigY + ROAD_WIDTH - 1); j ++)
              {
                init->cell[i][j].isWall =0;
              }
            }

            nowDigX = nextDigX;
            nowDigY = nextDigY;
            alreadyCreatedRoadArray[alreadyCreatedRoadNum][0] = nowDigX;
            alreadyCreatedRoadArray[alreadyCreatedRoadNum][1] = nowDigY;
            alreadyCreatedRoadNum ++;
            randomCreateRoadTrySccessfulFlag = 1;
          }
        }

        randomCreateRoadTryCnt ++;
      }

      if(randomCreateRoadTrySccessfulFlag == 0 && randomCreateRoadTryCnt >= RANDOM_CREATE_ROAD_TRY)
      {
        randomNum = random() % alreadyCreatedRoadNum;
        nowDigX = alreadyCreatedRoadArray[randomNum][0];
        nowDigY = alreadyCreatedRoadArray[randomNum][1];
      }
    }
  }

  for(i = 0; i < MAP_ALL_Y_RANGE; i ++)
  {
    for(j = 0; j < MAP_ALL_X_RANGE; j ++)
    {
      printf("%d ", init->cell[j][i].isWall);
    }
    printf("\n");
  }

  loadMapImage(init);
}

//
//自機の初期化関数
//
void initPlayerCharacter(Character* init)
{
  init->x = IMG_SIZE;
  init->y = IMG_SIZE;
  init->direction = 0;
  init->whereGoing = 0;

  loadCharacterImage("playerCharacter", init);
}

//
//自機の移動処理関数
//
void playerCharacterMove(Map* map, Character* character)
{
  switch (character->whereGoing)
  {
    case 's':
      character->y += PLAYER_CHARACTER_STEP;
      if(map->cell[(character->x + MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1
        || map->cell[(character-> x + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1)
      {
        character->y -= ((character->y + IMG_SIZE - 1 - MOVE_POSTPONEMENT) % IMG_SIZE + 1);
      }
      break;
    case 'a':
      character->x -= PLAYER_CHARACTER_STEP;
      if(map->cell[(character->x + MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1
        || map->cell[(character->x + MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1)
      {
        character->x += (IMG_SIZE - (character->x + MOVE_POSTPONEMENT) % IMG_SIZE);
      }
      break;
    case 'w':
      character->y -= PLAYER_CHARACTER_STEP;
      if(map->cell[(character->x + MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1
        || map->cell[(character-> x + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1)
      {
        character->y += (IMG_SIZE - (character->y + MOVE_POSTPONEMENT) % IMG_SIZE);
      }
      break;
    case 'd':
      character->x += PLAYER_CHARACTER_STEP;
      if(map->cell[(character->x + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1
        || map->cell[(character-> x+ IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE][(character->y + IMG_SIZE - 1 - MOVE_POSTPONEMENT) / IMG_SIZE].isWall == 1)
      {
        character->x -= ((character->x + IMG_SIZE - 1 - MOVE_POSTPONEMENT) % IMG_SIZE + 1);
      }
      break;
  }
}

//
//敵の初期化関数
//
void initEnemy(Character* init)
{
  int i;
  int randomNum;

  for(i = 0; i < ENEMY_NUM; i ++)
  {
    init[i].x = MAP_ALL_X_RANGE / 6 * (1 + ((i + 1) % 3 * 2)) * IMG_SIZE;
    init[i].y = MAP_ALL_Y_RANGE / 6 * (1 + ((i + 1) / 3 * 2)) * IMG_SIZE;
    init[i].direction = 0;
    init[i].whereGoing = 0;

    loadCharacterImage("enemyCharacter", &init[i]);
  }
}

//
//敵の移動処理関数
//
void enemyMove(int* flag, Character* enemy, Character* player)
{
  int i, j;
  int randomNum;
  int xDistance, yDistance;

  for(i = 0; i < ENEMY_NUM; i ++)
  {
    if(getDistance(player, &enemy[i]) / IMG_SIZE > FIELD_OF_VISION)
    {
      randomNum = random() % (IMG_SIZE / ENEMY_STEP * 2);
      if(randomNum == 0)
      {
        randomNum = random() % 4;
        enemy[i].direction = randomNum;
      }
    }
    else
    {
      if(player->x < enemy[i].x)
      {
        xDistance = enemy[i].x - player->x;
      }
      else
      {
        xDistance = player->x - enemy[i].x;
      }

      if(player->y < enemy[i].y)
      {
        yDistance = enemy[i].y - player->y;
      }
      else
      {
        yDistance = player->y - enemy[i].y;
      }

      if(xDistance > yDistance)
      {
        if(player->x < enemy[i].x)
        {
          enemy[i].direction = 1;
        }
        else
        {
          enemy[i].direction = 3;
        }
      }
      else
      {
        if(player->y < enemy[i].y)
        {
          enemy[i].direction = 2;
        }
        else
        {
          enemy[i].direction = 0;
        }
      }

      if(*flag == 1)
      {
        enemy[i].direction = (enemy[i].direction + 2) % 4;
      }
    }

    switch (enemy[i].direction)
    {
      case 0:
        enemy[i].y += ENEMY_STEP;
        if(enemy[i].y >=  (MAP_ALL_Y_RANGE - 1) * IMG_SIZE + 1)
        {
          enemy[i].y = (MAP_ALL_Y_RANGE - 1) * IMG_SIZE;
        }
        break;
      case 1:
        enemy[i].x -= ENEMY_STEP;
        if(enemy[i].x < 0)
        {
          enemy[i].x = 0;
        }
        break;
      case 2:
        enemy[i].y -= ENEMY_STEP;
        if(enemy[i].y < 0)
        {
          enemy[i].y = 0;
        }
        break;
      case 3:
        enemy[i].x += ENEMY_STEP;
        if(enemy[i].x >=  (MAP_ALL_X_RANGE - 1) * IMG_SIZE + 1)
        {
          enemy[i].x = (MAP_ALL_X_RANGE - 1) * IMG_SIZE;
        }
        break;
    }
  }
}

//
//自機と敵との接触判定関数
//
int isCollisioning(Character* character, Character* enemys)
{
  int i;
  int rtn = 0;

  for(i = 0; i < ENEMY_NUM; i ++)
  {
    if(enemys[i].x < character->x + COLLISION_POSTPONEMENT
      && enemys[i].x > character->x - COLLISION_POSTPONEMENT
      && enemys[i].y < character->y + COLLISION_POSTPONEMENT
      && enemys[i].y > character->y - COLLISION_POSTPONEMENT)
    {
      rtn = 1;
    }
  }

  return rtn;
}

//
//自機と敵との距離取得関数
//
int getDistance(Character* character, Character* enemy)
{
  int rtn;
  int xDistance, yDistance;

  if(character->x < enemy->x)
  {
    xDistance = enemy->x - character->x;
  }
  else
  {
    xDistance = character->x - enemy->x;
  }

  if(character->y < enemy->y)
  {
    yDistance = enemy->y - character->y;
  }
  else
  {
    yDistance = character->y - enemy->y;
  }

  rtn = (int)sqrt((double)(xDistance * xDistance + yDistance * yDistance));

  return rtn;
}

//
//スタート画面表示関数
//
void dispStartDisplay(Img* messageImg, Img* titleImg, Map* map)
{
  Img message, title;

  putMap(map, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

  putImg(messageImg, WINDOW_WIDTH / 2 - messageImg->imgInfo.Width / 2, WINDOW_HEIGHT - 100, 255);

  putImg(titleImg, WINDOW_WIDTH / 2 - titleImg->imgInfo.Width / 2, 100, 255);
}

//
//ゲームオーバー画面表示関数
//
void dispGameOverDisplay(Img* messageImg, Img* gameOverImg, Map* map)
{
  Img message, gameOver;

  putMap(map, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

  putImg(messageImg, WINDOW_WIDTH / 2 - messageImg->imgInfo.Width / 2, WINDOW_HEIGHT - 100, 255);

  putImg(gameOverImg, WINDOW_WIDTH / 2 - gameOverImg->imgInfo.Width / 2, 100, 255);
}

//
//クリア画面表示関数
//
void dispGameClearDisplay(Img* messageImg, Img* gameClearImg, Map* map)
{
  putMap(map, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

  putImg(messageImg, WINDOW_WIDTH / 2 - messageImg->imgInfo.Width / 2, WINDOW_HEIGHT - 100, 255);

  putImg(gameClearImg, WINDOW_WIDTH / 2 - gameClearImg->imgInfo.Width / 2, 100, 255);
}

//
//クリア判定関数
//
int  isCleared(Character* player)
{
  int rtn = 0;

  if(player->x >= (MAP_ALL_X_RANGE - 2) * IMG_SIZE && player->y >= (MAP_ALL_Y_RANGE - 2) * IMG_SIZE)
  {
    rtn = 1;
  }

  return rtn;
}

//
//残り燃料表示関数
//
void dispFuel(int fuelNum)
{
  int devide;
  glColor3ub(255, 255, 255);
  glRasterPos2i(WINDOW_WIDTH - 18 * 4, WINDOW_WIDTH - 18 * 2);

  for(devide = 100; devide > 0; devide = devide / 10)
  {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (fuelNum / devide) % 10 + '0');
  }
}
