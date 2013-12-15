#pragma once
#pragma once

#ifndef ___cFeller___
#define ___cFeller___

struct eTrees
{
	int		db;
	int		obj;
	int		type;
	float	proc;
	float	x;
	float	y;
	float	z;
};

struct eFeller
{
	int		db;
	int		obj;
	float	zp;
	float	am;
	float	minX;
	float	minY;
	float	minZ;
	float	maxX;
	float	maxY;
	float	maxZ;
	float	fond;
	float	itX;
	float	itY;
	float	itZ;
	float	itRX;
	float	itRY;
	float	itRZ;
	char	name[20];
	eTrees	Trees[ MAX_FELL_TREE ];
};



namespace fProperty
{
	class cFeller
	{
		public:
			static void loadFeller();
			static void loadTrees();
			static void ownerMenu(const int);
			static void clientMenu(const int);
			static void giveFellerTool(const int);
			static void removeFellerTool(const int);
			static bool getFellerTool(const int);
			static void startPreFellerGame(const int);
			static void startFellerGame(const int);
			static void onGUI(const int, const int);
			static void onDLG(int, int, int, int, const char*);
			static void actionTrees(const int);
			static void updateText(const int, const int);
			static void updateInfotable(const int);
			static int models[ 8 ];
			static struct eFeller cFeller::Feller[MAX_FELL];
	};

	enum rowsFeller
	{
		id,
		owner,
		property,
		type,
		x,
		y,
		z,
		price,
		bank,
		region,
		number,
		db,
		zp,
		am,
		minX,
		minY,
		minZ,
		maxX,
		maxY,
		maxZ,
		name,
		fond,
		itX,
		itY,
		itZ,
		itRX,
		itRY,
		itRZ,
		pname,
	};
}


#endif
