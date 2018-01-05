#include "commonHeader.h"

//
//  ウィンドウの表示内容を更新する
//
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
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
    glutTimerFunc(1000, timer, 0);
}
