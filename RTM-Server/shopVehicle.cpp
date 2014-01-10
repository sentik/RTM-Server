#include "main.h"
/*
������:
1. ������ ������� ����
2. ������� ��������� ����� � �����
3. ����� ������ ������ ������ � �����
*/


char  Properties::Shops::ShopVehicle::Gear[ 3 ][ 16 ] = { "��������", "������", "������" };
char  Properties::Shops::ShopVehicle::Group[ 4 ][ 16 ] = { "������", "�������", "�����", "��������" };

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
	cProperty::propertyLoadQuery(PropertyType::prAutosalon);
	//safe_query(con, "SELECT class_Property.*, class_Shop_vehicle.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Shop_vehicle  WHERE class_Property.property = class_Shop_vehicle.db AND class_Property.type = 3");
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
		Property[ countProperty ].link = i;	// ������ �� ���������
		//--------------------------------------------------------------
		strcpy(vehicle[ i ].name, row[ Properties::Shops::ShopVehicle::vehRows::name ]);
		//--------------------------------------------------------------
		if (Property[ countProperty ].owner)
		{
			strcpy(Property[ countProperty ].player, row[ Properties::Shops::ShopVehicle::vehRows::oName ]);
			sprintf(query, "���������: {B7FF00}%s\n{FFFFFF}�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s", vehicle[ i ].name, getSaZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].player);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "���������\n{FFFFFF}�����: {FF0000}%s {FFFFFF}�: {FF0000}%d\n{FFFFFF}���������: {FF0000}%d", getSaZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].price);
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
		safe_query(con, query);
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
	logprintf("[������� ���������]: \t���� ���������� ����������� \t- %d", i);
}

/*
void Properties::Shops::ShopVehicle::create(int price, float x, float y, float z)
{
	sProperty tmp;
	sVehicle vtmp;
	//-----------------------------------------------
	int interior = cInteriors::getRandom(PropertyType::prAutosalon);
	//-----------------------------------------------
	tmp.owner = tmp.status = tmp.bank = 0;
	tmp.style = interior;
	tmp.price = price;
	tmp.posX = x;
	tmp.posY = y;
	tmp.posZ = z;
	tmp.type = PropertyType::prBank;
	//-----------------------------------------------
	sprintf(query, "INSERT INTO class_Property SET `property` ='%d', type='%d', x='%f', y='%f', z='%f', price='%d'",
			tmp.property, PropertyType::prBank, x, y, z, price);
	safe_query(con, query);
	//-----------------------------------------------
	tmp.db = mysql_insert_id(con);


	//-----------------------------------------------
	countProperty++;
}
*/

void Properties::Shops::ShopVehicle::preView(const int u)
{
	const int shop = Property[ Player[ u ].status.inIndex ].link;
	if (vehicle[ shop ].Used)
	{
		SendClientMessage(u, -1, "[����������]: ��������, �� �� ������ ������ ��� �������� �����!");
		SendClientMessage(u, -1, "[����������]: ����������, ��������� ���� �� �����������.");
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
	Player[u].status.action = PlayerAction::ACTION_AUTOSHOP;
	vehicle[shop].Used = true;
}

void Properties::Shops::ShopVehicle::viewList(const int u, const int item)
{
	char field[ 64 ];
	//====================================================
	const int shop = Property[ Player[ u ].status.inIndex ].link;
	const int styl = Property[ Player[ u ].status.inIndex ].style;
	//====================================================
	if (items[ shop ][ item ].Amount > 0)  vehicle[ shop ].Item = item;
	else vehicle[ shop ].Item = 0;
	//====================================================
	const int modl = vehicle[ shop ].Item;
	const int speed = VehicleClass[ modl ].Speed;
	const int power = VehicleClass[ modl ].Power;
	const int group = VehicleClass[ modl ].Group;
	const int gear = VehicleClass[ modl ].Gear;
	const int back = 100;
	//====================================================
	if (vehicle[ shop ].Car)
	{
		DestroyVehicle(vehicle[ shop ].Car);
		vehicle[ shop ].Car = 0;
	}
	//====================================================
	sprintf(field, "%d$", items[shop][vehicle[shop].Item].Price), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::costVeh], field);
	sprintf(field, "%s �����", Group[ group ]), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ drawNames::group ], field);
	sprintf(field, "%s ������", Gear[ gear ]), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ drawNames::gear ], field);
	
	sprintf(field, "��������:\t\t %d ��/�", speed), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ drawNames::speedText ], field);
	sprintf(field, "��������:\t\t%d �.�", power), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ drawNames::power ], field);
	sprintf(field, "������,\t\t\t\t\t %dL", back), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[ shop ].Textdraw[ drawNames::fuel ], field);
	sprintf(field, "�������������"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::control], field);
	sprintf(field, "��������"), cClass::fixText(field, 32), PlayerTextDrawSetString(u, vehicle[shop].Textdraw[drawNames::speed], field);

	//====================================================
	vehicle[shop].Car = CreateVehicle(items[shop][vehicle[shop].Item].Model,
										Interior[ styl ].actX,
										Interior[ styl ].actY,
										Interior[ styl ].actZ,
										0.0f, 3, 3, 1000);
	//====================================================
	SetVehicleParamsEx(vehicle[ shop ].Car, false, false, false, true, false, false, false);
	SetVehicleVirtualWorld(vehicle[ shop ].Car, Player[ u ].status.inIndex);
	//====================================================
}

void Properties::Shops::ShopVehicle::viewCam(const int u)
{
	const int shop = Property[ Player[ u ].status.inIndex ].link;
	const int styl = Property[ Player[ u ].status.inIndex ].style;
	//------------------------------------------------------------	
	float xX = Interior[ styl ].actX + 4 * cos(vehicle[ shop ].angle);
	float xY = Interior[ styl ].actY + 4 * sin(vehicle[ shop ].angle);
	//------------------------------------------------------------	
	SetPlayerCameraPos(u, xX, xY, Interior[ styl ].actZ + rand() % 8);
	SetPlayerCameraLookAt(u, Interior[ styl ].actX, Interior[ styl ].actY, Interior[ styl ].actZ, CAMERA_MOVE);
	//------------------------------------------------------------	
	vehicle[ shop ].angle += rand() % 25;
}



void Properties::Shops::ShopVehicle::endView(const int u)
{
	const int shop = Property[ Player[ u ].status.inIndex ].link;
	Player[ u ].status.action = PlayerAction::ACTION_NONE;
	DestroyVehicle(vehicle[ shop ].Car);
	vehicle[ shop ].Used = false;
	SetCameraBehindPlayer(u);
	//==============================================================
	TextDrawHideForPlayer(u, drawPlayerChar[ SHOP_HEADER_VEHICLE ]);
	TextDrawHideForPlayer(u, drawPlayerChar[ REG_BG ]);
	TextDrawHideForPlayer(u, drawPlayerChar[ REG_BUTTON_BG ]);
	TextDrawHideForPlayer(u, drawPlayerChar[ REG_LEFT ]);
	TextDrawHideForPlayer(u, drawPlayerChar[ REG_SELECT ]);
	TextDrawHideForPlayer(u, drawPlayerChar[ REG_RIGHT ]);
	for (int i = 0; i < sizeof( vehicle[ shop ].Textdraw ); i++)
	{
		PlayerTextDrawDestroy(u, vehicle[ shop ].Textdraw[ i ]);
	}
}


void Properties::Shops::ShopVehicle::onDLG(int u, int dialogid, int response, int listitem, const char* inputtext)
{
	if (dialogid == DLG_VEHICLE_BUY)
	{
		if (response) 
			ShowPlayerDialog(u, DLG_VEHICLE_PAY, GUI_LIST, "������ ������", "������ ��������� \n������ ���������", "�����", "������");
		
	}
	//----------------------------------------------------------------------
	else if (dialogid == DLG_VEHICLE_PAY)
	{
		if(response)
		{
			if (listitem == 0)					//��������
			{
				using namespace Properties::Shops;
				const int idx = Property[ Player[ u ].status.inIndex ].link;
				const int item = 0;
				if (cPlayer::checkMoney(u, -ShopVehicle::items[ idx ][ item ].Price))
				{
					eVehicle tmp;
					//----------------------------------------------------
					tmp.Owner = Player[ u ].base.db;
					tmp.Model = ShopVehicle::items[ idx ][ item ].Model;
					//----------------------------------------------------
					tmp.posX = ShopVehicle::vehicle[ idx ].spawnX;
					tmp.posY = ShopVehicle::vehicle[ idx ].spawnY;
					tmp.posZ = ShopVehicle::vehicle[ idx ].spawnZ;
					tmp.posR = ShopVehicle::vehicle[ idx ].spawnR;
					tmp.Dist = tmp.posI = tmp.posW = 0;
					//----------------------------------------------------
					tmp.Boot = tmp.Bonnet = tmp.Locked = tmp.Light = tmp.Engine = false;
					tmp.color1 = tmp.color2 = 0;
					tmp.Heal = 1000.0f;
					tmp.Fuel = 20.0f;
					tmp.paint = -1;
					//----------------------------------------------------
					int veh = CreateVehicle(tmp.Model, tmp.posX, tmp.posY, tmp.posZ, tmp.posR, tmp.color1, tmp.color2, 500);
					//----------------------------------------------------
					strcpy(tmp.vNumber, "NONE");
					//----------------------------------------------------
					sprintf(query, "INSERT INTO world_Vehicles VALUES (NULL, '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%s', '%d', '%d', '%d', '%d', '%d')",
					tmp.Owner, tmp.Model, tmp.posX, tmp.posY, tmp.posZ, tmp.posR, tmp.posI, tmp.posW, tmp.color1, tmp.color1, tmp.paint, tmp.Heal, tmp.Fuel, tmp.Dist, tmp.vNumber, false, false, false, false, false);
					logprintf(query);
					//----------------------------------------------------
					safe_query(con, query);
					tmp.db = mysql_insert_id(con);
					//----------------------------------------------------
					world::Vehicles::Vehicle[ veh ] = tmp;
				}
			}
			//===========================================================================
			else                                //��������
			{
				SendClientMessage(u, -1, "��������, �� ��� ������� ��� � ����������!");
			}
		}
		ShopVehicle::endView(u);
	}
	//----------------------------------------------------------------------
}


void Properties::Shops::ShopVehicle::onGUI(const int u, const int draw)
{
	const int shop = Property[ Player[ u ].status.inIndex ].link;
	//----------------------------------------------------------------------
	if (draw == INVALID_TEXT_DRAW)
	{
		SendClientMessage(u, -1, "Xyuua");
		Properties::Shops::ShopVehicle::endView(u);
	}
	//----------------------------------------------------------------------			
	else if (draw == drawPlayerChar[ REG_LEFT ])			//�����
	{
		ShopVehicle::vehicle[ shop ].Item = clamp(ShopVehicle::vehicle[ shop ].Item - 1, 0, 100);
		ShopVehicle::viewList(u, ShopVehicle::vehicle[ shop ].Item);
	}
	else if (draw == drawPlayerChar[ REG_SELECT ])	//�������
	{
		Player[ u ].status.action = PlayerAction::ACTION_AUTOSHOP;
		const int idx = ShopVehicle::vehicle[ shop ].Item;
		char msg[ sizeof( language::property::shop::vehicle::action_Buy )];
		sprintf
		(
			msg, 
			language::property::shop::vehicle::action_Buy, 
			Player[ u ].strings.uName, 
			Player[ u ].strings.sName,
			VehicleClass[ idx ].Name,
			ShopVehicle::items[ shop ][ idx ].Price
		);
		ShowPlayerDialog(u, DLG_VEHICLE_BUY, GUI_MSG, language::property::shop::vehicle::header_Buy, msg, "������", "�����");
	}
	else if (draw == drawPlayerChar[ REG_RIGHT ])	//������
	{
		ShopVehicle::vehicle[ shop ].Item = clamp(ShopVehicle::vehicle[ shop ].Item + 1, 0, 100);
		ShopVehicle::viewList(u, ShopVehicle::vehicle[ shop ].Item);
	}
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
	vehicle[shop].Textdraw[drawNames::control] = CreatePlayerTextDraw(u, 30.000000, 245.0, "����������");
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

	vehicle[shop].Textdraw[drawNames::speed] = CreatePlayerTextDraw(u, 30.000000, 260.0, "��������");
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

void Properties::Shops::ShopVehicle::updateText(const int p, const int u)
{
	char msg[256];
	sprintf(Property[p].player, "%s %s", Player[u].strings.uName, Player[u].strings.sName);
	sprintf(msg, "���������: {B7FF00}%s\n{FFFFFF}�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s", vehicle[Property[p].link].name, getSaZoneName(Property[p].region), Property[p].number, Property[p].player);
	//=====================================================================================================
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Property[p].text, -1, msg);
}
