#pragma once

#ifndef __cInteriors__   
#define __cInteriors__   

#define MAX_INTERIORS		100


class cInteriors
{
	public:
	static void cInteriors::loadInterioList();
	static int cInteriors::getRandom(int);
};


struct  iInterior
{
	int db;				// Ид в базе данных
	int text;			//Текст выхда
	int pick;			//Пикап выхода
	int actT;			//Текст действия 1
	int actP;			//Пикап действия 1
	int subT;			//Текст действия 2
	int subP;			//Пикап действия 2
	//------------
	float posX;			//Кординаты выхода X
	float posY;			//Кординаты выхода Y
	float posZ;			//Кординаты выхода Z
	float posR;			//Угол поворта	   R
	//------------
	float actX;			//Кординаты для действия [1] X
	float actY;			//Кординаты для действия [1] Y
	float actZ;			//Кординаты для действия [1] Z
	//------------
	float subX;			//Кординаты для действия [2] X
	float subY;			//Кординаты для действия [2] Y
	float subZ;			//Кординаты для действия [2] Z
	//------------
	char posI;			//Ид	интерьера
	char Type;			//Тип	интерьера

};
struct iInterior extern Interior[ MAX_INTERIORS ];
int extern countInteriors;

namespace Interiors
{
	void loadInteriorList();
	enum InteriorRows
	{
		id,
		//---------
		posx,
		posy,
		posz,
		posr,
		//---------
		actx,
		acty,
		actz,
		//---------
		subx,
		suby,
		subz,
		//---------
		posi,
		type,
	};
}


#endif 