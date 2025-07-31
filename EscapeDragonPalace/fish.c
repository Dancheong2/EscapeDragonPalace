#include "monster.h"


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

void DrawFish() { //����� �׸��� �Լ�

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


void hit() { //���� > ���� ������(12) > �ٽ� ���(15) > ������ ������
	time_t start = time(NULL); // Ÿ���Լ��� �̿�
	time_t end = start + 1;
	Fhp--;
	Fcolor = 12;
	
	if (Fhp == 0) {
		Fcolor = 0; //���� �������� ���� ������ ���ִ� �ڵ�
	}

	_Invalidate();
	while(time(NULL) < end) {
		//1�ʰ� ��� ��
	}
	
	if (Fcolor == 12) {
		Fcolor = 15;
	}
}

void wall() { //���� ���� > �ݴ��
	switch (Fpoint) {
	case 0:
		Fpoint++;


		break;
	case 1:
		Fpoint--;


		break;
	}
}

int RunKey() {
	char k;

	k = _GetKey();


	if ('h' == k) {
		hit();
	}

	if ('w' == k) {
		wall();
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

void RunTimer() { //������ �ݺ��Ǵ� �ڵ�
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

int Fish() {

	RunKey();
	RunTimer();

	return 0;
}




int main() {
	_BeginWindow();
	while (1)
	{
		Fish();

		_Invalidate();
	}
	_EndWindow();
}