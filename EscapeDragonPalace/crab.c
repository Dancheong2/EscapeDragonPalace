#include "Rabbit.h"

Monster g_Crab = { 30, MONSTER_Y, Right, CRAB_HP, 1, E_MONSTER_CRAB, 0, 0 };

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

bool crabStratting = false;


// �ɰ� �׸��� �Լ�
// �Ͽ� ���� =================================
void DrawCrab(int posX, int posY)
{
	// ȭ�� ���� ���̸� ��� �� ��
	if (posX + CRAB_WIDTH < 0 || posX >= SCREEN_WIDTH) return;
	Rect PlayerPos = {player.Pos.x, player.Pos.y, 8, 3 };

	_SetColor(g_Crab.isDamaged ? 6 : 12);// �ǰ� �� �����, ��� ������

	for (int y = 0; y < CRAB_HEIGHT; y++)
	{
		if(IsOverlap(PlayerPos,(Rect){posX,posY, 9, 3 }))
		{
			const char* line = crabGraphic[1][y];
			for (int x = 0; line[x] != '\0'; x++) 
			{
				if (line[x] != ' ') 
				{
					if (0 <= posX + x && posX + x < SCREEN_WIDTH) {
						char ch[2] = { line[x], '\0' };
						_DrawText(posX + x, posY + y, ch);
					}
				}
			}
			crabStratting = true;
		}
		else
		{
			const char* line = crabGraphic[0][y];
			for (int x = 0; line[x] != '\0'; x++)
			{
				if (line[x] != ' ')
				{
					if (0 <= posX + x && posX + x < SCREEN_WIDTH) {
						char ch[2] = { line[x], '\0' };
						_DrawText(posX + x, posY + y, ch);
					}
				}
			}
		}
	}
	_SetColor(15);
}

/*void CrabAttack() {
	time_t start_time = time(NULL);
	double attceklastTimer = (double)clock() / CLOCKS_PER_SEC;

	while (time(NULL) - start_time <= 3) {
		if (crabStratting) {
			if (crabStratting = false)
				return;
			else {
				double atteckTime = (double)clock() / CLOCKS_PER_SEC;
				if (atteckTime - attceklastTimer >= 1.0) {
					player.Health = player.Health - E_CRAB_ATTACK;
					attceklastTimer = atteckTime;
				}
			}
		}
	}
	crabStratting = false;
}*/