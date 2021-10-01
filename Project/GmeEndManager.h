/*************************************************************************//*!

					@file	GameEndManager.h
					@brief	ゲーム終了管理。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CGmeEndManager {
private:
	bool		m_bGameEnd;			//ゲーム終了フラグ
	int			m_GameEndNo;		//ゲーム終了条件番号

	CGmeEndManager();
	~CGmeEndManager();
public:
	void SetGameEndCondition(int endNo);
	int GetGameEndCondition() { return m_GameEndNo; }
	bool IsGameEnd() { return m_bGameEnd; }

	/// <summary>
	/// シングルトンインスタンスを取得するための唯一のアクセス
	/// </summary>
	static CGmeEndManager& Instance()
	{
		static CGmeEndManager obj;
		return obj;
	}
};