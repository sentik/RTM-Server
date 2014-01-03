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
	eTutCounts	draws;
	int			closetime;
};

namespace extrimeDraws
{
	namespace tutorial
	{
		class func
		{
			public:
			static std::vector<eTutDraws> tutDraws;
			static void showText(const int playerid, const char * header, const char * text, bool autoclose, const int closetime);
		};
	}
}


#endif

