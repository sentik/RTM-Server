#pragma once

#ifndef __cClass__   
#define __cClass__   

#define MAX_CLASES	300
#define VEH_CLASES	212

class cClass
{
public:
	static void loadPlayerClass();
	static void loadVehicleClass();
	static void fixText(char * text, int size);

};

struct pClass
{
	int		cSkin;				//Скин			игрока
	int		cRace;				//Раса			игрока
	int		cNation;			//Нация			игрока
	int		cPower;				//Сила			игрока
	int		cSpeed;				//Выносливость	игрока
	int		cAgility;			//Ловкость		игрока
	bool	cSex;				//Пол			игрока
};
//TODO: Классы игроков
struct pClass extern PlayerClass[MAX_CLASES];


struct vClass
{
	char Name[ 32 ];
	char Group;
	char Gear;
	int  Speed;
	int  Power;
};
struct vClass extern VehicleClass[ VEH_CLASES ];

namespace ServerClass
{
	//------------------------------
	namespace Player
	{
		enum playerClassRows
		{
			skin,				//Скин				игрока
			race,				//Раса				игрока
			nation,				//Национальность	игрока
			sex,				//Пол				игрока
			power,				//Сила				игрока
			speed,				//Выносливость		игрока
			agility,			//Ловкость			игрока
		};
	}
	//------------------------------
	namespace Vehicle
	{
		enum vehiclesClassRows
		{
			id,					//Ид в базе
			name,				//Название
			model,				//Модель
			category,			//Категория
			gear,				//Привод
			speed,				//Скорость
			power				//Мощность
		};
	}
	//------------------------------
}


#endif 