#pragma once
#ifndef __cPlayer__
#define __cPlayer__

//#define MAX_PLAYERS		1000
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
	void getName(const int, char []);
	void Train(const int);
	void setCharHealth(const int, const float);
	void setCharArmour(const int, const float);
	void updateHealthBar(const int);
	void onPlayerGiveDamage(const int, const int, const float, const int);
	void onPlayerTakeDamage(const int, const int, const float, const int);
	int getDeathType(int);
}

/*
//Класс игрока
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

int extern drawPlayerChar[20];

struct pInfoGeneral
{
	int		db;
	int		exp;
	double	money;
	int		clas;
};

struct pInfoPosition
{
	float	x;
	float	y;
	float	z;
	float	r;
	int		interior;
	int		world;
};

struct pInfoNames
{
	char	uName[16];
	char	sName[16];
	char	login[16];
	char	pass[16];
	char	date[10];
};

struct pInfoStats
{
	unsigned char	action;
	unsigned char	seatid;
	unsigned char	state;
	int				vehicle;
	int				inType;
	int				inIndex;
	float			Health;
	float			Armour;
};

struct pInfoDraws
{
	unsigned char	money;
	unsigned char	tempDraws[24];
	unsigned char	spdSpeed;			
	unsigned char	spdState;			
	unsigned char	spdTitle;			
	unsigned char	spdFuel;			
	unsigned char	spdMilage;			
};

struct pInfoEtc
{
	int		belay;
	//--------------------------------------
	unsigned char	memType;			//Тип банды/ мафии/ 
	int		memIndex;			//Ид банды/ мафии/
	//Miner
	int		aMinerA;
	int		aMinerB;
	//Skills, разфасуешь...
	int		jSkills[3];
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
	int		pDraw;
	int reason;
};

struct  pInfo
{
	pInfoGeneral		base;
	pInfoPosition		pos;
	pInfoNames			strings;
	pInfoStats			status;
	pInfoDraws			draws;
	bool				isLogged;
	//	НЕ РАСОРТИРОВАНО
	pInfoEtc			xuita;
};
//TODO: Структура игрока
struct pInfo extern Player[MAX_PLAYERS];
//----------------------------------------------------------------
struct pChar
{
	int		pDB;				//Ид		персонажа
	int		cUserus;			//Ф.И		игрока (TextDraw)
	int		cMoney;				//Наличка	игрока (TextDraw)
	int		pClass;
	double	pMoney;				//Наличные	персонажа
	char	uName[12];			//Имя		игрока
	char	sName[12];			//Фамилия	игрока
	//------------------------------------------------
};
//TODO: Структура персонажей игрока
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

//База player_Character
enum PlayerRows
{
	plDB,			//Ид			персонажа
	plOwner,		//Ид			аккаунта
	pluName,		//Имя			персонажа
	plsName,		//Фамилия		персонажа
	plMoney,		//Наличные		персонажа
	plEXP,			//Опыт			персонажа
	plClass,		//Класс			персонажа
	plPosX,			//Позиция. X	персонажа
	plPosY, 		//Позиция. Y	персонажа
	plPosZ, 		//Позиция. Z	персонажа
	plPosR,			//Позиция. R	персонажа
	plPosI,			//Позиция. I	персонажа
	plPosW,			//Позиция. W	персонажа
	plPosP,
	plJob1,
	plJob2,
	plHealth,
	plArmour,
};

enum PlayerAction
{
	ACTION_NONE,
	ACTION_AUTH_PLAYER,
	ACTION_FREZSETPOS,
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
	ACTION_Belay,
};

enum DeathTypes
{
	reason_NONE,		// Нету
	reason_Fight,		// Переломы
	reason_Fire,		// Огестрел
	reason_Stab,		// Ножевые
	reason_Drive,		// Drive By
};


enum PlayerSkills
{
	SKILL_MINER,
	SKILL_FELLER,
};

std::mutex extern mutexUpdate;

#endif 