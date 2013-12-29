#pragma once
#define MAX_VEHICLES 2000

struct eVehicle
{
	int db;				//Ид в базе
	int Owner;			//Владелец
	int Model;			//Модель
	int	posI;			//Интерьер
	int	posW;			//Вирт. Мир
	int vUnix;			//Время использования
	int text3D;			//3dtext
	float posX;			//Позиция. X
	float posY;			//Позиция. Y
	float posZ;			//Позиция. Z
	float posR;			//Позиция. R
	float Heal;			//Здоровье авто
	float Fuel;			//Бензин
	float Dist;			//Пробег
	char color1;		//Цвет 1
	char color2;		//Цвет 2
	char paint;			//Цвет. Окраска
	char radio;			//Current radio station
	char vNumber[ 32 ]; //Номер
	bool Engine;		//Статус двигателя 
	bool Locked;		//Статус дверей
	bool Light;			//Статус свтеа
	bool Boot;			//Статус багажника
	bool Bonnet;		//Статус капота
};

std::mutex extern mutexSpidak;

namespace world
{
	std::mutex extern createVehicleMutex;
	class Vehicles
	{
		public:
		static struct eVehicle Vehicles::Vehicle[ MAX_VEHICLES ];
		static void Vehicles::loadVehicles();
		static void Vehicles::menuVehicle(int);
		static void Vehicles::showSpeed(int);
		static void Vehicles::hideSpeed(int);
		static void Vehicles::updateSpeed(int);
		static void Vehicles::loadPlayerVehs(int);
		//-------------------------------------------
		static void Vehicles::setOwner(int, int);
		static void Vehicles::locked(int, bool);
		static bool Vehicles::locked(int);
		//-------------------------------------------
		static bool Vehicles::isVehicleInCube(const int, float, float, float, float, float, float);
		//-------------------------------------------
		static int Vehicles::sCreateVehicle(const int, const float, const float, const float, const float, const int, const int, const int);
		static bool Vehicles::sDestroyVehicle(const int);


		enum VehcileRows
		{
			db,
			owner,
			model,
			posx,
			posy,
			posz,
			posr,
			posw,
			posi,
			col1,
			col2,
			col3,
			health,
			fuel,
			dist,
			number,
			engine,
			doors,
			light,
			boot,
			bonnet
		};
	};
}




//std::vector<eVehicle> extern Vehicle;
