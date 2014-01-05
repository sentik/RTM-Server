#pragma once

#ifndef _cDRawTut_
#define _cDrawTut_

struct eTutCounts
{
	int			header;
	int			body;
	int			close;
	int			text;
};

struct eTutDraws
{
	int			player;
	int			countPlayers;
	eTutCounts	draws;
	int			closetime;
	bool		global;
	char		head[64];
	char		text[256];
};

namespace extrimeDraws
{
	namespace tutorial
	{
		class func
		{
			public:
			static std::vector<eTutDraws> tutDraws;
			static void showText(const int playerid, const char * header, const char * text, const bool autoclose, const int closetime);
			static void showTextForAll(const char * head, const char * text, const bool autoclose, const int closetime);
			//-----------------------------------------------] Global API
			static int create(const char * head, const char * text);
			static bool destroy(const int number);
			static void show(const int number, const bool autoclose, const int closetime);
			static void hide(const int number);
		};
	}
}


#endif

