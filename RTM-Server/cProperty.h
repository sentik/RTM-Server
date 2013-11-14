#pragma once

#ifndef __cProperty__   
#define __cProperty__   
#include "configs.h"

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
	int		pick;
	int		text;
};
struct sProperty extern Property[ MAX_PROPERTY ];
extern int countProperty;

struct Banks
{
	int db;				//Ид банка
	int world;			//Вирт. мир
	//----------------------------------------
	int start;			//Время работы. Начало
	int end;			//Время работы. Конец
	//----------------------------------------
	float credit;		//Процент кредита
	float deposit;		//Процент вклада
	float send;			//Процент перевода
	float pay;			//Процент оплаты
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