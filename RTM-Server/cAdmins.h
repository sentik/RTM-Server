#pragma once

struct eAdmins
{
	int db;
	int player;
	unsigned char asses;
};


namespace world
{
	namespace Players
	{
		class Admins
		{
			public:
				static std::vector<eAdmins> Admin;
				static char Ranks[ 5 ][ 16 ];
				static void init();
				static void del(int);
				static void add(int, int);
				static bool isAllow(int, int);
				static bool isAsses(int, int);
				static bool isAdmin(int);
		};
	}
}

