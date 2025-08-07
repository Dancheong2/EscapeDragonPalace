#include "Rabbit.h"

void TriggerClam() {

}

// �̰� rabbit.c�� GetMonsterRect() ����ؼ� �ٽ� �ڵ� ¥�°� ���� ��
void UpdateClam(MyPoint pos, bool alive) {

	// �÷��̾ ���� ���� �ö� �� �ߵ�
	if (player.Pos.x == pos.x && player.Pos.y == pos.y) {
		alive = false;
	}
}
//�浹 �ϸ� ������ ����
// ���� �׸���
void DrawClam(int posX, int posY) {
	// ȭ�� ���� ���̸� ��� �� ��
	if (posX + CLAM_WIDTH < 0 || posX >= SCREEN_WIDTH) return;
	Rect PlayerPos = { player.Pos.x, player.Pos.y, 8, 3 };
	Rect MosterPos = { posX, posY, 1, 1 };

	for (int y = 0; y < CLAM_HEIGHT; y++)
	{
		const char* line = g_ClamGraphic[IsOverlap(PlayerPos, MosterPos) ? 1 : 0][y];
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
}


