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
	char msg[ 336 ];
	sprintf(msg, "{FFFFFF}�����������, �� ������������� ������ ���������� ��� ������������?\n�����: {00C0FF}%s {FFFFFF}�: {00C0FF}%d {FFFFFF}|| ���������: {00C0FF}%d${FFFFFF}",
				 cProperty::getZoneName(Property[p].region), Property[p].number, Property[p].price);
	//===============================================
	Player[ u ].inIndex = p;
	//===============================================
	switch (Property[p].type)
	{
		//------------------------------------------
		case PropertyType::prHouse:		//����
		{
									sprintf(msg, "%s || ���: {00C0FF}���", msg);
									break;
		}
		case PropertyType::prBank:		//�����
		{
									sprintf(msg, "%s || ���: {00C0FF}����", msg);
									break;
		}
		case PropertyType::prGas:		//��������
		{
									sprintf(msg, "%s || ���: {00C0FF}��������", msg);
									break;
		}
		case PropertyType::prAutosalon:	//����������
		{
									sprintf(msg, "%s || ���: {00C0FF}���������", msg);
									break;
		}
		case PropertyType::prMiner:		//�����
		{
									sprintf(msg, "%s || ���: {00C0FF}�����", msg);
									break;
		}
		case PropertyType::prFeller:	//���������
		{
									sprintf(msg, "%s || ���: {00C0FF}���������", msg);
									break;
		}
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
	if (Property[ p ].status == 0 && Property[ p ].owner == 0)	cProperty::buyMessage(u, p);
}


void cProperty::setOwner(const int p, const int owner)
{
	Property[p].owner = Player[owner].pDB;
	sprintf(query, "UPDATE class_Property SET owner = '%d' WHERE id = %d", Property[p].owner, Property[p].db);
	safe_query(con, query); 

	switch (Property[p].type)
	{
		case PropertyType::prHouse:		//����
		{
										cHouses::updateText(p, owner);
										break;
		}
		case PropertyType::prBank:		//�����
		{
										cBanks::updateText(p, owner);
										break;
		}
		case PropertyType::prAutosalon:	//����������
		{
										Properties::Shops::ShopVehicle::updateText(p, owner);
										break;
		}
		case PropertyType::prGas:		//��������
		{
										gasProperty::cGas::updateText(p, owner);
										break;
		}
		case PropertyType::prMiner:		//�����
		{
										Jobs::Miner::cMiner::updateText(p, owner);
										break;
		}
		case PropertyType::prFeller:	//���������
		{
										fProperty::cFeller::updateText(p, owner);
										break;
		}
	}
}


void cProperty::setStatus(const int p, const int status)
{
	Property[ p ].status = status;
	sprintf(query, "UPDATE class_Property SET status = '%d' WHERE id = %d", status, Property[ p ].db);
	safe_query(con, query);
}



/// <summary>
/// �������� ����� � ������������
/// <param name="u">* �� ������</param>
/// </summary>
/*
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
				else
				{
					Player[u].inIndex = i;

					if (Property[ i ].type == PropertyType::prGas) //��������
					{
						if (Property[ i ].owner == Player[ u ].pDB)
						{
							gasProperty::cGas::ownerMenu(u);
						}
						break;
					}
					else if (Property[ i ].type == PropertyType::prFeller)
					{
						if (Property[ i ].owner == Player[ u ].pDB)
								fProperty::cFeller::ownerMenu(u);
						else	fProperty::cFeller::clientMenu(u);
						break;
					}
					
					/*
					switch (Property[i].type)
					{
						case PropertyType::prHouse:		//����
						{
															goto enterToInterior;
															break;
						}
						case PropertyType::prBank:		//�����
						{
															goto enterToInterior;
															break;
						}
						case PropertyType::prAutosalon:	//����������
						{
															//Properties::Shops::ShopVehicle::updateText(p, owner);
															break;
						}
						case PropertyType::prGas:		//��������
						{
															if (Property[i].owner == Player[u].pDB)
															{
																gasProperty::cGas::ownerMenu(u);
															}
															break;
						}
						case PropertyType::prMiner:		//�����
						{
															//Jobs::Miner::cMiner::updateText(p, owner);
															break;
						}
						case PropertyType::prFeller:	//���������
						{
															if (Property[i].owner == Player[u].pDB)
															{
																fProperty::cFeller::ownerMenu(u);
															}
															else
															{
																fProperty::cFeller::clientMenu(u);
															}
															break;
						}
					}
					
					
				}
	enterToInterior:
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
		//	if (Player[ u ].pPosW != i) continue;	//���� ����� �� � ������ ����
			//--------------------------------------------------------------------
			if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ))
			{
				cPlayer::setCharPos(u, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ, false);
				cPlayer::setCharInterior(u, 0);
				cPlayer::setCharWorld(u, 0);
				cPlayer::setCharAngle(u, 0);
			}
			//--------------------------------------------------------------------
			else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].actX, Interior[ idx ].actY, Interior[ idx ].actZ))
			{
				cProperty::doAct(u);
			}
			//--------------------------------------------------------------------
			else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].subX, Interior[ idx ].subY, Interior[ idx ].subZ))
			{
				cProperty::doSub(u);
			}
		}

	

}
*/


void cProperty::enterProperty(const int u)
{
	for (int i = 0; i < countProperty; i++)
	{
		const int idx = Property[ i ].style;
		//-------------------------------------------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ))
		{
			Player[u].inIndex = i;
			//����� ��������� ���������
			if (Property[ i ].owner==0)
			{
				cProperty::statusMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			if (Property[ i ].type == PropertyType::prGas) //��������
			{
				if (Property[ i ].owner == Player[ u ].pDB)
				{
					gasProperty::cGas::ownerMenu(u);
				}
				break;
			}
			else if (Property[ i ].type == PropertyType::prFeller)
			{
				if (Property[ i ].owner == Player[ u ].pDB)
					fProperty::cFeller::ownerMenu(u);
				else	fProperty::cFeller::clientMenu(u);
				break;
			}
			else if (Property[ i ].type == PropertyType::prMiner)
			{
				Jobs::Miner::cMiner::showDLG(u);
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
		else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].actX, Interior[ idx ].actY, Interior[ idx ].actZ))
		{
			cProperty::doAct(u);
		}
		//--------------------------------------------------------------------
		else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].subX, Interior[ idx ].subY, Interior[ idx ].subZ))
		{
			cProperty::doSub(u);
		}
	}

}

void cProperty::doAct(int u)
{
	const int idx = Player[ u ].inIndex;
	switch (Property[idx].type)
	{
		//----------------------------------------
		case 2:	//����. ���������
		{
			cBanks::actStuff(u);
		}
		break;
		//----------------------------------------
	}
}

void cProperty::doSub(int u)
{
	const int idx = Player[ u ].inIndex;
	switch (Property[ idx ].type)
	{
		//----------------------------------------
		case PropertyType::prBank:	//����. ���������� ������
		{
			cBanks::actBill(u);
		}
		break;
		//----------------------------------------
		case PropertyType::prAutosalon:
		{
			Properties::Shops::ShopVehicle::preView(u);
		}
		break;
		//----------------------------------------
		case PropertyType::prBelays:
		{
			Properties::Belays::onAction(u);
		}
		break;
		//----------------------------------------
	}
}