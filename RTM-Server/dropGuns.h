#pragma once

#define MAX_DROPED_WEAPONS 512

struct eDropGun
{
	int id;
	int db;
	int weapon;
	int ammo;
	int obj;
	float posX;
	float posY;
	float posZ;

	/*eDropGun(int eDB, int eAmm, int eWeap, float eX, float eY, float eZ, int eOBJ) : db(eDB),
		weapon(eWeap), ammo(eWeap), posX(eX), posY(eY), posZ(eZ), obj(eOBJ) { }*/

};


namespace world
{
	class DropedGuns
	{
		public:
		static std::unordered_map<int, eDropGun> DropedGun;
		//static struct eDropGun DropedGun[ MAX_DROPED_WEAPONS ];
		static void DropedGuns::loadGuns();


		enum dgRows
		{
			db,
			model,
			ammo,
			posx,
			posy,
			posz
		};
	};

}








