#include "monster.h"

char fish[2][FISH_HEIGHT][FISH_WIDTH] = {
    {
        "  ______   ",
        " /o��))��\\/)",
        " \\______/\\)"
    }, // ���� �׸� 0
    {
        "    ______  ",
        "(\\/��((��o\\ ",
        " (/\\______/ "
    },// ������ �׸� 1
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

void UpdateFish(unsigned int now) {
    if (!m->alive) return;

    // �����ð� ������ �ǰ� ���� ����
    if (m->isDamaged && now - m->lastHitTime >= INVINCIBLE_TIME) {
        m->isDamaged = 0;
    }

    // �̵�
    m->x += m->dir;

    // �� �浹 �� ���� ��ȯ
    if (m->x <= 2) {
        m->x = 0 + 2;
        m->dir = 1;
    }
    if (m->x + FISH_WIDTH >= 82) {
        m->x = 80 - FISH_WIDTH + 2;
        m->dir = -1;
    }
}

void DrawFish() {
    for (int y = 0; y < FISH_HEIGHT; y++)
    {
        _SetColor(m->isDamaged ? 12 : 9);

        int idx;

        if (m->dir == 1){
            idx = Right;

            char* line = fish[idx][y];
            int len = strlen(line);

            for (int x = 0; x < len; x++)
            {
                if (line[x] != ' ')
                {
                    _DrawText(m->x + x, m->y + y, (char[]) { line[x], '\0' });
                }
            }
        }
        else{
            idx = Left;

            char* line = fish[idx][y];
            int len = strlen(line);

            for (int x = 0; x < len; x++)
            {
                if (line[x] != ' ')
                {
                    _DrawText(m->x + x, m->y + y, (char[]) { line[x], '\0' });
                }
            }          
        }

    }

    _SetColor(15);
}


// ���� �ǰ� �Լ� (ü�� ����, �ǰ� ���� ����)
void HitFish(unsigned int now, int damage) {
    if (m->isDamaged) return; // �������̸� ������ ����

    m->hp--;
    m->isDamaged = 1;
    m->lastHitTime = now;

    if (m->hp <= 0) {
        m->alive = 0; // ���� ó��
    }
}

void UpdateMonster()
{
	unsigned int now = _GetTickCount();

	int damage = 1; // ���� ���ݷ� �޾ƿ;� ��

	if (m->alive) {
		UpdateFish(now);
	}

    if (m->isDamaged)
    {
        void HitFish(now, damage);
    }
}
