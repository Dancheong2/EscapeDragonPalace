#include "monster.h"

// ���� ����
const char* crabGraphic[CRAB_HEIGHT] = {
    "(\\/) (\\/)",    
    "  \\o_o/ ",      
    " =(___)= "       
};

Monster g_Crab = { 30, MONSTER_Y, Right, CRAB_HP, 1, MONSTER_CRAB, 0, 0 };

void UpdateCrab(unsigned int now) {
    if (!g_Crab.alive) return; // �׾����� ó������ ����

    // ���� �ð� ����ߴ��� Ȯ��
    if (g_Crab.isDamaged && now - g_Crab.lastHitTime >= INVINCIBLE_TIME) {
        g_Crab.isDamaged = 0;
    }

    g_Crab.x += g_Crab.dir;

    if (g_Crab.x <= 0) {
        g_Crab.x = 0;
        g_Crab.dir = 1;
    }       
    if (g_Crab.x + CRAB_WIDTH >= 82) {
        g_Crab.x = 80 - CRAB_WIDTH + 2;
        g_Crab.dir = -1;
    }
}

// �ɰ� �׸��� �Լ�
void DrawCrab() {
    for (int y = 0; y < CRAB_HEIGHT; y++) {
        _SetColor(g_Crab.isDamaged ? 6 : 12);  // �ǰ� �� �����, ��� ������

        const char* line = crabGraphic[y]; 
        for (int x = 0; line[x] != '\0'; x++) {
            if (line[x] != ' ') {
                char ch[2] = { line[x], '\0' };
                _DrawText(g_Crab.x + x, g_Crab.y + y, ch);
            }
        }
    }

    _SetColor(15);
}

// �ɰ� �ǰ� ó�� �Լ�
void HitCrab(unsigned int now, int damage) {
    if (g_Crab.isDamaged) return; 

    g_Crab.hp -= damage;          
    g_Crab.isDamaged = 1;         // ���� ���� ����
    g_Crab.lastHitTime = now;     // �ǰ� �ð� ���

    if (g_Crab.hp <= 0) {
        g_Crab.alive = 0;         // ü���� 0 ���ϰ� �Ǹ� ��� ó��
    }
}

