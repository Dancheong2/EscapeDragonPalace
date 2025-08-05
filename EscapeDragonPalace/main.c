#include "map.h"
#include "Rabbit.h"
//================================================================

void Draw() // ȭ�� �׸���
{
    // ���� ���� ��
    if (!GetGameStart()) {
        GameStartScreen();  // ���ӽ��� ȭ�� ���
        // ���� ����Ʈ ȿ��
        if (GetGameStartText()) 
            _DrawText(23, 21, "�ƹ� Ű�� ���� ���� �����ϱ�");
        else 
            _DrawText(21, 21, "                               ");
    }
    // ���� ���� ��
    else {
        // ���ӿ������� ��
        if (IsGameOver)
        {
            GameOverScreen();   // ���ӿ��� ȭ�� ���
            // ���� ����Ʈ ȿ��
            if (GameOverText)
                _DrawText(14, 21, "�ƹ� Ű�� ���� ����ȭ������ ���ư���");
            else
                _DrawText(14, 21, "                                     ");
        }
        // �������� Ŭ����
        else if (StageClear())
        {
            _Delay(45);
            RabbitCAnim();  // �������� Ŭ���� ȭ�� ���
            SetMapStatus(GetMapStatus() + 1);   // �� �������ͽ� 1 ����
            SetSettingItem(false);  // �������� ������ ���� ����
        }
        // �÷��� ���� ��
        else {

            // ���� ���� �� ���� ��
            if (!GetWeaponChosen())
            {
                for (int i = 0; i < NUMWEAPON; i++)
                {
                    int isSelected = (i == GetSelectedIndex()); // ���� �������� ����
                    DrawWeapon(&weaponList[i], i, isSelected);  // ���� ���� ���, �������� ����� �����
                }
            }
            else
            {
                DrawMapBG(); // �� Ʋ �׸���
                _DrawText(3, 3, player.HeldWeapon->sprite); // ���� �׸��׸���
                DrawHealth();   // ü�¹� �׸���


                // �������� ������ ������ ������ �� �Ǿ����� ��
                if (!GetSettingItem()) {
                    for (int i = 0; i < numItem; i++)
                    {
                        // ���� ���������� ���� ������ ���̰� �ϱ�
                        if (itemList[i].mapStatus == GetMapStatus()) {
                            itemList[i].isHeld = false;
                        }
                        else {
                            itemList[i].isHeld = true;
                        }
                    }
                    // �������� ������ ���� �Ϸ�
                    SetSettingItem(true);
                }
                
                // ������ ���
                for (int i = 0; i < numItem; i++)
                {
                    if (!itemList[i].isHeld) {

                        DrawItem(&itemList[i], GetFrame());
                    }
                }
                

            }

            DrawPlayer();


            // TODO: ���Ͱ� ����ִٸ� ���� �׸��� �߰�
            //DrawFish();
            //DrawCrab();
            //DrawClam();

            // ���� ���
            for (int i = 0; i < numMonster; i++)
            {
                if (monsterList[i].alive) {

                    DrawMonster(monsterList[i]);
                }
            }


            // �÷��̾� �ֺ��� �������� ���� �� �˸����� ���
            if (IsNearItem())
            {
                _DrawText(player.Pos.x, player.Pos.y - 3.f, "e�� ���� ������ �Ա�");
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
    
    UpdatePlayer();

	SetIsNearItem(false); // �÷��̾ ������ ��ó�� �ִ��� ���� �ʱ�ȭ

    CheckItemPickup();  // ������ �Ծ����� üũ
    UpdateSpeedBuffs(); // �ӵ� ���� ���ӽð� üũ �� ���� ó��
    

    UpdateMonster();



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

    InitMonster();  // ���� �ʱ�ȭ
    InitItem();  // ������ �ʱ�ȭ
    InitWeapon(weaponList); // ���� �ʱ�ȭ
    InitPlayer();
    DrawStartScreen();  // ����ȭ�� �۵� �Լ� ���
    SelectWeapon(); // ���� ����
    player.HeldWeapon = &weaponList[GetSelectedIndex()];    // �÷��̾� ���� ����




    //����
    while (true)
    {
        GetInput();
        ItemFrameDelay();   // ������ ��� ȿ��
        Input(); // Ű �Է�

        Update(); // ������Ʈ

        _Invalidate(); // ȭ�� �׸��� (Draw() �Լ� �ڵ� ����)
        _Delay(30);


        if (IsGameOver)
        {
            ReturnStartScreen();    // ���ӿ��� ȭ�� ���
            main(); // ���� ��ȣ��

        }
    }


    _EndWindow();
}