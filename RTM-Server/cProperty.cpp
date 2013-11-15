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
	sprintf(query, "");


}


/// <summary>
/// ��������� ������� ������������
/// <param name="u">* �� ������</param>
/// <param name="p">* �� ������������</param>
/// </summary>
void cProperty::statusMessage(const int u, const int p)
{

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
