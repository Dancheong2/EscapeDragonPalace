#include "monster.h"

// ���� ����
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

Monster g_Fish = { 5, MONSTER_Y, Right, FISH_HP, 1, MONSTER_FISH, 0, 0 };

void UpdateFish(unsigned int now) {
	if (!g_Fish.alive) return;

	// �����ð� ������ �ǰ� ���� ����
	if (g_Fish.isDamaged && now - g_Fish.lastHitTime >= INVINCIBLE_TIME) {
		g_Fish.isDamaged = 0;
	}

	// �̵�
	g_Fish.x += g_Fish.dir;

	// �� �浹 �� ���� ��ȯ
	if (g_Fish.x <= 0) {
		g_Fish.x = 0;
		g_Fish.dir = 1;
	}
	if (g_Fish.x + FISH_WIDTH >= 82) {
		g_Fish.x = 80 - FISH_WIDTH + 2;
		g_Fish.dir = -1;
	}
}

void DrawFish() {
	for (int y = 0; y < FISH_HEIGHT; y++)
	{
		_SetColor(g_Fish.isDamaged ? 12 : 9);

		if (g_Fish.dir == Right) // ����� ������ �������� ��
		{
			char* line = fishGraphic[Right][y];
			int len = strlen(line);

			for (int x = 0; x < len; x++)
			{
				if (line[x] != ' ')
				{
					_DrawText(g_Fish.x + x, g_Fish.y + y, (char[]) { line[x], '\0' });
				}
			}
		}
		else // ����� ������ ������ ��
		{
			char* line = fishGraphic[Left][y];
			int len = strlen(line);

			for (int x = 0; x < len; x++)
			{
				if (line[x] != ' ')
				{
					_DrawText(g_Fish.x + x, g_Fish.y + y, (char[]) { line[x], '\0' });
				}
			}
		}

	}

	_SetColor(15);
}


// ���� �ǰ� �Լ� (ü�� ����, �ǰ� ���� ����)
void HitFish(unsigned int now, int damage) {
	if (g_Fish.isDamaged) return; // �������̸� ������ ����

	g_Fish.hp--;
	g_Fish.isDamaged = 1;
	g_Fish.lastHitTime = now;

	if (g_Fish.hp <= 0) {
		g_Fish.alive = 0; // ���� ó��
	}
}

void UpdateMonster()
{
	unsigned int now = _GetTickCount();
	UpdateCrab(now);
	UpdateClam();
	int damage = 1; // ���� ���ݷ� �޾ƿ;� ��

	if (g_Fish.alive) {
		UpdateFish(now);
	}

	if (g_Fish.isDamaged)
	{
		HitFish(now, damage);
	}
}
