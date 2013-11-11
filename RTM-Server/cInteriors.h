#pragma once

#ifndef __cInteriors__   
#define __cInteriors__   

#define MAX_INTERIORS		100


class cInteriors
{
	public:
	static void cInteriors::loadInterioList();
};


struct  iInterior
{
	int db;				// �� � ���� ������
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