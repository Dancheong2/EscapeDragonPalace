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
    if (!GameStart) {
        GameStartScreen();
        if (GameStartText) _DrawText(23, 21, "�ƹ� Ű�� ���� ���� �����ϱ�");
        else _DrawText(21, 21, "                               ");
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
        else if (stageClear)
        {
            _Delay(45);
            RabbitCAnim();
        }
        else {

            if (!weaponChosen)
            {
                for (int i = 0; i < NUMWEAPON; i++)
                {
                    int isSelected = (i == selectedIndex); // ���� �������� ����
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
                    if(itemList[i].mapStatus == GetMapStatus())
                        if (!itemList[i].isHeld)
                            DrawItem(&itemList[i], frame);
                }

            }

            DrawPlayer();




            if (isNearItem)
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

    isNearItem = false;

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
    system("mode con:cols=78 lines=25");
    SetConsoleTitle("���Ż��");

    InitPlayer();
    InitItem();  // ������ �ʱ�ȭ
    InitWeapon(weaponList); // ���� �ʱ�ȭ
    DrawStartScreen();
    SelectWeapon();
    player.HeldWeapon = &weaponList[selectedIndex];

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