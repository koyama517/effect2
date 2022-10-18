#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

const int kWindowWidth = 1920;
const int kWindowHeight = 1080;

/*********************************
	�\���̐錾��������
*********************************/

/******** �񎟌��x�N�g�� **********/

typedef struct vector2 {

	float x; //x
	float y; //y

};

/******** ���� **********/

typedef struct Distance {

	vector2 distance; //����xy
	float length; //���ۋ���

};

/******** �L�����N�^�[ **********/

typedef struct chara {

	vector2 translate; //�ʒu
	vector2 moveDirection; //�������
	float vectorLength; //�x�N�g������

	float radius; //�����蔻�蔼�a

	float speed; //�X�s�[�h
	float defSpeed; //�X�s�[�h�f�t�H���g/

	int HP; //�L�����N�^HP

	int damage; //�^����_���[�W

	int graph; //�L�����摜
	int graphRadius; //�摜���a

};

/*********************************
	�\���̐錾�����܂�
*********************************/

/*********************************
	�ϐ��錾��������
*********************************/

/******** ���[���h���W���_ **********/
vector2 worldPosOrigin{

	0, //x
	kWindowHeight //y

};

/******** �X�N���[�� **********/

//�J�n���W
vector2 scroolStartPos{

	kWindowWidth - kWindowWidth / 2, //x
	worldPosOrigin.y - kWindowHeight + kWindowHeight / 2 //y

};

//�X�N���[���l
vector2 scrool{

	0.0f, //x
	0.0f //y

};

/******** �v���C���[ **********/
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

//�X�y�[�X�L�[�g���K�[�p
int isPressSpace = false;

//�`���[�W�ł��邩
int canCharge = true;
//���݃`���[�W���Ă��邩
int isCharging = false;
//�`���[�W���������Ă��邩
int compCharge = false;

//�U������
int isAttacking = false;

//�`���[�W����Ă���p���[
float chargePower = 0.0f;
//�p���[�̍ő�l
float maxPower = 60.0f;

//�`���[�W�\�܂ł̃N�[���^�C��
float chargeCoolTime = 0.0f;
//�`���[�W�\�܂ł̃N�[���^�C���̃f�t�H���g�l
float defChargeCoolTime = 120.0f;

/*********************************
	�ϐ��錾�����܂�
*********************************/


void PlayerMove() {


	/******** �v���C���[�ړ� **********/

	//�x�N�g��������
	player.moveDirection.x = 0.0f;
	player.moveDirection.y = 0.0f;

	//�ړ������w��
	if (keys[DIK_UP] || keys[DIK_W]) {

		player.moveDirection.y++; //��

	}

	if (keys[DIK_LEFT] || keys[DIK_A]) {

		player.moveDirection.x--; //��

	}

	if (keys[DIK_DOWN] || keys[DIK_S]) {

		player.moveDirection.y--; //��

	}

	if (keys[DIK_RIGHT] || keys[DIK_D]) {

		player.moveDirection.x++; //�E

	}

	if (isCharging == false && isAttacking == false) {

		//�x�N�g���̒��������߂�
		player.vectorLength = sqrt(pow(player.moveDirection.x, 2) + pow(player.moveDirection.y, 2));

		//�x�N�g���̒�����0�ȊO�̎�
		if (player.vectorLength != 0.0f) {

			//x�����̈ړ�
			player.translate.x += player.moveDirection.x / player.vectorLength * player.speed;

			//y�����̈ړ�
			player.translate.y += player.moveDirection.y / player.vectorLength * player.speed;

		}
		else {

			//x�����̈ړ�
			player.translate.x += player.moveDirection.x * player.speed;

			//y�����̈ړ�
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