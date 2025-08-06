#include "monster.h"

//1. �̵� 2. ��Ÿ 3. ���� 4. ������ �����ؾ���.
void DrawTurtle(int dir, int posX, int posY) {
    if (posX + TURTLE_WIDTH < 0 || posX >= SCREEN_WIDTH) return;

    for (int y = 0; y < TURTLE_HEIGHT; y++) {
        const char* line = (char*)turtleGraphic[dir][y];
        int len = strlen(line);

        for (int x = 0; x < len; x++) {
            char ch = line[x];
            if (ch != ' ') {
                int drawX = posX + x;
                int drawY = posY + y;

                if (0 <= drawX && drawX < SCREEN_WIDTH && 0 <= drawY && drawY < SCREEN_HEIGHT) {
                    char temp[2];
                    temp[0] = ch;
                    temp[1] = '\0';
                    _DrawText(drawX, drawY, temp);
                }
            }
        }
    }
}
