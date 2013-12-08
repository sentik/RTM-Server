#include "main.h"

std::vector<eRadio> world::radio::cRadio::Radio;

void world::radio::cRadio::loadRadio()
{
	int i = 0;
	MYSQL_ROW row;
	MYSQL_RES *result;
	mysql_query(con, "SELECT * FROM class_Radio ORDER BY id");
	result = mysql_store_result(con);

	while (row = mysql_fetch_row(result))
	{
		eRadio tmp;
		tmp.db = atoi(row[0]);
		strcpy(tmp.name, row[1]);
		strcpy(tmp.url, row[2]);

		Radio.insert(Radio.end(), tmp);

		i++;
	}

	mysql_free_result(result);
	logprintf("\t\t%d Loaded radio's", i);
}

void world::radio::cRadio::showRadioList(const int u)
{
	char msg[256];
	int i = 1;
	strcpy(msg, "");
	for (auto id = Radio.begin(); id != Radio.end(); id++)
	{
		sprintf(msg, "%s[%d]\t-\t%s\n", msg, i, id->name);
		i++;
	}
	ShowPlayerDialog(u, DLG_RADIO_LIST, GUI_LIST, "Радиостанции", msg, "Select", "Cancel");
}