#include "Rabbit.h"

//Monster g_Crab = { 30, MONSTER_Y, Right, CRAB_HP, 1, E_MONSTER_CRAB, 0, 0 };

MyPoint GetCrabPos()
{
	//return g_Crab.pos;
}

int GetCrabDir()
{
	//return g_Crab.dir;
}

void UpdateCrab(unsigned int now) {

	// monster.c UpdateMonster()�� �̵�

}




// �ɰ� �׸��� �Լ�
// �Ͽ� ���� =================================
void DrawCrab(int posX, int posY)
{
	
	// ȭ�� ���� ���̸� ��� �� ��
	if (posX + CRAB_WIDTH < 0 || posX >= SCREEN_WIDTH) return;
	Rect PlayerPos = {player.Pos.x, player.Pos.y, 3, 3 };
	Rect MosterPos = { posX, posY, 1, 1};

	for (int y = 0; y < CRAB_HEIGHT; y++)
	{
			const char* line = crabGraphic[IsOverlap(PlayerPos, MosterPos) ? 1 : 0][y];
			//�浹�ϸ� 1, ���浹 �� 0
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
	_SetColor(15);
}


void CrabHitP(int posX, int posY) {//�ɰ� > �÷��̾� �����ϴ� �Լ�
	Rect PlayerPos = { player.Pos.x, player.Pos.y, 8, 3 };
	Rect MosterPos = { posX, posY, 1, 3 };
	if ((IsOverlap(PlayerPos, MosterPos)) == false)
		return;

	



	
}

