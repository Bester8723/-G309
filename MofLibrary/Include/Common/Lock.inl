/*************************************************************************//*!
					
					@file	Lock.inl
					@brief	���b�N�iPOSIX�Ȃ�Mutex�AWin�Ȃ�N���e�B�J���Z�N�V�����j

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			�R���X�g���N�^
		@param[in]		pl			���b�N�|�C���^

		@return			None
*//**************************************************************************/
FORCE_INLINE CFocusLock::CFocusLock(CLock* pl) :
m_pLock(NULL) {
	if (pl)
	{
		m_pLock = pl;
		m_pLock->Lock();
	}
}
/*************************************************************************//*!
		@brief			�f�X�g���N�^
		@param			None

		@return			None
*//**************************************************************************/
FORCE_INLINE CFocusLock::~CFocusLock(){
	if (m_pLock)
	{
		m_pLock->UnLock();
	}
}

//[EOF]