#pragma once
#include "init.h"

#define ITEM_SPRITE_ROWS 10     // ������ ��������Ʈ ���� ũ��
#define ITEM_SPRITE_COLS 20     // ������ ��������Ʈ ���� ũ��

#define ITEMNUM 2               // ������ ���� ��
#define MAX_ITEM_COUNT 100      // �ʿ� ������ �� �ִ� ������ �ν��Ͻ� ��

#define SPEEDUP 0.5     // �ӵ� ������
#define SPEEDDOWN 0.5   // �ӵ� ���Ұ�
#define LIFEUP 2        // ���� ������
#define LIFEDOWN 1      // ���� ���Ұ�

#define SEAWEED_WIDTH 11    // ���� �ʺ�
#define SEAWEED_HEIGHT 3    // ���� ����
#define BUBBLES_WIDTH 5     // ������ �ʺ�
#define BUBBLES_HEIGHT 2    // ������ ����
#define CLAM_WIDTH 6        // ���� �ʺ�
#define CLAM_HEIGHT 1       // ���� ����

// ������ ���� ������
typedef enum {
    E_ITEM_SPEED,   // �ӵ� ����
    E_ITEM_LIFE,    // ü�� ����
    E_ITEM_DEBUFF,  // �ӵ� �� ü�� ���� (�����)
} ItemType;

// ������ ����ü
typedef struct Item {
    ItemType type;          // ������ ����
	float x, y;             // ������ ��ġ ��ǥ
    bool isHeld;            // �÷��̾� ���� ����
	float width, height;    // ������ �ʺ�, ����
	MapStatus mapStatus;    // �������� �����ϴ� ��
} Item;

extern Item g_ItemList[MAX_ITEM_COUNT]; // ������ ����Ʈ
extern int g_ItemIdx;   // ������ ����

// �Լ�
void InitItem();        // ������ �ʱ�ȭ
void DrawItem();        // ������ �׸���
void ResetItem();       // ������ isHeld false�� �ʱ�ȭ
void ItemFrameDelay();  // ������ ��� ȿ��
