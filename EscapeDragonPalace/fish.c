#include "Rabbit.h"

void UpdateFish(unsigned int now) {

	// monster.c UpdateMonster()�� �̵�

}

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

void FishHitP(int posX, int posY) {//����� > �÷��̾� �����ϴ� �Լ�
	Rect PlayerPos = { player.Pos.x, player.Pos.y, 8, 3 };
	Rect MosterPos = { posX, posY, 3, 3 };
	DWORD now = GetTickCount();

	if ((IsOverlap(PlayerPos, MosterPos)) == false)
		return;

	// ���� �ð� üũ
	if (now - monsterList[E_MONSTER_CRAB].lastHitTime < INVINCIBLE_TIME) {
		return; // ���� ���� ���¸� ������ ����
	}

	player.Health -= E_FISH_ATTACK; // �÷��̾� ü�� 2 ����

	monsterList[E_MONSTER_CRAB].lastHitTime = now; // ������ �ǰ� �ð� ����
}
