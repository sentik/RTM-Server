#pragma once

#ifndef ___cMiner___
#define ___cMiner___

#include "configs.h"

#define		MINER_SH1_INFOTABLE		19477,-1862.1569f,-1650.453f,21.717f,0.0f,0.0f,180.0f
#define		MINER_SH1_CHECKPOS		-1854.617f,-1609.626f,18.328f
#define		MINER_SH1_RAZDEVALKA	-1874.77f,-1648.012f,20.958f
#define		MINER_SH1_IRON			-1981.823f,-1582.182f,15.228f
#define		MINER_SH1_IRON_RADIUS	20.0f
#define		MINER_SH1_SILVER		-2200.937f,-1551.121f,39.695f
#define		MINER_SH1_SILVER_RADIUS 40.0f

#define		MINER_SH2_INFOTABLE		19477,-396.337f,2206.285f,44.55f,0.0f,0.0f,270.0f
#define		MINER_SH2_CHECKPOS		-383.355f,2203.165f,39.515f
#define		MINER_SH2_RAZDEVALKA	-400.567f,2203.851f,44.076f
#define		MINER_SH2_CUPRUM		-237.061f,2169.673f,-6.420f
#define		MINER_SH2_CUPRUM_RADIUS 15.0f
#define		MINER_SH2_GOLD			-185.341f,1951.413f,-25.287f
#define		MINER_SH2_GOLD_RADIUS	35.0f

struct sMiner
{
	int		db;			//Ид в бд
	float	zp1;		//Зарплата за 1й метал
	float	zp2;		//Зарплата за 2й метал
	int		a1;			//Кол-во 1го метала
	int		a2;			//Кол-во 2го метала
	float	procent;	//Процентая добавка к стоимости на продажу
	int		infoTable;	//Обьект с информацией
};

namespace Jobs
{
	namespace Miner
	{
		class cMiner
		{
			public:
				static void loadMiner();
				static void giveMinerInstrument(const int);
				static void removeMinerInstrument(const int);
				static bool getMinerInstrument(const int);
				static void startMinerGame(const int);
				static void actionPicks(const int);
				static void onGUI(const int, const int);
				static struct sMiner  cMiner::miner[MAX_SH];
		};
		enum minerRows
		{
			db,
			owner,
			property,
			type,
			posX,
			posY,
			posZ,
			price,
			bank,
			region,
			number,
			id,
			zp1,
			zp2,
			a1,
			a2,
			proc,
			oName,
		};
	}
}

#endif