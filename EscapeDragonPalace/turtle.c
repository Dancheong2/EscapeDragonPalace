#include "init.h"
#include "turtle.h"
#include "map.h"

Turtle g_Turtle;


static TurtleState g_State;          // ���� ����
static unsigned int g_NextRushTime;  // ���� ���� �غ� ���� �ð�
static unsigned int g_PrepStartTime; // ���� �غ� ����
static unsigned int g_RushEndTime;   // ���� ������ ����(�� ���) ��� �ð�
static bool g_ShowPrep;              // ���� �غ� ������
static int g_RushCount;              // 3���� ������ ���°���� ����
static int g_RushDir;
static int g_InitialDir;             // ����Ŭ ���� �� ù ���� ���� ���
static int g_LastRandIdx;            // ���� ���� �ߺ� ����

// �̸������ ���� (2,3��° �������� ���� ���� �����ֱ�)
static bool g_ShowTarget = false;
static unsigned int g_TargetPreviewEnd = 0; //�̸����� ��
static int g_PendingTargetY = 0;

int g_TargetFirstY = TURTLE_IDLE_Y + 1; //ù ���� Y (�ٸ� ������ϱ� Y+1)
int g_TargetOptions[TURTLE_RUSH_OPTION_COUNT] = { 4, 9, 14 };
int g_StartX[2] = { -TURTLE_WIDTH, SCREEN_WIDTH };

const char* turtleGraphic[2][TURTLE_HEIGHT] = {
    {
        "       ______",
        "|\\   _/ \\__/ \\_ ___",
        "| \\_/ \\ /  \\ / \\ o_)",
        " \\__----------- __/",
        "    \\_|_|_|_|_/",
        "    |_|_\\  |_|_\\ "
    },
    {
        "       ______ ",
        " ___ _/ \\__/ \\_   /|",
        "(_o / \\ /  \\ / \\_/ |",
        " \\__ -----------__/",
        "     \\_|_|_|_|_/ ",
        "    /_|_|  /_|_|"
    }
};

static unsigned int randRange(unsigned min, unsigned max) {
    return min + (unsigned)(rand() % (max - min + 1));
}

void InitTurtle(unsigned int now) {
    srand((unsigned)time(NULL));

    // �⺻ ��ġ/����
    g_Turtle.pos.x = 58;
    g_Turtle.pos.y = TURTLE_IDLE_Y;
    g_Turtle.speed = 1.0f;
    g_Turtle.dir = 1;
    g_Turtle.hp = TURTLE_HP;
    g_Turtle.attack = 2;
    g_Turtle.alive = true;
    g_Turtle.isDamaged = false;
    g_Turtle.lastHitTime = now;

    g_State = TURTLE_STATE_IDLE;
    g_NextRushTime = now + randRange(10000, 15000); // 10~15�� �� ���� ����
    g_PrepStartTime = g_NextRushTime - 2000;       // ���� �� 2�� ���
    g_ShowPrep = false;
    g_RushCount = 0;

    g_InitialDir = -1;
    g_RushDir = g_InitialDir;
    g_LastRandIdx = -1;

    // �̸����� �ʱ�ȭ
    g_ShowTarget = false;
    g_TargetPreviewEnd = 0;
    g_PendingTargetY = 0;
}

void UpdateTurtle(unsigned int now) {
    if (!g_Turtle.alive) return;

    // �ǰ� �ʱ�ȭ(1��)
    if (g_Turtle.isDamaged && now - g_Turtle.lastHitTime >= 1000)
        g_Turtle.isDamaged = false;

    switch (g_State) {
    case TURTLE_STATE_IDLE:
        // ���� �ð��� �Ǹ� �غ� ���·� ��ȯ
        if (now >= g_PrepStartTime) {
            g_State = TURTLE_STATE_PREPARE_RUSH;
            g_PrepStartTime = now;
            g_ShowPrep = true; // ��� ���� ������
        }
        break;

    case TURTLE_STATE_PREPARE_RUSH:
        // �غ� �ð�(2��)�� ������ ���� ���� ���� ����
        if (now - g_PrepStartTime >= 2000) {
            g_State = TURTLE_STATE_RUSHING;
            g_ShowPrep = false;
            g_RushCount = 0;
            g_RushDir = g_InitialDir; // ����Ŭ�� ù ���� ���
            g_Turtle.dir = (g_RushDir < 0 ? 1 : 0);
            g_Turtle.pos.y = g_TargetFirstY; // ù ���� Y ����
            g_Turtle.pos.x = (g_RushDir < 0 ? g_StartX[1] - 20 : g_StartX[0] + 20);
            g_RushEndTime = now + 1000; // ù ������ ���� �ð�
        }
        break;

    case TURTLE_STATE_RUSHING: {
        // �̸����� ���� ������ �̵����� ����
        if (g_ShowTarget) {
            if (now < g_TargetPreviewEnd) {
                // �÷��̾�� ���� ��ġ ������
                break;
            }
            else {
                // �ڶ� ���� ��ġ�� ��ġ�ϰ� ���� ����
                g_ShowTarget = false;
                g_Turtle.pos.y = g_PendingTargetY;
                g_Turtle.pos.x = (g_RushDir < 0 ? g_StartX[1] - 20 : g_StartX[0] + 20);
                g_RushEndTime = now + 900; // ���� ������ ���� �ð�
            }
        }

        // ���� �̵�: �ӵ� * ���
        int step = (int)(g_Turtle.speed * 3);
        g_Turtle.pos.x += (g_RushDir < 0 ? -step : step);

        // ȭ���� ������ ���������� üũ
        bool passed = (g_RushDir < 0)
            ? (g_Turtle.pos.x + TURTLE_WIDTH < 0)
            : (g_Turtle.pos.x > SCREEN_WIDTH);

        if (passed && now >= g_RushEndTime) {
            g_RushCount++;
            if (g_RushCount < TURTLE_RUSH_COUNT) {
                // ���� ���� �غ�
                g_RushDir = -g_RushDir;
                g_Turtle.dir = (g_RushDir < 0 ? 1 : 0);
                int opts = sizeof(g_TargetOptions) / sizeof(int);
                int idx;
                do { idx = randRange(0, opts - 1); } while (idx == g_LastRandIdx && opts > 1);
                g_LastRandIdx = idx;

                // �̸�����
                g_PendingTargetY = g_TargetOptions[idx];
                g_ShowTarget = true;
                g_TargetPreviewEnd = now + 1000; // 1�� �̸�����
            }
            else {
                // IDLE�� ���ư��� ���� ����Ŭ �غ�
                g_State = TURTLE_STATE_IDLE;
                g_Turtle.pos.y = TURTLE_IDLE_Y;

                // ���� ����Ŭ�� ù ���� ������ ������Ű��
                g_InitialDir = -g_InitialDir;
                if (g_InitialDir > 0) {
                    g_Turtle.pos.x = g_StartX[0] + 14;
                    g_Turtle.dir = 0;
                }
                else {
                    g_Turtle.pos.x = g_StartX[1] - 22;
                    g_Turtle.dir = 1;
                }

                g_NextRushTime = now + randRange(10000, 15000);
                g_PrepStartTime = g_NextRushTime - 2000;
            }
        }
        break;
    }
    }
}

void DrawTurtle(void) {
    if (!g_Turtle.alive) return;

    if (g_ShowTarget) {
        const char* marker = "!";
        int len = strlen(marker);
        int mx = SCREEN_WIDTH / 2 - len / 2 + GetPlusX();
        int py = g_PendingTargetY - 3; if (py < 0) py = 0;
        _DrawText(mx, py, marker);
    }

    // ���� �߿� �ź��̰� ȭ�� ������ ������ ������ �׸��� ����
    if (g_State == TURTLE_STATE_RUSHING) {
        if (g_RushDir > 0 && g_Turtle.pos.x < 0) return;
        if (g_RushDir < 0 && g_Turtle.pos.x + TURTLE_WIDTH > SCREEN_WIDTH) return;
    }

    // ���� �ź��� �׸���
    int x = g_Turtle.pos.x - GetPlusX();
    if (g_State == TURTLE_STATE_PREPARE_RUSH) {
        const char* m = "�ڶ� ������ �غ����Դϴ�!";
        int l = strlen(m);
        _DrawText(SCREEN_WIDTH / 2 - l / 2 + GetPlusX(), 1, m);
    }

    int idx = (g_Turtle.dir == 0 ? 0 : 1);
    int lines = (g_State == TURTLE_STATE_RUSHING ? TURTLE_HEIGHT - 1 : TURTLE_HEIGHT);
    for (int r = 0; r < lines; ++r) {
        _DrawText(x, g_Turtle.pos.y + r, turtleGraphic[idx][r]);
    }
}