#pragma once
#include "init.h"

// ��ũ��
#define STAGE_CNT 5 // �������� ����
#define BG_CNT 5 // �� ��� ��� ����
#define BG_LINE 20 // �� ��� �� ��
#define PLATFORM_CNT 10 // ���� ����
#define MAP_HEIGHT 49 // �� ����
#define MAP_WIDTH SCREEN_WIDTH
#define GOAL_HEIGHT 5 // �������� ����

void Draw();
void DrawMap();
void Input();
void Update();
void UpdateMapPos();