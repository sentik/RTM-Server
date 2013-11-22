#pragma once
#ifndef __MAIN__   
#define __MAIN__   
#pragma warning(disable: 4244)
#define _CRT_SECURE_NO_WARNINGS

#define GAME_VERSION "0.78A"
#define DEFAULT_SPAWN 100.0f, 200.0f, 10.0f
#define SELECT_COLORUS 0xDCDCDC88
#define RANDOM_SEED	8 * getUnixTime() + 6 * clock()  - 123

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <thread>
#include <process.h>
#include <stdio.h>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
//--------------------------------------------
#include <sampgdk/a_players.h>
#include <sampgdk/a_vehicles.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>
//--------------------------------------------
#include <mysql.h>
#include <tinyxml/tinyxml.h>
//--------------------------------------------
#include<boost/system/error_code.hpp>
#include<boost/system/system_error.hpp>
//#include<boost / system / cygwin_error.hpp>
//#include<boost / system / linux_error.hpp>
#include<boost/system/windows_error.hpp>
//--------------------------------------------
#include "streamerlib.h"
#include "cTexrDraws.h"
#include "cInteriors.h"
#include "cProperty.h"
#include "cDialogs.h"
#include "dropGuns.h"
#include "cObjects.h"
#include "cVehicle.h"
#include "cHouses.h"
#include "configs.h"
#include "cPlayer.h"
#include "saZones.h"
#include "cClass.h"
#include "cState.h"
#include "cMiner.h"
#include "cChat.h"
#include "cGang.h"
#include "cBank.h"
#include "cGas.h"
#include "cmd.h"

#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <type_traits>

//--------------------------------------------
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
extern int uTime;

template <typename T> T clamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

static int getUnixTime();
static void initTextDraws();

static string perkCalculate(int value)
{
	string  str = "llllllllllllll";
	str.insert(value, "~l~");
	str.insert(0, "~p~");
	return str;
}
#endif 
