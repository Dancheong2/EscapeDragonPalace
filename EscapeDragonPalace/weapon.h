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

// ���� �ν��Ͻ� ����ü
typedef struct WeaponInstance {
    Weapon* weapon; // ���� ����
    int x, y;       // �� ��ġ
    int isHeld;     // 0: �ٴڿ� ����, 1: �÷��̾ ����
} WeaponInstance;

Weapon weaponList[NUMWEAPON];   // ���� ����Ʈ
char buffer[50];

// �Լ�
extern void InitWeapon(Weapon* weapons);
extern void DrawWeapon(const Weapon* w, int i, int isSelected);
extern void SelectWeapon();
bool GetWeaponChosen(); 
void SetWeaponChosen(bool src);
int GetSelectedIndex();