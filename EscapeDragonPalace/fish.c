#include "monster.h"

char fishGraphic[2][FISH_HEIGHT][FISH_WIDTH] = {
    {
        "  _______   ",
        " /o��))��\\/)",
        " \\_______/\\)"
    }, // ���� �׸� 0
    {
        "    _______  ",
        " (\\/��((��o\\",
        " (/\\_______/ "
    },// ������ �׸� 1
};

void InitFish(Monster fish, int x, int y) {
    fish.x = x;
    fish.y = y;
    fish.dir = 1;
    fish.hp = FISH_HP;
    fish.alive = 1;
    fish.type = MONSTER_FISH;
    fish.isDamaged = 0;
    fish.lastHitTime = 0;  // ������ �ǰ� �ð� �ʱ�ȭ
}

void UpdateFish(Monster fish, unsigned int now) {
    if (!fish.alive) return;

    // �����ð� ������ �ǰ� ���� ����
    if (fish.isDamaged && now - fish.lastHitTime >= INVINCIBLE_TIME) {
        fish.isDamaged = 0;
    }

    // �̵�
    fish.x += fish.dir;

    // �� �浹 �� ���� ��ȯ
    if (fish.x <= 0) {
        fish.x = 0;
        fish.dir = 1;
    }
    if (fish.x + FISH_WIDTH >= 82) {
        fish.x = 80 - FISH_WIDTH + 2;
        fish.dir = -1;
    }
}

void DrawFish(Monster fish) {
    for (int y = 0; y < FISH_HEIGHT; y++)
    {
        _SetColor(fish.isDamaged ? 12 : 9);

        int idx;

        if (fish.dir == 1){
            idx = Right;

            char* line = fishGraphic[idx][y];
            int len = strlen(line);

            for (int x = 0; x < len; x++)
            {
                if (line[x] != ' ')
                {
                    _DrawText(fish.x + x, fish.y + y, (char[]) { line[x], '\0' });
                }
            }
        }
        else{
            idx = Left;

            char* line = fishGraphic[idx][y];
            int len = strlen(line);

            for (int x = 0; x < len; x++)
            {
                if (line[x] != ' ')
                {
                    _DrawText(fish.x + x, fish.y + y, (char[]) { line[x], '\0' });
                }
            }          
        }

    }

    _SetColor(15);
}


// ���� �ǰ� �Լ� (ü�� ����, �ǰ� ���� ����)
void HitFish(Monster fish, unsigned int now, int damage) {
    if (fish.isDamaged) return; // �������̸� ������ ����

    fish.hp--;
    fish.isDamaged = 1;
    fish.lastHitTime = now;

    if (fish.hp <= 0) {
        fish.alive = 0; // ���� ó��
    }
}

void UpdateMonster(Monster fish)
{
	unsigned int now = _GetTickCount();

	int damage = 1; // ���� ���ݷ� �޾ƿ;� ��

	if (fish.alive) {
		UpdateFish(fish, now);
	}

    if (fish.isDamaged)
    {
        HitFish(fish, now, damage);
    }
}
