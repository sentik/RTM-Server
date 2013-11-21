#pragma once


#ifndef __dialogs__   
#define __dialogs__   
enum DIALOG_LIST
{
	DLG_NILL = -1,
	DLG_NONE = 0,
	DLG_WELCOME,				// Диалог приветствия
	DLG_LOGINFORM,				// Диалог формы ввода пароля
	DLG_AUTHPLAYER,				// Диалог формы авторизации
	DLG_REGISTER_NAME,			// Диалог
	DLG_REGISTER_CRD,			// Диалог
	DLG_PROPERTY_BUY,
	DLG_BABK_MAKE_ACC,
	DLG_VEHICLE_CONTROL,
	DLG_MAIN_MENU
};

enum DIALOG_STYLYS
{
	GUI_MSG,		// Диалог с сообщением
	GUI_INPUT,		// Диалог с формой для ввода
	GUI_LIST,		// Диалог со списком
	GUI_PASS,		// Диалог с формой для ввода пароля
};

class dialogs
{
public:
	static void dialogs::showDLGEnterName(const int);
	static void dialogs::showDLGEnterDate(const int);
	static void dialogs::genDLGItem(const int i, const char str[ ], char *);
};

#endif 