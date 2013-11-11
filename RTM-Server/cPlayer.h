#pragma once
#ifndef __cPlayer__
#define __cPlayer__

#define MAX_PLAYERS		1000
#define MAX_CHARS		5

//����� ������
class cPlayer
{
public:
	static int	cPlayer::checkLogin(const char*);
	static bool cPlayer::checkPass(int, const char*);
	static bool cPlayer::loadChars(int);
	static void cPlayer::unloadChars(int);
	static void cPlayer::setRegClassSkin(int, char);
	static void cPlayer::setClassSkin(int);
	static void cPlayer::showCharMaker(int);
	static void cPlayer::preSelectClass(int, int);
	static int  cPlayer::regPlayer(const char*, const char*);
	static int	cPlayer::regChar(const int);
	static void cPlayer::hideRegDraws(const int);
	static void cPlayer::destRegDraws(const int);
	static void cPlayer::loadPlayerChar(int);
	static void cPlayer::SpawnChar(const int);
	static void cPlayer::setCharAngle(const int, float);
	static void cPlayer::setCharInterior(const int, const int);
	static void cPlayer::setCharWorld(const int, const int);
	static void cPlayer::setCharPos(const int, float, float, float, bool);
	static void cPlayer::camSelectChar(int);
	static bool cPlayer::isRangeOfPoint(int i, float r, float x, float y, float z);
};

int extern drawPlayerChar[6];

struct  pInfo
{
	int		pDB;				//��		������
	int		pExp;				//��������	������
	char	uName[16];			//���		������
	char	sName[16];			//�������	������
	char	uLogin[16];			//�����		������
	char	uPassw[16];			//������	������
	char	pDate[10];			//����		������
	double	pMoney;				//��������	������
	int		pClass;				//�����		������
	float	pPosX;				//�������	������ X
	float	pPosY;				//�������	������ Y
	float	pPosZ;				//�������	������ Z
	float	pPosR;				//�������	������ A
	int		pPosW;				//�������	������ World
	int		pPosI;				//�������	������ Interior
	bool	isLogged;			//��������� �����?
	char	isAction;			//��������	������
};
//TODO: ��������� ������
struct pInfo extern Player[MAX_PLAYERS];
//----------------------------------------------------------------
struct pChar
{
	int		pDB;				//��		���������
	int		cUserus;			//�.�		������ (TextDraw)
	int		cMoney;				//�������	������ (TextDraw)
	int		pClass;
	double	pMoney;				//��������	���������
	char	uName[12];			//���		������
	char	sName[12];			//�������	������
	//------------------------------------------------
};
//TODO: ��������� ���������� ������
struct pChar extern PlayerChar[MAX_PLAYERS][MAX_CHARS];
//----------------------------------------------------------------
struct rChar
{
	int rAgility[2];
	int rSpeed[2];
	int rPower[2];
	int rNation;
	int rRace;
	int rSex;
};
struct rChar extern RegChar[MAX_PLAYERS];

//���� player_Character
enum PlayerRows
{
	plDB,			//��			���������
	plOwner,		//��			��������
	pluName,		//���			���������
	plsName,		//�������		���������
	plMoney,		//��������		���������
	plEXP,			//����			���������
	plClass,		//�����			���������
	plPosX,			//�������. X	���������
	plPosY, 		//�������. Y	���������
	plPosZ, 		//�������. Z	���������
	plPosR,			//�������. R	���������
	plPosI,			//�������. I	���������
	plPosW,			//�������. W	���������
};

enum PlayerAction
{
	ACTION_NONE,
	ACTION_AUTH_PLAYER,
	ACTION_FREZSETPOS,
};
#endif 