#include "init.h"
#include "map.h"
#include "item.h"
#include "screens.h"
#include "Rabbit.h"
#include "weapon.h"

// �Լ�

// ===========================================================
void Draw() // ȭ�� �׸���
{
    // ���� ���� ��
    if (!GetGameStart()) {
        GameStartScreen();
        if (GetGameStartText()) 
            _DrawText(23, 21, "�ƹ� Ű�� ���� ���� �����ϱ�");
        else 
            _DrawText(21, 21, "                               ");
    }
    // ���� ���� ��
    else {
        if (IsGameOver)
        {
            GameOverScreen();
            if (GameOverText) _DrawText(14, 21, "�ƹ� Ű�� ���� ����ȭ������ ���ư���");
            else _DrawText(14, 21, "                                     ");
        }
        // �������� Ŭ����
        else if (StageClear())
        {
            _Delay(45);
            RabbitCAnim();
            SetMapStatus();
            for (int i = 0; i < numItem; i++)
            {
                if (itemList[i].mapStatus == GetMapStatus()) {
                    itemList[i].isHeld = false;
                }
                else {
                    itemList[i].isHeld = true;
                }
            }
        }
        else {

            if (!GetWeaponChosen())
            {
                for (int i = 0; i < NUMWEAPON; i++)
                {
                    int isSelected = (i == GetSelectedIndex()); // ���� �������� ����
                    DrawWeapon(&weaponList[i], i, isSelected);
                }
            }
            else
            {
                DrawMap(); // �� �׸���
                _DrawText(3, 3, player.HeldWeapon->sprite);
                DrawHealth();

                for (int i = 0; i < numItem; i++)
                {
                    if (!itemList[i].isHeld) {
                        DrawItem(&itemList[i], frame);
                    }
                }

            }

            DrawPlayer();




            if (IsNearItem())
            {
                // ���� ================
                _DrawText(player.Pos.x, player.Pos.y - 3.f, "e�� ���� ������ �Ա�");
                // =====================

            }
        }

    }
}
// ===========================================================

// ������Ʈ ����
void Update()
{
    UpdateMapPos();
    // �Ͽ� ====================================
    UpdatePlayer();

	SetIsNearItem(false); // �÷��̾ ������ ��ó�� �ִ��� ���� �ʱ�ȭ

    CheckItemPickup();
    UpdateSpeedBuffs();
    // �Ͽ� ====================================

}

// Ű �Է�
void Input()
{
    g_Key = _GetKey();
}

void main()
{
    // init
    _BeginWindow();

    // �� ũ�� ����
    //col = ����, lines = ����
    SetConsoleTitle("���Ż��");

    InitPlayer();
    InitItem();  // ������ �ʱ�ȭ
    InitWeapon(weaponList); // ���� �ʱ�ȭ
    DrawStartScreen();
    SelectWeapon();
    player.HeldWeapon = &weaponList[GetSelectedIndex()];

    //����
    while (true)
    {
        GetInput();
        ItemFrameDelay();
        Input(); // Ű �Է�

        Update(); // ������Ʈ

        _Invalidate(); // ȭ�� �׸��� (Draw() �Լ� �ڵ� ����)
        _Delay(30);

        if (IsGameOver)
        {
            ReturnStartScreen();
            main();

        }
    }

    _EndWindow();
}