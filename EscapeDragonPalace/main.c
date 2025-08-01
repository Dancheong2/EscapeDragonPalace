#include "init.h"
#include "map.h"
#include "item.h"
#include "screens.h"
#include "Rabbit.h"
#include "weapon.h"
#include "monster.h"

// ���� ����

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
            SetMapStatus(GetMapStatus() + 1);
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
                DrawMapBG(); // �� Ʋ �׸���
                _DrawText(3, 3, player.HeldWeapon->sprite);
                DrawHealth();


                if (!GetSettingItem()) {
                    for (int i = 0; i < numItem; i++)
                    {
                        if (itemList[i].mapStatus == GetMapStatus()) {
                            itemList[i].isHeld = false;
                        }
                        else {
                            itemList[i].isHeld = true;
                        }
                    }
                    SetSettingItem(true);
                }
                
                for (int i = 0; i < numItem; i++)
                {
                    if (!itemList[i].isHeld) {

                        DrawItem(&itemList[i], GetFrame());
                    }
                }
                

            }

            DrawPlayer();

            // ���Ͱ� ����ִٸ� �׸���
            if (m->alive) {
                DrawFish(&m);
            }



            if (IsNearItem())
            {
                // ���� ================
                _DrawText(player.Pos.x, player.Pos.y - 3.f, "e�� ���� ������ �Ա�");
                // =====================

            }

            // �� Ʋ �׸���
            DrawMap();
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

    UpdateMonster(); // ���� ������Ʈ

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

    SetConsoleTitle("���Ż��");

    // Monster ����ü ���� �Ҵ�
    m = (Monster*)malloc(sizeof(Monster));

    InitPlayer();
    InitItem();  // ������ �ʱ�ȭ
    InitWeapon(weaponList); // ���� �ʱ�ȭ
    InitFish(m, 10, 5);
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

    // �޸� ����
    free(m);

    _EndWindow();
}