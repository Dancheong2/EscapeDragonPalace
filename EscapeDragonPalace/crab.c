#include "monster.h"

float Pspeed = 0.2;
int Php = 5;
int Ppoint = 0;
int Ppx,Ppy;
int Pcolor = 15;
int crush = 0;


char portun[2][3][16] = {
	{
		"(\\/) (\\/) ",
		"  \\o_o/ ",
		" =(___)= "
	},
	{
		"(\\/) (\\/) ",
		" \\o_o/ ",
		" =(___)= "
	}
};

void DrawPorturn() { //�ɰ� �׸��� �Լ�
    for (int i = 0; i < 3; i++) {
        _DrawTextColor(Ppx, Ppy+ i, portun[crush][i], Pcolor);
    }

}

void Draw() {
    DrawPorturn();
}

void hit() {
    time_t start = time(NULL); // ������ �� �������� �ڵ� �� ������ �ٲ���ٰ� �ٽ� ���ƿ��� �ڵ�
    time_t end = start + 1;

    Php--;

    Pcolor = 12;//���������� ����

    if (Php == 0) { //�������
        Pcolor = 0;
    }

    _Invalidate();
    while (time(NULL) < end) {
        //1�ʰ� ���
    }

    if (Pcolor == 12) { // ������� �ٽ� ���ƿ���
        Pcolor = 15;
    }
}

void wall() { //���� ���� > �ݴ�� �����̰�
    switch (Ppoint) {
    case 0:
        Ppoint++;


        break;
    case 1:
        Ppoint--;


        break;
    }
}

void move() {
    

    switch (Ppoint) {
    case 0:
        
        Ppx++;

        break;
    case 1:
        
        Ppx--;

        break;
    }
}


void P_RunTimer() { //�ݺ������� Ű�� �ȹް� �����̵���

    static long oldT = 0;
    long newT;
    

    newT = _GetTickCount();
    if (abs(newT - oldT) < 1000*Pspeed)
    {
        return;
    }
    else
    {
        oldT = newT;
    }
    //=======

    move();
    _Invalidate();
}

int RunKey() {
    char k;
    k = _GetKey();


    //Ű�� �����
    if ('h' == k) {
        hit();
    }
    if ('w' == k) {
        wall();
    }
}

int Portun() {
    srand(time(NULL));
    crush = rand() % 2; //�ɰ԰� �������� ��Ҵ� �ǰ�

    RunKey();

    P_RunTimer();
}


int main() {
    _BeginWindow();

    while (1) 
    {
        Portun();
		_Invalidate();
    }

    _EndWindow();
}