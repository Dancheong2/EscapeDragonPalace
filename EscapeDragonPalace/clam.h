#pragma once

// ��ũ��
#define CLAM_WIDTH 1
#define CLAM_HEIGHT 7
#define CLAM_HP 1

// ��������
static const char* clamGraphic = "(\\  /)";

//���� �Լ�
void TriggerClam();
void UpdateClam(MyPoint pos, bool alive);
void DrawClam(MyPoint pos);
MyPoint GetClamPos();
int GetClamDir();