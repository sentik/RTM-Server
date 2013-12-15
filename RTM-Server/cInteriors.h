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
	int db;				// �� � ���� ������
	int text;			//����� �����
	int pick;			//����� ������
	int actT;			//����� �������� 1
	int actP;			//����� �������� 1
	int subT;			//����� �������� 2
	int subP;			//����� �������� 2
	//------------
	float posX;			//��������� ������ X
	float posY;			//��������� ������ Y
	float posZ;			//��������� ������ Z
	float posR;			//���� �������	   R
	//------------
	float actX;			//��������� ��� �������� [1] X
	float actY;			//��������� ��� �������� [1] Y
	float actZ;			//��������� ��� �������� [1] Z
	//------------
	float subX;			//��������� ��� �������� [2] X
	float subY;			//��������� ��� �������� [2] Y
	float subZ;			//��������� ��� �������� [2] Z
	//------------
	char posI;			//��	���������
	char Type;			//���	���������

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