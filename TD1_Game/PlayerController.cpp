#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

const int kWindowWidth = 1920;
const int kWindowHeight = 1080;

/*********************************
	構造体宣言ここから
*********************************/

/******** 二次元ベクトル **********/

typedef struct vector2 {

	float x; //x
	float y; //y

};

/******** 距離 **********/

typedef struct Distance {

	vector2 distance; //距離xy
	float length; //実際距離

};

/******** キャラクター **********/

typedef struct chara {

	vector2 translate; //位置
	vector2 moveDirection; //動作方向
	float vectorLength; //ベクトル長さ

	float radius; //当たり判定半径

	float speed; //スピード
	float defSpeed; //スピードデフォルト/

	int HP; //キャラクタHP

	int damage; //与えるダメージ

	int graph; //キャラ画像
	int graphRadius; //画像半径

};

/*********************************
	構造体宣言ここまで
*********************************/

/*********************************
	変数宣言ここから
*********************************/

/******** ワールド座標原点 **********/
vector2 worldPosOrigin{

	0, //x
	kWindowHeight //y

};

/******** スクロール **********/

//開始座標
vector2 scroolStartPos{

	kWindowWidth - kWindowWidth / 2, //x
	worldPosOrigin.y - kWindowHeight + kWindowHeight / 2 //y

};

//スクロール値
vector2 scrool{

	0.0f, //x
	0.0f //y

};

/******** プレイヤー **********/
chara player{

	kWindowWidth * 1.5f, kWindowHeight, //translate x, y
	0.0f, 0.0f, //moveDirection x, y
	0.0f, //vectorLength

	64.0f, //radius

	5.0f, //speed
	5.0f, //defSpeed

	1, //HP

	10, //damage

	Novice::LoadTexture("./resources/graph/player/player.png"), //graph
	128 //graphRadius

};

float theta = 0.0f;

//スペースキートリガー用
int isPressSpace = false;

//チャージできるか
int canCharge = true;
//現在チャージしているか
int isCharging = false;
//チャージが完了しているか
int compCharge = false;

//攻撃中か
int isAttacking = false;

//チャージされているパワー
float chargePower = 0.0f;
//パワーの最大値
float maxPower = 60.0f;

//チャージ可能までのクールタイム
float chargeCoolTime = 0.0f;
//チャージ可能までのクールタイムのデフォルト値
float defChargeCoolTime = 120.0f;

/*********************************
	変数宣言ここまで
*********************************/


void PlayerMove() {


	/******** プレイヤー移動 **********/

	//ベクトル初期化
	player.moveDirection.x = 0.0f;
	player.moveDirection.y = 0.0f;

	//移動方向指定
	if (keys[DIK_UP] || keys[DIK_W]) {

		player.moveDirection.y++; //上

	}

	if (keys[DIK_LEFT] || keys[DIK_A]) {

		player.moveDirection.x--; //左

	}

	if (keys[DIK_DOWN] || keys[DIK_S]) {

		player.moveDirection.y--; //下

	}

	if (keys[DIK_RIGHT] || keys[DIK_D]) {

		player.moveDirection.x++; //右

	}

	if (isCharging == false && isAttacking == false) {

		//ベクトルの長さを求める
		player.vectorLength = sqrt(pow(player.moveDirection.x, 2) + pow(player.moveDirection.y, 2));

		//ベクトルの長さが0以外の時
		if (player.vectorLength != 0.0f) {

			//x方向の移動
			player.translate.x += player.moveDirection.x / player.vectorLength * player.speed;

			//y方向の移動
			player.translate.y += player.moveDirection.y / player.vectorLength * player.speed;

		}
		else {

			//x方向の移動
			player.translate.x += player.moveDirection.x * player.speed;

			//y方向の移動
			player.translate.y += player.moveDirection.y * player.speed;

		}

	}

	if (player.translate.x <= 0 + player.radius / 2) {

		player.translate.x = player.radius / 2;

	}
	else if (player.translate.x >= kWindowWidth * 3 - player.radius / 2) {

		player.translate.x = kWindowWidth * 3 - player.radius / 2;

	}

	if (player.translate.y <= 0 + player.radius / 2) {

		player.translate.y = player.radius / 2;

	}
	else if (player.translate.y >= kWindowHeight * 2 - player.radius / 2) {

		player.translate.y = kWindowHeight * 2 - player.radius / 2;

	}

}