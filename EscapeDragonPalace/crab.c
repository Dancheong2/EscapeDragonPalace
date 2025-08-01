#include "monster.h"

const char* crabGraphic[CRAB_HEIGHT] = {
    "(\\/) (\\/)",    
    "   \\o_o/ ",      
    "  =(___)= "       
};

// �ɰ� �ʱ�ȭ �Լ�
void InitCrab(Monster crab, int x, int y) {
    crab.x = x;                 
    crab.y = y;                 
    crab.dir = 1;               
    crab.hp = CRAB_HP;          
    crab.alive = 1;             
    crab.type = MONSTER_CRAB;   
    crab.isDamaged = 0;         
    crab.lastHitTime = 0;       
}

void UpdateCrab(Monster crab, unsigned int now) {
    if (!crab.alive) return; // �׾����� ó������ ����

    // ���� �ð� ����ߴ��� Ȯ��
    if (crab.isDamaged && now - crab.lastHitTime >= INVINCIBLE_TIME) {
        crab.isDamaged = 0;
    }

    crab.x += crab.dir;

    if (crab.x <= 0) {
        crab.x = 0;
        crab.dir = 1;
    }       
    if (crab.x + CRAB_WIDTH >= 80) {
        crab.x = 80 - CRAB_WIDTH;
        crab.dir = -1;
    }
}

// �ɰ� �׸��� �Լ�
void DrawCrab(Monster crab) {
    for (int y = 0; y < CRAB_HEIGHT; y++) {
        _SetColor(crab.isDamaged ? 6 : 12);  // �ǰ� �� �����, ��� ������

        const char* line = crabGraphic[y]; 
        for (int x = 0; line[x] != '\0'; x++) {
            if (line[x] != ' ') {
                char ch[2] = { line[x], '\0' };
                _DrawText(crab.x + x, crab.y + y, ch);
            }
        }
    }

    _SetColor(15);
}

// �ɰ� �ǰ� ó�� �Լ�
void HitCrab(Monster crab, unsigned int now, int damage) {
    if (crab.isDamaged) return; 

    crab.hp -= damage;          
    crab.isDamaged = 1;         // ���� ���� ����
    crab.lastHitTime = now;     // �ǰ� �ð� ���

    if (crab.hp <= 0) {
        crab.alive = 0;         // ü���� 0 ���ϰ� �Ǹ� ��� ó��
    }
}