#pragma once

#ifndef __cProperty__   
#define __cProperty__   
#include "configs.h"
#include "shopVehicle.h"


namespace Properties
{
	enum propertyTypes
	{
		Property_None,
		Property_House,
	};
}


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
	unsigned char	style;
	unsigned char	status;
	unsigned char	type;			//��� ���������
	char	player[16];		//��� ���������
	int		pick;
	int		text;
	int		region;			//Property region
	int		number;			//Property number of region
};
struct sProperty extern Property[ MAX_PROPERTY ];
extern int countProperty;

class cProperty
{
public:
	//-------------------------------------------
	static void cProperty::enterProperty(const int);
	static void cProperty::buyMessage(const int, const int);
	static void cProperty::statusMessage(const int, const int);
	static char* cProperty::getZoneName(const int);
	static int cProperty::getZoneNumber(float, float, float);
	static void cProperty::beforBuy(const int);
	//============================================================
	static void cProperty::setOwner(const int, const int);
	static void cProperty::setStatus(const int, const int);
	//============================================================
	static void cProperty::doAct(int);
	static void cProperty::doSub(int);
};

enum PropertyType
{
	prNone,				// ����
	prHouse,			// ����
	prBank,				// �����
	prAutosalon,		// ����������
	prMiner,			// �����
	prGas,				// ��������
	prFeller,			// ���������
	prFarms,			// �����
	prFactMetal,		// ������
	prBelays,			// ��������� ��������
};

#endif 