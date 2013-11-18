#include "main.h"

std::unordered_map<int, eDropGun> world::DropedGuns::DropedGun;

void world::DropedGuns::loadGuns()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM world_DropedGuns");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		eDropGun temp;
		temp.db = atoi(row[ DropedGuns::dgRows::db ]);
		temp.weapon = atoi(row[ DropedGuns::dgRows::model ]);
		temp.ammo = atoi(row[ DropedGuns::dgRows::ammo ]);
		//==================================================================
		temp.posX = atof(row[ DropedGuns::dgRows::posx ]);
		temp.posY = atof(row[ DropedGuns::dgRows::posy ]);
		temp.posZ = atof(row[ DropedGuns::dgRows::posz ]);
		//==================================================================
		temp.obj = StreamerCall::Native::CreateDynamicObject(temp.weapon,
															 temp.posX,
															 temp.posY,
															 temp.posZ,
															 90, 0, 90, 0, 0);
		//==================================================================
		world::DropedGuns::DropedGun.insert(make_pair(i, temp));
		i++;
	}
	logprintf("Было загруженно %d оружий", i);
}












//struct eDropGun world::DropedGuns::DropedGun[ MAX_DROPED_WEAPONS ];

/*
void world::DropedGuns::loadGuns()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM ");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		DropedGun[ i ].db		= atoi(row[ DropedGuns::dgRows::db ]);
		DropedGun[ i ].weapon   = atoi(row[ DropedGuns::dgRows::model ]);
		DropedGun[ i ].ammo		= atoi(row[ DropedGuns::dgRows::ammo ]);
		//==================================================================
		DropedGun[ i ].posX = atof(row[ DropedGuns::dgRows::posx ]);
		DropedGun[ i ].posY = atof(row[ DropedGuns::dgRows::posy ]);
		DropedGun[ i ].posZ = atof(row[ DropedGuns::dgRows::posz ]);
		//==================================================================
		DropedGun[ i ].obj = StreamerCall::Native::CreateDynamicObject()
	}
}
*/