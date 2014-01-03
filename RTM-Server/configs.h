#pragma once
#ifndef __cConfig__   
#define __cConfig__   


/*----------------- MYSQL Connector -----------------*/

#define		MYSQL_HOST					"127.0.0.1"
#define		MYSQL_BASE					"samp"
#define		MYSQL_USER					"root"
#define 	MYSQL_PASS					""
/*
#define		MYSQL_HOST					"server48.hosting.reg.ru"
#define		MYSQL_BASE					"u7301517_samp"
#define		MYSQL_USER					"u7301517_dev"
#define 	MYSQL_PASS					"dev1488"*/

/*----------------- MYSQL Connector -----------------*/

//DEBUG
//#define DEBUG_GANG 0




#define	MAX_SH			2
#define MAX_GAS			10
#define MAX_FELL		5
#define MAX_BANKS		20
#define MAX_HOUSES		500
#define MAX_DIS_OBJ		96
#define MAX_PROPERTY	550
#define MAX_FELL_TREE	32
#define MAX_FACT_M		10

/*---------------Registration Character--------------*/
#define		CREG_SKIN_POS				1302.7f,-792.3f,96.5f
#define		CREG_CAMR_POS				1300.4f,-791.0f,97.5f
/*---------------Registration Character--------------*/

#define DEFAULT_HEAL_PRICE 75

#define RADIUS_SHOUT	70.0f
#define RADIUS_WHISPER	5.0f
#define RADIUS_ACTIONS	30.0f
#define TIME_SHOUT		10 * 1000
#define TIME_ACTIONS	10 * 1000




#define	BANKOMAT_MODEL				2942

#define ENTER_RADIUS	1.5f
#define EXIT_PICKUP		19132
#define INFO_PICKUP		1239


#define	CLOTH_PICKUP	1275
#define	DOLLAR_PICKUP	1274

#define HOUSE_GREEN		1273	// green house
#define HOUSE_RED		1272	// blue house

#define	TREE_SPEED		0.5f	// Default: 0.005f
#define TREE_OFFSET		24

#define	REG_SPAWN_X		1700.0f
#define	REG_SPAWN_Y		-1954.0f
#define	REG_SPAWN_Z		14.9f
#define REG_SPAWN_INT	0
#define REG_SPAWN_WOR	56

#define INFOTABLE_MODEL 3077

#define ACTION_COLOR	-11490561

#define TEMP_JOB_POS	-397.5255,179.5468,1008.3950

#define MINER_MENU_COLOR	"C4DD0E"

#endif 
