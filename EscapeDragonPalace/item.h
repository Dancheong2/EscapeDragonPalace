#pragma once

#define ITEM_SPRITE_ROWS 10
#define ITEM_SPRITE_CLOS 20
#define ITEMNUM 2            // ������ ���� ��
#define MAX_ITEM_COUNT 100   // �ʿ� ������ �� �ִ� ������ �ν��Ͻ� ��

typedef enum {
    ITEM_SPEED,
    ITEM_LIFE
} ItemType;

typedef struct Item {
    ItemType type;
    float x, y;
    bool isHeld;    // 0: �ٴڿ� ����, 1: �÷��̾ ����
    int value;     // ȿ�� ��ġ
    float width, height;
} Item;

typedef char SpriteType[2][ITEM_SPRITE_ROWS][ITEM_SPRITE_CLOS];

extern SpriteType seaweedSprite;
extern SpriteType bubblesSprite;

extern Item itemList[MAX_ITEM_COUNT];
extern int numItem;

void InitItem();
void DrawItem(Item* item, int frame);
void ItemFrameDelay();
