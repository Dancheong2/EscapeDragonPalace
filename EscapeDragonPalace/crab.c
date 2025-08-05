#include "Rabbit.h"

Monster g_Crab = { 30, MONSTER_Y, Right, CRAB_HP, 1, MONSTER_CRAB, 0, 0 };

MyPoint GetCrabPos()
{
	return g_Crab.pos;
}

int GetCrabDir()
{
	return g_Crab.dir;
}

void UpdateCrab(unsigned int now) {

	// monster.c UpdateMonster()�� �̵�

}


// �ɰ� �׸��� �Լ�
// �Ͽ� ���� =================================
void DrawCrab(MyPoint pos)
{
	float dx = player.Pos.x - g_Crab.pos.x; //���⼭����
	float dy = player.Pos.y - g_Crab.pos.y;

	_SetColor(g_Crab.isDamaged ? 6 : 12);// �ǰ� �� �����, ��� ������

	for (int y = 0; y < CRAB_HEIGHT; y++)
	{
		if (sqrt(dx * dx + dy * dy) <= 2)
		{
			const char* line = crabGraphic[1][y];
			for (int x = 0; line[x] != '\0'; x++) 
			{
				if (line[x] != ' ') 
				{
					char ch[2] = { line[x], '\0' };
					_DrawText(g_Crab.pos.x + x, g_Crab.pos.y + y, ch);
				}
			}
		}
		else
		{
			const char* line = crabGraphic[0][y];
			for (int x = 0; line[x] != '\0'; x++)
			{
				if (line[x] != ' ')
				{
					char ch[2] = { line[x], '\0' };
					_DrawText(pos.x + x, pos.y + y, ch);
				}
			}
		}
	}
	_SetColor(15);
}
