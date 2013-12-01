#ifdef DEFAULT_RUSSIAN


/*
����� ������� �� 30.11.2013:
1. ������� ��������� �������� �� ������ (���� �� �������)   !!!
2. ������� ��������� (�������� ���� �� �������)				!!!
3. �������� 24x7 ( ����� ���� ��� ������� ������)			???
4. ������������ ( ���������� � ����������� �������)			!!!
5. ������� ������ ��� ����									!!!
6. ������� ������ ��� ����									!!!
7. ������� �������� ���� �� ��������.						!!!
8. ������� ��������������� � �����������					???
==============================
*������� ������������:
1. ���������� ������������									!!!
2. ������� ������� ��������									?!?
3. ��������� ������� ������� �� C++							?!?
4. ������� ���������� ���������� (���������� ���)			???
*/


namespace language
{
	namespace dropGuns
	{
		const char logLoaded[ 48 ] = "���� ���������� %d ������";
	}

	namespace player
	{
		namespace admin
		{
			const char noPermision[80]		= "{FF0000}������: {FFFFFF}�� �� ������ ��������������� ������������� ������: %s";
		}

		namespace cmd
		{
			const char useVeh[64]			= "�����������: /veh [������] (����������� [���� 1] [���� 2])";
		}
	}

	namespace property
	{

		


		namespace shop
		{
			namespace vehicle
			{
				const char header_Buy[ 32 ] = "[���������] :: ������� ����";
				const char action_Buy[ 128 ] = "������������, %s %s, �� ������������ ������ ������ %s �� %d$ ?";
			}
		}

		namespace bank
		{
			const char Header_Acc_MAKE[32]	 = "[����] ��������� �����";
			const char Header_Acc_BILL[ 32 ] = "[����] ���������� �������";


			
			//----------------------------------------------------------------------------
			const char percentHeader[48]	= "[����]: ���������� � ���������";
			const char percentCredit[64]	= "�������� �� ��������: \t\t%0.1f%%\n";
			const char percentSend[64]		= "�������� �� ���������:  \t\t%0.1f%%\n";
			const char percentDeposi[64]	= "�������� �� �������:  \t\t%0.1f%%\n";
			const char percentPay[64]		= "�������� �� ������:  \t\t\t%0.1f%%\n";
			//----------------------------------------------------------------------------
			const char Acc_Make[144]		= "������������, %s %s, ���������� ������� ���-���.\n���-��� ����� �������� �� 4 �� 8 ����.\n��������, 787898 ��� 020190";
		}
	}

	namespace jobs
	{
		namespace miner
		{
			const char actionOne[ 96 ]		= "�� ������: {B700FF}%d {FFFFFF}����� ������, ����� {B700FF}%d{FFFFFF} �����";
			const char actionTwo[ 96 ]		= "�� ������: {B700FF}%d {FFFFFF}����� �������, ����� {B700FF}%d{FFFFFF} �����";
			const char actionThree[ 96 ]	= "�� ������: {B700FF}%d {FFFFFF}����� ����, ����� {B700FF}%d{FFFFFF} �����";
			const char actionFour[ 96 ]		= "�� ������: {B700FF}%d {FFFFFF}����� ������, ����� {B700FF}%d{FFFFFF} �����";
			//----------------------------------------------------------------------------
			const char disActionOne[ 96 ]	= "�� �������:{FF0000} %d {FFFFFF}����� ������, ����� {FF0000}%d{FFFFFF} �����";
			const char disActionTwo[ 96 ]	= "�� �������:{FF0000} %d {FFFFFF}����� �������, ����� {FF0000}%d{FFFFFF} �����";
			const char disActionThree[ 96 ] = "�� �������:{FF0000} %d {FFFFFF}����� ����, ����� {FF0000}%d{FFFFFF} �����";
			const char disActionFour[ 96 ]	= "�� �������:{FF0000} %d {FFFFFF}����� ������, ����� {FF0000}%d{FFFFFF} �����";
			//----------------------------------------------------------------------------
			const char otherAction[32]		= "�� ������: {FFAF00}������";
			//----------------------------------------------------------------------------
			const char tableSH1[176]		= "����������\n��������� ������ ������: {B700FF}%.2f$\n{FFFFFF}��������� ������ �������: {B700FF}%.2f$\n{FFFFFF}�����\n������ �����: {B700FF}%d\n{FFFFFF}������� �����: {B700FF}%d";
			const char tableSH2[176]		= "����������\n��������� ������ ����: {B700FF}%.2f$\n{FFFFFF}��������� ������ ������: {B700FF}%.2f$\n{FFFFFF}�����\n���� �����: {B700FF}%d\n{FFFFFF}������ �����: {B700FF}%d";
		}

		namespace feller
		{
			const char actionOne[96]		= "�� �������: {FF0000}%d {FFFFFF}������ ���������, ����� {FF0000}%d {FFFFFF}������";
			const char actionTwo[96]		= "�� ������: {B7FF00}%d {FFFFFF}������ ���������, ����� {B7FF00}%d {FFFFFF}������";
			const char actionThree[32]		= "�� ������: {FFAF00}������";
			const char actionFour[48]		= "�� ����������: {FF0000}-%.2f {FFFFFF}��������";
			//----------------------------------------------------------------------------
			const char preActionOne[56]		= "�� ��������� �������� ������ ({B7FF00}������{FFFFFF})";
			const char preActionTwo[56]		= "�� ��������� �������� ������ ({B70000}��������{FFFFFF})";
		}
	}
}



#endif