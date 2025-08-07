#include "monster.h"
#include "Rabbit.h"


//1. �̵� 2. ��Ÿ 3. ���� 4. ������ �����ؾ���.

const char* turtleGraphic[2][TURTLE_HEIGHT] = {
    {
        "        ______ ",
        "  ___ _/ \\__/ \\_   /|",
        " (_o / \\ /  \\ / \\_/ |",
        "  \\__ -----------__/",
        "      \\_|_|_|_|_/ ",
        "     /_|_|  /_|_|"
    },
    {
        "       ______",
        "|\\   _/ \\__/ \\_ ___",
        "| \\_/ \\ /  \\ / \\ o_)",
        " \\__----------- __/",
        "    \\_|_|_|_|_/",
        "    |_|_\\  |_|_\\ "
    }
};

static Monster g_Turtle = { {50, MONSTER_Y}, 1, TURTLE_HP, 1, E_MONSTER_TURTLE, 0, 0 };

MyPoint GetTurtlePos() {
    return g_Turtle.pos;
}

int GetTurtleDir() {
    return g_Turtle.dir;
}

void UpdateTurtle(Monster* turtle, unsigned int now) {
    if (!g_Turtle.alive) return;

    // �ǰ� �����ð� üũ
    if (g_Turtle.isDamaged && now - g_Turtle.lastHitTime >= INVINCIBLE_TIME) {
        g_Turtle.isDamaged = 0;
    }

    // �̵�
    if (g_Turtle.dir == 0) {
        g_Turtle.pos.x--;
        if (g_Turtle.pos.x <= 0) g_Turtle.dir = 1;
    }
    else {
        g_Turtle.pos.x++;
        if (g_Turtle.pos.x >= 80) g_Turtle.dir = 0;
    }

    DrawTurtle();
}

void DrawTurtle() {
    if (!g_Turtle.alive) return;

    int frame = g_Turtle.dir;

    if (g_Turtle.isDamaged)
        _SetColor(12);
    else
        _SetColor(11);

    for (int i = 0; i < TURTLE_HEIGHT; i++) {
        _DrawText(g_Turtle.pos.x, g_Turtle.pos.y + i, (char*)turtleGraphic[frame][i]);
    }

    _SetColor(15);
}