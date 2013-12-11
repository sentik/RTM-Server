#pragma once


#ifndef __dialogs__   
#define __dialogs__   
enum DIALOG_LIST
{
	DLG_NILL = -1,
	DLG_NONE = 0,
	DLG_WELCOME,				// ������ �����������
	DLG_LOGINFORM,				// ������ ����� ����� ������
	DLG_AUTHPLAYER,				// ������ ����� �����������
	DLG_REGISTER_NAME,			// ������
	DLG_REGISTER_CRD,			// ������
	DLG_PROPERTY_BUY,
	DLG_BABK_MAKE_ACC,
	DLG_VEHICLE_CONTROL,
	DLG_MAIN_MENU,
	DLG_BANK_BILLING,
	DLG_BANK_PERCENT,
	DLG_BANK_SELECTACC,
	DLG_BANK_SELECTPASS,
	DLG_BANK_ACC_BILLING,
	DLG_BANK_EMTY2,
	DLG_BANK_TAKE,
	DLG_BANK_PAY,
	DLG_BANK_TRANS,
	DLG_VEHICLE_BUY,
	DLG_VEHICLE_PAY,
	DLG_RADIO_LIST,
	DLG_GAS_MAIN,
	DLG_GAS_EMTY,
	DLG_GAS_CTRL,
	DLG_GAS_CTRL_COST,
	DLG_GAS_CTRL_NAME,
	DLG_GAS_CTRL_BANK,
	DLG_GANG_MAKE_INTRO,
	DLG_GANG_MAKE_NAME,
	DLG_GANG_MAKE_COLOR,
	DLG_GANG_MAKE_PRE_PROPERTY,
	DLG_GANG_MAKE_PROPERTY,
};

enum DIALOG_STYLYS
{
	GUI_MSG,		// ������ � ����������
	GUI_INPUT,		// ������ � ������ ��� �����
	GUI_LIST,		// ������ �� �������
	GUI_PASS,		// ������ � ������ ��� ����� ������
};

class dialogs
{
public:
	static void dialogs::showDLGEnterName(const int);
	static void dialogs::showDLGEnterDate(const int);
	static void dialogs::genDLGItem(const int i, const char str[ ], char *);
};

#endif 