#pragma once


/*
�����, ������� �����, ������ ���������.
��� �� ��� ����� ��� ���������, ����� ���������� ...
*/



/*
����� ������� �� 30.11.2013:
1. ������� ��������� �������� �� ������ (���� �� �������)   !!!
2. ������� ��������� (�������� ���� �� �������)				!!!
3. �������� 24x7 ( ����� ���� ��� ������� ������)			???
4. ������������ ( ���������� � ����������� �������)			!!!
5. ������� ������ ��� ����									!!!
6. ������� ������ ��� ����									!!!
7. ������� �������� ���� �� ��������.						!!!
8. ������� ��������������� � �����������					???
==============================
*������� ������������:
1. ���������� ������������									!!!
2. ������� ������� ��������									?!?
3. ��������� ������� ������� �� C++							?!?
4. ������� ���������� ���������� (���������� ���)			???
*/


#ifndef __MAIN__   
#define __MAIN__   

//======================================================
#define DEFAULT_RUSSIAN 1		//�� ��������� �������
//#define DEFAULT_ENGLISH 1		//�� ��������� ���������
//#define DEFAULT_GERMAN 1		//�� ��������� ��������
//======================================================

#pragma warning(disable: 4244)
#define _CRT_SECURE_NO_WARNINGS
#define GAME_VERSION "0.80A"
#define DEFAULT_SPAWN 100.0f, 200.0f, 10.0f
#define SELECT_COLORUS 0xDCDCDC88
#define RANDOM_SEED	8 * getUnixTime() + 6 * clock()  - 123
//#define BOOST_THREAD_DONT_USE_CHRONO 1 
#define tocolor(r, g, b, a) ( ( r & 0xff ) << 24 ) + ( ( g & 0xff ) << 16 ) + ( ( b & 0xff ) << 8 ) + ( a & 0xff )

#include "Mutex.h"



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
#include <mutex>
//--------------------------------------------
#include <sampgdk/a_samp.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_vehicles.h>
#include <sampgdk/a_objects.h>
#include <sampgdk/core.h>
#include <sampgdk/plugin.h>
//--------------------------------------------
#include <mysql.h>
#include <tinyxml/tinyxml.h>
//--------------------------------------------
#include "streamerlib.h"
#include "cTexrDraws.h"
#include "cInteriors.h"
#include "invertory.h"
#include "cProperty.h"
#include "cDialogs.h"
#include "dropGuns.h"
#include "cObjects.h"
#include "cPickups.h"
#include "cFarmer.h"
#include "cFactoryMetal.h"
#include "cVehicle.h"
#include "cHouses.h"
#include "configs.h"
#include "cPlayer.h"
#include "cAdmins.h"
#include "cRadio.h"
//-------------------------] Intro
#include "cIntro.h"
#include "cBelay.h"
#include "moveDraw.h"

#include "saZones.h"
#include "cFeller.h"
#include "cClass.h"
#include "cState.h"
#include "cMiner.h"
#include "cChat.h"
#include "cJobs.h"
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


#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
//#include<boost / system / cygwin_error.hpp>
//#include<boost / system / linux_error.hpp>
#include <boost/system/windows_error.hpp>
//---------------------
#ifdef DEFAULT_RUSSIAN
#include "Russian.h"
#endif
//---------------------
#ifdef DEFAULT_ENGLISH
#include "English.h"
#endif
//---------------------
#ifdef DEFAULT_GERMAN
#include "German.h"
#endif
//---------------------
std::mutex extern mutexStreamGlobal;		// STREAMER MUTEX
std::mutex extern mutexStreamPlayer;		// STREAMER MUTEX
std::mutex extern mutexMYSQL;		// STREAMER MUTEX


std::mutex extern mutexTTD;		// STREAMER MUTEX



int safe_query(MYSQL *conn, char query[ ]);
//--------------------------------------------
using namespace std;
//--------------------------------------------
typedef void(*logprintf_t)(const char*, ...);
extern logprintf_t logprintf;
//--------------------------------------------

//TODO: ���������� ���������
//======================================
extern regex expLogin;
extern regex expNames;
extern regex expDate;
extern regex expCode;

extern regex expString;
extern regex expFloat;
extern regex expNumber;
//======================================
//TODO: MYSQL-����������
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


