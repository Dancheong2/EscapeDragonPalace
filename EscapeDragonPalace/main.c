#include "init.h"
#include "item.h"
#include "Rabbit.h"
#include "map.h"
#include "weapon.h"
#include "monster.h"
#include "screens.h"
#include "turtle.h"
#include "fish_big.h"
#include "fish_small.h"

// ===============================================================

void Draw() // ȭ�� �׸���
{
    // ���� ���� ��
    if (!GetGameStart()) {
        _SetColor(E_White); // ���� �� ����
        GameStartScreen();  // ���ӽ��� ȭ�� ���
        // ���� ����Ʈ ȿ��
        if (GetTextE())
            _SetColor(E_White); // ���� �� ����
        else
            _SetColor(E_Gray); // ���� �� ����
        _DrawText(26, 22, "�ƹ� Ű�� ���� ���� �����ϱ�");


    }
    // ���� ���� ��
    else {
        // ���ӿ������� ��
        if (GetIsGameOver())
        {
            _SetColor(E_White); // ���� �� ����
            GameOverScreen();   // ���ӿ��� ȭ�� ���
            // ���� ����Ʈ ȿ��
            if (GetTextE())
                _SetColor(E_White); // ���� �� ����
            else
                _SetColor(E_Gray); // ���� �� ����
            _DrawText(23, 21, "�ƹ� Ű�� ���� ����ȭ������ ���ư���");


        }
        // �������� Ŭ����
        else if (StageClear())
        {
            RabbitSCAnim();  // �������� Ŭ���� ȭ�� ���

            _Delay(45);
        }
		else if (GetTurtleHp() <= 0) // �ڶ� ������ ü���� 0 ������ �� (���� Ŭ����)
        {
            _SetColor(E_White); // ���� �� ����
            GameClearSceen(); // ���� Ŭ���� ȭ�� ���
            // ���� ����Ʈ ȿ��
            if (GetTextE())
                _SetColor(E_White); // ���� �� ����
            else
                _SetColor(E_Gray); // ���� �� ����
            _DrawText(12, 21, "ESC�� ���� ���� Ȥ�� �ƹ� Ű�� ���� ����ȭ������ ���ư���");


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

                strcpy(weaponList[0].name, "���");
                strcpy(weaponList[0].sprite, "--|====>");
                weaponList[0].attack = 2;
                weaponList[0].attackSpeed = 2;

                DrawMapBG(); // �� ��� �׸���

                // �������� ������ ������ ������ �� �Ǿ����� ��
                if (!GetMapSetting()) {
                    ItemSetting();
                }

                // ������ ���
                DrawItem();
                _SetColor(E_White); // ������ �� ���� �ʱ�ȭ


                // ���� ���  
                DrawMonster();
                if (GetMapStatus() == E_Ground) DrawTurtle();
                _SetColor(E_White); // ���� �� ���� �ʱ�ȭ

                // �÷��̾� �ֺ��� �������� ���� �� �˸����� ���
                if (IsNearItem())
                {
                    _DrawText(player.Pos.x, player.Pos.y - 3.f, "e�� ���� ������ �Ա�");
                }

                _DrawText(3, 3, player.HeldWeapon->sprite); // ���� �׸��׸���
                DrawHealth();   // ü�¹� �׸���
                DrawBuffNDebuff();
            }

            // �÷��̾� ���
            DrawPlayer();
            _SetColor(E_White);


            // �� Ʋ �׸���
            DrawMap();
        }
    }
}
// ===========================================================

// ������Ʈ ����
void Update()
{
    if (GetAsyncKeyState('H') & 0x8000)
    {
        g_Turtle.mon.hp = 0;
    }
    UpdateMapPos();

    UpdatePlayer();

    SetIsNearItem(false); // �÷��̾ ������ ��ó�� �ִ��� ���� �ʱ�ȭ

    CheckItemPickup();  // ������ �Ծ����� üũ
    UpdateBuffs(); // �ӵ� ���� ���ӽð� üũ �� ���� ó��


    UpdateMonster();
	MonsterHitPlayer(); // ���� �ǰ� ó�� �Լ�
    PlayerHitMonster();
	PlayerHitTurtle(); // �÷��̾ �ڶ� �����ߴ��� üũ

    // �������� ��� �ڶ� ������Ʈ
    unsigned long now = _GetTickCount();
    if (GetMapStatus() == E_Ground)
    {
        UpdateTurtle(now);
    }
}

// Ű �Է�
void Input()
{
    g_Key = _GetKey();
}

void main()
{
    // �ʱ�ȭ
    _BeginWindow();
    InitWeapon(weaponList); // ���� �ʱ�ȭ
    InitItem();  // ������ �ʱ�ȭ
    while (true)
    {
        InitPlayer();
        ResetBigFish();
        ResetSmallFish();
        InitMonster();  // ���� �ʱ�ȭ
        unsigned long startTime = _GetTickCount();
        InitTurtle(startTime);  // �ڶ�(����) �ʱ�ȭ

        SetConsoleTitle("���Ż��");

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

            if (GetIsGameOver())
            {
                system("cls"); // ȭ�� �����

                ReturnStartScreen();    // ���ӿ��� ȭ�� ���
                break;
            }
			if (GetTurtleHp() <= 0) // �ڶ� ������ ü���� 0 ������ �� (���� Ŭ����)
			{
				system("cls"); // ȭ�� �����
				DrawGameClearScreen(); // ���� Ŭ���� ȭ�� ���
				break;
			}
        }


        _EndWindow();
    }
}