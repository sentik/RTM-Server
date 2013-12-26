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
	static bool sqlSetInt(const char * table, const char * field, const int value, const int id);
	static bool sqlSetFloat(const char * table, const char * field, const float value, const int id);
	static bool sqlSetString(const char * table, const char * field, const char * value, const int id);
	static void keyGame(const int u);
	static void updateKeyGame(const int u);
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

struct kgText
{
	int				tid;
	unsigned char	key;
	unsigned char	alpha;
	float			x;
	float			y;
};

struct kgText extern kgPlayerText[MAX_PLAYERS][16];

const char kgKeys[10][16] = 
{
	"LD_BEAT:upl",
	"LD_BEAT:upr",
	"LD_BEAT:up",
	"LD_BEAT:left",
	"LD_BEAT:right",
	"LD_BEAT:down",
	"LD_BEAT:downr",
	"LD_BEAT:downl",
	"null",
	"null"
};

enum kgKeys
{
	KG_KEY_UPLEFT,
	KG_KEY_UPRIGHT,
	KG_KEY_UP,
	KG_KEY_LEFT,
	KG_KEY_RIGHT,
	KG_KEY_DOWN,
	KG_KEY_DOWNRIGHT,
	KG_KEY_DOWNLEFT,
	KG_KEY_NULL1,
	KG_KEY_NULL2,
};

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