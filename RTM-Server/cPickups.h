#pragma once

#ifndef ___cPickups___
#define ___cPickups___

struct ePickups
{
	int db;				//Ид в Базе Данных
	//====================================
	int eModel;			//Вход. Модель
	char eText[ 32 ];	//Вход.	Текст
	float eX;			//Вход. PosX
	float eY;			//Вход. PosY
	float eZ;			//Вход. PosZ
	int	eI;				//Вход. Интерьер
	int	eW;				//Вход.	Вирт. Мир
	//====================================
	int qModel;			//Выход. Модель
	char qText[ 32 ];	//Выход. Текст
	float qX;			//Выход. PosX
	float qY;			//Выход. PosY
	float qZ;			//Выход. PosZ
	int	qI;				//Выход. Интерьер
	int	qW;				//Выход. Вирт. Мир
};

namespace world
{
	namespace pickups
	{
		class cPickups
		{
			public:
				static std::vector<ePickups> Pickups;
				static void loadPickups();
				static void actionPickups(const int);
		};

		enum rowsPick
		{
			id,
			model_1,
			model_2,
			text_1,
			text_2,
			x,
			y,
			z,
			ex,
			ey,
			ez,
			int_1,
			int_2,
			world_1,
			world_2,
		};
	}
}
#endif

/*
id
model_1
model_2
text_1
text_2
x
y
z
ex
ey
ez
int_1
int_2
world_1
world
*/