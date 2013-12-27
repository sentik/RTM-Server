#pragma once
#ifndef __farms__   
#define __farms__   


#define MAX_FARMS 10

struct sPos
{
	float X;
	float Y;
	float Z;
};

struct sFarmItems
{
	int				db;
	int				obj;
	int				model;
	int				amount;
	float			proc;
	sPos			pos;

};

struct sWareHouse
{
	int				db;
	unsigned char	level;
	unsigned char	style;
	int				model;
	sPos			enter;
	sPos			object;
	sPos			rotation;
	int				pick;
	int				info;
	int				obj;
};

struct sFarm
{
	int				db;
	char			name[ 32 ];
	//-------------------------
	float			minX;
	float			minY;
	float			maxX;
	float			maxY;
	//-------------------------
	int				zome;
	int				icon;
	sFarmItems		item[ 64 ];
	sWareHouse		WH[8];
};



namespace Properties
{
	namespace Farms
	{
		int extern count;
		struct sFarm extern Farm[ MAX_FARMS ];

		void load();
		void save();
		void onAction(const int);
		void onPickUp(const int);
		void onGUI(const int, const int);
		void onDLG(int, int, int, int, const char*);
		void makePick();

		enum farmRows
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
			name,
			style,
			sX,
			sY,
			eX,
			eY,
			pname,
		};

	}


}

#endif 


