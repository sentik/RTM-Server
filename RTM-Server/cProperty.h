#pragma once

#ifndef __cProperty__   
#define __cProperty__   


#define MAX_HOUSES		10000
#define MAX_PROPERTY	MAX_HOUSES + 100

struct Property
{
	int		db;				//Ид в бд
	int		owner;			//Владелец
	int		property;		//Ссылка на имущество (БД)
	int		price;			//Стоимость
	float	posx;			//Позиция x
	float	posy;			//Позиция y
	float	posz;			//Позиция z
	int		bank;			//Ссылка на счет в банке
	int		link;			//Ссылка на имущество (локальная)
	char	player[16];		//Имя владельца
	char	type;			//Тип имущества
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