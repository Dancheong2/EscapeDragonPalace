#include "init.h"
#include "map.h"

int g_Key;

// �Լ�

// ȭ�� �׸���
void Draw()
{
    DrawMap(); // �� �׸���
}

// ������Ʈ ����
void Update()
{
    UpdateMapPos();
}

// Ű �Է�
void Input()
{
    g_Key = _GetKey();
}

void main()
{
    // �� ũ�� ����
    //col = ����, lines = ����
    system("mode con:cols=78 lines=25");
    SetConsoleTitle("���Ż��");

    // init
    _BeginWindow();

    //����
    while (true)
    {
        Input(); // Ű �Է�

        Update(); // ������Ʈ

        _Invalidate(); // ȭ�� �׸��� (Draw() �Լ� �ڵ� ����)
    }

    _EndWindow();
}