#pragma once

#ifndef ___cPickups___
#define ___cPickups___

struct ePickups
{
	int db;				//�� � ���� ������
	//====================================
	int eModel;			//����. ������
	char eText[ 32 ];	//����.	�����
	float eX;			//����. PosX
	float eY;			//����. PosY
	float eZ;			//����. PosZ
	int	eI;				//����. ��������
	int	eW;				//����.	����. ���
	//====================================
	int qModel;			//�����. ������
	char qText[ 32 ];	//�����. �����
	float qX;			//�����. PosX
	float qY;			//�����. PosY
	float qZ;			//�����. PosZ
	int	qI;				//�����. ��������
	int	qW;				//�����. ����. ���
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