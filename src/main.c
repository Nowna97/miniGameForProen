#include "commonHeader.h"

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("miniGame");
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
  glClearColor(0, 0, 0, 1.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  //  コールバック関数の登録
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(1000, timer, 0);

  initGame();

  //  イベントループ突入
  glutMainLoop();

  return(0);
}
