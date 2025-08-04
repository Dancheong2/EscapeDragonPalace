#include "Rabbit.h"
#include "weapon.h"
#include "clam.h"
#include "crab.h"
#include "fish.h"

#define MONSTER_H

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
    MyPoint pos;        // ��ġ
    int dir;            // ���� 
    int hp;             // ü��
    bool alive;          // ��������
    MonsterType type;   // ���� ����
    int isDamaged;      // �ǰ� ����(���� ����)
    unsigned int lastHitTime;  // ������ �ǰ� �ð�
    MapStatus monsterStatus; 
} Monster;

void UpdateMonster();

// (�ڶ� �Լ��� ���� �������� �߰�)