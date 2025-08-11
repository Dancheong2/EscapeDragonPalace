#include "init.h"
#include "crab.h"
#include "Rabbit.h"

// ���� ����
Monster g_CrabMon;	// �ɰ� ���� ����ü ���� ����
Skill g_CrabSkill;	// �ɰ� ��ų ����ü ���� ����
Crab g_CrabList[STAGE_CNT][CRAB_CNT];	// �ɰ� ����Ʈ �迭
int g_CrabListIdx[STAGE_CNT] = { 0, };
DWORD lastBleedTick = 0; // ���� ������ üũ�� Ÿ�̸�
int bleedCount = 0;      // ���� ������ Ƚ��(3)



static bool Crab_IsOnGround(Crab* crab)// �ɰ԰� ���� ���� �ִ��� Ȯ��
{
	// �߾� X��ǥ
	int tileX = (crab->pos.x + (CRAB_WIDTH / 2)) / TILE_SIZE;
	// �߹� YŸ�� ��ǥ
	int tileY = (crab->pos.y + CRAB_HEIGHT) / TILE_SIZE;

	// �� ���� üũ
	if (tileY < 0 || tileY >= MAP_HEIGHT || tileX < 0 || tileX >= MAP_WIDTH)
		return false;

	// ���� �� �޾ƿ���
	int mapStatus = GetMapStatus();

	// �������� ���� Ȯ��
	if (mapStatus >= 0 && mapStatus < STAGE_CNT)
	{
		if (g_StagePlatform[mapStatus][tileY][tileX] == '=')
			return true;
	}

	// �⺻ �� ���� Ȯ��
	if (g_Map[tileY][tileX] == '=')
		return true;

	return false;
}

static void Crab_ApplyGravity(Crab* crab) //�߷��� ����
{
	if (!Crab_IsOnGround(crab))// �ɰ԰� ���� ���� ���� ������ �߷� ����
	{
		// ���� ������ ����
		crab->pos.y += 1.0f;

		// ȭ�� �ϴ� ���� ����
		if (crab->pos.y > SCREEN_HEIGHT - CRAB_HEIGHT -1) //-1 ���ϸ� �ȿ� ��
			crab->pos.y = SCREEN_HEIGHT - CRAB_HEIGHT -1;
	}
	else
	{
		// ���� ���� ����
		int tileY = (crab->pos.y + CRAB_HEIGHT) / TILE_SIZE;
		crab->pos.y = (tileY * TILE_SIZE) - CRAB_HEIGHT;
	}
}

void UpdateCrab(unsigned long now)
{
	Crab* tempCrab = g_CrabList[GetMapStatus()];

	for (int idx = 0; idx < g_CrabListIdx[GetMapStatus()]; idx++)
	{

		//���� ����� �ɰԶ�� �Ѿ
		if (tempCrab[idx].mon.alive == false) continue;



		// �߷� ����
		Crab_ApplyGravity(&tempCrab[idx]);


		// �÷��̾ ������ ���Դ��� Ȯ��
		if (player.Pos.x - (tempCrab[idx].pos.x - GetPlusX()) > (player.Pos.x - GetPlusX()) - CRAB_EYE)// �÷�	�̾ ������ ������ ���
			tempCrab[idx].state = true;
		else if (player.Pos.x - (tempCrab[idx].pos.x - GetPlusX()) < (player.Pos.x - GetPlusX()) + CRAB_EYE)// �÷��̾ ������ ������ �ʾ��� ���
			tempCrab[idx].state = false;

		
		if (tempCrab[idx].state) {// �ɰ԰� �÷��̾ �߰��ϴ� ����
			if (tempCrab[idx].pos.x > player.Pos.x + GetPlusX() + RABBIT_WIDTH)// �÷��̾ �ɰԺ��� �����ʿ� ���� ���
				tempCrab[idx].dir = E_Left;
			else if (tempCrab[idx].pos.x < player.Pos.x + GetPlusX())// �÷��̾ �ɰԺ��� ���ʿ� ���� ���
				tempCrab[idx].dir = E_Right;
		}
		else {// �ɰ԰� �÷��̾ �߰����� �ʴ� ����(���� ������ ������)
			if (tempCrab[idx].pos.x <= tempCrab[idx].startPosX)
				tempCrab[idx].dir = E_Right;
			if (tempCrab[idx].pos.x + CRAB_WIDTH >= tempCrab[idx].startPosX + tempCrab[idx].moveNum)
				tempCrab[idx].dir = E_Left;
		}

		// �̵�
		tempCrab[idx].pos.x += (tempCrab[idx].dir == E_Right) ? g_CrabMon.speed : -g_CrabMon.speed;
	}
}

	


void DrawCrab()
{
	// ���� �� ������ �ӽ÷� �ҷ�����
	Crab* tempCrab = g_CrabList[GetMapStatus()];
	int imageDir;
	for (int idx = 0; idx < g_CrabListIdx[GetMapStatus()]; idx++)
	{
		if (!tempCrab[idx].mon.alive) continue;


		// �����ð� ������ �ǰ� ���� ����
		if (tempCrab[idx].mon.isDamaged && GetTickCount() - tempCrab[idx].mon.lastHitTime >= MONSTER_INVINCIBLE_TIME)
			tempCrab[idx].mon.isDamaged = false;

		// �ǰ� �� �����, ��� ������
		_SetColor(tempCrab[idx].mon.isDamaged ? E_Yellow : E_BrightRed);

		int posX = tempCrab[idx].pos.x - GetPlusX();

		if(player.isBleeding ==true){
			imageDir = E_Left;
		}
		else {
			imageDir = E_Right;
		}
		

		for (int y = 0; y < CRAB_HEIGHT; y++)
		{
			for (int x = 0; x < CRAB_WIDTH; x++)
			{
				if (g_CrabGraphic[imageDir][y][x] != ' ')
				{
					// ȭ�� ���� ���� ���� ��� �׸���
					if (0 <= posX + x && SCREEN_WIDTH > posX + x)
					{
						_DrawText(posX + x, tempCrab[idx].pos.y + y,
							(char[]) {g_CrabGraphic[imageDir][y][x], 0});
					}
				}
			}
		}
	}
}//�ɰ� �׸���

// �ɰ� ���� üũ, ���� �ִϸ��̼� ó��
void CheckAttacking()
{
	for (int i = 0; i < g_CrabListIdx[GetMapStatus()]; i++)
	{
		// ���� ������ ��� �Ѿ��
		if (!g_CrabList[GetMapStatus()][i].mon.alive) continue;
	}
}



//�ɰ� > �÷��̾� �浹 üũ(üũ�� �ϴ� �뵵)
void CrabHitPlayer() {
	if (player.isBleeding == true) return; // �̹� ���� ���¸� �浹 üũ �� ��

	for (int idx = 0; idx < g_CrabListIdx[GetMapStatus()]; idx++)
	{
		Crab* tempCrab = &g_CrabList[GetMapStatus()][idx];
		int posX = tempCrab->pos.x - GetPlusX();
		int posY = tempCrab->pos.y;
		Rect PlayerPos = GetPlayerRect();
		Rect MonsterPos = { posX, posY, 1, 3 };

		if (!tempCrab->mon.alive) continue;

		if (IsOverlap(PlayerPos, MonsterPos)) {
			// ���� ����
			player.isBleeding = true;
			bleedCount = 0; // ���� ������ ī��Ʈ �ʱ�ȭ
			lastBleedTick = GetTickCount() - INVINCIBLE_TIME; // ���� Ÿ�̸� �ʱ�ȭ
		}

	}
}

void BleedPlayer() {//����
	if (!player.isBleeding) return; // ���� ���°� �ƴϸ� �ƹ��͵� �� ��

	DWORD now = GetTickCount();

	SetInvincibleTime(true);	// �÷��̾� ���� �ð� ����
	player.lastHitTime = GetTickCount(); // �÷��̾� ������ �ǰ� �ð� ����
	
	if (now - lastBleedTick >= INVINCIBLE_TIME) {
		player.Health -= 1;       // HP ����
		bleedCount++;             // ������ Ƚ�� ����
		lastBleedTick = now;      // Ÿ�̸� ����

		if (bleedCount >= 3) {    // 3�� ������ ���� ����
			SetInvincibleTime(false);	// �÷��̾� ���� �ð� ����
			player.isBleeding = false;
			bleedCount = 0;
		}
	}
}

// �÷��̾� -> �ɰ� ����
void PlayerHitCrab()
{
	Crab* crabList = &g_CrabList[GetMapStatus()];
	DWORD now = GetTickCount();
	Rect PlayerWeaponPos = GetWeaponRect();

	for (int idx = 0; idx < g_CrabListIdx[GetMapStatus()]; idx++)
	{
		Crab* tempCrab = &g_CrabList[GetMapStatus()][idx];// ���� �ɰ� ����
		int posX = tempCrab->pos.x - GetPlusX();
		int posY = tempCrab->pos.y;
		Rect MosterPos = { posX, posY, 10, 3 };

		if (!player.IsAttacking) continue;//�÷��̾ ���� ���� �ƴ� ��� �Ѿ��

		if (!tempCrab->mon.alive) continue; // ���Ͱ� �׾��� ��� �Ѿ��

		if (tempCrab->mon.isDamaged) continue; // ���Ͱ� ���� ������ ��� �Ѿ��

		if (!(IsOverlap(PlayerWeaponPos, MosterPos))) continue;

		if (now - tempCrab->mon.lastHitTime < MONSTER_INVINCIBLE_TIME) continue;
		tempCrab->mon.hp -= player.HeldWeapon->attack; // �ɰ� ü�� ����
		tempCrab->mon.isDamaged = true; // ���� ���·� ����
		tempCrab->mon.lastHitTime = now; // ������ �ǰ� �ð� ����


		if (tempCrab->mon.hp <= 0) {
			tempCrab->mon.alive = false;// ü���� 0 ���ϰ� �Ǹ� ��� ó��
		}
	}
}


void ResetCrab() {
	for (int i = 0; i < STAGE_CNT; i++)
	{
		Crab* tempCrab = g_CrabList[i];
		for (int idx = 0; idx < g_CrabListIdx[i]; idx++)
		{
			tempCrab[idx].mon.alive = false;
		}
	}
}

// �ɰ� �ʱ�ȭ
void InitCrab()
{
	for (int i = 0; i < STAGE_CNT; i++) {
		g_CrabListIdx[i] = 0;
	}
	// �ɰ� ����� �Ӽ� ����
	g_CrabMon = (Monster)
	{
		.alive = true,		// ���� ����
		.hp = 5,			// ü��
		.isDamaged = false,	// �ǰ� ���� (���� ����)
		.lastHitTime = 0,	// ������ �ǰ� �ð�
		.speed = 0.8,		// �̵� �ӵ�
	};
	g_CrabSkill = (Skill)
	{
		.isAttack = false,	// ��ų ��� ����
		.attack = 1,		// ���ݷ� (�� ĭ)
		.attackCnt = 3,		// ���� Ƚ��
		.coolTime = 4000,	// ��Ÿ�� (2��)
	};

	// ����
	g_CrabList[E_Jail][g_CrabListIdx[E_Jail]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 95,		// X ��ǥ
		.pos.y = 21,		// Y ��ǥ
		.startPosX = 95,	// �ʱ� X ��ǥ
		.moveNum = 64,		// �̵� ����
		.dir = E_Right,
	};

	g_CrabList[E_Jail][g_CrabListIdx[E_Jail]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 170,
		.pos.y = 21,
		.startPosX = 170,
		.moveNum = 64,
		.dir = E_Right,
	};

	g_CrabList[E_Jail][g_CrabListIdx[E_Jail]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 277,
		.pos.y = 21,
		.startPosX = 277,
		.moveNum = 92,
		.dir = E_Right,
	};

	// ���
	g_CrabList[E_DragonPalace][g_CrabListIdx[E_DragonPalace]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 72,
		.pos.y = 21,
		.startPosX = 72,
		.moveNum = 60,
		.dir = E_Right,
	};

	g_CrabList[E_DragonPalace][g_CrabListIdx[E_DragonPalace]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 170,
		.pos.y = 21,
		.startPosX = 170,
		.moveNum = 61,
		.dir = E_Right,
	};

	g_CrabList[E_DragonPalace][g_CrabListIdx[E_DragonPalace]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 246,
		.pos.y = 21,
		.startPosX = 246,
		.moveNum = 86,
		.dir = E_Right,
	};

	g_CrabList[E_DragonPalace][g_CrabListIdx[E_DragonPalace]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 440,
		.pos.y = 21,
		.startPosX = 440,
		.moveNum = 125,
		.dir = E_Right,
	};

	// �ٴ�1
	g_CrabList[E_Sea1][g_CrabListIdx[E_Sea1]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 80,
		.pos.y = 13,
		.startPosX = 80,
		.moveNum = 96,
		.dir = E_Right,
	};

	g_CrabList[E_Sea1][g_CrabListIdx[E_Sea1]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 187,
		.pos.y = 21,
		.startPosX = 187,
		.moveNum = 75,
		.dir = E_Right,
	};

	g_CrabList[E_Sea1][g_CrabListIdx[E_Sea1]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 373,
		.pos.y = 21,
		.startPosX = 373,
		.moveNum = 73,
		.dir = E_Right,
	};

	g_CrabList[E_Sea1][g_CrabListIdx[E_Sea1]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 574,
		.pos.y = 17,
		.startPosX = 574,
		.moveNum = 60,
		.dir = E_Right,
	};

	g_CrabList[E_Sea1][g_CrabListIdx[E_Sea1]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 580,
		.pos.y = 7,
		.startPosX = 580,
		.moveNum = 47,
		.dir = E_Right,
	};

	// �ٴ�2
	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 76,
		.pos.y = 10,
		.startPosX = 76,
		.moveNum = 76,
		.dir = E_Right,
	};

	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 150,
		.pos.y = 21,
		.startPosX = 150,
		.moveNum = 41,
		.dir = E_Right,
	};

	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 404,
		.pos.y = 21,
		.startPosX = 404,
		.moveNum = 50,
		.dir = E_Right,
	};

	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 546,
		.pos.y = 21,
		.startPosX = 491,
		.moveNum = 55,
		.dir = E_Right,
	};

	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 491,
		.pos.y = 16,
		.startPosX = 491,
		.moveNum = 55,
		.dir = E_Right,
	};

	g_CrabList[E_Sea2][g_CrabListIdx[E_Sea2]++] = (Crab)
	{
		.mon = g_CrabMon,
		.skill = g_CrabSkill,
		.pos.x = 610,
		.pos.y = 21,
		.startPosX = 610,
		.moveNum = 62,
		.dir = E_Right,
	};
}