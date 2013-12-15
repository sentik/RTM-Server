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
	DLG_MAIN_MENU,
	//--------------------------] Banks client dialogs
	DLG_BANK_BILLING,
	DLG_BANK_PERCENT,
	DLG_BANK_SELECTACC,
	DLG_BANK_SELECTPASS,
	DLG_BANK_ACC_BILLING,
	DLG_BANK_EMTY2,
	DLG_BANK_TAKE,
	DLG_BANK_PAY,
	DLG_BANK_TRANS,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//--------------------------] Banks owner dialogs
	DLG_BANKOWNER_MAIN,
	DLG_BANKOWNER_PERCENTS,
	DLG_BANKOWNER_PERCENTS_SET,
	DLG_BANKOWNER_SETNAME,
	DLG_BANKOWNER_MONEY,
	DLG_BANKOWNER_MONEY_PAY,
	DLG_BANKOWNER_MONEY_DEP,
	DLG_BANKOWNER_EMTY,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//--------------------------] Feller owner dialogs
	DLG_FELLEROWNER_MAIN,
	DLG_FELLEROWNER_SETNAME,
	DLG_FELLEROWNER_COSTS,
	DLG_FELLEROWNER_COSTS_EMTY,
	DLG_FELLEROWNER_COSTS_ZP,
	DLG_FELLEROWNER_COSTS_BN,
	DLG_FELLEROWNER_COSTS_MN,
	DLG_FELLEROWNER_COSTS_MN_PAY,
	DLG_FELLEROWNER_COSTS_MN_DEP,
	DLG_FELLEROWNER_EMTY,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//--------------------------] Feller client dialogs
	DLG_FELLER_MAIN,
	DLG_FELLER_MONEY,
	DLG_FELLER_MONEYBANK,
	DLG_FELLER_EMTY,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	DLG_VEHICLE_BUY,
	DLG_VEHICLE_PAY,
	DLG_RADIO_LIST,
	//--------------------------] Gas owner dialogs
	DLG_GAS_MAIN,
	DLG_GAS_EMTY,
	DLG_GAS_CTRL,
	DLG_GAS_CTRL_COST,
	DLG_GAS_CTRL_NAME,
	DLG_GAS_CTRL_BANK,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
	//--------------------------] Gang system dialogs
	DLG_GANG_MAKE_INTRO,
	DLG_GANG_MAKE_NAME,
	DLG_GANG_MAKE_COLOR,
	DLG_GANG_MAKE_PRE_PROPERTY,
	DLG_GANG_MAKE_PROPERTY,
	DLG_GANG_MENU_MAIN,
	//^^^^^^^^^^^^^^^^^^^^^^^^^^
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