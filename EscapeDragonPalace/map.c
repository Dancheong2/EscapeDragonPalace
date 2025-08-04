#include "map.h"
#include "Rabbit.h"

int g_Plus_X = 0; // X��ǥ �̵� ������

// TODO: �� ���� �� E_Jail���� ����
// TODO: �� Ŭ���� �� �ڵ����� �Ѿ��
// ���� �� ����
MapStatus g_MapStatus = 0;

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
	// ���� ���� ���
	if (g_MapStatus == E_Ground)
	{
		// ��� �׸���
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			_DrawTextColor(0, y, g_StageBG[g_MapStatus][y], E_Gray);

		// ���� �׸���
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			char* tmpPlatform = g_StagePlatform[g_MapStatus][y]; // ���� ���� ���� ���� ��������
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				if (tmpPlatform[x ] != ' ')
					_DrawTextColor(x, y, (char[]) { tmpPlatform[x], 0 }, E_White);
			}
		}
	}
	// �Ϲ� ���� ���
	else
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
				if (tmpPlatform[x + g_Plus_X] != ' ')
					_DrawTextColor(x, y, (char[]) { tmpPlatform[x + g_Plus_X], 0 }, E_White);
			}
		}
	}
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