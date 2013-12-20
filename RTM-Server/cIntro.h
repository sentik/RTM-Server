#pragma once

#ifndef ___cIntro___
#define ___cIntro___

namespace cPlayer
{
	namespace Intro
	{
		class cIntro
		{
			public:
				static void initTrain(const int);
				static void updateIntro(const int);
				static void drawIntro(const int);
		};
	}
}

#endif