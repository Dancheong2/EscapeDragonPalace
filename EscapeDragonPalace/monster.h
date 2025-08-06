#include "weapon.h"
#include "map.h"
#include "clam.h"
#include "crab.h"
#include "fish.h"

#define MONSTER_H

#define INVINCIBLE_TIME 1000  // 1�� �����ð�

#define Right 0
#define Left 1

#define MONSTER_Y 21 // ���� Y��ǥ �ʱ� ��ġ

#define MAX_Monster_COUNT 100


typedef enum MonsterType {
    MONSTER_FISH,
    MONSTER_CRAB,
    MONSTER_CLAM,
    MONSTER_TURTLE,
    MONSTER_TYPE_COUNT
} MonsterType;

typedef struct Monster {
    MyPoint pos;        // ��ġ
    int dir;            // ���� 
    int hp;             // ü��
    bool alive;          // ��������
    MonsterType type;   // ���� ����
    bool isDamaged;      // �ǰ� ����(���� ����)
    unsigned int lastHitTime;  // ������ �ǰ� �ð�
    MapStatus mapStatus; // �� �����Ҷ� ���
} Monster;

extern Monster monsterList[MAX_Monster_COUNT];
extern int numMonster;

void UpdateMonster();
void HitMonster(Monster* monster, Weapon* weapon, unsigned int now);
void InitMonster();
void DrawMonster();

// (�ڶ� �Լ��� ���� �������� �߰�)