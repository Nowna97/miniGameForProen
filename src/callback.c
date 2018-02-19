#include "commonHeader.h"

//
//画面描画の際に呼び出されるコールバック関数
//
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  switch (mode)
  {
    case 0: //init
      pushSpace = 0;
      fuel = FUEL_MAX;
      initMap(&gameMap);
      initPlayerCharacter(&playerCharacter);
      initEnemy(&enemyCharacter);
      mode = 1;
      break;
    case 1: //title
      dispStartDisplay(&pushSpaceKey, &title, &gameMap);
      if(pushSpace == 1)
      {
        pushSpace = 0;
        mode = 2;
      }
      break;
    case 2: //game
      playerCharacterMove(&gameMap, &playerCharacter);
      enemyMove(&pushSpace, &enemyCharacter, &playerCharacter);
      putMap(&gameMap, playerCharacter.x, playerCharacter.y);
      putCharacter(&playerCharacter, playerCharacter.x, playerCharacter.y);
      putEnemy(&enemyCharacter, playerCharacter.x, playerCharacter.y);

      if(pushSpace == 1 && fuel > 0)
      {
        fuel -= 1;

        putImg(&smallFog[0], 0, 0, 150);
        putImg(&smallFog[1], 0, 0, 200);
        putImg(&smallFog[2], 0, 0, 255);
      }
      else
      {
        putImg(&bigFog[0], 0, 0, 150);
        putImg(&bigFog[1], 0, 0, 200);
        putImg(&bigFog[2], 0, 0, 255);
      }
      dispFuel(fuel);
      if(isCollisioning(&playerCharacter, &enemyCharacter) == 1)
      {
        pushSpace = 0;
        mode = 3;
      }
      else if(isCleared(&playerCharacter) == 1)
      {
        pushSpace = 0;
        mode = 4;
      }
      break;
    case 3: //gameOver
      dispGameOverDisplay(&pushSpaceKey, &gameOver, &gameMap);
      if(pushSpace == 1)
      {
        pushSpace = 0;
        mode = 0;
      }
      break;
    case 4: //gameClear
      dispGameClearDisplay(&pushSpaceKey, &gameClear, &gameMap);
      if(pushSpace == 1)
      {
        pushSpace = 0;
        mode = 0;
      }
      break;
  }

  glFlush();
  glutSwapBuffers();
}

//
//ウィンドウサイズの変更の際に呼び出されるコールバック関数
//
void reshape(int w, int h)
{
  glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glScaled(1, -1, 1);
  glTranslated(0, -h, 0);
}

//
//タイマー割込で呼び出されるコールバック関数
//
void timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

//
//キーが押された際に呼び出されるコールバック関数
//
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 's':
      playerCharacter.direction = 0;
      playerCharacter.whereGoing = 's';
      break;
    case 'a':
      playerCharacter.direction = 1;
      playerCharacter.whereGoing = 'a';
      break;
    case 'w':
      playerCharacter.direction = 2;
      playerCharacter.whereGoing = 'w';
      break;
    case 'd':
      playerCharacter.direction = 3;
      playerCharacter.whereGoing = 'd';
      break;
    case ' ':
      pushSpace = !pushSpace;
      break;
  }
}

//
//キーが離された際に呼び出されるコールバック関数
//
void keyboardUp(unsigned char key, int x, int y)
{
  if(playerCharacter.whereGoing == key)
  {
    playerCharacter.whereGoing = 0;
  }
}
