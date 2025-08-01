#include "init.h"
#include "Rabbit.h"
#include "weapon.h"

#ifndef MONSTER_H
#define MONSTER_H

#define FISH_WIDTH 15
#define FISH_HEIGHT 3
#define FISH_HP 3

#define CRAB_WIDTH 13
#define CRAB_HEIGHT 3
#define CRAB_HP 5

#define INVINCIBLE_TIME 1000  // 1�� �����ð�

#define Right 1
#define Left 0


typedef enum {
    MONSTER_FISH,
    MONSTER_CRAB,
    MONSTER_CLAM,
    MONSTER_TURTLE,
    MONSTER_TYPE_COUNT
} MonsterType;

typedef struct {
    int x, y;           // ��ġ
    int dir;            // ���� (1: ������, -1: ����)
    int hp;             // ü��
    int alive;          // ��������
    MonsterType type;   // ���� ����
    int isDamaged;      // �ǰ� ����(���� ����)
    unsigned int lastHitTime;  // ������ �ǰ� �ð�
} Monster;
extern Monster fish;
extern Monster crab;

void UpdateMonster(Monster fish);
// ����� �Լ�
void InitFish(Monster fish, int x, int y);
void UpdateFish(Monster fish, unsigned int now);
void DrawFish(Monster fish);
void HitFish(Monster fish, unsigned int now, int damage);

// �ɰ� �Լ�
void InitCrab(Monster crab, int x, int y);
void UpdateCrab(Monster crab, unsigned int now);
void DrawCrab(Monster crab);
void HitCrab(Monster crab, unsigned int now, int damage);
// (����, �ڶ� �Լ��� ���� �������� �߰�)

#endif