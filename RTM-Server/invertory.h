#pragma once


struct eInvertory
{
	int db;
	int model;
	int amount;
	int obj;
};

namespace world
{
	namespace Players
	{
		class invertory
		{
			public:
			static std::vector<eInvertory> inv[1000];
			static std::vector<eInvertory> loot[ 1000 ];
			static void load(const int);
			static void show(const int);
			static void hide(const int);
			static void onGUI(const int, const int);

		};
	}
}



