/*******************************************************
=============== �����: ��������� �������� ==============
********************************************************/
#ifndef __BELAY__   
#define __BELAY__   

const int MAX_Belays = 64;



struct sBelay
{
	int db;
	int price;
	//----------------------------------------
	int start;			//����� ������. ������
	int end;			//����� ������. �����
	//----------------------------------------
	unsigned char perDrive;					// ���
	unsigned char perFight;					// ��������
	unsigned char perFire;					// ���������
	unsigned char perStab;					// �������
	unsigned char perSick;					// �������
	unsigned char perEtc;					// ������
	//----------------------------------------
	char name[32 ];
	double fond;
};


namespace Properties
{
	namespace Belays
	{
		int extern count;
		struct sBelay extern Belay[ MAX_Belays ];
		//------------------------------------------------
		void load();
		void makePick();
		void onAction(const int);
		void onDLG(int, int, int, int, const char*);
		void regPlayer(int, int);
		bool checkPlayer(int);

		enum rowBelays
		{
			id,
			owner,
			property,
			type,
			x,
			y,
			z,
			price,
			bank,
			region,
			number,
			db,
			name,
			style,
			balance,
			bprice,
			tstart,
			tend,
			perDrive,
			perSick,
			perFight,
			perFire,
			perStab,
			perEtc,
			pname,
		};

	}
}




#endif 
