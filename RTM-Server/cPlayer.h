#pragma once
#ifndef __cPlayer__
#define __cPlayer__

#define MAX_PLAYERS		1000
#define MAX_CHARS		5


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

};

int extern drawPlayerChar[15];

struct  pInfo
{
	int		pDB;				//Ид		игрока
	int		pExp;				//Прогресс	игрока
	char	uName[16];			//Имя		игрока
	char	sName[16];			//Фамилия	игрока
	char	uLogin[16];			//Логин		игрока
	char	uPassw[16];			//Пароль	игрока
	char	pDate[10];			//Дата		игрока
	double	pMoney;				//Наличные	игрока
	int		pClass;				//Класс		игрока
	float	pPosX;				//Позиция	игрока X
	float	pPosY;				//Позиция	игрока Y
	float	pPosZ;				//Позиция	игрока Z
	float	pPosR;				//Позиция	игрока A
	int		pPosW;				//Позиция	игрока World
	int		pPosI;				//Позиция	игрока Interior
	bool	isLogged;			//Авторизов игрок?
	char	isAction;			//Действие	игрока
	char	pCarid;				//Ид		транспорта
	char	pSeatid;			//Ид		места в транспорте
	char	pState;				//Состаяние	игрока
	int		inType;
	int		inIndex;
	//Потом пихани куда надо, ок.
	int		spdSpeed;			//TextDraw
	int		spdState;			//TextDraw
	int		spdTitle;			//TextDraw
	int		spdFuel;			//TextDraw
	int		spdMilage;			//TextDraw
	int		minerDraw[20];		//TextDraws miner
	char	role;				//Роль игрока
	//--------------------------------------
	char	memType;			//Тип банды/ мафии/ 
	int		memIndex;			//Ид банды/ мафии/
	//Miner
	int		aMinerA;
	int		aMinerB;
	//Skills, разфасуешь...
	int		jSkills[3];
	//Money draw
	int		tCents;
	
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
	ACTION_USEPROP_GAS,
};

enum PlayerSkills
{
	SKILL_MINER,
	SKILL_FELLER,
};
#endif 