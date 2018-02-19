#include "commonHeader.h"

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("miniGame");
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
  glClearColor(0, 0, 0, 1.0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  //  コールバック関数の登録
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutTimerFunc(100, timer, 0);

  mode = 0;

  loadImg("./resource/pushSpaceKey.png", &pushSpaceKey);
  loadImg("./resource/gameClear.png", &gameClear);
  loadImg("./resource/gameOver.png", &gameOver);
  loadImg("./resource/title.png", &title);
  loadImg("./resource/bigFog1.png", &bigFog[0]);
  loadImg("./resource/bigFog2.png", &bigFog[1]);
  loadImg("./resource/bigFog3.png", &bigFog[2]);
  loadImg("./resource/smallFog1.png", &smallFog[0]);
  loadImg("./resource/smallFog2.png", &smallFog[1]);
  loadImg("./resource/smallFog3.png", &smallFog[2]);
  
  //  イベントループ突入
  glutMainLoop();

  return(0);
}
