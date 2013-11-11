#pragma once

#ifndef __cProperty__   
#define __cProperty__   

#define MAX_HOUSES		500
#define MAX_PROPERTY	MAX_HOUSES + 100
#define MAX_DIS_OBJ		96
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
	char	style;
	char	status;
	char	type;			//Тип имущества
	char	player[16];		//Имя владельца
};
struct sProperty extern Property[ MAX_PROPERTY ];
extern int countProperty;

struct Houses
{
	int db;
	int style;
};
struct Houses extern Houses[MAX_HOUSES];
extern int countHouses;

struct eHouseDesine
{
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	int model;
	int obj;
	int db;
};
struct eHouseDesine extern HouseDesine[ MAX_HOUSES ][ MAX_DIS_OBJ ];

class cProperty
{
public:
	static void cProperty::loadHouses();
	static void cProperty::loadHouseInteriors();
	static void cProperty::createHouseInterior(int);
	//-------------------------------------------
	static void cProperty::enterProperty(const int);
	static void cProperty::buyMessage(const int, const int);
	static void cProperty::statusMessage(const int, const int);
	//-------------------------------------------
};


namespace Properties
{
	namespace Houses
	{
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

		namespace Desine
		{

		}
	}
}


#endif 