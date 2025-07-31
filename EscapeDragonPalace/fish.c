#include "monster.h"
#include"mtg.h"


float Fspeed = 0.4;
int Fhp = 4;
int Fpoint = 1;
int Fpx,Fpy;
int Fcolor = 15;

char fish[2][3][16] = {
	{"  ______", //0
	 " / o )) \\/)",
	 " \\______/\\)"
	},
	{"   ______", //1
	 "(\\/ (( o \\",
	 "(/\\______/"
	}
};

void DrawFish() { //����� �׸���

	for (int i = 0; i < 3; i++) {
		_DrawTextColor(Fpx, Fpy + i, fish[Fpoint][i], Fcolor);
	}
}

void Draw() {
	char temp[80];
	DrawFish();

	
	//test��
	sprintf(temp,"Hp : %d",Fhp);
	_DrawText(10, 10, temp);
	sprintf(temp, "point : %d", Fpoint);
	_DrawText(10, 11, temp);
	

}

void RunIni() {
	_Invalidate();
}


int RunKey() {
	char k;

	k = _GetKey();

}

void hit() { //���� > ���� ������ > �ٽ� ��� > ������ ������
	time_t start = time(NULL); // Ÿ���Լ��� �̿�
	time_t end = start + 1;
	Fhp--;
	Fcolor = 12;
	
	if (Fhp == 0) {
		Fcolor = 0;
	}

	_Invalidate();
	while(time(NULL) < end) {
		//���
	}
	
	if (Fcolor == 12) {
		Fcolor = 15;
	}

	return start;
	
}
void wall(){ //���� ���� > �ݴ��
	switch (Fpoint) {
	case 0:
		Fpoint++;


		break;
	case 1:
		Fpoint--;


		break;
	}
}
//���Ŀ� move�� wall�̶� ������(Ű���� �ȹ޴´ٴ� ����)
void move() {
	//wall();
	switch (Fpoint) {
	case 0:
		Fpx--;
		
		

		break;
	case 1:
		Fpx++;
		

		break;
	}

}

void RunTimer() {
	static long oldT = 0;
	long newT;

	newT = _GetTickCount();
	if (abs(newT - oldT) < 1000 * Fspeed) {
		return;
	}
	else
		oldT = newT;
	
	//�ݺ��� ���� ���⿡


	move();

	_Invalidate();
}

void Fish() {
	RunIni();
	while (1) {

		if (Fhp == -1) { //����
			break;
		}
		if ('d' == RunKey()) {
			hit();
		}

		if ('w' == RunKey()) {
			wall();
		}
		RunTimer();
		_Invalidate();

	}
	
	return 0;
}




int main() {
	_BeginWindow();
	Fish();
	_EndWindow();
}