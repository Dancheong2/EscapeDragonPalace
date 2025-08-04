#include "init.h"
#include "item.h"

char seaweedSprite[2][ITEM_SPRITE_ROWS][ITEM_SPRITE_COLS] = {
	{
		" )) (( ((",
		"((   )) ))",
		" )) (( (("
	},
	{
		"((  )) ))",
		" ))(( ((",
		"((  )) ))"
	}
};
char bubblesSprite[2][ITEM_SPRITE_ROWS][ITEM_SPRITE_COLS] = {
	{
		"��.o",
		".��o"
	},
	{
		".��o",
		"��.o"
	}
};


Item itemList[MAX_ITEM_COUNT];
int numItem = 0;
int frame = 0;


bool SettingItem = false;

bool GetSettingItem()
{
	return SettingItem;
}

void SetSettingItem(bool src)
{
	SettingItem = src;
}

// frame �� ��������
int GetFrame()
{
	return frame;
}


clock_t lastFrameTime = 0;
const int frameDelay = 400;  // 200ms���� ������ ��ȯ

void ItemFrameDelay() {
	clock_t now = clock();
	int elapsed = (now - lastFrameTime) * 1000 / CLOCKS_PER_SEC;

	if (elapsed >= frameDelay) {
		frame = (frame + 1) % 2;
		lastFrameTime = now;
	}

	_Invalidate();  // �� ������ �׸���� ���!
}


void DrawItem(Item* item, int frame) {

	SpriteType* sprite = &seaweedSprite;

	switch (item->type) {
	case ITEM_LIFE:
		sprite = &seaweedSprite;
		break;
	case ITEM_SPEED:
		sprite = &bubblesSprite;
		break;
	}

	int tempX = item->x - GetPlusX();


	for (int row = 0; row < ITEM_SPRITE_ROWS; row++) {
		if ((*sprite)[frame][row] == '\0') break;  // ���� ���̸� �ߴ�

		for (int col = 0; col < ITEM_SPRITE_COLS; col++)
		{
			// ������ ��ġ�� ȭ�� ���� ���� ���� ���
			if(0 <= tempX + col && SCREEN_WIDTH >= tempX + col)
			{
				if (tempX + 7 > 0 && tempX < SCREEN_WIDTH) {
					_DrawText(tempX + col, item->y + row, (char[]) { (*sprite)[frame][row][col], 0 });
				}
			}
		}
	}
}



void InitItem() {

	// ������

	// ����
	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 353, .y = 14,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 0
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 530, .y = 12,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 0
	};

	// ������
	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 160, .y = 22,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 0
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 570, .y = 22,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 0
	};


	// ��ø�

	// ����
	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 206, .y = 9,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 1
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 288, .y = 6,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 1
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 467, .y = 1,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 1
	};

	// ������
	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 190, .y = 22,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 1
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 340, .y = 22,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 1
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 484, .y = 22,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 1
	};

	// �ٴٸ� 1

	// ����
	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 99, .y = 21,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 2
	};

	itemList[numItem++] = (Item){
	.type = ITEM_LIFE,
	.x = 429, .y = 21,
	.isHeld = false,
	.value = 2,
	.width = 11,
	.height = 3,
	.mapStatus = 2
	};

	// ������
	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 131, .y = 9,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 2
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 282, .y = 8,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 2
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 386, .y = 14,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 2
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 563, .y = 13,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 2
	};

	// �ٴٸ� 2

	// ����
	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 100, .y = 21,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 3
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 210, .y = 5,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 3
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 471, .y = 21,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 3
	};

	itemList[numItem++] = (Item){
		.type = ITEM_LIFE,
		.x = 542, .y = 11,
		.isHeld = false,
		.value = 2,
		.width = 11,
		.height = 3,
		.mapStatus = 3
	};

	// ������
	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 138, .y = 11,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 3
	};

	itemList[numItem++] = (Item){
		.type = ITEM_SPEED,
		.x = 440, .y = 17,
		.isHeld = true,
		.value = 1,
		.width = 5,
		.height = 2,
		.mapStatus = 3
	};

}
