/*************************************************************************//*!

					@file	GameModeManager.h
					@brief	�Q�[�����[�h�Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CGameModeManager {
private:
	int					m_PlayModeNo;			//�V�ԃ��[�h�ԍ�

	CGameModeManager();
	~CGameModeManager();
public:
	void SetPlayMode(int no) { m_PlayModeNo = no; }
	int GetPlayMode() { return m_PlayModeNo; }

	/// <summary>
	/// �V���O���g���C���X�^���X���擾���邽�߂̗B��̃A�N�Z�X
	/// </summary>
	static CGameModeManager& Instance()
	{
		static CGameModeManager obj;
		return obj;
	}
};