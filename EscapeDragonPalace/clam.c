#include "Rabbit.h"

Monster g_Clam = { { 20, 23 }, Right, CLAM_HP, true, MONSTER_CLAM, 0, 0 };

MyPoint GetClamPos()
{
    return g_Clam.pos;
}

int GetClamDir()
{
    return g_Clam.dir;
}

void TriggerClam() {
    
}

// �̰� rabbit.c�� GetMonsterRect() ����ؼ� �ٽ� �ڵ� ¥�°� ���� ��
void UpdateClam(MyPoint pos, bool alive) {

    // �÷��̾ ���� ���� �ö� �� �ߵ�
    if (player.Pos.x == pos.x && player.Pos.y == pos.y) {
        alive = false;
    }
}

void DrawClam(MyPoint pos) {
    int tempX = pos.x + GetPlusX();

    //if (g_Clam.alive) {
    //    for (int y = 0; y < CLAM_HEIGHT; y++) {
    //        for (int x = 0; x < CLAM_WIDTH; x++)
    //        {
    //            // ���� ��ġ�� ȭ�� ���� ���� ���� ���
    //            if (tempX - x >= 0 && tempX + x < SCREEN_WIDTH)
    //            {
    //                _DrawText(tempX + x, pos.y + y, (char[]) { clamGraphic[x], 0 });
    //            }
    //        }
    //    }
    //}
    //else
    //{
    //    _DrawText(pos.x + GetPlusX(), pos.y, " ");
    //}

    if (g_Clam.alive) {
        _DrawText(pos.x, pos.y, clamGraphic);
    }
    else {
        _DrawText(pos.x, pos.y, " ");
    }
}


