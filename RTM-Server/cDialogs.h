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
	DLG_MAIN_MENU
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