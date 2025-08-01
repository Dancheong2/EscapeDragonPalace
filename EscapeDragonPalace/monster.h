#include "init.h"
#include "Rabbit.h"
#include "weapon.h"

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

#define MONSTER_Y 21 // ���� Y��ǥ �ʱ� ��ġ


typedef enum MonsterType {
    MONSTER_FISH,
    MONSTER_CRAB,
    MONSTER_CLAM,
    MONSTER_TURTLE,
    MONSTER_TYPE_COUNT
} MonsterType;

typedef struct Monster {
    int x, y;           // ��ġ
    int dir;            // ���� (1: ������, -1: ����)
    int hp;             // ü��
    int alive;          // ��������
    MonsterType type;   // ���� ����
    int isDamaged;      // �ǰ� ����(���� ����)
    unsigned int lastHitTime;  // ������ �ǰ� �ð�
} Monster;

void UpdateMonster();
// ����� �Լ�
void InitFish(int x, int y);
void UpdateFish(unsigned int now);
void DrawFish();
void HitFish(unsigned int now, int damage);

// �ɰ� �Լ�
void InitCrab(int x, int y);
void UpdateCrab(unsigned int now);
void DrawCrab();
void HitCrab(unsigned int now, int damage);
// (����, �ڶ� �Լ��� ���� �������� �߰�)