#include "main.h"
PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int, int, int, int, const char*);


PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext)
{
	if (Player[ playerid ].isAction == PlayerAction::ACTION_NONE)
	{
		switch (dialogid)
		{
			case DLG_WELCOME:
			{
			case_welcome:
				char message[ 620 ];
				strcpy(message, "{078ad6}===========================================================\n");
				strcat(message, "{7d67dd}������������, ����������, ������� ��� ����� ����.\n");
				strcat(message, "�������� ����� �����, ���� � ��� ������ ��� ����.\n");
				strcat(message, "{FFFFFF}-{5c84e9}����� ����� ���� �� �������� ���������� �������� [A-Za-z]\n");
				strcat(message, "{FFFFFF}-{5c84e9}����� ����� ��� �� ��������� ����� [0-9] � ����. ������ _\n");
				strcat(message, "{FFFFFF}-{5c84e9}����� ������ ���� �� ������ 4 � �� ������ 16 ��������\n");
				strcat(message, "{FFFFFF}-{5c84e9}����� �� ������� ��� ����������� ����� � ����.\n");
				strcat(message, "{FFFFFF}-{5c84e9}����� �� �������� RP-�����.\n");
				strcat(message, "{078ad6}===========================================================\n");
				strcat(message, "\t\t{7d67dd}������������ � ��� ����� ������!");
				ShowPlayerDialog(playerid, DLG_LOGINFORM, GUI_INPUT, "[West-RP]: ����� �����������", message, "�����", "");
				break;
			}
			case DLG_LOGINFORM:
			{
				char message[ 700 ];
				//---------------------------------
				if (!regex_match(inputtext, expLogin)) goto case_welcome;
				//---------------------------------
				Player[ playerid ].pDB = cPlayer::checkLogin(inputtext);
				SetPlayerName(playerid, inputtext);
				if (Player[ playerid ].pDB == 0)
				{
					strcpy(Player[ playerid ].uLogin, inputtext);
				}
			case_login:
				if (Player[ playerid ].pDB)
				{
					strcpy(message, "{078ad6}===========================================================\n");
					strcat(message, "{7d67dd}�� ���� ����� ������ ��� �� ����� �������!\n");
					strcat(message, "����������, ������� ��� ������ ����.\n");
					strcat(message, "{078ad6}===========================================================\n");
					strcat(message, "{FFFFFF}-{5c84e9}�� ���������, ������ ������������ � ��������.\n");
					strcat(message, "{FFFFFF}-{5c84e9}������ qwerty � qWeRtY - ��� ������ ������!\n");
					strcat(message, "{078ad6}===========================================================");
				}
				else
				{
					strcpy(message, "{078ad6}===========================================================\n");
					strcat(message, "{7d67dd}�� ���� ������ ��� �� ����� �������!\n");
					strcat(message, "����������, ������� ��� ������ ����.\n");
					strcat(message, "{078ad6}===========================================================\n");
					strcat(message, "{FFFFFF}-{5c84e9}������ ����� ���� �� �������� ���������� �������� [A-Za-z]\n");
					strcat(message, "{FFFFFF}-{5c84e9}������ ����� ��� �� ��������� ����� [0-9] � ����. ������ _\n");
					strcat(message, "{FFFFFF}-{5c84e9}������ ������ ���� �� ������ 4 � �� ������ 16 ��������\n");
					strcat(message, "{FFFFFF}-{5c84e9}�� ���������, ������ ������������ � ��������.\n");
					strcat(message, "{FFFFFF}-{5c84e9}������ qwerty � qWeRtY - ��� ������ ������!\n");
					strcat(message, "{078ad6}===========================================================");
				}
				ShowPlayerDialog(playerid, DLG_AUTHPLAYER, GUI_INPUT, "[����������]: ����� �����������", message, "�����", "�����");
				break;
			}
			case DLG_AUTHPLAYER:
			{
				if (!response)							goto case_welcome;
				if (!regex_match(inputtext, expLogin))	goto case_login;
				//-----------------------------------------
				strcpy(Player[ playerid ].uPassw, inputtext);
				//-----------------------------------------
				cPlayer::camSelectChar(playerid);
				//-----------------------------------------
				if (Player[ playerid ].pDB)
				{
					if (!cPlayer::checkPass(Player[ playerid ].pDB, Player[ playerid ].uPassw))	goto case_login;
					if (cPlayer::loadChars(playerid))
						cPlayer::setRegClassSkin(playerid, 0);
					else	cPlayer::showCharMaker(playerid);
				}
				else
				{
					Player[ playerid ].pDB = cPlayer::regPlayer(Player[ playerid ].uLogin, Player[ playerid ].uPassw);
					cPlayer::showCharMaker(playerid);
				}
				break;
			}
			case DLG_REGISTER_NAME:
			{
				if (!response)		goto case_login;
				if (!regex_match(inputtext, expNames))				dialogs::showDLGEnterName(playerid);
				else
				{
					if (sscanf(inputtext, "%s %s", Player[ playerid ].uName, Player[ playerid ].sName) != 2)
						dialogs::showDLGEnterName(playerid);
					else	dialogs::showDLGEnterDate(playerid);
				}
				break;
			}
			case DLG_REGISTER_CRD:
			{
				if (!response)		goto case_login;
				if (!regex_match(inputtext, expDate))				dialogs::showDLGEnterDate(playerid);
				else
				{
					cPlayer::destRegDraws(playerid);
					strcpy(Player[ playerid ].pDate, inputtext);
					//-----------------------------------------
					Player[ playerid ].pDB = cPlayer::regChar(playerid);
					//-----------------------------------------
					Player[ playerid ].isAction = PlayerAction::ACTION_NONE;
					Player[ playerid ].isLogged = true;
					//-----------------------------------------
					cPlayer::SpawnChar(playerid);
				}
				break;
			}
			case DLG_VEHICLE_CONTROL: //Engine [%d]\nLights [%d]\nBoot [%d]\nBonnet [%d]
			{
				if (!response) return true;

				const int vehid = Player[ playerid ].pCarid;

				if (listitem == 0)
				{
					world::Vehicles::Vehicle[ vehid ].Engine = !world::Vehicles::Vehicle[ vehid ].Engine;
					SetVehicleParamsEx(vehid, world::Vehicles::Vehicle[ vehid ].Engine, world::Vehicles::Vehicle[ vehid ].Light, false, world::Vehicles::Vehicle[ vehid ].Locked, world::Vehicles::Vehicle[ vehid ].Bonnet, world::Vehicles::Vehicle[ vehid ].Boot, false);
				}
				else if (listitem == 1)
				{
					world::Vehicles::Vehicle[ vehid ].Light = !world::Vehicles::Vehicle[ vehid ].Light;
					SetVehicleParamsEx(vehid, world::Vehicles::Vehicle[ vehid ].Engine, world::Vehicles::Vehicle[ vehid ].Light, false, world::Vehicles::Vehicle[ vehid ].Locked, world::Vehicles::Vehicle[ vehid ].Bonnet, world::Vehicles::Vehicle[ vehid ].Boot, false);
				}
				else if (listitem == 2)
				{
					world::Vehicles::Vehicle[ vehid ].Boot = !world::Vehicles::Vehicle[ vehid ].Boot;
					SetVehicleParamsEx(vehid, world::Vehicles::Vehicle[ vehid ].Engine, world::Vehicles::Vehicle[ vehid ].Light, false, world::Vehicles::Vehicle[ vehid ].Locked, world::Vehicles::Vehicle[ vehid ].Bonnet, world::Vehicles::Vehicle[ vehid ].Boot, false);
				}
				else if (listitem == 3)
				{
					world::Vehicles::Vehicle[ vehid ].Bonnet = !world::Vehicles::Vehicle[ vehid ].Bonnet;
					SetVehicleParamsEx(vehid, world::Vehicles::Vehicle[ vehid ].Engine, world::Vehicles::Vehicle[ vehid ].Light, false, world::Vehicles::Vehicle[ vehid ].Locked, world::Vehicles::Vehicle[ vehid ].Bonnet, world::Vehicles::Vehicle[ vehid ].Boot, false);
				}
				else if (listitem == 4)
				{
					world::radio::cRadio::showRadioList(playerid);
					return true;
				}
				world::Vehicles::menuVehicle(playerid);
				break;
			}
			case DLG_RADIO_LIST:
			{
				if (!response) return true;

				const int vid = Player[playerid].pCarid;
				world::Vehicles::Vehicle[vid].radio = listitem;

				for (int i = 0; i < MAX_PLAYERS; i++)
				{
					if (Player[i].pSeatid != -1)
					{
						if (Player[i].pCarid == vid)
						{
							PlayAudioStreamForPlayer(playerid, world::radio::cRadio::Radio.at(listitem).url);
						}
					}
				}
				break;
			}
			case DLG_PROPERTY_BUY:
			{
				if (!response) return 1;
				int idx = Player[playerid].inIndex;
				if (cPlayer::checkMoney(playerid, Property[idx].price))
				{
					cProperty::setOwner(idx, playerid);
					cPlayer::givePlayerMoney(playerid, -Property[idx].price);
					cProperty::beforBuy(playerid);
				}
				break;
			}
		}
	}
	//---------------------------------------------------------------------------
	else if (Player[ playerid ].isAction == PlayerAction::ACTION_BANKBILL)
	{
		cBanks::onDLG(playerid, dialogid, response, listitem, inputtext);
	}
	//---------------------------------------------------------------------------
	else if (Player[ playerid ].isAction == PlayerAction::ACTION_AUTOSHOP)
	{
		Properties::Shops::ShopVehicle::onDLG(playerid, dialogid, response, listitem, inputtext);
	}
	//---------------------------------------------------------------------------
	else if (Player[playerid].isAction == PlayerAction::ACTION_USEPROP_GAS)
	{
		gasProperty::cGas::onDLG(playerid, dialogid, response, listitem, inputtext);
	}
	//---------------------------------------------------------------------------
	return true;
}

void dialogs::showDLGEnterDate(const int u)
{
	char message[800];
	//----------------------------------------------------------------------------------------------------------------
	strcpy(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}����������, ������� ���� �������� ��������� ����\n");
	strcat(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}����������: ������� ���� � ������� ��.��.����");
	//----------------------------------------------------------------------------------------------------------------
	ShowPlayerDialog(u, DLG_REGISTER_CRD, GUI_INPUT, "[West-RP]: ����������� ����������", message, "�����", "������");
}

void dialogs::showDLGEnterName(const int u)
{
	char message[800];
	//----------------------------------------------------------------------------------------------------------------
	strcpy(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}����������, ������� ���� ��� � ������� ����.\n");
	strcat(message, "{FFFFFF}-{B7FF00}��� � ������� ������ ���� ��������� ��������\n");
	strcat(message, "{FFFFFF}-{B7FF00}��� � ������� ����� ��������� ��������� ������� [A-Za-z]\n");
	strcat(message, "{FFFFFF}-{B7FF00}��� � ������� ����� ��������� ������������ ������� [�-��-�]\n");
	strcat(message, "{FFFFFF}-{B7FF00}���, ��� � ������� ������ ���������� � ��������� �����\n");
	strcat(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}��������:{B7FF00} ������� �������, Alex West");
	//----------------------------------------------------------------------------------------------------------------
	ShowPlayerDialog(u, DLG_REGISTER_NAME, GUI_INPUT, "[West-RP]: ����������� ����������", message, "�����", "������");
}

void dialogs::genDLGItem(const int i, const char str[], char *res)
{
	char line[ 80 ];
	sprintf(line, "{FFFFFF}[{84ecff}%d{FFFFFF}] {84ecff}%s\n", i, str);
	strcat(res, line);
}