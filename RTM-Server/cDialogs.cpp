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
			strcat(message, "{FFFFFF}Здравствуйте, пожалуйста, укажите ваш логин ниже.\n");
			strcat(message, "Создайте новый логин, если у вас сейчас его нету.\n");
			strcat(message, "{FFFFFF}-{B7FF00}Логин может быть из символов латинского алфавита [A-Za-z]\n");
			strcat(message, "{FFFFFF}-{B7FF00}Логин может так же содержать цифры [0-9] и спец. символ _\n");
			strcat(message, "{FFFFFF}-{B7FF00}Логин должен быть не короче 4 и не длинее 16 символов\n");
			strcat(message, "{FFFFFF}-{B7FF00}Логин не обходим для дальнейшего входа в игру.\n");
			strcat(message, "{FFFFFF}-{B7FF00}Логин не является RP-ником.\n");
			strcat(message, "{FFAF00}===========================================================\n");
			strcat(message, "\t\t{B7FF00}Присоеденись к нам прямо сейчас!");
			ShowPlayerDialog(playerid, DLG_LOGINFORM, GUI_INPUT, "[West-RP]: Форма авторизации", message, "Войти", "");
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
				strcat(message, "{00DDFF}Мы рады вновь видеть вас на нашем сервере!\n");
				strcat(message, "Пожалуйста, укажите ваш пароль ниже.\n");
				strcat(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}-{00DDFF}Не забывайте, пароль чувствителен к регистру.\n");
				strcat(message, "{FFFFFF}-{00DDFF}Пароли qwerty и qWeRtY - это разные пароли!\n");
				strcat(message, "{FFAF00}===========================================================");
			}
			else
			{
				strcpy(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}Мы рады видеть вас на нашем сервере!\n");
				strcat(message, "Пожалуйста, укажите ваш пароль ниже.\n");
				strcat(message, "{FFAF00}===========================================================\n");
				strcat(message, "{FFFFFF}-{B7FF00}Пароль может быть из символов латинского алфавита [A-Za-z]\n");
				strcat(message, "{FFFFFF}-{B7FF00}Пароль может так же содержать цифры [0-9] и спец. символ _\n");
				strcat(message, "{FFFFFF}-{B7FF00}Пароль должен быть не короче 4 и не длинее 16 символов\n");
				strcat(message, "{FFFFFF}-{B7FF00}Не забывайте, пароль чувствителен к регистру.\n");
				strcat(message, "{FFFFFF}-{B7FF00}Пароли qwerty и qWeRtY - это разные пароли!\n");
				strcat(message, "{FFAF00}===========================================================");
			}
			ShowPlayerDialog(playerid, DLG_AUTHPLAYER, GUI_INPUT, "[Информация]: Форма авторизации", message, "Войти", "Назад");
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
		case DLG_PROPERTY_BUY:
		{
			if (!response) return 1;
			int idx = Player[ playerid ].inIndex;
			if (cPlayer::checkMoney(playerid, Property[ idx ].price))
			{
				cProperty::setOwner(idx, Player[ playerid ].pDB);
				cPlayer::givePlayerMoney(playerid, -Property[ idx ].price);
				cProperty::beforBuy(playerid);
			}
			break;
		}
		case DLG_VEHICLE_CONTROL: //Engine [%d]\nLights [%d]\nBoot [%d]\nBonnet [%d]
		{
			#define vehid Player[playerid].pCarid
			if (!response) return true;
			if (listitem == 0)
			{
				Vehicle[vehid].Engine = !Vehicle[vehid].Engine;
				SetVehicleParamsEx(vehid, Vehicle[vehid].Engine, Vehicle[vehid].Light, false, Vehicle[vehid].Locked, Vehicle[vehid].Bonnet, Vehicle[vehid].Boot, false);
			}
			else if (listitem == 1)
			{
				Vehicle[vehid].Light = !Vehicle[vehid].Light;
				SetVehicleParamsEx(vehid, Vehicle[vehid].Engine, Vehicle[vehid].Light, false, Vehicle[vehid].Locked, Vehicle[vehid].Bonnet, Vehicle[vehid].Boot, false);
			}
			else if (listitem == 2)
			{
				Vehicle[vehid].Boot = !Vehicle[vehid].Boot;
				SetVehicleParamsEx(vehid, Vehicle[vehid].Engine, Vehicle[vehid].Light, false, Vehicle[vehid].Locked, Vehicle[vehid].Bonnet, Vehicle[vehid].Boot, false);
			}
			else if (listitem == 3)
			{
				Vehicle[vehid].Bonnet = !Vehicle[vehid].Bonnet;
				SetVehicleParamsEx(vehid, Vehicle[vehid].Engine, Vehicle[vehid].Light, false, Vehicle[vehid].Locked, Vehicle[vehid].Bonnet, Vehicle[vehid].Boot, false);
			}
			cVehicle::menuVehicle(playerid);
			#undef vehid
		}
	}
	return true;
}

void dialogs::showDLGEnterDate(const int u)
{
	char message[800];
	//----------------------------------------------------------------------------------------------------------------
	strcpy(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}Пожалуйста, укажите дату рождения персонажа ниже\n");
	strcat(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}Примечание: укажите дату в формате ДД.ММ.ГГГГ");
	//----------------------------------------------------------------------------------------------------------------
	ShowPlayerDialog(u, DLG_REGISTER_CRD, GUI_INPUT, "[West-RP]: Регистрация перосанажа", message, "Далее", "Отмена");
}

void dialogs::showDLGEnterName(const int u)
{
	char message[800];
	//----------------------------------------------------------------------------------------------------------------
	strcpy(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}Пожалуйста, укажите ваше имя и фамилию ниже.\n");
	strcat(message, "{FFFFFF}-{B7FF00}Имя и фамилия должны быть разделены пробелом\n");
	strcat(message, "{FFFFFF}-{B7FF00}Имя и фамилия могут содержать латинские символы [A-Za-z]\n");
	strcat(message, "{FFFFFF}-{B7FF00}Имя и фамилия могут содержать кирилические символы [А-Яа-я]\n");
	strcat(message, "{FFFFFF}-{B7FF00}Имя, как и фамилия должны начинаться с заглавной буквы\n");
	strcat(message, "{FFAF00}===========================================================\n");
	strcat(message, "{FFFFFF}Например:{B7FF00} Дмитрий Донской, Alex West");
	//----------------------------------------------------------------------------------------------------------------
	ShowPlayerDialog(u, DLG_REGISTER_NAME, GUI_INPUT, "[West-RP]: Регистрация перосанажа", message, "Далее", "Отмена");
}

void dialogs::genDLGItem(const int i, const char str[], char *res)
{
	char line[ 80 ];
	sprintf(line, "{FFFFFF}[{990099}%d{FFFFFF}] {990099}%s\n", i, str);
	strcat(res, line);
}