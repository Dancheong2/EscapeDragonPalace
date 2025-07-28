#pragma once
#include "init.h"

// ��ũ��
#define STAGE_CNT 4 // �Ϲ� �������� ����
#define BG_CNT 5 // �� ��� ��� ����
#define BG_LINE 20 // �� ��� �� ��
#define PLATFORM_CNT 10 // ���� ����
#define MAP_HEIGHT 49 // �� ����
#define MAP_WIDTH SCREEN_WIDTH // �� �ʺ�
#define GOAL_HEIGHT 5 // �������� ����

void Draw();
void DrawNormalMap(); // �Ϲ� �� �׸���
void DrawNormalBG(); // �Ϲ� �� ��� �׸���
void DrawBossMap(); // ���� �� �׸���
void UpdateMapPos();
int GetMapStatus(); // �� ���� �޾ƿ���

// CMD ����
typedef enum CMDColor
{
	E_Black,
	E_Blue,
	E_Green,
	E_Teal, // û�ϻ�
	E_Red,
	E_Purple,
	E_Yellow,
	E_White,
	E_Gray,
	E_BrightBlue,
	E_BrightGreen,
	E_BrightTeal,
	E_BrightRed,
	E_BrightPurple,
	E_BrightYellow,
	E_BrightWhite,
} CMDColor;

typedef enum MapBgColor
{
	E_CJail = E_Gray,
	E_CDragonPalace = E_BrightBlue,
	E_CSea1 = E_Blue,
	E_CSea2 = E_Blue,
	E_CGround = E_Green,
} MapBgColor;

typedef enum MapStatus
{
	E_Jail,
	E_DragonPalace,
	E_Sea1,
	E_Sea2,
	E_Boss,
} MapStatus;

typedef struct StageBG
{
	MyPoint pos;
	CMDColor color;
	char bg[20][256];
} StageBG;