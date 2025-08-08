#pragma once

#define TURTLE_HEIGHT      6
#define TURTLE_WIDTH       13
#define TURTLE_HP          80

// ���� Ƚ�� (�� ����Ŭ�� �� �� ��������)
#define TURTLE_RUSH_COUNT  3
// Idle ������ �� �ź��� Y ��ǥ
#define TURTLE_IDLE_Y      18

// ���� �ɼ� ���� (ù ���� ����)
#define TURTLE_RUSH_OPTION_COUNT 3

// ù ���� Y��ǥ (Idle���� 1ĭ ��)
extern int g_TargetFirstY;
// ���� �������� ����� Y �ɼǵ� (���� ����)
extern int g_TargetOptions[TURTLE_RUSH_OPTION_COUNT];
// ���� X��ǥ: [0]=���� ����, [1]=������ ����
extern int g_StartX[2];

typedef struct { int x, y; } Point;

typedef struct {
    Point pos;
    float speed;
    int dir;
    int hp;
    int attack;
    bool alive;
    bool isDamaged;
    unsigned int lastHitTime;
} Turtle;

//���� ����
typedef enum {
    TURTLE_STATE_IDLE, // ��� ����
    TURTLE_STATE_PREPARE_RUSH, // ���� �غ�
    TURTLE_STATE_RUSHING // ������
} TurtleState;

extern Turtle g_Turtle;

void InitTurtle(unsigned int now);
void UpdateTurtle(unsigned int now);
void DrawTurtle(void);
