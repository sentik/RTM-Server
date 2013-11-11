#pragma once

#ifndef __cClass__   
#define __cClass__   

#define MAX_CLASES	300
class cClass
{
public:
	static void loadPlayerClass();
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

#endif 