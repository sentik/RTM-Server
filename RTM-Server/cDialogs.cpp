#include "main.h"
PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int, int, int, int, const char*);


PLUGIN_EXPORT bool PLUGIN_CALL OnDialogResponse(int playerid, int dialogid, int response, int listitem, const char* inputtext)
{
	switch (dialogid)
	{
		case DLG_WELCOME:
		{
		case_welcome:
			char message[620];
			strcpy(message, "{FFAF00}===========================================================\n");
			strcat(message, "{FFFFFF}������������, ����������, ������� ��� ����� ����.\n");
			strcat(message, "�������� ����� �����, ���� � ��� ������ ��� ����.\n");
			strcat(message, "{FFFFFF}-{B7FF00}����� ����� ���� �� �������� ���������� �������� [A-Za-z]\n");
			strcat(message, "{FFFFFF}-{B7FF00}����� ����� ��� �� ��������� ����� [0-9] � ����. ������ _\n");
			strcat(message, "{FFFFFF}-{B7FF00}����� ������ ���� �� ������ 4 � �� ������ 16 ��������\n");
			strcat(message, "{FFFFFF}-{B7FF00}����� �� ������� ��� ����������� ����� � ����.\n");
			strcat(message, "{FFFFFF}-{B7FF00}����� �� �������� RP-�����.\n");
			strcat(message, "{FFAF00}===========================================================\n");
			strcat(message, "\t\t{B7FF00}������������ � ��� ����� ������!");
			ShowPlayerDialog(playerid, DLG_LOGINFORM, GUI_INPUT, "[West-RP]: ����� �����������", message, "�����", "");
			break;
		}
		case DLG_LOGINFORM:
		{
			char message[700];
			//---------------------------------
			if (!regex_match(inputtext, expLogin)) goto case_welcome;
			//---------------------------------
			Player[playerid].pDB = cPlayer::checkLogin(inputtext);
			if (Player[playerid].pDB == 0)
			{
				strcpy(Player[playerid].uLogin, inputtext);
			}
			case_login:
			if (Player[playerid].pDB)
			{
				strcpy(message, "{FFAF00}===========================================================\n");
				strcat(message, "{00DDFF}�� ���� ����� ������ ��� �� ����� �������!\n");
				strcat(message, "����������, ������� ��� ������ ����.\n");
				strcat(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}-{00DDFF}�� ���������, ������ ������������ � ��������.\n");
				strcat(message, "{FFFFFF}-{00DDFF}������ qwerty � qWeRtY - ��� ������ ������!\n");
				strcat(message, "{FFAF00}===========================================================");
			}
			else
			{
				strcpy(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}�� ���� ������ ��� �� ����� �������!\n");
				strcat(message, "����������, ������� ��� ������ ����.\n");
				strcat(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}-{B7FF00}������ ����� ���� �� �������� ���������� �������� [A-Za-z]\n");
				strcat(message, "{FFFFFF}-{B7FF00}������ ����� ��� �� ��������� ����� [0-9] � ����. ������ _\n");
				strcat(message, "{FFFFFF}-{B7FF00}������ ������ ���� �� ������ 4 � �� ������ 16 ��������\n");
				strcat(message, "{FFFFFF}-{B7FF00}�� ���������, ������ ������������ � ��������.\n");
				strcat(message, "{FFFFFF}-{B7FF00}������ qwerty � qWeRtY - ��� ������ ������!\n");
				strcat(message, "{FFAF00}===========================================================");
			}
			ShowPlayerDialog(playerid, DLG_AUTHPLAYER, GUI_INPUT, "[����������]: ����� �����������", message, "�����", "�����");
			break;
		}
		case DLG_AUTHPLAYER:
		{
			if (!response)							goto case_welcome;
			if (!regex_match(inputtext, expLogin))	goto case_login;
			//-----------------------------------------
			strcpy(Player[playerid].uPassw, inputtext);
			//-----------------------------------------
			cPlayer::camSelectChar(playerid);
			//-----------------------------------------
			if (Player[playerid].pDB)
			{
				if (!cPlayer::checkPass(Player[playerid].pDB, Player[playerid].uPassw))	goto case_login;
				if (cPlayer::loadChars(playerid))
					cPlayer::setRegClassSkin(playerid, 0);
				else	cPlayer::showCharMaker(playerid);
			}
			else
			{
				Player[playerid].pDB = cPlayer::regPlayer(Player[playerid].uLogin, Player[playerid].uPassw);
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
				if (sscanf(inputtext, "%s %s", Player[playerid].uName, Player[playerid].sName) != 2)
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

				strcpy(Player[playerid].pDate, inputtext);
				//-----------------------------------------
				cPlayer::regChar(playerid);
				//-----------------------------------------
				Player[playerid].isAction = PlayerAction::ACTION_NONE;
				Player[playerid].isLogged = true;
				//-----------------------------------------
				cPlayer::SpawnChar(playerid);
			}
		}
	}
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