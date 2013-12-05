#include "main.h"

struct eGas  gasProperty::cGas::Gas[MAX_GAS];

void gasProperty::cGas::loadGas()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Gas.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Gas  WHERE class_Property.property = class_Gas.id AND class_Property.type = 5");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while ((row = mysql_fetch_row(result)))
	{
		Property[countProperty].db			= atoi(row[gasProperty::rowsGas::id]);
		Property[countProperty].bank		= atoi(row[gasProperty::rowsGas::bank]);
		Property[countProperty].owner		= atoi(row[gasProperty::rowsGas::owner]);
		Property[countProperty].price		= atoi(row[gasProperty::rowsGas::price]);
		Property[countProperty].type		= atoi(row[gasProperty::rowsGas::type]);
		Property[countProperty].posX		= atof(row[gasProperty::rowsGas::x]);
		Property[countProperty].posY		= atof(row[gasProperty::rowsGas::y]);
		Property[countProperty].posZ		= atof(row[gasProperty::rowsGas::z]);
		Property[countProperty].property	= atoi(row[gasProperty::rowsGas::property]);
		//Property[countProperty].style		= atoi(row[gasProperty::rowsGas::style]);
		Property[countProperty].region		= atoi(row[gasProperty::rowsGas::region]);
		Property[countProperty].number		= atoi(row[gasProperty::rowsGas::number]);
		//--------------------------------------------------------------
		//--------------------------------------------------------------
		gasProperty::cGas::Gas[i].db		= atoi(row[gasProperty::rowsGas::db]);
		gasProperty::cGas::Gas[i].fuel		= atof(row[gasProperty::rowsGas::fuel]);
		gasProperty::cGas::Gas[i].maxX		= atof(row[gasProperty::rowsGas::maxX]);
		gasProperty::cGas::Gas[i].maxY		= atof(row[gasProperty::rowsGas::maxY]);
		gasProperty::cGas::Gas[i].maxZ		= atof(row[gasProperty::rowsGas::maxZ]);
		gasProperty::cGas::Gas[i].minX		= atof(row[gasProperty::rowsGas::minX]);
		gasProperty::cGas::Gas[i].minY		= atof(row[gasProperty::rowsGas::minY]);
		gasProperty::cGas::Gas[i].minZ		= atof(row[gasProperty::rowsGas::minZ]);
		gasProperty::cGas::Gas[i].cost		= atof(row[gasProperty::rowsGas::cost]);
		strcpy(gasProperty::cGas::Gas[i].name,  row[gasProperty::rowsGas::name]);

		Property[countProperty].link = i;
		//--------------------------------------------------------------
		if (Property[countProperty].owner)
		{
			strcpy(Property[countProperty].player, row[gasProperty::rowsGas::pname]);
			sprintf(query, "{FFFFFF}Заправка: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", gasProperty::cGas::Gas[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].player);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}Заправка: {FF0000}%s\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", gasProperty::cGas::Gas[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		//-----------------------------------------------------------------------------------------------------------
		Property[countProperty].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
			Property[countProperty].posX,
			Property[countProperty].posY,
			Property[countProperty].posZ, 30.0f);
		//-----------------------------------------------------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно заправок \t- %d", i);
}

void gasProperty::cGas::fillingVehicle(const int u)
{
	const int car = Player[u].pCarid;
	for (int i = 0; i < MAX_PROPERTY; i++)
	{
		if (Property[i].type == 5)
		{
			const int d = Property[i].link;

			if (world::Vehicles::isVehicleInCube(car, Gas[d].minX, Gas[d].minY, Gas[d].minZ, Gas[d].maxX, Gas[d].maxY, Gas[d].maxZ) && cPlayer::isPlayerInCube(u, Gas[d].minX, Gas[d].minY, Gas[d].minZ, Gas[d].maxX, Gas[d].maxY, Gas[d].maxZ))
			{
				thread(gasProperty::cGas::fillingVehicleProcess, u, i).detach();
				break;
			}
		}
	}
}

void gasProperty::cGas::fillingVehicleProcess(const int u, const int i)
{
	char msg[64];
	const int d = Property[i].link;
	const int car = Player[u].pCarid;
	const int tmpText = StreamerCall::Native::CreateDynamic3DTextLabel("Заправка", -1, 0.0f, 0.0f, 0.5f, 20.0f, 65535, car);

	cPlayer::givePlayerMoney(u, -Gas[i].cost * (100.0f - world::Vehicles::Vehicle[car].Fuel));

	case_filling:

	Sleep(1000);

	if (world::Vehicles::isVehicleInCube(car, Gas[d].minX, Gas[d].minY, Gas[d].minZ, Gas[d].maxX, Gas[d].maxY, Gas[d].maxZ))
	{
		if (world::Vehicles::Vehicle[car].Engine)
		{
			case_fillingCancel:
			StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, language::property::gas::fillingCancel);
			Sleep(5000);
			StreamerCall::Native::DestroyDynamic3DTextLabel(tmpText);
		}
		else
		{
			if (world::Vehicles::Vehicle[car].Fuel >= 100.0f)
			{
				world::Vehicles::Vehicle[car].Fuel = 100.0f;
				StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, language::property::gas::fillingDone);
				Sleep(5000);
				StreamerCall::Native::DestroyDynamic3DTextLabel(tmpText);
			}
			else
			{
				world::Vehicles::Vehicle[car].Fuel += ((0.0f + rand() % 250) / 100);
				sprintf(msg, language::property::gas::fillingProcess, world::Vehicles::Vehicle[car].Fuel);
				StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, msg);
				goto case_filling;
			}
		}
	}
	else
	{
		goto case_fillingCancel;
	}
}