#pragma once

#ifndef __cClass__   
#define __cClass__   

#define MAX_CLASES	300
class cClass
{
public:
	static void loadPlayerClass();
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

#endif 