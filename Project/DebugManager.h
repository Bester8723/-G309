/*************************************************************************//*!

					@file	DebugManager.h
					@brief	デバッグフラグ管理。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
class CDebugManager {
private:
	bool		m_bDebug;			//デバッグフラグ

	CDebugManager() : m_bDebug(false) {}
	~CDebugManager() {}
public:
	void SetDebugFlg(bool flg) { m_bDebug = flg; }
	bool GetDebugFlg() { return m_bDebug; }

	/// <summary>
	/// シングルトンインスタンスを取得するための唯一のアクセス
	/// </summary>
	static CDebugManager& Instance()
	{
		static CDebugManager obj;
		return obj;
	}
};