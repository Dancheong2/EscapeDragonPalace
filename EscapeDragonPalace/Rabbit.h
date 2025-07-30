#pragma once

#include "weapon.h"
#include "item.h"


// --------------------------------------------------

bool IsOverlap();
void CheckItemPickup();
void UpdateSpeedBuffs();
void ClearRabbitAt();
void DrawRabbitAt();
void RabbitCAnim();
void GetInput();
void ApplyGravity();
void CheckGround();
void PlayerYPosition();
void JumpFN();
void AttackFN();
void moveFN();
bool ISOnGoal();
void ClearInputBuffer();
void UpdatePlayer();
void DrawPlayer();
void DrawHealth();
void InitPlayer();

// --------------------------------------------------

#define RabbitX 25 // Rabbit char ���� ũ��
#define RabbitY 3 // Rabbit char ���� ũ��

#define JUMP_POWER -2.5f // ���� ���� (������ �� ���� ���� ������)
#define GRAVITY 0.5f // �߷� ���ӵ�
#define MAX_FALL_SPEED 4.0f  // �ִ� ���� �ӵ�

#define MAX_BUFFS 10



// --------------------------------------------------

typedef struct Player
{
	MyPoint Pos; // �÷��̾� ��ġ
	float Speed; // �÷��̾� �̵� �ӵ�
	int Health; // �÷��̾� ü��

	Weapon* HeldWeapon; // ���� (0 = ���, 1 = �ܰ�, 2 = â)

	float VelY; // Y�� �ӵ� (����, ���� ��)
	bool IsJumping; // ���� ������ ����
	int Direction; // �÷��̾� ���� (0 = ������, 1 = ����)

	bool IsAttacking;      // ���� ������ ����
	DWORD attackStartTime; // ���� ���� �ð�
	int attackDuration; // ���� ���� �ð� (ms)

	int AttackFrame;       // ���� �ִϸ��̼� ������ ī����
	int AttackFrameMax;    // ���� ���⿡ �´� ���� �ִϸ��̼� ������ ����
}Player;
Player player;


typedef struct SpeedBuff {
	float amount;       // ������
	DWORD endTime;      // ���� �ð� (ms)
	bool active;
} SpeedBuff;


typedef struct Rect {
	float x, y, w, h;
} Rect;

bool IsOverlap(Rect player, Rect Obj);
Rect GetPlayerRect();
Rect GetItemRect(Item item);
void CheckItemPickup();
void UpdateSpeedBuffs();
bool isNearItem = false;

SpeedBuff speedBuffs[MAX_BUFFS];

float amount;


char g_Key;

char Rabbit[14][RabbitY][RabbitX] =
{
	{
		"        (\\(\\",
		"        ('-')",
		"       o(��--|====>"
	}, // ��� ������ �⺻
	{
		"         /)/)",
		"        ('-')",
		"  <====|--��)o"
	}, // ��� ���� �⺻
	{
		"        (\\(\\ ",
		"        ('-')",
		"       o(����--|====>"
	}, // ��� ������ ����
	{
		"         /)/) ",
		"        ('-') ",
		"<====|--����)o"
	}, // ��� ���� ����
	{
		"        (\\(\\ ",
		"        ('-')",
		"       o(��-|=>"
	}, // �ܰ� ������ �⺻
	{
		"         /)/) ",
		"        ('-') ",
		"      <=|-��)o"
	}, // �ܰ� ���� �⺻
	{
		"        (\\(\\ ",
		"        ('-')",
		"       o(����-|=>"
	}, // �ܰ� ������ ����
	{
		"         /)/) ",
		"        ('-') ",
		"    <=|-����)o"
	}, // �ܰ� ���� ����
	{
		"        (\\(\\ ",
		"        ('-')",
		"       o(��------>"
	}, // â ������ �⺻
	{
		"         /)/) ",
		"        ('-') ",
		"   <------��)o"
	}, // â ���� �⺻
	{
		"        (\\(\\ ",
		"        ('-')",
		"       o(����------>"
	}, // â ������ ����
	{
		"         /)/) ",
		"        ('-') ",
		" <------����)o"
	}, // â ���� ����
	{
		"        (\\(\\",
		"        ('-')",
		"       o(   )"
	}, // �÷��̾� ������
	{
		"         /)/) ",
		"        ('-') ",
		"        (   )o"
	}, // �÷��̾� ����
};


bool g_KeyW = false;
bool g_KeyA = false;
bool g_KeyD = false;

bool halfHealth = false; // ü�� ��ĭ

bool g_MouseClick = false;

bool stageClear = false; // �������� Ŭ���� ����


//�ִϸ��̼� ���� ����
int animFrame;         // 0 ~ jumpFrames*2-1 (up + down)
int animRepeatCount;   // �ִϸ��̼� �ݺ� Ƚ��
int jumpFrames;  // �ö󰡴� ������ ����
int maxRepeats;  // �ִ� �ݺ� Ƚ��
int centerX;
int baseY;
int jumpHeight;
int animFramesTotal; // ��ü �ִϸ��̼� ���� (up+down)

bool animGoingUp = true;  // ���� �� �ö󰡴��� ����

