#pragma once

#define ESC 27 // ESC Ű ��

void GameStartScreen();
void GameOverScreen();
void DrawStartScreen();
void ReturnStartScreen();
bool GetGameStart(); // ���� ���� ���� �������� �Լ�
bool GetIsGameOver();	// ���� ���� ���� ��ȯ
void SetIsGameOver(int src);
bool GetTextE();		// ���� ����Ʈ ȿ��
void SetTextE(int src);
void GameClearSceen(); // ���� Ŭ���� ȭ�� ��� �Լ�
void DrawGameClearScreen(); // ���� Ŭ���� ȭ�� ��� �Լ�