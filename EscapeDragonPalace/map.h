#pragma once
#include "init.h"

// ��ũ��
#define STAGE_CNT 5 // �������� ����
#define BG_CNT 5 // �� ��� ��� ����
#define BG_LINE 20 // �� ��� �� ��
#define MAP_HEIGHT 25 // �� ����
#define GOAL_POS_X 4 // �������� �ʱ���ġ X
#define GOAL_POS_Y 7 // �������� �ʱ���ġ Y

void Draw();
void DrawMap();
void Input();
void Update();
void UpdateMapPos();