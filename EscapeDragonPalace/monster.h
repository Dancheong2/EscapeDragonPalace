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

#define ClAM_WIDTH 1
#define CLAM_HEIGHT 1
#define CLAM_HP 1

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
    int dir;            // ���� 
    int hp;             // ü��
    int alive;          // ��������
    MonsterType type;   // ���� ����
    int isDamaged;      // �ǰ� ����(���� ����)
    unsigned int lastHitTime;  // ������ �ǰ� �ð�
    MapStatus monsterStatus; 
} Monster;

void UpdateMonster();
// ����� �Լ�
void UpdateFish(unsigned int now);
void DrawFish();
void HitFish(unsigned int now, int damage);

// �ɰ� �Լ�
void UpdateCrab(unsigned int now);
void DrawCrab();
void HitCrab(unsigned int now, int damage);
void ChasunsignedeCrab(unsigned int slap,int Paware, int Maware);

//���� �Լ�
void TriggerClam();
void UpdateClam();
void DrawClam();

// (�ڶ� �Լ��� ���� �������� �߰�)