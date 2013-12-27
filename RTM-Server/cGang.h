#pragma once
#define MAX_GANGS 10000

struct eRanks
{
	int db;
	char name[ 24 ];
	bool useChat;
	bool useVehs;
	bool useWares;
	bool useInvite;
};

struct sGang
{
	int db;
	int owner;
	int color;
	int rep;
	char name[ 32 ];
	int prop;
	eRanks ranks[ 5 ];
};

namespace world
{
	namespace gangs
	{
		int extern count;
		struct sGang extern Gang[ MAX_GANGS ];
		//=====================================
		
		void load();
		void save();
		void save(int);
		void create(int, int);
		void listProp(int, char []);
		int getProp(int, int);
		void onDLG(int, int, int, int, const char*);
	
		void showOwner(int);
		void showPlayer(int);

	}
}

