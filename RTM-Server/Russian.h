#ifdef DEFAULT_RUSSIAN



namespace language
{
	namespace dropGuns
	{
		const char logLoaded[ 48 ] = "���� ���������� %d ������";
	}

	namespace player
	{
		namespace actions
		{
			const char tryMSG[ 2 ][ 128 ] = { "* %s �������� %s (������)", "* %s �������� %s (��������)" };
			const char tryBuble[ 2 ][ 128 ] = { "* �������� %s (������)", "* �������� %s (��������)" };

			const char shoutMSG[ 128 ]		=  "{FFFFFF}%s ������[ {FF0000}%d {FFFFFF} ]: {FADBB8}%s" ;
			const char whisperMSG[ 128 ]	=  "{FFFFFF}%s ������[ {FF0000}%d {FFFFFF} ]: {FADBB8}%s";
		}


		namespace admin
		{
			const char noPermision[80]		= "{FF0000}������: {FFFFFF}�� �� ������ ��������������� ������������� ������: %s";
		}

		namespace cmd
		{
			const char useVeh[64]			= "�����������: /veh [������] (����������� [���� 1] [���� 2])";
		}
	}

	namespace gang
	{
		const char stat_Name[ 64 ] = "�������� �����: \t\t\t %s\n";
		const char stat_RepLS[ 64 ] = "��������� � LS: \t\t\t %d/%d\n";
		const char stat_RepSF[ 64 ] = "��������� � SF: \t\t\t %d/%d\n";
		const char stat_RepLV[ 64 ] = "��������� � LV: \t\t\t %d/%d\n";

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
			const char percentHeader[32]	= "[����]: ���������� � ���������";
			const char percentCredit[64]	= "{FFFFFF}�������� �� ��������: {84ecff}\t\t%0.1f%%\n";
			const char percentSend[64]		= "{FFFFFF}�������� �� ���������:{84ecff}\t\t%0.1f%%\n";
			const char percentDeposi[64]	= "{FFFFFF}�������� �� �������:  {84ecff}\t\t%0.1f%%\n";
			const char percentPay[64]		= "{FFFFFF}�������� �� ������:   {84ecff}\t\t%0.1f%%\n";
			//----------------------------------------------------------------------------
			const char Acc_Make[176]		= "{FFFFFF}������������ {84ecff}%s %s, {FFFFFF}���������� ������� ���-���.\n���-��� ����� �������� �� 4 �� 8 ����.\n��������: {84ecff}787898 {FFFFFF}��� {84ecff}020190";
			const char afterMake[88]		= "{FFFFFF}��� ����� �����: {84ecff}%d\n{FFFFFF}��� ���-���: {84ecff}%d";
			const char enterCode[64]		= "{FFFFFF}������� ��� ���-��� ��� ������: {84ecff}%d";
			const char afterTake[64]		= "{FFFFFF}�����:{84ecff}\t\t%.2f$\n{FFFFFF}��������:{84ecff}\t%.2f$";
			const char afterPay[48]			= "{FFFFFF}��������� ��:{84ecff}\t%.2f$";
			const char startTransfer[128]	= "{FFFFFF}������� ����� �������� � ����� ����� ����� ������.\n������� ������: {84ecff}%.2f$\n\n{FFFFFF}������: {84ecff}15.56 1";
			const char afterTransfer[80]	= "{FFFFFF}�����������:{84ecff}\t%0.2f$\n{FFFFFF}��������:{84ecff}\t%.2f$";
		}

		namespace gas
		{
			const char fillingDone[32]		= "{B7FF00}��������� ���������";
			const char fillingProcess[32]	= "������� � ����: {B700FF}%.2fL";
			const char fillingCancel[32]	= "{B70000}��������� �����������";
		}
	}

	namespace jobs
	{
		namespace general
		{
			const char jobList[3][10]		= { "���", "�����", "�������" };
		}
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

	namespace dialogs
	{
		namespace buttons
		{
			const char btnOK[8]				= "������";
			const char btnNext[8]			= "�����";
			const char btnBack[8]			= "�����";
			const char btnDone[8]			= "������";
			const char btnClose[8]			= "�������";
			const char btnCancel[8]			= "������";
			const char btnSelect[8]			= "�������";
		}
	}
}



#endif