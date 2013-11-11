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
	int		cSkin;				//����			������
	int		cRace;				//����			������
	int		cNation;			//�����			������
	int		cPower;				//����			������
	int		cSpeed;				//������������	������
	int		cAgility;			//��������		������
	bool	cSex;				//���			������
};
//TODO: ������ �������
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
			skin,				//����				������
			race,				//����				������
			nation,				//��������������	������
			sex,				//���				������
			power,				//����				������
			speed,				//������������		������
			agility,			//��������			������
		};
	}
	//------------------------------
	namespace Vehicle
	{
		enum vehiclesClassRows
		{
			id,					//�� � ����
			name,				//��������
			model,				//������
			category,			//���������
			gear,				//������
			speed,				//��������
			power				//��������
		};
	}
	//------------------------------
}


#endif 