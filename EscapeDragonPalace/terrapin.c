#include "monster.h"


#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

const char* turtle[] = {
    "        ______ ",
    "  ___ _/ \\__/ \\_   /|",
    " (_o / \\ /  \\ / \\_/ |",
    "  \\__ -----------__/",
    "      \\_|_|_|_|_/ ",
    "     /_|_|  /_|_|"
};

#define TURTLE_HEIGHT 6
#define TURTLE_WIDTH 22
#define TURTLE_Y (SCREEN_HEIGHT - TURTLE_HEIGHT)
#define TURTLE_X 55

#define WATER_CHAR '@'

enum Direction { UP, MIDDLE, DOWN };
enum Direction currentDir = MIDDLE;

int waterY = -1;
int waterLength = 0;  // ������ ����
int tcolor = 15;
int Hp = 80;

int getDirectionY(enum Direction dir) {
    switch (dir) {
    case UP: return TURTLE_Y + 1;
    case MIDDLE: return TURTLE_Y + 3;
    case DOWN: return TURTLE_Y + 5;
    }
    return TURTLE_Y + 3;
}

void DrawWaterBlast(int y, int length) {
    if (length > TURTLE_X) length = TURTLE_X;  // �ڶ� ���� ���� �Ѿ�� �ʵ��� ����

    char line[81] = { 0 };
    for (int i = 0; i < length; i++) {
        line[i] = WATER_CHAR;
    }
    line[length] = '\0';

    _DrawText(0, y, line);
}

void Draw() {
    // ȭ�� Ŭ����
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        char blank[SCREEN_WIDTH + 1];
        for (int i = 0; i < SCREEN_WIDTH; i++) blank[i] = ' ';
        blank[SCREEN_WIDTH] = '\0';
        _DrawText(0, y, blank);
    }

    // �ڶ� �׸���
    for (int i = 0; i < TURTLE_HEIGHT; i++) {
        _DrawTextColor(TURTLE_X, TURTLE_Y + i, (char*)turtle[i],tcolor);
    }

    // ���� ǥ�� (�ڶ� �� �Ӹ� ���ʿ� ����ǥ)
    int arrowY = getDirectionY(currentDir);
    _DrawText(TURTLE_X - 4, arrowY, "!!!");

    // ������ �׸���
    if (waterLength > 0) {
        DrawWaterBlast(waterY, waterLength);
    }
}

void hit() {
    time_t start = time(NULL); // Ÿ���Լ��� �̿�
    time_t end = start + 1;
    Hp--;
    tcolor = 12;

    if (Hp == 0) {
        tcolor = 0;
    }

    _Invalidate();
    while (time(NULL) < end) {
        //���
    }

    if (tcolor == 12) {
        tcolor = 15;
    }

    return start;

}

int main() {
    srand((unsigned int)time(NULL));
    _BeginWindow();

    while (1) {
        currentDir = (enum Direction)(rand() % 3);

        // ESC Ű ������ ����
        char key = _GetKey();
        if (key == 27) break;
        if (key == 'w')
            hit();


        // ���� ���� 3��
        waterLength = 0;
        _Invalidate();
        _Delay(3000);

        // ������ ������ �ѹ濡 �� �ϰ� 2�� �����ֱ�
        waterY = getDirectionY(currentDir);
        waterLength = TURTLE_X; // �ڶ� ���� ������ �� ä��
        _Invalidate();
        _Delay(2000);

        // ������ �����
        waterLength = 0;
        _Invalidate();

        
    }

    _EndWindow();
    return 0;
}