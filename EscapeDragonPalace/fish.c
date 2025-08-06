#include "Rabbit.h"

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
void DrawFish(int dir, int posX, int posY) {

	// ȭ�� ���� ���̸� ��� �� ��
	if (posX + FISH_WIDTH < 0 || posX >= SCREEN_WIDTH) return;

	for (int y = 0; y < FISH_HEIGHT; y++) {
		char* line = g_FishGraphic[dir][y];
		int len = strlen(line);

		for (int x = 0; x < len; x++) {
			if (line[x] != ' ') {
				if (0 <= posX + x && posX + x < SCREEN_WIDTH) {
					_DrawText(posX + x, posY + y, (char[]) { line[x], '\0' });
				}
			}
		}
	}

	_SetColor(15);

}
