#include "init.h"
#include "map.h"
#include "Rabbit.h"

int g_Plus_X = 0; // X��ǥ �̵� ������

// TODO: �� ���� �� E_Jail���� ����
// TODO: �� Ŭ���� �� �ڵ����� �Ѿ��
// ���� �� ����
MapStatus g_MapStatus = E_Jail;

// TODO: �ڵ� ����
// �� Ʋ �׸���
void DrawMap()
{
	_DrawText(0, 0, "==============================================================================");
	_DrawText(0, SCREEN_HEIGHT - 1, "==============================================================================");
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		_DrawText(0, y, "��");
		_DrawText(78, y, "��");
	}
}

// �� ��� �׸���
void DrawMapBG()
{
	// ��� �׸���
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		char* tmpBG = g_StageBG[g_MapStatus][y]; // ���� ���� ��� ���� ��������
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			_DrawTextColor(x, y, (char[]) { tmpBG[x + g_Plus_X], 0 }, E_Gray);
		}
	}
	// ���� �׸���
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		char* tmpPlatform = g_StagePlatform[g_MapStatus][y]; // ���� ���� ���� ���� ��������
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			_DrawTextColor(x, y, (char[]) { tmpPlatform[x + g_Plus_X], 0 }, E_White);
		}
	}

	//// ���� ���� ���
	//if (g_MapStatus == E_Ground)
	//{
	//	// ��� �׸���
	//	for (int i = 0; i < BG_CNT; i++)
	//	{
	//		StageBG tmpBG = g_StageBG[g_MapStatus][i]; // ���� ���� ��� ���� ��������
	//		for (int y = 0; y < SCREEN_HEIGHT; y++)
	//		{
	//			_DrawTextColor(tmpBG.pos.x, tmpBG.pos.y, tmpBG.bg[y], tmpBG.color);
	//		}
	//	}
	//	// ���� �׸���
	//	for (int i = 0; i < PLATFORM_LINE_CNT; i++)
	//	{
	//		StageBG tmpPlatform = g_StagePlatform2[g_MapStatus][i]; // ���� ���� ���� ���� ��������
	//		for (int y = 0; y < SCREEN_HEIGHT; y++)
	//		{
	//			_DrawTextColor(tmpPlatform.pos.x, tmpPlatform.pos.y, tmpPlatform.bg[y], tmpPlatform.color);
	//		}
	//	}
	//}
}

// ���� �� �ҷ�����
int GetMapStatus()
{
	return g_MapStatus;
}

// ���� �� ���� �����ϱ�
void SetMapStatus(int src)
{
	g_MapStatus = src;
}

// X ������ �ҷ�����
int GetPlusX()
{
	return g_Plus_X;
}

// �� ��ġ ������Ʈ
void UpdateMapPos()
{
	if (GetKeyA() && player.Pos.x <= 24 || GetAsyncKeyState('A') & 0x8000)
	{
		SetMapEnd(false);
		g_Plus_X -= player.Speed;
	}
	else if (GetKeyD() && player.Pos.x >= 26 || GetAsyncKeyState('D') & 0x8000)
	{
		SetMapEnd(false);
		g_Plus_X += player.Speed;
	}

	// X��ǥ �������� ���� �Ѿ ��
	if (g_Plus_X < 0)
	{
		g_Plus_X = 0;
		SetMapEnd(true);
	}
	else if (g_Plus_X > MAP_WIDTH - SCREEN_WIDTH)
	{
		g_Plus_X = MAP_WIDTH - SCREEN_WIDTH;
		SetMapEnd(true);
	}

}