#pragma once
#define MAX_VEHICLES 2000

struct eVehicle
{
	int db;				//�� � ����
	int Owner;			//��������
	int Model;			//������
	int	posI;			//��������
	int	posW;			//����. ���
	int vUnix;			//����� �������������
	int text3D;			//3dtext
	float posX;			//�������. X
	float posY;			//�������. Y
	float posZ;			//�������. Z
	float posR;			//�������. R
	float Heal;			//�������� ����
	float Fuel;			//������
	float Dist;			//������
	char color1;		//���� 1
	char color2;		//���� 2
	char paint;			//����. �������
	char radio;			//Current radio station
	char vNumber[ 32 ]; //�����
	bool Engine;		//������ ��������� 
	bool Locked;		//������ ������
	bool Light;			//������ �����
	bool Boot;			//������ ���������
	bool Bonnet;		//������ ������
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
