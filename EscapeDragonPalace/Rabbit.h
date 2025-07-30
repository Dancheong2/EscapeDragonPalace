#pragma once

#include "weapon.h"
#include "item.h"
#include "screens.h"

// --------------------------------------------------

bool MapEnd();
bool GetKeyW();
bool GetKeyA();
bool GetKeyD();
bool GetKeyS();
bool IsNearItem();
void SetIsNearItem(bool src);
bool StageClear();
bool IsOverlap();
void CheckItemPickup();
void UpdateSpeedBuffs();
void ClearRabbitAt();
void DrawRabbitAt();
void RabbitCAnim();
void GetInput();
void ApplyGravity();
bool CheckGround();
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

SpeedBuff speedBuffs[MAX_BUFFS];




