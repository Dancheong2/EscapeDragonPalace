#include "init.h"
#include "Rabbit.h"

#define GX 70 // ��ǥ ���� X ��ǥ
#define GY 22 // ��ǥ ���� Y ��ǥ

//--------------------------------------------------

float amount;

char Rabbit[14][RabbitY][RabbitX] =
{
    {
        "        (\\(\\",
        "        ('-')",
        "       o(��--|====>"
    }, // ��� ������ �⺻
    {
        "         /)/)",
        "        ('-')",
        "  <====|--��)o"
    }, // ��� ���� �⺻
    {
        "        (\\(\\ ",
        "        ('-')",
        "       o(����--|====>"
    }, // ��� ������ ����
    {
        "         /)/) ",
        "        ('-') ",
        "<====|--����)o"
    }, // ��� ���� ����
    {
        "        (\\(\\ ",
        "        ('-')",
        "       o(��-|=>"
    }, // �ܰ� ������ �⺻
    {
        "         /)/) ",
        "        ('-') ",
        "      <=|-��)o"
    }, // �ܰ� ���� �⺻
    {
        "        (\\(\\ ",
        "        ('-')",
        "       o(����-|=>"
    }, // �ܰ� ������ ����
    {
        "         /)/) ",
        "        ('-') ",
        "    <=|-����)o"
    }, // �ܰ� ���� ����
    {
        "        (\\(\\ ",
        "        ('-')",
        "       o(��------>"
    }, // â ������ �⺻
    {
        "         /)/) ",
        "        ('-') ",
        "   <------��)o"
    }, // â ���� �⺻
    {
        "        (\\(\\ ",
        "        ('-')",
        "       o(����------>"
    }, // â ������ ����
    {
        "         /)/) ",
        "        ('-') ",
        " <------����)o"
    }, // â ���� ����
    {
        "        (\\(\\",
        "        ('-')",
        "       o(   )"
    }, // �÷��̾� ������
    {
        "         /)/) ",
        "        ('-') ",
        "        (   )o"
    }, // �÷��̾� ����
};


bool g_KeyW = false;
bool g_KeyA = false;
bool g_KeyD = false;

bool halfHealth = false; // ü�� ��ĭ

bool g_MouseClick = false;


//�ִϸ��̼� ���� ����
int animFrame;         // 0 ~ jumpFrames*2-1 (up + down)
int animRepeatCount;   // �ִϸ��̼� �ݺ� Ƚ��
int jumpFrames;  // �ö󰡴� ������ ����
int maxRepeats;  // �ִ� �ݺ� Ƚ��
int centerX;
int baseY;
int jumpHeight;
int animFramesTotal; // ��ü �ִϸ��̼� ���� (up+down)

bool animGoingUp = true;  // ���� �� �ö󰡴��� ����

// --------------------------------------------------
// �÷��̾�� ������Ʈ �浹 üũ
bool IsOverlap(Rect player, Rect Obj)
{
    return (player.x < Obj.x + Obj.w) && (player.x + player.w > Obj.x) &&
        (player.y < Obj.y + Obj.h) && (player.y + player.h > Obj.y);
}

// �÷��̾��� �浹 ���� ��ȯ
Rect GetPlayerRect()
{
    return (Rect) { player.Pos.x, player.Pos.y, 8, 3 };
}

// �������� �浹 ���� ��ȯ
Rect GetItemRect(Item item)
{
    return (Rect) { item.x - 7, item.y, item.width + 2, item.height };
}

// ������ �Ծ����� üũ
void CheckItemPickup()
{

    Rect playerRect = GetPlayerRect();

    for (int i = 0; i < numItem; i++)
    {
        if (itemList[i].isHeld) continue;

        Rect itemRect = GetItemRect(itemList[i]);

        if (IsOverlap(playerRect, itemRect))
        {
            isNearItem = true;  // �������
            if (GetAsyncKeyState('E') & 0x8000)
            {
                itemList[i].isHeld = true;
                switch (itemList[i].type) {
                case ITEM_LIFE:
                    player.Health += itemList[i].value;
                    break;
                case ITEM_SPEED:
                    // �ӵ� ������, ���ӽð�(ms)
                    amount = itemList[i].value;
                    DWORD duration = 5000; // ��: 5��

                    for (int j = 0; j < MAX_BUFFS; j++)
                    {
                        if (!speedBuffs[j].active)
                        {
                            speedBuffs[j].active = true;
                            speedBuffs[j].amount = amount;
                            speedBuffs[j].endTime = GetTickCount() + duration;
                            player.Speed += amount; // ��� ����
                            break;
                        }
                        break;
                    }
                    break;
                }
            }
        }
    }
}

// �ӵ� ���� ���ӽð� üũ �� ���� ó��
void UpdateSpeedBuffs()
{
    DWORD now = GetTickCount();

    for (int i = 0; i < MAX_BUFFS; i++)
    {
        if (speedBuffs[i].active && now >= speedBuffs[i].endTime)
        {
            player.Speed -= speedBuffs[i].amount; // ������� ����
            speedBuffs[i].active = false;
        }
    }
}

void ClearRabbitAt(int x, int y) 
{
    for (int row = 0; row < RabbitY; row++) 
    {
        // RabbitX ũ�⸸ŭ ���� �׸���
        char blankLine[RabbitX + 1];
        memset(blankLine, ' ', RabbitX);
        blankLine[RabbitX] = '\0';

        _DrawText(x, y + row, blankLine);
    }
}

void DrawRabbitAt(int x, int y, int idx) 
{
    for (int row = 0; row < RabbitY; row++) 
    {
        _DrawText(x, y + row, Rabbit[idx][row]);
    }
}

void RabbitCAnim() // Rabbit clear �ִϸ��̼�
{
	_DrawText(36, 10, "�ƹ� Ű�� ���� ���� ���������� �Ѿ��");

    player.Pos.x = 10.0f;
    player.Pos.y = 21.0f;

    static int prevX = -1, prevY = -1;

    // ���� ��ġ �����
    if (prevX >= 0 && prevY >= 0)
    {
        ClearRabbitAt(prevX, prevY);
    }

    // �ö󰡴� ������ �������� ������ �Ǵ�
    int yOffset;
    if (animFrame < jumpFrames)
    {
        // �ö󰡴� ��: yOffset ���� Ŀ�� (0,1,2,...)
        yOffset = (jumpHeight * animFrame) / jumpFrames;
    }
    else
    {
        // �������� ��: yOffset ���� �۾��� (jumpHeight,...1,0)
        int downFrame = animFrame - jumpFrames;
        yOffset = (jumpHeight * (jumpFrames - downFrame)) / jumpFrames;
    }

    int currentY = baseY - yOffset;

    // �䳢 �׸���
    int idx = 12;  // ������ �䳢 ��������Ʈ �ε���
    DrawRabbitAt(centerX, currentY, idx);

    prevX = centerX;
    prevY = currentY;

    // �ִϸ��̼� ������ ����
    animFrame++;

    // �� ����Ŭ ��������
    if (animFrame >= jumpFrames * 2)
    {
        animFrame = 0;
        animRepeatCount++;

        // �ִϸ��̼� �ݺ� ����
        if (animRepeatCount >= maxRepeats)
        {
            animRepeatCount = 0;

            // �ִϸ��̼� ���� �� ���� ��ġ�� �䳢 �׸���
            ClearRabbitAt(prevX, prevY);
            DrawRabbitAt(centerX, baseY, idx);
        }
    }
}

void GetInput() // GetAsyncKeyState�� ���� Ű �Է� ����
{
    g_KeyW = (GetAsyncKeyState('W') & 0x8000);
    g_KeyA = (GetAsyncKeyState('A') & 0x8000);
    g_KeyD = (GetAsyncKeyState('D') & 0x8000);

    // ���콺 ���� ��ư Ŭ�� ����
    g_MouseClick = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
}

void ApplyGravity() // �߷� ���� �Լ�
{

}

bool CheckGround() // �ٴ� üũ �Լ�
{
    
}

void PlayerYPosition() // �÷��̾� Y ��ġ ���� �Լ�
{
	
}

void JumpFN()
{
    // ���� ����
    if (!player.IsJumping && g_KeyW)
    {
        player.IsJumping = true;
        player.VelY = JUMP_POWER;
    }

    // �߷� ����
    if (player.IsJumping)
    {
        player.VelY += GRAVITY;
        if (player.VelY > MAX_FALL_SPEED)
            player.VelY = MAX_FALL_SPEED;

        player.Pos.y += player.VelY;

        if (player.Pos.y >= 21.0f)
        {
            player.Pos.y = 21.0f;
            player.VelY = 0.0f;
            player.IsJumping = false;
        }
    }
}

void AttackFN()
{
    // ���� ����: ���콺 Ŭ�� && ���� �� �ƴ�
    if (g_MouseClick && !player.IsAttacking)
    {
        player.IsAttacking = true;
        player.AttackFrame = 0;
        player.attackStartTime = GetTickCount();

        switch (player.HeldWeapon ? player.HeldWeapon->attackSpeed : 1)
        {
        case 3: player.AttackFrameMax = 10; player.attackDuration = 100; break; // �ܰ�
        case 2: player.AttackFrameMax = 15; player.attackDuration = 300; break; // ���
        case 1: player.AttackFrameMax = 20; player.attackDuration = 500; break; // â
        default: player.AttackFrameMax = 15; player.attackDuration = 300; break;
        }
    }

    // ���� �ִϸ��̼� ó��
    if (player.IsAttacking)
    {
        player.AttackFrame++;

        if (GetTickCount() - player.attackStartTime >= player.attackDuration)
        {
            player.IsAttacking = false;
            player.AttackFrame = 0;
        }
    }
}

void moveFN()
{
    // �̵� ó��
    float move = player.IsJumping ? player.Speed * 1.2f : player.Speed;

    if (g_KeyA)
    {
        player.Pos.x -= move;
        player.Direction = 1;
    }
    if (g_KeyD)
    {
        player.Pos.x += move;
        player.Direction = 0;
    }
}

bool ISOnGoal()
{
    /*int idx;
    int dir = player.Direction;

    if (!weaponChosen)
        idx = dir == 0 ? 12 : 13;
    else {
        int weaponType = player.HeldWeapon ? player.HeldWeapon->attackSpeed : 2;
        if (weaponType == 3)      idx = dir == 0 ? 4 : 5;
        else if (weaponType == 2) idx = dir == 0 ? 0 : 1;
        else                      idx = dir == 0 ? 8 : 9;
        if (player.IsAttacking) {
            if (weaponType == 3)      idx = dir == 0 ? 6 : 7;
            else if (weaponType == 2) idx = dir == 0 ? 2 : 3;
            else                      idx = dir == 0 ? 10 : 11;
        }
    }

    for (int y = 0; y < RabbitY; y++) {
        const char* line = Rabbit[idx][y];
        int len = strlen(line);
        for (int x = 0; x < len; x++) {
            if (line[x] != ' ') {
                int px = (int)player.Pos.x + x;
                int py = (int)player.Pos.y + y;
                if (px == GX && py == GY)
                    return true;
            }
        }
    }
    return false;*/
}

// Ű���� ���� ���� �Լ�
void ClearInputBuffer()
{
    while (_kbhit()) _getch();
}

void UpdatePlayer() // �÷��̾� �̵� Ű �Է� ó�� 
{
    int iR = 0;
    int iL = 0;

    switch (player.HeldWeapon->attackSpeed)
    {
    case 3:  // �ܰ�
        iR = 17;
        iL = 2;
        break;
    case 2:  // ���
        iR = 21;
        iL = -2;
        break;
    case 1:  // â
        iR = 20;
        iL = -1;
        break;
    }

    // ��� üũ
    if (player.Pos.x < 0 - iL) player.Pos.x = 0 - iL;
    if (player.Pos.x > SCREEN_WIDTH - iR) player.Pos.x = SCREEN_WIDTH - iR;
    if (player.Pos.y < 0) player.Pos.y = 0;
    if (player.Pos.y > SCREEN_HEIGHT - RabbitY) player.Pos.y = SCREEN_HEIGHT - RabbitY;

    JumpFN();

    AttackFN();

    moveFN();

    // Rabbit�� @�� ��Ҵ��� üũ
    if (ISOnGoal())
    {
        stageClear = true;
    }

    if (_kbhit())
    {
        g_Key = _getch();

        if (stageClear == false)
        {
            ClearInputBuffer(); // Ű���� ���� ����
        }
        else if (g_Key != -1 && stageClear == true)
        {
            stageClear = false; // �������� Ŭ���� ���� �ʱ�ȭ
        }
    }
    
}

void DrawPlayer()
{
    int idx;
    int dir = player.Direction;

    if (!weaponChosen) 
    {
        // ���� ���� ��: ���� ���� �䳢 �̹��� ���
        idx = dir == 0 ? 12 : 13; // ������/����
    }
    else 
    {
        int weaponType = player.HeldWeapon ? player.HeldWeapon->attackSpeed : 2;
        if (weaponType == 3)      idx = dir == 0 ? 4 : 5;
        else if (weaponType == 2) idx = dir == 0 ? 0 : 1;
        else                      idx = dir == 0 ? 8 : 9;

        if (player.IsAttacking) 
        {
            if (weaponType == 3)      idx = dir == 0 ? 6 : 7;
            else if (weaponType == 2) idx = dir == 0 ? 2 : 3;
            else                      idx = dir == 0 ? 10 : 11;
        }
    }

    for (int y = 0; y < RabbitY; y++) 
    {
        const char* line = Rabbit[idx][y];
        int len = strlen(line);
        for (int x = 0; x < len; x++) 
        {
            if (line[x] != ' ') 
            {
                _DrawText((int)player.Pos.x + x, (int)player.Pos.y + y, (char[]) { line[x], '\0' });
            }
        }
    }
}

void DrawHealth() // �÷��̾� ü�� �׸���
{
    if (player.Health > 0)
    {

        if (player.Health % 2 == 1)
        {
            halfHealth = true; // ü�� ��ĭ �ִ�
        }

        int x = 3;

        for (size_t i = 0; i < player.Health / 2; i++)
        {
            _DrawText(x, 1, "��"); // ü�� ������ �׸���
            x += 3;
        }

        if (halfHealth)
        {
            halfHealth = false;

            _DrawText(x, 1, "��"); // ü�� ��ĭ ������ �׸���
        }
    }
    else
    {
        IsGameOver = true;
    }
}

void InitPlayer() // �ʱ�ȭ
{
    player.Pos.x = 10.0f;
    player.Pos.y = 21.0f;
    player.Speed = 1.0f;
    player.Health = 10;
    player.VelY = 0.0f;
    player.IsJumping = false;
    player.Direction = 0;

    player.IsAttacking = false;
    player.AttackFrame = 0;
    player.attackStartTime = 0;

    // ����
    player.HeldWeapon = &weaponList[selectedIndex];

    // ���� �ӵ��� ���� ���� ���� �ð� ����
    int speed = player.HeldWeapon->attackSpeed;
    player.attackDuration = (speed == 3) ? 100 : (speed == 2) ? 200 : 400;

    switch (player.HeldWeapon->attackSpeed)
    {
    case 3:  // �ܰ�
        player.attackDuration = 100;
        break;
    case 2:  // ���
        player.attackDuration = 300;
        break;
    case 1:  // â
        player.attackDuration = 500;
        break;
    }

    animFrame = 0;
    animRepeatCount = 0;
    jumpFrames = 5;
    maxRepeats = 4;
    centerX = 40;
    baseY = 20;
    jumpHeight = 2;
    animFramesTotal = 10;

    isNearItem = false;
}

