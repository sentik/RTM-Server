#pragma once
#ifndef __cPlayer__
#define __cPlayer__

#define MAX_PLAYERS		1000
#define MAX_CHARS		5


namespace cPlayer
{
	int	checkLogin(const char*);
	bool checkPass(int, const char*);
	bool loadChars(int);
	void unloadChars(int);
	void setRegClassSkin(int, char);
	void setClassSkin(int);
	void showCharMaker(int);
	void preSelectClass(int, int);
	int  regPlayer(const char*, const char*);
	int	regChar(const int);
	void hideRegDraws(const int);
	void destRegDraws(const int);
	void loadPlayerChar(int, int);
	void SpawnChar(const int);
	void setCharAngle(const int, float);
	void setCharInterior(const int, const int);
	void setCharWorld(const int, const int);
	void setCharPos(const int, float, float, float, bool);
	void camSelectChar(int);
	bool isRangeOfPoint(int, float, float, float, float);
	bool checkMoney(const int, float);
	void update();
	void getPlayerPos(const int);
	void givePlayerMoney(const int, float);
	void updatePos(const int);
	bool isPlayerInCube(const int, float, float, float, float, float, float);
	void updateMoney(const int);
	void giveExp(const int, const int);
	void PreloadAnimLib(const int);
	void getName(const int, char[]);
	void Train(const int);
	void setCharHealth(const int, const float);
	void setCharArmour(const int, const float);
	void updateHealthBar(const int);
	void onPlayerGiveDamage(const int, const int, const float, const unsigned char);
	void onPlayerTakeDamage(const int, const int, const float, const unsigned char);
}

/*
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
	static void cPlayer::loadPlayerChar(int, int);
	static void cPlayer::SpawnChar(const int);
	static void cPlayer::setCharAngle(const int, float);
	static void cPlayer::setCharInterior(const int, const int);
	static void cPlayer::setCharWorld(const int, const int);
	static void cPlayer::setCharPos(const int, float, float, float, bool);
	static void cPlayer::camSelectChar(int);
	static bool cPlayer::isRangeOfPoint(int, float, float, float, float);
	static bool cPlayer::checkMoney(const int, float);
	static void cPlayer::update();
	static void cPlayer::getPlayerPos(const int);
	static void cPlayer::givePlayerMoney(const int, float);
	static void cPlayer::updatePos(const int);
	static bool cPlayer::isPlayerInCube(const int, float, float, float, float, float, float);
	static void cPlayer::updateMoney(const int);

};*/

int extern drawPlayerChar[15];

struct sAC
{
	float	Health;
	float	Armour;
};

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
	unsigned char	isAction;			//��������	������
	int	pCarid;				//��		����������
	unsigned char	pSeatid;			//��		����� � ����������
	unsigned char	pState;				//���������	������
	int		inType;
	int		inIndex;
	//����� ������ ���� ����, ��.
	int		spdSpeed;			//TextDraw
	int		spdState;			//TextDraw
	int		spdTitle;			//TextDraw
	int		spdFuel;			//TextDraw
	int		spdMilage;			//TextDraw
	int		minerDraw[20];		//TextDraws miner
	unsigned char	role;				//���� ������
	//--------------------------------------
	unsigned char	memType;			//��� �����/ �����/ 
	int		memIndex;			//�� �����/ �����/
	//Miner
	int		aMinerA;
	int		aMinerB;
	//Skills, ����������...
	int		jSkills[3];
	//Money draw
	int		tCents;
	// 3dtext hpbar & name
	int		pBar;
	//Jobs
	unsigned char	pJob1;
	unsigned char	pJob2;
	float	minerZP;
	//for mini-game
	bool	isKeyGame;
	unsigned char	kgUD;
	unsigned char	kgLR;
	sAC		AC;
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
	plPosP,
	plJob1,
	plJob2,
};

enum PlayerAction
{
	ACTION_NONE,
	ACTION_AUTH_PLAYER,
	ACTION_FREZSETPOS,
	ACTION_USERENT,
	ACTION_MINERGAME,
	ACTION_BANKBILL,
	ACTION_AUTOSHOP,
	ACTION_PREFELGAME,
	ACTION_FELGAME,
	ACTION_FELJOB,
	ACTION_FARMER,
	ACTION_USEPROP_GAS,
	ACTION_GANG_MAKE,
	ACTION_USEFELLERDLG,
	ACTION_USEFELLERDLG_ONJOB,
	ACTION_Death,
	ACTION_USEJOBSDLG,
	ACTION_USEMINERDLG,
};

enum PlayerSkills
{
	SKILL_MINER,
	SKILL_FELLER,
};
#endif 