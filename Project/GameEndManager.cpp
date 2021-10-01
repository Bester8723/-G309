/*************************************************************************//*!

					@file	GameEndManager.cpp
					@brief	ゲーム終了管理。

															@author	池上　綾香
*//**************************************************************************/
#include "GameEndManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
CGameEndManager::CGameEndManager() :
m_bGameEnd(false),
m_GameEndNo(0) {
}

/// <summary>
/// デストラクタ
/// </summary>
CGameEndManager::~CGameEndManager() {
}

/// <summary>
/// ゲーム終了条件を設定
/// </summary>
/// <param name="endNo">終了番号</param>
void CGameEndManager::SetGameEndCondition(int endNo) {
	m_GameEndNo = endNo;
	m_bGameEnd = true;
}