#pragma once

#define NUMWEAPON 3 // ���� ���� ����
#define WEAPON_SPRITE_LENGTH  21 // ���� ��������Ʈ ����

// ���� ����ü
typedef struct Weapon {
	char name[30];                      // ���� �̸�
	char sprite[WEAPON_SPRITE_LENGTH];  // ���� ��������Ʈ
    int attack;                         // ���ݷ�
    int attackSpeed;                    // ���ݼӵ�
} Weapon;

Weapon weaponList[NUMWEAPON];   // ���� ����Ʈ
char buffer[50];				// ���� ���� ��¿� ����

// �Լ�
void SelectWeapon();		// ���� ���� �Լ�
int GetSelectedIndex();		// ���õ� ���� �ε��� ��ȯ �Լ�
bool GetWeaponChosen();		// ���� ���� ���� ��ȯ �Լ�
void SetWeaponChosen(bool src);		// ���� ���� ���� ���� �Լ�
void InitWeapon(Weapon* weapons);	// ���� �ʱ�ȭ �Լ�
void DrawWeapon(const Weapon* w, int i, int isSelected); // ���� ���� ��� �Լ�
