#pragma once

#define FISH_WIDTH 15
#define FISH_HEIGHT 3
#define FISH_HP 3

// ���� ����
static char fishGraphic[2][FISH_HEIGHT][FISH_WIDTH] = {
	{
		"  _______   ",
		" /o��))��\\/)",
		" \\_______/\\)"
	}, // ���� �׸� 0
	{
		"    _______  ",
		" (\\/��((��o\\",
		" (/\\_______/ "
	},// ������ �׸� 1
};

// ����� �Լ�
void UpdateFish(unsigned int now);
void DrawFish();
void HitFish(unsigned int now, int damage);