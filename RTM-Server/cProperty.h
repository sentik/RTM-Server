#pragma once

#ifndef __cProperty__   
#define __cProperty__   
#include "configs.h"

struct sProperty
{
	int		db;				//�� � ��
	int		owner;			//��������
	int		property;		//������ �� ��������� (��)
	int		price;			//���������
	float	posX;			//������� x
	float	posY;			//������� y
	float	posZ;			//������� z
	int		bank;			//������ �� ���� � �����
	int		link;			//������ �� ��������� (���������)
	char	style;
	char	status;
	char	type;			//��� ���������
	char	player[16];		//��� ���������
	int		pick;
	int		text;
};
struct sProperty extern Property[ MAX_PROPERTY ];
extern int countProperty;

struct Banks
{
	int db;				//�� �����
	int world;			//����. ���
	//----------------------------------------
	int start;			//����� ������. ������
	int end;			//����� ������. �����
	//----------------------------------------
	float credit;		//������� �������
	float deposit;		//������� ������
	float send;			//������� ��������
	float pay;			//������� ������
};

class cProperty
{
public:
	//-------------------------------------------
	static void cProperty::enterProperty(const int);
	static void cProperty::buyMessage(const int, const int);
	static void cProperty::statusMessage(const int, const int);
	//-------------------------------------------
};




#endif 