#pragma once

#ifndef __cProperty__   
#define __cProperty__   


#define MAX_HOUSES		10000
#define MAX_PROPERTY	MAX_HOUSES + 100

struct Property
{
	int		db;				//�� � ��
	int		owner;			//��������
	int		property;		//������ �� ��������� (��)
	int		price;			//���������
	float	posx;			//������� x
	float	posy;			//������� y
	float	posz;			//������� z
	int		bank;			//������ �� ���� � �����
	int		link;			//������ �� ��������� (���������)
	char	player[16];		//��� ���������
	char	type;			//��� ���������
};
struct Property extern Property[MAX_PROPERTY];
extern int countProperty;

struct Houses
{
	int db;
	int style;
};
struct Houses extern Houses[MAX_HOUSES];
extern int countHouses;

class cProperty
{
public:
	static void cProperty::loadHouses();
	static void cProperty::enterProperty();
};

enum HouseRows
{
	id,
	owner,
	property,
	type,
	posx,
	posy,
	posz,
	price,
	bank,
	db,
	style,
	oName,
};


#endif 