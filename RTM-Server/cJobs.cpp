#include "main.h"

bool cPlayer::Jobs::cJobs::isInJob(const int u, const int j)
{
	if (Player[u].pJob1 == j)
		return true;
	else if (Player[u].pJob2 == j)
		return true;
	return false;
}

bool cPlayer::Jobs::cJobs::setJob(const int u, const int j)
{
	if (Player[u].pJob1 == cPlayer::Jobs::PlayerJob::JOB_NONE)
	{
		Player[u].pJob1 = j;
		return true;
	}
	else if (Player[u].pJob2 == cPlayer::Jobs::PlayerJob::JOB_NONE)
	{
		Player[u].pJob2 = j;
		return true;
	}
	return false;
}

void cPlayer::Jobs::cJobs::showDLG(const int u)
{
	char msg[128] = "";
	dialogs::genDLGItem(1, "��������", msg, "FFAF00");
	dialogs::genDLGItem(2, "������ �����", msg, "FFAF00");
	ShowPlayerDialog(u, DLG_JOB_MAIN, GUI_LIST, "����� �����", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnClose);
	Player[u].isAction = PlayerAction::ACTION_USEJOBSDLG;
}

void cPlayer::Jobs::cJobs::onDLG(const int u, const int dialogid, const int response, const int listitem, const char * inputtext)
{
	char msg[256] = "";

	switch (dialogid)
	{
		case DIALOG_LIST::DLG_JOB_MAIN:
		{
			if (response)
			{
				if ( listitem == 0 )
				{
					dialogs::genDLGItem(1, language::jobs::general::jobList[Player[u].pJob1], msg, "FFAF00");
					dialogs::genDLGItem(2, language::jobs::general::jobList[Player[u].pJob2], msg, "FFAF00");
					ShowPlayerDialog(u, DLG_JOB_LEAVE, GUI_LIST, "�������� �:", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else
				{
					for ( int i = 1; i < (sizeof( language::jobs::general::jobList) / sizeof(language::jobs::general::jobList[0])); i++ )
					{
						dialogs::genDLGItem(i, language::jobs::general::jobList[i], msg, "FFAF00");
					}
					ShowPlayerDialog(u, DLG_JOB_LIST, GUI_LIST, "��������� ��:", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DIALOG_LIST::DLG_JOB_LIST:
		{
			if ( response )
			{
				if ( cPlayer::Jobs::cJobs::setJob(u, listitem + 1) )
				{
					sprintf(msg, "{B7FF00}����������: {FFFFFF}����������� �� ���������� �� ������: %s", language::jobs::general::jobList[listitem+1]);
					SendClientMessage(u, -1, msg);
				}
				else
				{
					SendClientMessage(u, -1, "{FF0000}������: {FFFFFF}�� ������� ��������� �� ������.");
				}
			}
			cPlayer::Jobs::cJobs::showDLG(u);
			break;
		}
		case DIALOG_LIST::DLG_JOB_LEAVE:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
					Player[u].pJob1 = cPlayer::Jobs::PlayerJob::JOB_NONE;
				}
				else
				{
					Player[u].pJob2 = cPlayer::Jobs::PlayerJob::JOB_NONE;
				}
				SendClientMessage(u, -1, "{B7FF00}����������: {FFFFFF}�� ������� ��������� � ������.");
			}
			cPlayer::Jobs::cJobs::showDLG(u);
			break;
		}
	}
}
