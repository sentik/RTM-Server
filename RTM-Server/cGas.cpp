#include "main.h"

struct eGas  gasProperty::cGas::Gas[MAX_GAS];
std::mutex gasProperty::fillingVehicle;

void gasProperty::cGas::loadGas()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	cProperty::propertyLoadQuery(PropertyType::prGas);
	//safe_query(con, "SELECT class_Property.*, class_Gas.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Gas  WHERE class_Property.property = class_Gas.id AND class_Property.type = 5");
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
			sprintf(query, "{FFFFFF}��������: {B7FF00}%s\n{FFFFFF}�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s\n{FFFFFF}��������� �����: {B7FF00}%.2f", gasProperty::cGas::Gas[i].name, getSaZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].player, Gas[i].cost);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}��������: {FF0000}%s\n{FFFFFF}�����: {FF0000}%s {FFFFFF}�: {FF0000}%d\n{FFFFFF}���������: {FF0000}%d$", gasProperty::cGas::Gas[i].name, getSaZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
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
	logprintf("[������� ���������]: \t���� ���������� �������� \t- %d", i);
}

void gasProperty::cGas::saveGas()
{
	for (int i = 0; i < MAX_GAS; i++)
	{
		if (Gas[i].db == 0) continue;
		char msg[128];
		sprintf(msg, "UPDATE class_Gas SET fuel = %.2f, name = '%s', cost = %.2f WHERE id = %d", Gas[i].fuel, Gas[i].name, Gas[i].cost, Gas[i].db);
		safe_query(con, msg);
	}
}

void gasProperty::cGas::fillingVehicle(const int u)
{
	const int car = Player[u].status.vehicle;
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
	gasProperty::fillingVehicle.lock();

	char msg[64];
	const int d = Property[i].link;
	const int car = Player[u].status.vehicle;
	const float cost = Gas[d].cost * (100.0f - world::Vehicles::Vehicle[car].Fuel);
	const int tmpText = world::Vehicles::Vehicle[car].text3D;
	float fuel;

	StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, "��������");

	cPlayer::givePlayerMoney(u, -cost);
	cBanks::giveBalance(Property[i].bank, cost);

	gasProperty::fillingVehicle.unlock();

	case_filling:

	std::this_thread::sleep_for(std::chrono::seconds(1));

	gasProperty::fillingVehicle.lock();

	if (world::Vehicles::isVehicleInCube(car, Gas[d].minX, Gas[d].minY, Gas[d].minZ, Gas[d].maxX, Gas[d].maxY, Gas[d].maxZ))
	{
		if (world::Vehicles::Vehicle[car].Engine)
		{
			case_fillingCancel:
			StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, language::property::gas::fillingCancel);
			std::this_thread::sleep_for(std::chrono::seconds(5));
			StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, "");
		}
		else
		{
			if (world::Vehicles::Vehicle[car].Fuel >= 100.0f)
			{
				world::Vehicles::Vehicle[car].Fuel = 100.0f;
				StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, language::property::gas::fillingDone);
				std::this_thread::sleep_for(std::chrono::seconds(5));
				StreamerCall::Native::UpdateDynamic3DTextLabelText(tmpText, -1, "");
			}
			else
			{
				fuel = ((0.0f + rand() % 250) / 100);
				world::Vehicles::Vehicle[car].Fuel += fuel;
				Gas[d].fuel -= fuel;
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

	gasProperty::fillingVehicle.unlock();
}

void gasProperty::cGas::updateText(const int p, const int u = -1)
{
	char msg[256];
	if(u != -1) sprintf(Property[p].player, "%s %s", Player[u].strings.uName, Player[u].strings.sName);
	sprintf(msg, "{FFFFFF}��������: {B7FF00}%s\n{FFFFFF}�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s\n{FFFFFF}��������� �����: {B7FF00}%.2f", gasProperty::cGas::Gas[Property[p].link].name, getSaZoneName(Property[p].region), Property[p].number, Property[p].player, gasProperty::cGas::Gas[Property[p].link].cost);
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Property[p].text, -1, msg);
}

void gasProperty::cGas::ownerMenu(const int u)
{
	char msg[128] = "";
	dialogs::genDLGItem(1, "����������", msg);
	dialogs::genDLGItem(2, "����������", msg);
	ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_MAIN, GUI_LIST, gasProperty::cGas::Gas[Property[Player[u].status.inIndex].link].name, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnCancel);
	Player[u].status.action = PlayerAction::ACTION_USEPROP_GAS;
}

void gasProperty::cGas::onDLG(const int u, const int dialogid, const int response, const int listitem, const char* inputtext)
{
	char msg[256] = "";
	const int p = Player[u].status.inIndex;
	const int l = Property[p].link;

	switch (dialogid)
	{
		case DIALOG_LIST::DLG_GAS_MAIN:
		{
			if (response)
			{
				if (listitem == 0)
				{
					sprintf(msg, "{FFFFFF}��������: {00C0FF}%s\n{FFFFFF}�����: {00C0FF}%s {FFFFFF}�: {00C0FF}%d\n{FFFFFF}� �����: {00C0FF}%d\n{FFFFFF}���-�� �������: {00C0FF}%.2fL\n{FFFFFF}��������� �����:{00C0FF} %.2f$",
								 Gas[l].name, getSaZoneName(Property[p].region), Property[p].number, Property[p].bank, Gas[l].fuel, Gas[l].cost);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_EMTY, GUI_MSG, Gas[l].name, msg, language::dialogs::buttons::btnBack, "");
				}
				else
				{
	case_ctrldialog:
					dialogs::genDLGItem(1, "����", msg);
					dialogs::genDLGItem(2, "��������", msg);
					dialogs::genDLGItem(3, "����� �����", msg);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_CTRL, GUI_LIST, Gas[l].name, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Player[u].status.action = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DIALOG_LIST::DLG_GAS_EMTY:
		{
	case_maindialog:
			gasProperty::cGas::ownerMenu(u);
			break;
		}
		case DIALOG_LIST::DLG_GAS_CTRL:
		{
			if (response)
			{
				if (listitem == 0)
				{
	case_costdialog:
					sprintf(msg, "{FFFFFF}������� ���� �� ���� �������.\n������� ����: {00C0FF}%.2f$", Gas[l].cost);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_CTRL_COST, GUI_INPUT, Gas[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 1)
				{
	case_namedialog:
					sprintf(msg, "{FFFFFF}������� �������� ��������.\n������� ��������: {00C0FF}%s", Gas[l].name);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_CTRL_NAME, GUI_INPUT, Gas[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)
				{
	case_bankdialog:
					sprintf(msg, "{FFFFFF}������� ����� ����������� �����.\n������� ����: {00C0FF}%d", Property[p].bank);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_CTRL_BANK, GUI_INPUT, Gas[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
goto case_maindialog;
			}
			break;
		}
		case DIALOG_LIST::DLG_GAS_CTRL_COST:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					Gas[l].cost = atof(inputtext);
					gasProperty::cGas::updateText(p);
					sprintf(msg, "{FFFFFF}���� ����������: {00C0FF}%.2f$", Gas[l].cost);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_EMTY, GUI_MSG, Gas[l].name, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_costdialog;
				}
			}
			else
			{
goto case_ctrldialog;
			}
			break;
		}
		case DIALOG_LIST::DLG_GAS_CTRL_NAME:
		{
			if (response)
			{
				if (regex_match(inputtext, expString))
				{
					strcpy(Gas[l].name, inputtext);
					gasProperty::cGas::updateText(p);
					sprintf(msg, "{FFFFFF}�������� ����������: {00C0FF}%s", Gas[l].name);
					ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_EMTY, GUI_MSG, Gas[l].name, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_namedialog;
				}
			}
			else
			{
goto case_ctrldialog;
			}
			break;
		}
		case DIALOG_LIST::DLG_GAS_CTRL_BANK:
		{
			if (response)
			{
				if (regex_match(inputtext, expNumber))
				{
					const int number = atoi(inputtext);

					if (cBanks::isValidNumber(number))
					{
						Property[p].bank = number;
						sprintf(msg, "{FFFFFF}����� ����� ����������: {00C0FF}%d", number);
						ShowPlayerDialog(u, DIALOG_LIST::DLG_GAS_EMTY, GUI_MSG, Gas[l].name, msg, language::dialogs::buttons::btnOK, "");
					}
					else
					{
goto case_bankdialog;
					}
				}
				else
				{
goto case_bankdialog;
				}
			}
			else
			{
goto case_ctrldialog;
			}
			break;
		}
	}
}