#pragma once

// inlcude
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include "mtg.h" // mtg ���� �ҷ�����

// ��ũ��
#define SCREEN_WIDTH 80 // ȭ�� �ʺ�
#define SCREEN_HEIGHT 25 // ȭ�� ����
#define STR_MAX 256 // ���ڿ� �ִ� ũ��

// ����ü
typedef struct MyPoint
{
    float x;
    float y;
} MyPoint;

// ������
// ����
typedef enum {
    E_RIGHT,
    E_LEFT,
} Direction;

// ���� ����
int g_Key;