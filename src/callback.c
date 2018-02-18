#include "commonHeader.h"
//
//  ウィンドウの表示内容を更新する
//
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  playerCharacterMove(&gameMap, &playerCharacter);
  enemyMove(&pushingSpace, &enemyCharacter, &playerCharacter);
  putMap(&gameMap, IMG_SIZE + playerCharacter.x, IMG_SIZE + playerCharacter.y);
  putCharacter(&playerCharacter, IMG_SIZE + playerCharacter.x, IMG_SIZE + playerCharacter.y);
  putEnemy(&enemyCharacter, IMG_SIZE + playerCharacter.x, IMG_SIZE + playerCharacter.y);
  printf("%d\n", getDistance(&playerCharacter, &enemyCharacter[0]) / IMG_SIZE);
  glFlush();
  glutSwapBuffers();
}

//
//  ウィンドウのサイズ変更が発生したときに座標系を再設定する関数
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
//  タイマー割り込みで画面を描画し直す
//
void timer(int t)
{
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

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
      pushingSpace = !pushingSpace;
      break;
  }
}

void keyboardUp(unsigned char key, int x, int y)
{
  if(playerCharacter.whereGoing == key)
  {
    playerCharacter.whereGoing = 0;
  }
}
