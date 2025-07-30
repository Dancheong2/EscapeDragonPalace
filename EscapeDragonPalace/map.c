#include "init.h"
#include "map.h"

int g_Plus_Y = 24; // ����, ��� �� ���� ��ġ
int g_Plus_X = 0; // �ٴ� 1, 2 �� ���� ��ġ

// TODO: �� ���� �� E_Jail���� ����
// TODO: �� Ŭ���� �� �ڵ����� �Ѿ��
// ���� �� ����
MapStatus g_MapStatus = E_Sea1;

// �� �׸���
// TODO: �ڵ� ����
void DrawMap()
{
	switch (g_MapStatus)
	{
	case E_Jail: case E_DragonPalace:	// ���� ����, ����� ���
		// ��� �׸���
		for (int i = 0; i < BG_CNT; i++)
		{
			StageBG tmpBG = g_StageBG[g_MapStatus][i]; // ���� ���� ��� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				int tmpY = tmpBG.pos.y + y - g_Plus_Y;
				// ��� ���� ���� ���� �� ���
				if (tmpY >= 0 && tmpY <= SCREEN_HEIGHT)
					_DrawTextColor(tmpBG.pos.x, tmpY, tmpBG.bg[y], tmpBG.color);
			}
		}
		// ���� �׸���
		for (int i = 0; i < PLATFORM_LINE_CNT; i++)
		{
			StageBG tmpPlatform = g_StagePlatform[g_MapStatus][i]; // ���� ���� ���� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				int tmpY = tmpPlatform.pos.y + y - g_Plus_Y;

				// ��� ���� ���� ���� �� ���
				if (tmpY >= 0 && tmpY <= SCREEN_HEIGHT)
					_DrawTextColor(tmpPlatform.pos.x, tmpY, tmpPlatform.bg[y], tmpPlatform.color);
			}
		}
		break;

	case E_Sea1: case E_Sea2:	// ���� �ٴ�1, �ٴ�2�� ���
		// ��� �׸���
		for (int i = 0; i < BG_CNT; i++)
		{
			StageBG tmpBG = g_StageBG[g_MapStatus][i]; // ���� ���� ��� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				for (int x = 0; x < SCREEN_WIDTH; x++)
				{
					int tmpX = tmpBG.pos.x + x - g_Plus_X;
					if (tmpX >= 0 && tmpX <= SCREEN_WIDTH) // ����� ���� ���� ���� ���� ���
						_DrawTextColor(tmpX, tmpBG.pos.y + y, (char[]) { tmpBG.bg[y][x], 0 }, tmpBG.color);

				}
			}
		}
		// ���� �׸���
		for (int i = 0; i < PLATFORM_LINE_CNT; i++)
		{
			StageBG tmpPlatform = g_StagePlatform[g_MapStatus][i]; // ���� ���� ���� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				int tmpX = tmpPlatform.pos.x + y - g_Plus_X;
				if (tmpX >= 0 && tmpX <= SCREEN_WIDTH) // ����� ���� ���� ���� ���� ���
					_DrawTextColor(tmpX, tmpPlatform.pos.y, (char[]) { tmpPlatform.bg[y], 0 }, tmpPlatform.color);
			}
		}
		break;

	case E_Ground:	// ���� ����(������)�� ���
		// ��� �׸���
		for (int i = 0; i < BG_CNT; i++)
		{
			StageBG tmpBG = g_StageBG[g_MapStatus][i]; // ���� ���� ��� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				_DrawTextColor(tmpBG.pos.x, tmpBG.pos.y, tmpBG.bg[y], tmpBG.color);
			}
		}
		// ���� �׸���
		for (int i = 0; i < PLATFORM_LINE_CNT; i++)
		{
			StageBG tmpPlatform = g_StagePlatform[g_MapStatus][i]; // ���� ���� ���� ���� ��������
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				_DrawTextColor(tmpPlatform.pos.x, tmpPlatform.pos.y, tmpPlatform.bg[y], tmpPlatform.color);
			}
		}
		break;
	}

	// �� Ʋ �׸���
	_DrawText(0, 0, "==============================================================================");
	_DrawText(0, SCREEN_HEIGHT - 1, "==============================================================================");
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		_DrawText(0, y, "��");
		_DrawText(76, y, "��");
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

// �� ��ġ ������Ʈ
void UpdateMapPos()
{
	switch (g_MapStatus)
	{
	case E_Jail: case E_DragonPalace:
		if (g_Key == 'w' || g_Key == 'W')
		{
			--g_Plus_Y;
		}
		else if (g_Key == 's' || g_Key == 'S')
		{
			++g_Plus_Y;
		}
		if (g_Plus_Y < 0)
			g_Plus_Y = 0;
		else if (g_Plus_Y > 24)
			g_Plus_Y = 24;
		break;
	case E_Sea1: case E_Sea2:
		if (g_Key == 'a' || g_Key == 'A')
		{
			g_Plus_X -= 2;
		}
		else if (g_Key == 'd' || g_Key == 'D')
		{
			g_Plus_X += 2;
		}
		if (g_Plus_X < 0)
			g_Plus_X = 0;
		else if (g_Plus_X > 222)
			g_Plus_X = 222;
		break;
	}

}