#include "monster.h"
#include "init.h"

// ������ �׸�
char fishRight[FISH_HEIGHT][FISH_WIDTH] = {
    "  ______   ",
    " / o )) \\/)",
    " \\______/\\)"
};

// ���� �׸�
char fishLeft[FISH_HEIGHT][FISH_WIDTH] = {
    "   ______  ",
    "(\\/ (( o \\ ",
    "(/\\______/ "
};

void InitFish(Monster* m, int x, int y) {
    m->x = x;
    m->y = y;
    m->dir = 1;
    m->hp = FISH_HP;
    m->alive = 1;
    m->type = MONSTER_FISH;
    m->isDamaged = 0;
    m->lastHitTime = 0;  // ������ �ǰ� �ð� �ʱ�ȭ
}

void UpdateFish(Monster* m, unsigned int now) {
    if (!m->alive) return;

    // �����ð� ������ �ǰ� ���� ����
    if (m->isDamaged && now - m->lastHitTime >= INVINCIBLE_TIME) {
        m->isDamaged = 0;
    }

    // �̵�
    m->x += m->dir;

    // �� �浹 �� ���� ��ȯ
    if (m->x <= 0) {
        m->x = 0;
        m->dir = 1;
    }
    if (m->x + FISH_WIDTH >= 80) {
        m->x = 80 - FISH_WIDTH;
        m->dir = -1;
    }
}

void DrawFish(Monster* m) {
    for (int i = 0; i < FISH_HEIGHT; i++) {
        _SetColor(m->isDamaged ? 12 : 9);
        if (m->dir == 1)
            _DrawText(m->x, m->y + i, fishRight[i]);
        else
            _DrawText(m->x, m->y + i, fishLeft[i]);
    }
    _SetColor(15);
}


// ���� �ǰ� �Լ� (ü�� ����, �ǰ� ���� ����)
void HitFish(Monster* m, unsigned int now, int damage) {
    if (m->isDamaged) return; // �������̸� ������ ����

    m->hp--;
    m->isDamaged = 1;
    m->lastHitTime = now;

    if (m->hp <= 0) {
        m->alive = 0; // ���� ó��
    }
}
