#include "main.h"



char  Properties::Shops::ShopVehicle::Gear[ 3 ][ 16 ] = { "Передний", "Задний", "Полный" };
char  Properties::Shops::ShopVehicle::Group[ 4 ][ 16 ] = { "Эконом", "Бизнесс", "Спорт", "Грузовые" };

struct sVehicle   Properties::Shops::ShopVehicle::vehicle[ MAX_VEHSHOPS ];
struct eItem	  Properties::Shops::ShopVehicle::items[MAX_VEHSHOPS][20];




void Properties::Shops::ShopVehicle::loadShop()
{
	int i = 0;
	int v = 0;
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
			sprintf(query, "Автосалон: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", vehicle[ i ].name, cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].player);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "Автосалон\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d", cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].price);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
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
		v = 0;
		sprintf(query, "SELECT id,model,cost,amount FROM class_Shop_vehicle_items WHERE sid = %d", vehicle[i].db);
		mysql_query(con, query);
		MYSQL_RES *subres = mysql_store_result(con);
		MYSQL_ROW subrow;
		while ((subrow = mysql_fetch_row(subres)))
		{
			items[countProperty][v].DB = atoi(subrow[itemRows::bid]);
			items[countProperty][v].Price = atoi(subrow[itemRows::cost]);
			items[countProperty][v].Model = atoi(subrow[itemRows::model]);
			items[countProperty][v].Amount = atoi(subrow[itemRows::amount]);
			logprintf("loadItemsRow: %d|%d|%d|%d", items[countProperty][v].DB, items[countProperty][v].Price, items[countProperty][v].Model, items[countProperty][v].Amount);
			v++;
		}
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
	Player[u].isAction = PlayerAction::ACTION_USERENT;
	vehicle[shop].Used = true;
}

void Properties::Shops::ShopVehicle::viewList(const int u, const int item)
{
	char field[ 64 ];
	//====================================================
	const int shop = Property[ Player[ u ].inIndex ].link;
	const int styl = Property[ Player[ u ].inIndex ].style;
	const int modl = 0;
	//====================================================
	for (int i = 0; i < 20; i++)
	{
		if (items[shop][i].Amount > 0)
		{
			vehicle[shop].Item = i;
		}
	}
	//====================================================
	if (vehicle[ shop ].Car)
	{
		DestroyVehicle(vehicle[ shop ].Car);
		vehicle[ shop ].Car = 0;
	}
	//====================================================
	sprintf(field, "%d$", items[shop][vehicle[shop].Item].Price), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::costVeh], field);
	sprintf(field, "%s класс", Group[0]), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::group], field);
	sprintf(field, "%s привод", Gear[0]), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::gear], field);
	
	sprintf(field, "Скорость:\t\t %d км/ч", 180), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::speedText], field);
	sprintf(field, "Мощность:\t\t%d л.с", 200), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::power], field);
	sprintf(field, "Дизель,\t\t\t\t\t %dL", 200), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::fuel], field);
	sprintf(field, "Маневренность"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::control], field);
	sprintf(field, "Скорость"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::speed], field);

	//====================================================
	vehicle[shop].Car = CreateVehicle(items[shop][vehicle[shop].Item].Model,
										Interior[ styl ].actX,
										Interior[ styl ].actY,
										Interior[ styl ].actZ,
										0.0f, 3, 3, 1000);
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
	SetPlayerCameraPos(u, xX, xY, Interior[ styl ].actZ + rand() % 8);
	SetPlayerCameraLookAt(u, Interior[ styl ].actX, Interior[ styl ].actY, Interior[ styl ].actZ, CAMERA_MOVE);
	//------------------------------------------------------------	
	vehicle[ shop ].angle += rand() % 25;
}

void  Properties::Shops::ShopVehicle::initTextDraws(const int u, const int shop)
{
	TextDrawShowForPlayer(u, drawPlayerChar[SHOP_HEADER_VEHICLE]);
	TextDrawShowForPlayer(u, drawPlayerChar[REG_BG]);
	TextDrawShowForPlayer(u, drawPlayerChar[REG_BUTTON_BG]);
	TextDrawShowForPlayer(u, drawPlayerChar[REG_LEFT]);
	TextDrawShowForPlayer(u, drawPlayerChar[REG_SELECT]);
	TextDrawShowForPlayer(u, drawPlayerChar[REG_RIGHT]);


	vehicle[shop].Textdraw[drawNames::gear] = CreatePlayerTextDraw(u, 30.000000, 170.0, Gear[0]);
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::gear], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::gear], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::gear], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::gear], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::gear], 0);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::gear], 1);
	PlayerTextDrawSetShadow(u, vehicle[shop].Textdraw[drawNames::gear], 0);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::gear], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::gear], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::gear], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::gear], 0);

	vehicle[shop].Textdraw[drawNames::group] = CreatePlayerTextDraw(u, 30.000000, 185.0, Group[0]);
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::group], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::group], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::group], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::group], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::group], 0);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::group], 1);
	PlayerTextDrawSetShadow(u, vehicle[shop].Textdraw[drawNames::group], 0);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::group], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::group], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::group], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::group], 0);


	vehicle[shop].Textdraw[drawNames::speedText] = CreatePlayerTextDraw(u, 30.000000, 200.0, "SPEED");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::speedText], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::speedText], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::speedText], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::speedText], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::speedText], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::speedText], 1);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::speedText], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::speedText], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::speedText], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::speedText], 0);

	vehicle[shop].Textdraw[drawNames::power] = CreatePlayerTextDraw(u, 30.0, 215.0, "Power");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::power], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::power], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::power], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::power], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::power], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::power], 1);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::power], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::power], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::power], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::power], 0);
	
	vehicle[shop].Textdraw[drawNames::fuel] = CreatePlayerTextDraw(u, 30.000000, 230.000000, "Fuel");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::fuel], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::fuel], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::fuel], 0.400000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::fuel], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::fuel], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::fuel], 1);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::fuel], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::fuel], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::fuel], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::fuel], 0);

	//====================================================================================================

	//====================================================================================================
	vehicle[shop].Textdraw[drawNames::control] = CreatePlayerTextDraw(u, 30.000000, 245.0, "Управление");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::control], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::control], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::control], 0.300000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::control], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::control], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::control], 1);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::control], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::control], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::control], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::control], 0);

	vehicle[shop].Textdraw[drawNames::controlValue] = CreatePlayerTextDraw(u, 140.000000, 245.0, "~p~lllllll~l~lllllll");
	PlayerTextDrawAlignment(u, vehicle[shop].Textdraw[drawNames::controlValue], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::controlValue], 255);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::controlValue], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::controlValue], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::controlValue], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::controlValue], 0);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::controlValue], 1);
	PlayerTextDrawSetShadow(u, vehicle[shop].Textdraw[drawNames::controlValue], 0);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::controlValue], 0);

	vehicle[shop].Textdraw[drawNames::speed] = CreatePlayerTextDraw(u, 30.000000, 260.0, "Скорость");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::speed], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::speed], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::speed], 0.300000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::speed], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::speed], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::speed], 1);
	PlayerTextDrawUseBox(u, vehicle[shop].Textdraw[drawNames::speed], 1);
	PlayerTextDrawBoxColor(u, vehicle[shop].Textdraw[drawNames::speed], -1778346416);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::speed], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::speed], 0);

	vehicle[shop].Textdraw[drawNames::speedValue] = CreatePlayerTextDraw(u, 140.000000, 260.0, "~p~lllllll~l~lllllll");
	PlayerTextDrawAlignment(u, vehicle[shop].Textdraw[drawNames::speedValue], 2);
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::speedValue], 255);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::speedValue], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::speedValue], 0.500000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::speedValue], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::speedValue], 0);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::speedValue], 1);
	PlayerTextDrawSetShadow(u, vehicle[shop].Textdraw[drawNames::speedValue], 0);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::speedValue], 0);


	vehicle[shop].Textdraw[drawNames::costVeh] = CreatePlayerTextDraw(u, 60.0, 285.0, "150000$");
	PlayerTextDrawBackgroundColor(u, vehicle[shop].Textdraw[drawNames::costVeh], 80);
	PlayerTextDrawFont(u, vehicle[shop].Textdraw[drawNames::costVeh], 1);
	PlayerTextDrawLetterSize(u, vehicle[shop].Textdraw[drawNames::costVeh], 0.700000, 1.000000);
	PlayerTextDrawColor(u, vehicle[shop].Textdraw[drawNames::costVeh], -1);
	PlayerTextDrawSetOutline(u, vehicle[shop].Textdraw[drawNames::costVeh], 1);
	PlayerTextDrawSetProportional(u, vehicle[shop].Textdraw[drawNames::costVeh], 1);
	PlayerTextDrawTextSize(u, vehicle[shop].Textdraw[drawNames::costVeh], 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(u, vehicle[shop].Textdraw[drawNames::costVeh], 0);




	//====================================================================================================

}

void Properties::Shops::ShopVehicle::endView(const int u)
{
	const int shop = Property[Player[u].inIndex].link;

	SetCameraBehindPlayer(u);

	TextDrawHideForPlayer(u, drawPlayerChar[SHOP_HEADER_VEHICLE]);
	TextDrawHideForPlayer(u, drawPlayerChar[REG_BG]);
	TextDrawHideForPlayer(u, drawPlayerChar[REG_BUTTON_BG]);
	TextDrawHideForPlayer(u, drawPlayerChar[REG_LEFT]);
	TextDrawHideForPlayer(u, drawPlayerChar[REG_SELECT]);
	TextDrawHideForPlayer(u, drawPlayerChar[REG_RIGHT]);

	DestroyVehicle(vehicle[shop].Car);
	vehicle[shop].Used = false;
	Player[u].isAction = PlayerAction::ACTION_NONE;

	for (int i = 0; i < sizeof( vehicle[ shop ].Textdraw ); i++)
	{
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ i ]);
		/*PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::control ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::controlValue ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::costVeh ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::fuel ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::gear ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::group ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::power ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::speed ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::speedText ]);
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ drawNames::speedValue ]);*/
	}
}

void Properties::Shops::ShopVehicle::listView(const int u, bool left)
{
	if (left)
	{

	}
	else
	{

	}
}