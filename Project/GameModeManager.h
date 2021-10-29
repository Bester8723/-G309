/*************************************************************************//*!

					@file	GameModeManager.h
					@brief	ゲームモード管理。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CGameModeManager {
private:
	int					m_PlayModeNo;			//遊ぶモード番号

	CGameModeManager();
	~CGameModeManager();
public:
	void SetPlayMode(int no) { m_PlayModeNo = no; }
	int GetPlayMode() { return m_PlayModeNo; }

	/// <summary>
	/// シングルトンインスタンスを取得するための唯一のアクセス
	/// </summary>
	static CGameModeManager& Instance()
	{
		static CGameModeManager obj;
		return obj;
	}
};