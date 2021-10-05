/*************************************************************************//*!

					@file	GameEndManager.h
					@brief	�Q�[���I���Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CGameEndManager {
private:
	bool		m_bGameEnd;			//�Q�[���I���t���O
	int			m_GameEndNo;		//�Q�[���I�������ԍ�

	CGameEndManager();
	~CGameEndManager();
public:
	void SetGameEndCondition(int endNo);
	int GetGameEndCondition() { return m_GameEndNo; }
	bool IsGameEnd() { return m_bGameEnd; }

	/// <summary>
	/// �V���O���g���C���X�^���X���擾���邽�߂̗B��̃A�N�Z�X
	/// </summary>
	static CGameEndManager& Instance()
	{
		static CGameEndManager obj;
		return obj;
	}
};