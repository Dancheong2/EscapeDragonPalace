#include "Rabbit.h"
Monster g_Fish = { { 5, MONSTER_Y }, Right, FISH_HP, true, MONSTER_FISH, 0, 0 }; // �����

bool GetFishAlive()
{
	return g_Fish.alive;
}

bool GetFishIsDamaged()
{
	return g_Fish.isDamaged;
}

MyPoint GetFishPos()
{
	return g_Fish.pos;
}

int GetFishDir()
{
	return g_Fish.dir;
}


void UpdateFish(unsigned int now) {

	// monster.c UpdateMonster()�� �̵�

}

/*	// ������
void DrawFish() {
	for (int y = 0; y < FISH_HEIGHT; y++)
	{
		_SetColor(g_Fish.isDamaged ? 12 : 9);

		if (g_Fish.dir == Right) // ����� ������ �������� ��
		{
			char* line = g_FishGraphic[Right][y];
			int len = strlen(line);

			for (int x = 0; x < len; x++)
			{
				if (line[x] != ' ')
				{
					_DrawText(g_Fish.pos.x + x, g_Fish.pos.y + y, (char[]) { line[x], '\0' });
				}
			}
		}
		else // ����� ������ ������ ��
		{
			// Left �� 0 �̾��µ� �������� -1�� �ٲٴϱ� �迭���� ������ �׳� [0][y] ���� �ٲ��
			char* line = g_FishGraphic[0][y];
			int len = strlen(line);

			for (int x = 0; x < len; x++)
			{
				if (line[x] != ' ')
				{
					_DrawText(g_Fish.pos.x + x, g_Fish.pos.y + y, (char[]) { line[x], '\0' });
				}
			}
		}

	}

	_SetColor(15);
}
*/

// ������� �ּ� ����
void DrawFish(int dir, MyPoint pos) {

	int tempX = pos.x - GetPlusX();  // ī�޶� ���� ��ġ ����

	// ȭ�� ���� ���̸� ��� �� ��
	if (tempX + FISH_WIDTH < 0 || tempX >= SCREEN_WIDTH) return;

	for (int y = 0; y < FISH_HEIGHT; y++) {
		char* line = g_FishGraphic[dir][y];
		int len = strlen(line);

		for (int x = 0; x < len; x++) {
			if (line[x] != ' ') {
				if (0 <= tempX + x && tempX + x < SCREEN_WIDTH) {
					_DrawText(tempX + x, pos.y + y, (char[]) { line[x], '\0' });
				}
			}
		}
	}

	_SetColor(15);

}
