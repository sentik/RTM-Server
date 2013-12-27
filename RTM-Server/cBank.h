#pragma once

#ifndef __cBanks__   
#define __cBanks__   

#include "configs.h"
struct eBanks
{
	int db;				//Ид банка
	int world;			//Вирт. мир
	//----------------------------------------
	int start;			//Время работы. Начало
	int end;			//Время работы. Конец
	//----------------------------------------
	float credit;		//Процент кредита
	float deposit;		//Процент вклада
	float send;			//Процент перевода
	float pay;			//Процент оплаты
	//----------------------------------------
	double fond;
	//----------------------------------------
	char title[ 32 ];
};

struct eBanks extern Bank[ MAX_BANKS ];
extern int countBanks;


struct eATM
{
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	double balance;
	float percent;
	int db;				//Ид банкомата
	int owner;
	int obj;			//Ид объекта
	int info;
	int pick;
};

struct eATM extern bankATM[ MAX_BANKS ][256];
extern int countATM;




namespace Properties
{
	namespace Bank
	{
		namespace atm
		{
			enum atmRows
			{
				id,
				owner,
				posx,
				posy,
				posz,
				rotx,
				roty,
				rotz,
				balance,
				percent,
				name,
			};
		}

		enum BankRows
		{
			id,
			owner,
			property,
			type,
			posx,
			posy,
			posz,
			price,
			bank,
			region,
			number,
			db,
			credit,
			deposit,
			pay,
			send,
			title,
			start,
			end,
			style,
			fond,
			oName,
		};
	}

}

class cBanks
{
	public:
		static void cBanks::loadBanks();
		static void cBanks::saveBanks();
		static void cBanks::loadATM();

		static void cBanks::create(int, float, float, float);
		static void cBanks::makePick();

		static void cBanks::getBalance(int, double *);
		static void cBanks::setBalance(int, double);
		static void cBanks::giveBalance(int, double);
		static bool cBanks::atBank(int, double);
		static void cBanks::actStuff(int);
		static void cBanks::actBill(int);
		static void cBanks::accMenu(int);
		static int cBanks::createAcc(int, int, int);
		static void cBanks::onDLG(int, int, int, int, const char*);
		static void cBanks::updateText(const int, const int);
		static bool cBanks::isValidNumber(const int);

};




#endif