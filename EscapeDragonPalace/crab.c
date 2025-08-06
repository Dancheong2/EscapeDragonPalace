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

bool CheckCollison(Rect p, Rect crab) {
	if ((p.x < crab.x + crab.w) && (p.x + p.w > crab.x) &&
		(p.y < crab.y + crab.h) && (p.y + p.h > crab.y))
		return true;
	return false;
}



// �ɰ� �׸��� �Լ�
// �Ͽ� ���� =================================
void DrawCrab(MyPoint pos)
{
	Rect PlayerPos = {player.Pos.x, player.Pos.y, 8, 3 };

	_SetColor(g_Crab.isDamaged ? 6 : 12);// �ǰ� �� �����, ��� ������

	for (int y = 0; y < CRAB_HEIGHT; y++)
	{
		if(CheckCollison(PlayerPos,(Rect){g_Crab.pos.x,g_Crab.pos.y, 9, 3 }))
		{
			const char* line = crabGraphic[1][y];
			for (int x = 0; line[x] != '\0'; x++) 
			{
				if (line[x] != ' ') 
				{
					char ch[2] = { line[x], '\0' };
					_DrawText(pos.x + x, pos.y + y, ch);
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

