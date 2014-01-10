#include "main.h"
//----------------------------------------
//std::vector<eVehicle> Vehicle;
struct eVehicle  world::Vehicles::Vehicle[ MAX_VEHICLES ];
std::mutex mutexSpidak;
std::mutex world::createVehicleMutex;
//----------------------------------------


void world::Vehicles::loadVehicles()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	safe_query(con, "");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{

	}
}

void world::Vehicles::loadPlayerVehs(int u)
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	sprintf(query, "SELECT * FROM world_Vehicles WHERE owner = %d", Player[ u ].base.db), safe_query(con, query);
	//------------------------------------------------------------
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		struct eVehicle tmp;
		tmp.db = atoi(row[ VehcileRows::db]);
		tmp.Owner = atoi(row[ VehcileRows::owner ]);
		tmp.Model = atoi(row[ VehcileRows::model ]);
		//============================================
		tmp.color1 = atoi(row[ VehcileRows::col1 ]);
		tmp.color2 = atoi(row[ VehcileRows::col2 ]);
		tmp.paint = atoi(row[ VehcileRows::col3 ]);
		//============================================
		tmp.posX = atof(row[ VehcileRows::posx ]);
		tmp.posY = atof(row[ VehcileRows::posy ]);
		tmp.posZ = atof(row[ VehcileRows::posz ]);
		tmp.posR = atof(row[ VehcileRows::posr ]);
		tmp.posI = atoi(row[ VehcileRows::posi ]);
		tmp.posW = atoi(row[ VehcileRows::posw ]);
		//============================================
		tmp.Heal = atof(row[ VehcileRows::health ]);
		tmp.Fuel = atof(row[ VehcileRows::fuel ]);
		tmp.Dist = atof(row[ VehcileRows::dist ]);
		//============================================
		tmp.Engine = ( atoi(row[ VehcileRows::engine ]) ) ? ( true ) : ( false );
		tmp.Locked = ( atoi(row[ VehcileRows::doors ]) ) ? ( true ) : ( false );
		tmp.Light = ( atoi(row[ VehcileRows::light ]) ) ? ( true ) : ( false );
		tmp.Bonnet = ( atoi(row[ VehcileRows::bonnet ]) ) ? ( true ) : ( false );
		tmp.Boot = ( atoi(row[ VehcileRows::boot ]) ) ? ( true ) : ( false );
		//============================================
		int veh = world::Vehicles::sCreateVehicle(tmp.Model, tmp.posX, tmp.posY, tmp.posZ, tmp.posR, tmp.color1, tmp.color2, 99999);
		//============================================
		strcpy(tmp.vNumber, row[ VehcileRows::number ]);
		SetVehicleNumberPlate(veh, tmp.vNumber);
		ChangeVehiclePaintjob(veh, tmp.paint);
		//------------------------------------------------------------------
		SetVehicleParamsEx(veh, tmp.Engine, tmp.Light, tmp.Locked, tmp.Locked, tmp.Bonnet, tmp.Boot, false);
		//------------------------------------------------------------------
		LinkVehicleToInterior(veh, tmp.posI);
		SetVehicleVirtualWorld(veh, tmp.posW);
		//============================================
		world::Vehicles::Vehicle[ veh ] = tmp;
	}
}

void world::Vehicles::menuVehicle(int u)
{
	const int vehid = Player[u].status.vehicle;
	char text[152];
	sprintf(text, "«%s{FFFFFF}»\t\tДвигатель\n«%s{FFFFFF}»\t\tФары\n«%s{FFFFFF}»\t\tБагажник\n«%s{FFFFFF}»\t\tКапот\n«{00C0FF}%s{FFFFFF}»", Vehicle[vehid].Engine ? ("{00C0FF}ON") : ("{FF0000}OFF"), Vehicle[vehid].Light ? ("{00C0FF}ON") : ("{FF0000}OFF"), Vehicle[vehid].Boot ? ("{00C0FF}ON") : ("{FF0000}OFF"), Vehicle[vehid].Bonnet ? ("{00C0FF}ON") : ("{FF0000}OFF"), 
					world::radio::cRadio::Radio.at(Vehicle[vehid].radio).name);
	ShowPlayerDialog(u, DLG_VEHICLE_CONTROL, GUI_LIST, "{00C0FF}Управление транспортом", text, "OK", "CANCEL");
	#undef vehid
}

void world::Vehicles::showSpeed(int u)
{
	TextDrawShowForPlayer(u, drawPlayerChar[SPD_BG]);

	Player[u].draws.spdTitle = CreatePlayerTextDraw(u, 510.000000, 291.000000, VehicleClass[GetVehicleModel(Player[u].status.vehicle)-400].Name);
	PlayerTextDrawBackgroundColor(u, Player[u].draws.spdTitle, -1778346416);
	PlayerTextDrawFont(u, Player[u].draws.spdTitle, 0);
	PlayerTextDrawLetterSize(u, Player[u].draws.spdTitle, 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].draws.spdTitle, -1);
	PlayerTextDrawSetOutline(u, Player[u].draws.spdTitle, 1);
	PlayerTextDrawSetProportional(u, Player[u].draws.spdTitle, 1);
	PlayerTextDrawSetSelectable(u, Player[u].draws.spdTitle, 0);
	PlayerTextDrawShow(u, Player[u].draws.spdTitle);

	Player[u].draws.spdSpeed = CreatePlayerTextDraw(u, 622.000000, 305.000000, "170 Km/h ~p~lllllllllllllll~l~lllll");
	PlayerTextDrawAlignment(u, Player[u].draws.spdSpeed, 3);
	PlayerTextDrawBackgroundColor(u, Player[u].draws.spdSpeed, -1778346416);
	PlayerTextDrawFont(u, Player[u].draws.spdSpeed, 1);
	PlayerTextDrawLetterSize(u, Player[u].draws.spdSpeed, 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].draws.spdSpeed, -1);
	PlayerTextDrawSetOutline(u, Player[u].draws.spdSpeed, 1);
	PlayerTextDrawSetProportional(u, Player[u].draws.spdSpeed, 1);
	PlayerTextDrawSetSelectable(u, Player[u].draws.spdSpeed, 0);
	PlayerTextDrawShow(u, Player[u].draws.spdSpeed);

	Player[u].draws.spdFuel = CreatePlayerTextDraw(u, 622.000000, 320.000000, "100L ~p~llllllllllllllllllll");
	PlayerTextDrawAlignment(u, Player[u].draws.spdFuel, 3);
	PlayerTextDrawBackgroundColor(u, Player[u].draws.spdFuel, -1778346416);
	PlayerTextDrawFont(u, Player[u].draws.spdFuel, 1);
	PlayerTextDrawLetterSize(u, Player[u].draws.spdFuel, 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].draws.spdFuel, -1);
	PlayerTextDrawSetOutline(u, Player[u].draws.spdFuel, 1);
	PlayerTextDrawSetProportional(u, Player[u].draws.spdFuel, 1);
	PlayerTextDrawSetSelectable(u, Player[u].draws.spdFuel, 0);
	PlayerTextDrawShow(u, Player[u].draws.spdFuel);

	Player[u].draws.spdMilage = CreatePlayerTextDraw(u, 622.000000, 335.000000, "00001 Km ~p~llllllllllllllllllll");
	PlayerTextDrawAlignment(u, Player[u].draws.spdMilage, 3);
	PlayerTextDrawBackgroundColor(u, Player[u].draws.spdMilage, -1778346416);
	PlayerTextDrawFont(u, Player[u].draws.spdMilage, 1);
	PlayerTextDrawLetterSize(u, Player[u].draws.spdMilage, 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].draws.spdMilage, -1);
	PlayerTextDrawSetOutline(u, Player[u].draws.spdMilage, 1);
	PlayerTextDrawSetProportional(u, Player[u].draws.spdMilage, 1);
	PlayerTextDrawSetSelectable(u, Player[u].draws.spdMilage, 0);
	PlayerTextDrawShow(u, Player[u].draws.spdMilage);

	Player[u].draws.spdState = CreatePlayerTextDraw(u, 580.000000, 348.000000, "~l~ENGINE ~p~LIGHT ~l~DOORS");
	PlayerTextDrawAlignment(u, Player[u].draws.spdState, 2);
	PlayerTextDrawBackgroundColor(u, Player[u].draws.spdState, -1778346416);
	PlayerTextDrawFont(u, Player[u].draws.spdState, 1);
	PlayerTextDrawLetterSize(u, Player[u].draws.spdState, 0.350000, 1.000000);
	PlayerTextDrawColor(u, Player[u].draws.spdState, -1);
	PlayerTextDrawSetOutline(u, Player[u].draws.spdState, 1);
	PlayerTextDrawSetProportional(u, Player[u].draws.spdState, 1);
	PlayerTextDrawUseBox(u, Player[u].draws.spdState, 1);
	PlayerTextDrawBoxColor(u, Player[u].draws.spdState, -1778346416);
	PlayerTextDrawTextSize(u, Player[u].draws.spdState, 0.000000, 120.000000);
	PlayerTextDrawSetSelectable(u, Player[u].draws.spdState, 0);
	PlayerTextDrawShow(u, Player[u].draws.spdState);
}

void world::Vehicles::hideSpeed(int u)
{
	TextDrawHideForPlayer(u, drawPlayerChar[SPD_BG]);
	PlayerTextDrawDestroy(u, Player[u].draws.spdState);
	PlayerTextDrawDestroy(u, Player[u].draws.spdTitle);
	PlayerTextDrawDestroy(u, Player[u].draws.spdSpeed);
	PlayerTextDrawDestroy(u, Player[u].draws.spdFuel);
	PlayerTextDrawDestroy(u, Player[u].draws.spdMilage);
}

void world::Vehicles::updateSpeed(int u)
{
	mutexSpidak.lock();
	const int car = Player[u].status.vehicle;
	if (Vehicle[car].Fuel <= 0.0f)
	{
		Vehicle[car].Engine = false;
		SetVehicleParamsEx(car, Vehicle[car].Engine, Vehicle[car].Light, false, Vehicle[car].Locked, Vehicle[car].Bonnet, Vehicle[car].Boot, false);
	goto case_speed;
	}
	else
	{
	case_speed:
		float x, y, z;
		char tmp[ 64 ];
		float xuita;
		string row = "llllllllllllllllllll";
		string rowDist = "llllllllllllllllllll";
		string rowFuel = "llllllllllllllllllll";
		char act[ 2 ][ 4 ] = { "~l~", "~p~" };
		//======================================================
		GetVehicleVelocity(car, &x, &y, &z);
		const int speed = (int)floor(sqrt(x*x + y*y + z*z) * 180);
		const float speedAlt = sqrt(x*x + y*y + z*z) / 180;
		const char path = ( speed / 12 < 20 ) ? ( speed / 12 ) : ( 20 );
		const char pathFuel = (int)Vehicle[ car ].Fuel / 5 ? (int)Vehicle[ car ].Fuel / 5 : ( 0 );
		const char pathDist = ( std::modf(Vehicle[ car ].Dist, &xuita) * 100 ) / 5;
		//======================================================
		row.insert(path, "~l~");
		rowFuel.insert(pathFuel, "~l~");
		rowDist.insert(pathDist, "~l~");
		//======================================================
		Vehicle[car].Dist += speedAlt;
		Vehicle[car].Fuel -= (speedAlt / 10);
		//======================================================
		sprintf(tmp, "%.2f Km ~p~%s", Vehicle[car].Dist, rowDist.c_str());
		PlayerTextDrawSetString(u, Player[u].draws.spdMilage, tmp);
		//======================================================
		sprintf(tmp, "%.2fL ~p~%s", Vehicle[car].Fuel, rowFuel.c_str());
		PlayerTextDrawSetString(u, Player[u].draws.spdFuel, tmp);
		//======================================================
		sprintf(tmp, "%d Km/h ~p~%s", speed, row.c_str());
		PlayerTextDrawSetString(u, Player[ u ].draws.spdSpeed, tmp);
		//======================================================	
		sprintf(tmp, "%sENGINE %sLIGHT %sDOORS",
			act[Vehicle[car].Engine],
			act[Vehicle[car].Light],
			act[Vehicle[car].Locked]);
		PlayerTextDrawSetString(u, Player[ u ].draws.spdState, tmp);
		//======================================================	
	}
	mutexSpidak.unlock();
}



void world::Vehicles::setOwner(int v, int u)
{

}


/// <summary>
/// Установить статус дверей
/// <param name="v">* Ид авто</param>
/// <param name="s">* Статус</param>
/// </summary>

void world::Vehicles::locked(int v, bool s)
{
	bool obj = false;
	//=======================
	GetVehicleParamsEx(v, &Vehicle[ v ].Engine, &Vehicle[ v ].Light, &Vehicle[ v ].Locked, &Vehicle[ v ].Locked, &Vehicle[ v ].Bonnet, &Vehicle[ v ].Boot, &obj);
	SetVehicleParamsEx(v, Vehicle[ v ].Engine, Vehicle[ v ].Light, s, s, Vehicle[ v ].Bonnet, Vehicle[ v ].Boot, obj);
	//=======================
	sprintf(query, "UPDATE world_Vehicles SET locked = %d WHERE id = %d", Vehicle[ v ].Locked, Vehicle[ v ].db);
	safe_query(con, query);
	//=======================
	Vehicle[ v ].Locked = s;
}

/// <summary>
/// Получить статус дверей
/// <param name="v">* Ид авто</param>
/// </summary>

bool world::Vehicles::locked(int v)
{
	return Vehicle[ v ].Locked;
}

/*
	Вектора это круто, но у нас не на столько пиздец =)
	Да все плюшки круты, ты не забывай changelog.txt обновлять а то нахуя его добавил получается.
*/

bool world::Vehicles::isVehicleInCube(const int v, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	float x;
	float y;
	float z;
	//================================================================================
	GetVehiclePos(v, &x, &y, &z);
	//================================================================================
	return (x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ) ? true : false;
}

int world::Vehicles::sCreateVehicle(const int model, const float x, const float y, const float z, const float a, const int c1, const int c2, const int res)
{
	world::createVehicleMutex.lock();
	int i = CreateVehicle(model, x, y, z, a, c1, c2, res);
	world::createVehicleMutex.unlock();

	Vehicle[i].Model = model;
	Vehicle[i].color1 = c1;
	Vehicle[i].color2 = c2;
	Vehicle[i].paint = -1;
	Vehicle[i].text3D = StreamerCall::Native::CreateDynamic3DTextLabel("", -1, 0.0f, 0.0f, 0.5f, 20.0f, 65535, i);
	return i;
}

bool world::Vehicles::sDestroyVehicle(const int v)
{
	if (DestroyVehicle(v))
	{
		StreamerCall::Native::DestroyDynamic3DTextLabel(Vehicle[v].text3D);
		return true;
	}
	return false;
}