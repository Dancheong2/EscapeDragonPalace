#include "init.h"
#include "monster.h"

Monster monsterList[MAX_Monster_COUNT];	// ���� �迭 ����
int numMonster = 0;

// ���� ������Ʈ
void UpdateMonster()
{
	// �Ͽ� ���� ================================

	for (int i = 0; i < numMonster; i++) {

		if (monsterList[i].type == MONSTER_CLAM) {
			UpdateClam(monsterList[i].pos, monsterList[i].alive);
		}
		else if (monsterList[i].type == MONSTER_TURTLE) {

		}
		else {
			// ȭ�鿡 ������ �ʴ� ����(�׾��ų� �ٸ� ��������)�� ��� �Ѿ��
			if (!monsterList[i].alive) continue;
			unsigned int now = _GetTickCount();

			// �����ð� ������ �ǰ� ���� ����
			if (monsterList[i].isDamaged && now - monsterList[i].lastHitTime >= INVINCIBLE_TIME) {
				monsterList[i].isDamaged = 0;
			}

			// ���� �̵�
			if (monsterList[i].dir == Right)
				monsterList[i].pos.x += 1;
			else
				monsterList[i].pos.x -= 1;

			// ���� �� �浹 �� ���� ��ȯ
			if (monsterList[i].pos.x <= 0) {
				monsterList[i].pos.x = 0;
				monsterList[i].dir = Right;
			}

			// ���� Ÿ�Կ� ���� ������ �� �浹�� ������ȯ
			if (monsterList[i].type == MONSTER_FISH) {
				// �����
				if (monsterList[i].pos.x + FISH_WIDTH >= 82) {
					monsterList[i].pos.x = 80 - FISH_WIDTH + 2;
					monsterList[i].dir = Left;
				}
			}
			else {
				// �ɰ�
				if (monsterList[i].pos.x + CRAB_WIDTH >= 82) {
					monsterList[i].pos.x = 80 - CRAB_WIDTH + 2;
					monsterList[i].dir = Left;
				}
			}

		}

	}

	//UpdateCrab(now);
	//UpdateClam();
	// =========================================

	// int damage = 1; // ���� ���ݷ� �޾ƿ;� ��
	/*
	if (GetFishAlive()) {
		UpdateFish(now);
	}

	if (GetFishIsDamaged())
	{
		HitFish(now, damage);
	}
	*/
}

// ���� �׸��� �Լ�
void DrawMonster(Monster monster) {
	switch (monster.type)
	{
	case MONSTER_FISH:
		_SetColor(monster.isDamaged ? 12 : 9);
		DrawFish(monster.dir, monster.pos);
		break;
	case MONSTER_CRAB:
		_SetColor(monster.isDamaged ? 6 : 12);  // �ǰ� �� �����, ��� ������
		DrawCrab(monster.pos);
		break;
	case MONSTER_CLAM:
		DrawClam(monster.pos);
		break;
	case MONSTER_TURTLE:
		break;
	}
}


// ���� �ǰ� ó�� �Լ�
void HitMonster(Monster monster, Weapon* weapon, unsigned int now) {
	if (monster.isDamaged) return;

	monster.hp -= weapon->attack;
	monster.isDamaged = true;	// ���� ���� ����
	monster.lastHitTime = now;	// �ǰ� �ð� ���

	if (monster.hp <= 0) {
		monster.alive = false;         // ü���� 0 ���ϰ� �Ǹ� ��� ó��
	}
}


// ���� �ʱ�ȭ �Լ�
void InitMonster() {
	monsterList[numMonster++] = (Monster){
		.pos.x = 40,
		.pos.y = 21,
		.dir = Right,
		.hp = 5,
		.alive = true,
		.type = MONSTER_CRAB,
		.isDamaged = false,
		.lastHitTime = 0,
		.monsterStatus = 0
	};

	monsterList[numMonster++] = (Monster){
		.pos.x = 20,
		.pos.y = 21,
		.dir = Right,
		.hp = 5,
		.alive = true,
		.type = MONSTER_FISH,
		.isDamaged = false,
		.lastHitTime = 0,
		.monsterStatus = 0
	};

	monsterList[numMonster++] = (Monster){
		.pos.x = 30,
		.pos.y = 23,
		.dir = Right,
		.hp = 5,
		.alive = true,
		.type = MONSTER_CLAM,
		.isDamaged = false,
		.lastHitTime = 0,
		.monsterStatus = 0
	};
}