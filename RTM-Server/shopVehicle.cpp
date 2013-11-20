#include "main.h"



char  Properties::Shops::ShopVehicle::Gear[ 3 ][ 16 ] = { "Передний", "Задний", "Полный" };
char  Properties::Shops::ShopVehicle::Group[ 4 ][ 16 ] = { "Эконом", "Бизнесс", "Спорт", "Грузовые" };

struct sVehicle   Properties::Shops::ShopVehicle::vehicle[ MAX_VEHSHOPS ];
struct eItem	  Properties::Shops::ShopVehicle::items[ 64 ];




void Properties::Shops::ShopVehicle::loadShop()
{
	int i = 0;
	MYSQL_ROW row;
/*	//------------------------------------------------------------
	cClass::fixText(Gear[ 0 ], 16);
	cClass::fixText(Gear[ 1 ], 16);
	cClass::fixText(Gear[ 2 ], 16);
	//------------------------------------------------------------
	cClass::fixText(Group[ 0 ], 16);
	cClass::fixText(Group[ 1 ], 16);
	cClass::fixText(Group[ 2 ], 16);
	cClass::fixText(Group[ 3 ], 16);*/
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Shop_vehicle.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Shop_vehicle  WHERE class_Property.property = class_Shop_vehicle.db AND class_Property.type = 3");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while (( row = mysql_fetch_row(result) ))
	{
		Property[ countProperty ].db = atoi(row[Properties::Shops::ShopVehicle::vehRows::id ]);
		Property[ countProperty ].bank = atoi(row[Properties::Shops::ShopVehicle::vehRows::bank ]);
		Property[ countProperty ].owner = atoi(row[Properties::Shops::ShopVehicle::vehRows::owner ]);
		Property[ countProperty ].price = atoi(row[Properties::Shops::ShopVehicle::vehRows::price ]);
		Property[ countProperty ].type = atoi(row[Properties::Shops::ShopVehicle::vehRows::type ]);
		Property[ countProperty ].posX = atof(row[Properties::Shops::ShopVehicle::vehRows::posx ]);
		Property[ countProperty ].posY = atof(row[Properties::Shops::ShopVehicle::vehRows::posy ]);
		Property[ countProperty ].posZ = atof(row[Properties::Shops::ShopVehicle::vehRows::posz ]);
		Property[ countProperty ].property = atoi(row[Properties::Shops::ShopVehicle::vehRows::property ]);
		Property[ countProperty ].style = atoi(row[Properties::Shops::ShopVehicle::vehRows::style ]);
		Property[ countProperty ].region = atoi(row[Properties::Shops::ShopVehicle::vehRows::region ]);
		Property[ countProperty ].number = atoi(row[Properties::Shops::ShopVehicle::vehRows::number ]);
		//--------------------------------------------------------------
		vehicle[ i ].db = atoi(row[ Properties::Shops::ShopVehicle::vehRows::db ]);
		vehicle[ i ].type = atoi(row[ Properties::Shops::ShopVehicle::vehRows::category ]);
		vehicle[ i ].spawnR = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnr ]);
		vehicle[ i ].spawnX = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnx ]);
		vehicle[ i ].spawnY = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawny ]);
		vehicle[ i ].spawnZ = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnz ]);
		Property[ countProperty ].link = i;	// Ссылка на имущество
		//--------------------------------------------------------------
		strcpy(vehicle[ i ].name, row[ Properties::Shops::ShopVehicle::vehRows::name ]);
		//--------------------------------------------------------------
		if (Property[ countProperty ].owner)
		{
			strcpy(Property[ countProperty ].player, row[ Properties::Shops::ShopVehicle::vehRows::oName ]);
			sprintf(query, "[Автосалон]\n{B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", vehicle[ i ].name, cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].player);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_GREEN, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "[Автосалон]\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d", cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].price);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_RED, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		//-----------------------------------------------------------------------------------------------------------
		Property[ countProperty ].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
																						Property[ countProperty ].posX,
																						Property[ countProperty ].posY,
																						Property[ countProperty ].posZ, 30.0f);
		//-----------------------------------------------------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно автосалонов \t- %d", i);
}


void Properties::Shops::ShopVehicle::preView(const int u)
{
	const int shop = Property[ Player[ u ].inIndex ].link;
	if (vehicle[ shop ].Used)
	{
		SendClientMessage(u, -1, "[Информация]: Извините, но на данный момент наш менеджер занят!");
		SendClientMessage(u, -1, "[Информация]: Пожалуйста, подождите пока он освободится.");
		return;
	}
	//===================================================
	ShopVehicle::initTextDraws(u, shop);
	//===================================================
	viewList(u, 0);
	viewCam(u);
	//===================================================
	for (int i = 0; i < sizeof( vehicle[ shop ].Textdraw ); i++)
	{
		PlayerTextDrawShow(u, i);
	}
	//===================================================
	SelectTextDraw(u, 0xA3B4C5FF);
}

void Properties::Shops::ShopVehicle::viewList(const int u, const int item)
{
	char field[ 64 ];
	//====================================================
	const int shop = Property[ Player[ u ].inIndex ].link;
	const int styl = Property[ Player[ u ].inIndex ].style;
	const int modl = 0;
	//====================================================
	if (vehicle[ shop ].Car)
	{
		DestroyVehicle(vehicle[ shop ].Car);
		vehicle[ shop ].Car = 0;
	}
	//====================================================
	items[ shop ].Model = 560;
	sprintf(field, "%s класс", Group[ 0 ]), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 11 ], field);
	sprintf(field, "%s привод", Gear[ 0 ]), cClass::fixText(field, 32),	PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 12 ], field);
	
	sprintf(field, "Скорость:\t\t %d км/ч",	 180), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 6 ], field);
	sprintf(field, "Мощность:\t\t%d л.с",   200), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 7 ], field);
	sprintf(field, "Дизель,\t\t\t\t\t %dL", 200), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 10 ], field);
	sprintf(field, "Маневренность"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 8 ], field);
	sprintf(field, "Скорость"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ 13 ], field);

	//====================================================
	vehicle[ shop ].Car = CreateVehicle(items[ shop ].Model,
										Interior[ styl ].actX,
										Interior[ styl ].actY,
										Interior[ styl ].actZ,
										vehicle[ shop ].angle, 3, 3, 1000);
	//====================================================
	SetVehicleParamsEx(vehicle[ shop ].Car, false, false, false, true, false, false, false);
	SetVehicleVirtualWorld(vehicle[ shop ].Car, Player[ u ].inIndex);
	//====================================================
}

void Properties::Shops::ShopVehicle::viewCam(const int u)
{
	const int shop = Property[ Player[ u ].inIndex ].link;
	const int styl = Property[ Player[ u ].inIndex ].style;
	//------------------------------------------------------------	
	float xX = Interior[ styl ].actX + 4 * cos(vehicle[ shop ].angle);
	float xY = Interior[ styl ].actY + 4 * sin(vehicle[ shop ].angle);
	//------------------------------------------------------------	
	SetPlayerCameraPos(u, xX, xY, Interior[ styl ].actZ + rand() % 15);
	SetPlayerCameraLookAt(u, Interior[ styl ].actX, Interior[ styl ].actY, Interior[ styl ].actZ, CAMERA_MOVE);
	//------------------------------------------------------------	
	vehicle[ shop ].angle += rand() % 25;
}

void  Properties::Shops::ShopVehicle::initTextDraws(const int u, const int shop)
{
	// In OnPlayerConnect prefferably, we procced to create our textdraws:
	vehicle[ shop ].Textdraw[ 0 ] = CreatePlayerTextDraw(u, 100.000000, 160.000000, "_");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 0 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 0 ], 255);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 0 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 0 ], 0.500000, 17.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 0 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 0 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 0 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 0 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 0 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 0 ], 80);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 0 ], 0.000000, 150.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 0 ], 0);

	vehicle[ shop ].Textdraw[ 1 ] = CreatePlayerTextDraw(u, 100.000000, 153.000000, "Vehicle Shop");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 1 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 1 ], -1778346416);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 1 ], 0);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 1 ], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 1 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 1 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 1 ], 1);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 1 ], 0);

	vehicle[ shop ].Textdraw[ 2 ] = CreatePlayerTextDraw(u, 100.000000, 318.000000, "_");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 2 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 2 ], 255);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 2 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 2 ], 0.500000, 1.199998);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 2 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 2 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 2 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 2 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 2 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 2 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 2 ], 0.000000, 150.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 2 ], 0);

	vehicle[ shop ].Textdraw[ 3 ] = CreatePlayerTextDraw(u, 25.000000, 316.000000, "ld_beat:left");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 3 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 3 ], 0);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 3 ], 4);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 3 ], 0.500000, 1.100000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 3 ], 100);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 3 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 3 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 3 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 3 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 3 ], 255);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 3 ], 30.000000, 15.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 3 ], 1);

	vehicle[ shop ].Textdraw[ 4 ] = CreatePlayerTextDraw(u, 145.000000, 316.000000, "ld_beat:right");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 4 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 4 ], 0);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 4 ], 4);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 4 ], 0.500000, 1.100000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 4 ], 100);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 4 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 4 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 4 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 4 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 4 ], 255);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 4 ], 30.000000, 15.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 4 ], 1);

	vehicle[ shop ].Textdraw[ 5 ] = CreatePlayerTextDraw(u, 100.000000, 316.000000, "SELECT");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 5 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 5 ], 0);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 5 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 5 ], 0.609999, 1.399999);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 5 ], 100);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 5 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 5 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 5 ], 1);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 5 ], 1);


	vehicle[ shop ].Textdraw[ 12 ] = CreatePlayerTextDraw(u, 30.000000, 170.0, Gear[0]);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 12 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 12 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 12 ], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 12 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 12 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 12 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 12 ], 0);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 12 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 12 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 12 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 12 ], 0);

	vehicle[ shop ].Textdraw[ 11 ] = CreatePlayerTextDraw(u, 30.000000, 185.0, Group[ 0 ]);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 11 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 11 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 11 ], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 11 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 11 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 11 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 11 ], 0);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 11 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 11 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 11 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 11 ], 0);


	vehicle[ shop ].Textdraw[ 6 ] = CreatePlayerTextDraw(u, 30.000000, 200.0, "SPEED");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 6 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 6 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 6 ], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 6 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 6 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 6 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 6 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 6 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 6 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 6 ], 0);

	vehicle[ shop ].Textdraw[ 7 ] = CreatePlayerTextDraw(u, 30.0, 215.0, "Power");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 7 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 7 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 7 ], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 7 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 7 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 7 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 7 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 7 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 7 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 7 ], 0);
	
	vehicle[ shop ].Textdraw[ 10 ] = CreatePlayerTextDraw(u, 30.000000, 230.000000, "Fuel");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 10 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 10 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 10 ], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 10 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 10 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 7 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 10 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 10 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 10 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 10 ], 0);

	//====================================================================================================

	//====================================================================================================
	vehicle[ shop ].Textdraw[ 8 ] = CreatePlayerTextDraw(u, 30.000000, 245.0, "Управление");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 8 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 8 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 8 ], 0.300000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 8 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 8 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 8 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 8 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 8 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 8 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 8 ], 0);

	vehicle[ shop ].Textdraw[ 9 ] = CreatePlayerTextDraw(u, 140.000000, 245.0, "~p~lllllll~l~lllllll");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 9 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 9 ], 255);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 9 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 9 ], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 9 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 9 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 9 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 9 ], 0);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 9 ], 0);

	vehicle[ shop ].Textdraw[ 13 ] = CreatePlayerTextDraw(u, 30.000000, 260.0, "Скорость");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 13 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 13 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 13 ], 0.300000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 13 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 13 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 13 ], 1);
	PlayerTextDrawUseBox(u, vehicle[ shop ].Textdraw[ 13 ], 1);
	PlayerTextDrawBoxColor(u, vehicle[ shop ].Textdraw[ 13 ], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 13 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 13 ], 0);

	vehicle[ shop ].Textdraw[ 14 ] = CreatePlayerTextDraw(u, 140.000000, 260.0, "~p~lllllll~l~lllllll");
	PlayerTextDrawAlignment(u, vehicle[ shop ].Textdraw[ 14 ], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 14 ], 255);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 14 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 14 ], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 14 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 14 ], 0);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 14 ], 1);
	PlayerTextDrawSetShadow(u, vehicle[ shop ].Textdraw[ 14 ], 0);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 14 ], 0);


	vehicle[ shop ].Textdraw[ 15 ] = CreatePlayerTextDraw(u, 60.0, 285.0, "150000$");
	PlayerTextDrawBackgroundColor(u, vehicle[ shop ].Textdraw[ 15 ], 80);
	PlayerTextDrawFont(u, vehicle[ shop ].Textdraw[ 15 ], 1);
	PlayerTextDrawLetterSize(u, vehicle[ shop ].Textdraw[ 15 ], 0.700000, 1.000000);
	PlayerTextDrawColor(u, vehicle[ shop ].Textdraw[ 15 ], -1);
	PlayerTextDrawSetOutline(u, vehicle[ shop ].Textdraw[ 15 ], 1);
	PlayerTextDrawSetProportional(u, vehicle[ shop ].Textdraw[ 15 ], 1);
	PlayerTextDrawTextSize(u, vehicle[ shop ].Textdraw[ 15 ], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[ shop ].Textdraw[ 15 ], 0);




	//====================================================================================================

}