#include "main.h"

//------------------------------
std::vector<eAdmins> world::Players::Admins::Admin;
//------------------------------


char world::Players::Admins::Ranks[ 5 ][ 16 ] = {
	{ "Помошник"},	{ "Мл. Модератор" },	
	{ "Модератор" },{ "Адмиминистратор" },	
	{ "Основатель" }};

/// <summary>
/// Загрузить список администраторов
/// </summary>
void world::Players::Admins::init()
{
	int i = 0;
	MYSQL_ROW row;
	Admin.reserve(32);
	safe_query(con, "SELECT * FROM player_Admins WHERE asses > 0");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		eAdmins tmp;
		//----------------------------
		tmp.db		= atoi(row[ 0 ]);
		tmp.player	= atoi(row[ 1 ]);
		tmp.asses	= atoi(row[ 2 ]);
		//----------------------------
		Admin.insert(Admin.end(), tmp);
	}
	logprintf("Было загруженно %d администраторов", mysql_num_rows(result));
	mysql_free_result(result);
}

/// <summary>
/// Удалить игрока из адмимистраторов
/// <param name="u">* Ид игрока</param>
/// </summary>
void world::Players::Admins::del(int u)
{
	const int db = Player[ u ].pDB;
	for (auto it = Admin.begin(); it != Admin.end(); it++)
	{
		if (it->player == db)
		{
			sprintf(query, "DELETE FROM player_Admins WHERE id='%d'", it->db);
			safe_query(con, query);
			Admin.erase(it);
		}
	}
}

/// <summary>
/// Добавить игрока в адмимистраторы
/// <param name="u">* Ид игрока</param>
/// <param name="a">* Уровень доступа</param>
/// </summary>
void world::Players::Admins::add(int u, int a)
{
	eAdmins tmp;
	const int db = Player[ u ].pDB;
	//-----------------------------
	sprintf(query, "REPLACE INTO player_Admins SET player=%d, asses=%d", db, a), safe_query(con, query);
	//-----------------------------
	tmp.db = mysql_insert_id(con);
	tmp.player = db;
	tmp.asses = a;
	//-----------------------------
	Admin.insert(Admin.end(), tmp);
}

/// <summary>
/// Проверить уровень доступа
/// <param name="u">* Ид игрока</param>
/// <param name="a">* Уровень доступа</param>
/// </summary>
bool world::Players::Admins::isAsses(int u, int a)
{
	const int db = Player[ u ].pDB;
	if (IsPlayerAdmin(u)) return true;
	for (auto it = Admin.begin(); it != Admin.end(); it++)
	{
		if (it->player == db)
		if (it->asses >= a)
		{
			sprintf(query, "req: %d/%d", a, it->asses);
			SendClientMessage(u, -1, query);
			return true;
		}
				
	}
	return false;
}

bool world::Players::Admins::isAllow(int u, int a)
{
	char msg[ 144 ];
	if (isAsses(u, a)) return true;
	a = clamp(a, 0, 4);
	sprintf(msg, language::player::admin::noPermision, Ranks[ a ]);
	SendClientMessage(u, -1, msg);
	return false;
}

/// <summary>
/// Является ли игрок администратором
/// <param name="u">* Ид игрока</param>
/// </summary>
bool world::Players::Admins::isAdmin(int u)
{
	const int db = Player[ u ].pDB;
	for (auto it = Admin.begin(); it != Admin.end(); it++)
	{
		if (it->player == db)
			return true;
	}
	return false;
}
