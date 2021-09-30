/*************************************************************************//*!

					@file	DebugManager.h
					@brief	�f�o�b�O�t���O�Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#pragma once
class CDebugManager {
private:
	bool		m_bDebug;			//�f�o�b�O�t���O

	CDebugManager() : m_bDebug(false) {}
	~CDebugManager() {}
public:
	void SetDebugFlg(bool flg) { m_bDebug = flg; }
	bool GetDebugFlg() { return m_bDebug; }

	/// <summary>
	/// �V���O���g���C���X�^���X���擾���邽�߂̗B��̃A�N�Z�X
	/// </summary>
	static CDebugManager& Instance()
	{
		static CDebugManager obj;
		return obj;
	}
};