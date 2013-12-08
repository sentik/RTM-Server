#pragma once

#ifndef ___cRadio___
#define ___cRadio___

struct eRadio
{
	int		db;
	char	name[32];
	char	url[64];
};

namespace world
{
	namespace radio
	{
		class cRadio
		{
			public:
				static std::vector<eRadio> Radio;
				static void loadRadio();
				static void showRadioList(const int);
		};
	}
}


#endif