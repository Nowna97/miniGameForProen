#include "commonHeader.h"

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
}
