#include "main.h"

struct sProperty		Property	[ MAX_PROPERTY ] = { { 0, 0 } };
int countProperty;

/// <summary>
/// ��������� ������� ������������
/// <param name="u">* �� ������</param>
/// <param name="p">* �� ������������</param>
/// </summary>
void cProperty::buyMessage(const int u, const int p)
{
	char msg[ 512 ];
	//===============================================
	Player[ u ].inIndex = p;
	//===============================================
	switch (Property[p].type)
	{
		//------------------------------------------
		case 1:	//����
		{
			sprintf(msg, "������������, �� ����������� ������ ���������� ���� ���?\n����� ����: %s %d\n��������� �������: %d$", 
					"nill", 0, Property[p].price);
		}
		break;
		//------------------------------------------
	}
	ShowPlayerDialog(u, DLG_PROPERTY_BUY, GUI_MSG, "������� ������������", msg, "�����", "������");
}


/// <summary>
/// ��������� ����� ������� ������������
/// <param name="u">* �� ������</param>
/// </summary>
void cProperty::beforBuy(const int u)
{
	char msg[ 600 ];
	strcpy(msg, "============================================ \n");
	strcat(msg, "\t����������� ��� � �������� ������������.	  \n");
	strcat(msg, "============================================ \n");
	strcat(msg, "������ 24 ���� �� ������ �������� ���������, \n");
	strcat(msg, "������� ���������� ������������ ��������!    \n");
	strcat(msg, "��������� ����� �������� � ����� ��� ���������\n");
	strcat(msg, "============================================  \n");
	strcat(msg, "����� ��������, �� ������ ������ �� ������    \n");
	strcat(msg, "��� ���������� ������ ������� /mm -> ���������\n");
	strcat(msg, "============================================  \n");
	strcat(msg, "\t����� ��������, ������ �������� ���� !");
	ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "[����������]", msg, "�������", "");
}


/// <summary>
/// ��������� ������� ������������
/// <param name="u">* �� ������</param>
/// <param name="p">* �� ������������</param>
/// </summary>
void cProperty::statusMessage(const int u, const int p)
{

}


void cProperty::setOwner(const int p, const int owner)
{
	Property[ p ].owner = owner;
	sprintf(query, "UPDATE class_Property SET owner = '%d' WHERE id = %d", owner, Property[ p ].db);
	mysql_query(con, query); 
}


void cProperty::setStatus(const int p, const int status)
{
	Property[ p ].status = status;
	sprintf(query, "UPDATE class_Property SET status = '%d' WHERE id = %d", status, Property[ p ].db);
	mysql_query(con, query);
}



/// <summary>
/// �������� ����� � ������������
/// <param name="u">* �� ������</param>
/// </summary>
void cProperty::enterProperty(const int u)
{
	for (int i = 0; i < countProperty; i++)
	{
		const int idx = Property[ i ].style;
		//-----------------------------------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ))
		{
			if (!Property[ i ].owner)
			{
				cProperty::buyMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			if (Property[ i ].status)
			{
				cProperty::statusMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			cPlayer::setCharPos(u, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ, true);
			cPlayer::setCharInterior(u, Interior[ idx ].posI);
			cPlayer::setCharAngle(u, Interior[ idx ].posR);
			cPlayer::setCharWorld(u, i);
			//-----------------------------------------------------------------------------------------------
			break;
		}
		//--------------------------------------------------------------------
		if (Player[ u ].pPosW != i) continue;	//���� ����� �� � ������ ����
		//--------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ))
		{
			cPlayer::setCharPos(u, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ, false);
			cPlayer::setCharInterior(u, 0);
			cPlayer::setCharWorld(u, 0);
			cPlayer::setCharAngle(u, 0);
		}
		//--------------------------------------------------------------------
	}
}
