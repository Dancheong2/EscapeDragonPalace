#include "init.h"
#include "monster.h"

// ���� ������Ʈ
void UpdateMonster()
{
	unsigned int now = _GetTickCount();
	UpdateCrab(now);
	UpdateClam();
	int damage = 1; // ���� ���ݷ� �޾ƿ;� ��

	if (GetFishAlive()) {
		UpdateFish(now);
	}

	if (GetFishIsDamaged())
	{
		HitFish(now, damage);
	}
}