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
	int		db;				//Ид в бд
	int		owner;			//Владелец
	int		property;		//Ссылка на имущество (БД)
	int		price;			//Стоимость
	float	posX;			//Позиция x
	float	posY;			//Позиция y
	float	posZ;			//Позиция z
	int		bank;			//Ссылка на счет в банке
	int		link;			//Ссылка на имущество (локальная)
	unsigned char	style;
	unsigned char	status;
	unsigned char	type;			//Тип имущества
	char	player[16];		//Имя владельца
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
	prNone,				// Нету
	prHouse,			// Дома
	prBank,				// Банки
	prAutosalon,		// Автосалоны
	prMiner,			// Шахты
	prGas,				// Заправки
	prFeller,			// Лесопилки
	prFarms,			// Фермы
	prFactMetal,		// Заводы
	prBelays,			// Страховые компании
};

#endif 