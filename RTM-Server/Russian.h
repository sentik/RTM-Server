#ifdef DEFAULT_RUSSIAN



namespace language
{
	namespace dropGuns
	{
		const char logLoaded[ 48 ] = "Было загруженно %d оружий";
	}

	namespace player
	{
		namespace admin
		{
			const char noPermision[80]		= "{FF0000}Ошибка: {FFFFFF}Вы не можете воспользоваться возможностями группы: %s";
		}
	}

	namespace property
	{
		namespace bank
		{
			const char Header_Acc_MAKE[32]	= "[Банк] Заведение счета";
			//----------------------------------------------------------------------------
			const char percentHeader[48]	= "[Банк]: Информация о процентах";
			const char percentCredit[64]	= "Проценты по кредитам: \t\t%0.1f%%\n";
			const char percentSend[64]		= "Проценты по переводам:  \t\t%0.1f%%\n";
			const char percentDeposi[64]	= "Проценты по вкладам:  \t\t%0.1f%%\n";
			const char percentPay[64]		= "Проценты по оплате:  \t\t\t%0.1f%%\n";
			//----------------------------------------------------------------------------
			const char Acc_Make[144]		= "Здравствуйте, %s %s, пожалуйста укажите Пин-Код.\nПин-код может состоять от 4 до 8 цифр.\nНапример, 787898 или 020190";
		}
	}

	namespace jobs
	{
		namespace miner
		{
			const char actionOne[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм железа, всего { B700FF }%d { FFFFFF } грамм";
			const char actionTwo[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм серебра, всего {B700FF}%d{FFFFFF} грамм";
			const char actionThree[ 96 ]	= "Вы добыли: {B700FF}%d {FFFFFF}грамм меди, всего {B700FF}%d{FFFFFF} грамм";
			const char actionFour[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм золота, всего {B700FF}%d{FFFFFF} грамм";
			//----------------------------------------------------------------------------
			const char disActionOne[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм железа, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionTwo[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм серебра, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionThree[ 96 ] = "Вы уронили:{FF0000} %d {FFFFFF}грамм меди, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionFour[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм золота, всего {FF0000}%d{FFFFFF} грамм";
			//----------------------------------------------------------------------------
			const char otherAction[26]		= "Вы добыли: {FFAF00}воздух";
			//----------------------------------------------------------------------------
			const char tableSH1[175]		= "Информация\nСтоимость грамма железа: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма серебра: {B700FF}%.2f$\n{FFFFFF}Склад\nЖелеза грамм: {B700FF}%d\n{FFFFFF}Серебра грамм: {B700FF}%d";
			const char tableSH2[175]		= "Информация\nСтоимость грамма меди: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма золота: {B700FF}%.2f$\n{FFFFFF}Склад\nМеди грамм: {B700FF}%d\n{FFFFFF}Золота грамм: {B700FF}%d";
		}
	}
}



#endif