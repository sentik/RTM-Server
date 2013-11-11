#pragma once
#ifndef __MAIN__   
#define __MAIN__   
#pragma warning(disable: 4244)
#define _CRT_SECURE_NO_WARNINGS

#define GAME_VERSION "0.6A"
#define DEFAULT_SPAWN 100.0f, 200.0f, 10.0f
#define SELECT_COLORUS 0xDCDCDC88
#define RANDOM_SEED	8 * time(0) + 6 * clock()  - 123





#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <thread>
//--------------------------------------------
#include <sampgdk/a_players.h>
#include <sampgdk/a_vehicles.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>
//--------------------------------------------
#include <mysql.h>
//--------------------------------------------
#include<boost/system/error_code.hpp>
#include<boost/system/system_error.hpp>
//#include<boost / system / cygwin_error.hpp>
//#include<boost / system / linux_error.hpp>
#include<boost/system/windows_error.hpp>
//--------------------------------------------
#include "cPlayer.h"
#include "streamerlib.h"
#include "cTexrDraws.h"
#include "cInteriors.h"
#include "cProperty.h"
#include "cDialogs.h"

#include "configs.h"
#include "cClass.h"
#include "cState.h"



using namespace std;
//--------------------------------------------
typedef void(*logprintf_t)(const char*, ...);
extern logprintf_t logprintf;
//--------------------------------------------

//TODO: –егул€рные выражени€
//======================================
extern regex expLogin;
extern regex expNames;
extern regex expDate;
//======================================
//TODO: MYSQL-соединение
extern MYSQL *con;
//======================================
extern char strSpeed[13];
extern char strMuscular[13];
extern char strAgility[13];
//======================================
extern char RaceList[3][16];
extern char Natioins[5][18]; 
extern char SexArray[2][16];
//----------------------------------------------------------------
extern char query[512];

template <typename T> T clamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

static string perkCalculate(int value)
{
	string  str = "llllllllllllll";
	str.insert(value, "~l~");
	str.insert(0, "~p~");
	return str;
}
#endif 
