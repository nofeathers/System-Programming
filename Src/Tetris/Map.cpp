#include "pch.h"
#include "Map.h"

void CMap::Clear(void)
{
	m_nPosX = 0; /*블록 좌표 x*/
	m_nPosY = 0; /*블록 좌표 y*/

	memcpy(m_szMapData[0], "**            **", 16 + 1);
	memcpy(m_szMapData[1], "**            **", 16 + 1);
	memcpy(m_szMapData[2], "**            **", 16 + 1);
	memcpy(m_szMapData[3], "**            **", 16 + 1);
	memcpy(m_szMapData[4], "**            **", 16 + 1);
	memcpy(m_szMapData[5], "**            **", 16 + 1);
	memcpy(m_szMapData[6], "**            **", 16 + 1);
	memcpy(m_szMapData[7], "**            **", 16 + 1);
	memcpy(m_szMapData[8], "**            **", 16 + 1);
	memcpy(m_szMapData[9], "**            **", 16 + 1);
	memcpy(m_szMapData[10], "**            **", 16 + 1);
	memcpy(m_szMapData[11], "**            **", 16 + 1);
	memcpy(m_szMapData[12], "**            **", 16 + 1);
	memcpy(m_szMapData[13], "**            **", 16 + 1);
	memcpy(m_szMapData[14], "**            **", 16 + 1);
	memcpy(m_szMapData[15], "**            **", 16 + 1);
	memcpy(m_szMapData[16], "**            **", 16 + 1);
	memcpy(m_szMapData[17], "**            **", 16 + 1);
	memcpy(m_szMapData[18], "****************", 16 + 1);
	memcpy(m_szMapData[19], "****************", 16 + 1);
}

bool CMap::IsCollide(const CTetrimino* pTetrimino) const /* 블록 충동 검사 */
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (pTetrimino->GetBlock(pTetrimino->GetRotation(), y, x) == ' ')
				continue;

			int nMapX = pTetrimino->GetPosX() + x;
			int nMapY = pTetrimino->GetPosY() + y;

			if (nMapX < 0 || nMapX >= g_nMapWidth || nMapY < 0 || nMapY >= g_nMapHeight)
				return true;

			if (m_szMapData[nMapY][nMapX] != ' ')
				return true;
		}
	}
	return false;
}

void CMap::Pile(const CTetrimino* pTetrimino) /* 바닥 검사 및 줄 완성 검사 */
{
	const int nPosX = pTetrimino->GetPosX();
	const int nPosY = pTetrimino->GetPosY();
	const int nRotation = pTetrimino->GetRotation();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			const char block = pTetrimino->GetBlock(nRotation, i, j);
			if (block != ' ')
			{
				const int nMapX = nPosX + j;
				const int nMapY = nPosY + i;

				if (nMapX >= 0 && nMapX < g_nMapWidth && nMapY >= 0 && nMapY < g_nMapHeight - 2)
				{
					m_szMapData[nMapY][nMapX] = block;
				}
			}
		}
	}
	for (int i = g_nMapHeight - 3; i >= 0; i--)
	{
		bool bLineComplete = true;
		for (int j = 2; j < g_nMapWidth - 2; j++)
		{
			if (m_szMapData[i][j] == ' ')
			{
				bLineComplete = false;
				break;
			}
		}
		if (bLineComplete)
		{
			for (int moveY = i; moveY > 0; moveY--)
			{
				for (int j = 2; j < g_nMapWidth - 2; j++)
				{
					m_szMapData[moveY][j] = m_szMapData[moveY - 1][j];
				}
			}

			for (int j = 2; j < g_nMapWidth - 2; j++)
			{
				m_szMapData[0][j] = ' ';
			}
			i++;
		}
	}
}

void CMap::OnDraw(CRenderer* pRenderer)
{
	for (int i = 0; i < g_nMapHeight; i++)
		pRenderer->Draw(m_nPosX, m_nPosY + i, m_szMapData[i], g_nMapWidth);
}