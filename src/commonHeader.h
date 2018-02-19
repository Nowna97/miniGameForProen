#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glpng.h>

#define WINDOW_WIDTH  (IMG_SIZE * MAP_DISP_X_RANGE) //ウィンドウサイズ
#define WINDOW_HEIGHT (IMG_SIZE * MAP_DISP_Y_RANGE)

#define IMG_SIZE 48 //ブロック, キャラクターなどの画像サイズ

#define MAP_ALL_X_RANGE 21  //迷路のマス数
#define MAP_ALL_Y_RANGE 21

#define MAP_DISP_X_RANGE 11 //画面に表示するマス数
#define MAP_DISP_Y_RANGE 11

#define ROAD_WIDTH 1  //通路の幅
#define WALL_THICKNESS 1  //壁の厚さ

#define RANDOM_CREATE_ROAD_TRY 4  //穴掘り法の周囲探索の試行回数

#define PLAYER_CHARACTER_STEP 4 //自機の歩幅
#define MOVE_POSTPONEMENT 4 //移動時の判定の猶予
#define COLLISION_POSTPONEMENT (IMG_SIZE / 2) //自機と敵との接触判定の猶予
#define FUEL_MAX 999  //燃料の初期値, 最大値

#define ENEMY_NUM 7 //敵の数
#define ENEMY_STEP 4  //敵の歩幅
#define FIELD_OF_VISION 5 //敵の視界

typedef struct
{
  GLuint img;
  pngInfo imgInfo;
}Img; //画像データを格納する構造体

typedef struct
{
  int isWall; //0..通路 1..壁
  Img img;  //Img構造体
}Cell;  //1マス分のデータを格納する構造体

typedef struct
{
  Cell cell[MAP_ALL_X_RANGE][MAP_ALL_Y_RANGE];  //cell構造体の2重配列
}Map; //迷路全体のデータを格納する構造体

typedef struct
{
  int x;
  int y;
  int direction;
  int whereGoing;
  Img img[4];
}Character; //自機, 敵のデータを格納する構造体

int mode; //0..初期化 1..タイトル画面 2..ゲーム本編 3..ゲームオーバー画面 4..クリア画面
Map gameMap;  //迷路全体
Character playerCharacter;  //自機
Character enemyCharacter[ENEMY_NUM];  //ENEMY_NUMの数の敵
int pushSpace;  //スペースキーが押されたか
int fuel; //残り燃料

//
//画像データ
//
Img title; //タイトル画面
Img gameOver; //ゲームオーバー画面
Img gameClear;  //クリア画面
Img pushSpaceKey; //「PUSH SPACE KEY」の文字
Img bigFog[3];  //消灯時の暗闇(3重)
Img smallFog[3];  //点灯時の暗闇(3重)

//
//callback.c
//
void display(void); //画面描画の際に呼び出されるコールバック関数
void reshape(int, int); //ウィンドウサイズの変更の際に呼び出されるコールバック関数
void timer(int); //タイマー割込で呼び出されるコールバック関数
void keyboard(unsigned char, int, int); //キーが押された際に呼び出されるコールバック関数
void keyboardUp(unsigned char, int, int); //キーが離された際に呼び出されるコールバック関数

//
//img.c
//
void loadImg(char*, Img*);  //画像データ読込関数
void putImg(Img*, int, int, int); //画像表示関数
void loadMapImage(Map*);  //迷路全体の画像データ読込関数
void putMap(Map*, int, int); //迷路の画像表示関数
void loadCharacterImage(char*, Character*); //キャラクターの画像データ読込関数
void putCharacter(Character*, int, int);  //キャラクターの画像表示関数
void putEnemy(Character*, int, int);  //敵の画像表示関数

//
//game.c
//
void initMap(Map*); //迷路全体の初期化関数
void initPlayerCharacter(Character*); //自機の初期化関数
void playerCharacterMove(Map*, Character*); //自機の移動処理関数
void initEnemy(Character*); //敵の初期化関数
void enemyMove(int*, Character*, Character*); //敵の移動処理関数
int  isCollisioning(Character*, Character*);  //自機と敵との接触判定関数
int  getDistance(Character*, Character*); //自機と敵との距離取得関数
void dispStartDisplay(Img*, Img*, Map*);  //スタート画面表示関数
void dispGameOverDisplay(Img*, Img*, Map*);  //ゲームオーバー画面表示関数
void dispGameClearDisplay(Img*, Img*, Map*);  //クリア画面表示関数
int  isCleared(Character*);  //クリア判定関数
void dispFuel(int);  //残り燃料表示関数
