#pragma once
#include "init.h"

// ��ũ��
#define STAGE_CNT 5 // �������� ����
#define BG_CNT 5 // �� ��� ��� ����
#define BG_LINE 20 // �� ��� �� ��
#define MAP_HEIGHT 25 // �� ����
#define GOAL_HEIGHT 5 // �������� ����

void Draw();
void DrawMap();
void Input();
void Update();
void UpdateMapPos();