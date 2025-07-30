#include "init.h"
#include "item.h"

char seaweedSprite[2][ITEM_SPRITE_ROWS][ITEM_SPRITE_CLOS] = {
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
char bubblesSprite[2][ITEM_SPRITE_ROWS][ITEM_SPRITE_CLOS] = {
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

// ���� ���� ���� ��������
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

    for (int row = 0; row < ITEM_SPRITE_ROWS; row++) {
        if ((*sprite)[frame][row] == '\0') break;  // ���� ���̸� �ߴ�
        _DrawText(item->x, item->y + row, (*sprite)[frame][row]);
    }
}



void InitItem() {

    // ù ��° ������ - ����
    itemList[numItem++] = (Item){
        .type = ITEM_LIFE,
        .x = 30, .y = 21,
        .isHeld = false,
        .value = 2,
        .width = 11,
        .height = 3,
        .mapStatus = 0
    };

    // �� ��° ������ - ������
    itemList[numItem++] = (Item){
        .type = ITEM_SPEED,
        .x = 60, .y = 22,
        .isHeld = true,
        .value = 1,
        .width = 5,
        .height = 2,
        .mapStatus = 0
    };
}
