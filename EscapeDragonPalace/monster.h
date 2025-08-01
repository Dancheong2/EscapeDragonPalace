#include "init.h"

#ifndef MONSTER_H
#define MONSTER_H

#define FISH_WIDTH 15
#define FISH_HEIGHT 3
#define FISH_HP 3

#define CRAB_WIDTH 11
#define CRAB_HEIGHT 3
#define CRAB_HP 5

#define INVINCIBLE_TIME 1000  // 1�� �����ð�

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

// ����� �Լ�
void InitFish(Monster* m, int x, int y);
void UpdateFish(Monster* m, unsigned int now);
void DrawFish(const Monster* m);
void HitFish(Monster* m, unsigned int now, int damage);
/* �ɰ��ϰ� �����Ұ��� - ��ȯ
// �ɰ� �Լ�
void InitCrab(Monster* m, int x, int y);
void UpdateCrab(Monster* m, unsigned int now, int playerX, int playerY);
void DrawCrab(const Monster* m);
void HitCrab(Monster* m, unsigned int now, int damage);
*/
// (����, �ڶ� �Լ��� ���� �������� �߰�)

#endif