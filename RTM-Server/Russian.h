#ifdef DEFAULT_RUSSIAN



namespace language
{
	namespace dropGuns
	{
		const char logLoaded[ 48 ] = "Было загруженно %d оружий";
	}

	namespace player
	{
		namespace actions
		{
			const char tryMSG[ 2 ][ 128 ] = { "* %s пытается %s (Удачно)", "* %s пытается %s (Неудачно)" };
			const char tryBuble[ 2 ][ 128 ] = { "* пытается %s (Удачно)", "* пытается %s (Неудачно)" };

			const char shoutMSG[ 128 ]		=  "{FFFFFF}%s кричит[ {FF0000}%d {FFFFFF} ]: {FADBB8}%s" ;
			const char whisperMSG[ 128 ]	=  "{FFFFFF}%s шепчет[ {FF0000}%d {FFFFFF} ]: {FADBB8}%s";
		}


		namespace admin
		{
			const char noPermision[80]		= "{FF0000}Ошибка: {FFFFFF}Вы не можете воспользоваться возможностями группы: %s";
		}

		namespace cmd
		{
			const char useVeh[64]			= "Используйте: /veh [модель] (опционально [цвет 1] [цвет 2])";
		}
	}

	namespace gang
	{
		const char stat_Name[ 64 ] = "Название банды: \t\t\t %s\n";
		const char stat_RepLS[ 64 ] = "Репутация в LS: \t\t\t %d/%d\n";
		const char stat_RepSF[ 64 ] = "Репутация в SF: \t\t\t %d/%d\n";
		const char stat_RepLV[ 64 ] = "Репутация в LV: \t\t\t %d/%d\n";

	}


	namespace property
	{

		


		namespace shop
		{
			namespace vehicle
			{
				const char header_Buy[ 32 ] = "[Автосалон] :: Покупка авто";
				const char action_Buy[ 128 ] = "Здравствуйте, %s %s, вы дейтвительно хотите купить %s за %d$ ?";
			}
		}

		namespace bank
		{
			const char Header_Acc_MAKE[32]	 = "[Банк] Заведение счета";
			const char Header_Acc_BILL[ 32 ] = "[Банк] Управление счетами";
			//----------------------------------------------------------------------------
			const char percentHeader[32]	= "[Банк]: Информация о процентах";
			const char percentCredit[64]	= "{FFFFFF}Проценты по кредитам: {84ecff}\t\t%0.1f%%\n";
			const char percentSend[64]		= "{FFFFFF}Проценты по переводам:{84ecff}\t\t%0.1f%%\n";
			const char percentDeposi[64]	= "{FFFFFF}Проценты по вкладам:  {84ecff}\t\t%0.1f%%\n";
			const char percentPay[64]		= "{FFFFFF}Проценты по оплате:   {84ecff}\t\t%0.1f%%\n";
			//----------------------------------------------------------------------------
			const char Acc_Make[176]		= "{FFFFFF}Здравствуйте {84ecff}%s %s, {FFFFFF}пожалуйста укажите Пин-Код.\nПин-код может состоять от 4 до 8 цифр.\nНапример: {84ecff}787898 {FFFFFF}или {84ecff}020190";
			const char afterMake[88]		= "{FFFFFF}Ваш номер счёта: {84ecff}%d\n{FFFFFF}Ваш пин-код: {84ecff}%d";
			const char enterCode[64]		= "{FFFFFF}Введите ваш пин-код для номера: {84ecff}%d";
			const char afterTake[64]		= "{FFFFFF}Снято:{84ecff}\t\t%.2f$\n{FFFFFF}Комиссия:{84ecff}\t%.2f$";
			const char afterPay[48]			= "{FFFFFF}Пополнено на:{84ecff}\t%.2f$";
			const char startTransfer[128]	= "{FFFFFF}Введите сумму перевода и номер счёта через пробел.\nТекущей баланс: {84ecff}%.2f$\n\n{FFFFFF}Пример: {84ecff}15.56 1";
			const char afterTransfer[80]	= "{FFFFFF}Переведенно:{84ecff}\t%0.2f$\n{FFFFFF}Комиссия:{84ecff}\t%.2f$";
		}

		namespace gas
		{
			const char fillingDone[32]		= "{B7FF00}транспорт заправлен";
			const char fillingProcess[32]	= "Топливо в баке: {B700FF}%.2fL";
			const char fillingCancel[32]	= "{B70000}остановка заправления";
		}
	}

	namespace jobs
	{
		namespace general
		{
			const char jobList[3][10]		= { "Нет", "Щахтёр", "Лесоруб" };
		}
		namespace miner
		{
			const char actionOne[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм железа, всего {B700FF}%d{FFFFFF} грамм";
			const char actionTwo[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм серебра, всего {B700FF}%d{FFFFFF} грамм";
			const char actionThree[ 96 ]	= "Вы добыли: {B700FF}%d {FFFFFF}грамм меди, всего {B700FF}%d{FFFFFF} грамм";
			const char actionFour[ 96 ]		= "Вы добыли: {B700FF}%d {FFFFFF}грамм золота, всего {B700FF}%d{FFFFFF} грамм";
			//----------------------------------------------------------------------------
			const char disActionOne[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм железа, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionTwo[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм серебра, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionThree[ 96 ] = "Вы уронили:{FF0000} %d {FFFFFF}грамм меди, всего {FF0000}%d{FFFFFF} грамм";
			const char disActionFour[ 96 ]	= "Вы уронили:{FF0000} %d {FFFFFF}грамм золота, всего {FF0000}%d{FFFFFF} грамм";
			//----------------------------------------------------------------------------
			const char otherAction[32]		= "Вы добыли: {FFAF00}воздух";
			//----------------------------------------------------------------------------
			const char tableSH1[176]		= "Информация\nСтоимость грамма железа: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма серебра: {B700FF}%.2f$\n{FFFFFF}Склад\nЖелеза грамм: {B700FF}%d\n{FFFFFF}Серебра грамм: {B700FF}%d";
			const char tableSH2[176]		= "Информация\nСтоимость грамма меди: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма золота: {B700FF}%.2f$\n{FFFFFF}Склад\nМеди грамм: {B700FF}%d\n{FFFFFF}Золота грамм: {B700FF}%d";
		}

		namespace feller
		{
			const char actionOne[96]		= "Вы уронили: {FF0000}%d {FFFFFF}единиц древесины, всего {FF0000}%d {FFFFFF}единиц";
			const char actionTwo[96]		= "Вы добыли: {B7FF00}%d {FFFFFF}единиц древесины, всего {B7FF00}%d {FFFFFF}единиц";
			const char actionThree[32]		= "Вы добыли: {FFAF00}воздух";
			const char actionFour[48]		= "Вы поранились: {FF0000}-%.2f {FFFFFF}здоровья";
			//----------------------------------------------------------------------------
			const char preActionOne[56]		= "Вы пытаетесь повалить дерево ({B7FF00}Удачно{FFFFFF})";
			const char preActionTwo[56]		= "Вы пытаетесь повалить дерево ({B70000}Неудачно{FFFFFF})";
		}
	}

	namespace dialogs
	{
		namespace buttons
		{
			const char btnOK[8]				= "Хорошо";
			const char btnNext[8]			= "Далее";
			const char btnBack[8]			= "Назад";
			const char btnDone[8]			= "Готово";
			const char btnClose[8]			= "Закрыть";
			const char btnCancel[8]			= "Отмена";
			const char btnSelect[8]			= "Выбрать";
		}
	}
}



#endif