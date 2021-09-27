/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"GameDefine.h"
#include	"SceneBase.h"
#include	"SceneTitle.h"
#include	"SceneStageSelect.h"
#include	"SceneGame.h"
#include	"SceneResult.h"

//�f�o�b�O�p�t���O
bool m_bDebug = false;
//�V�[���N���X
CSceneBase* gpScene = NULL;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�ŏ��Ɏ��s�����V�[���̏�����
	gpScene = new CSceneGame();
	gpScene->Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�V�[���̍X�V
	gpScene->Update();
	//�V�[�����I��������
	if (gpScene->IsEnd())
	{
		//���̃V�[�����擾
		int change = gpScene->GetNextScene();
		//�Â��V�[������������
		gpScene->Release();
		delete gpScene;
		//���̃V�[���ԍ��ɉ����ăV�[��������ď���������
		switch (change)
		{
		case SCENENO_TITLE:
			gpScene = new CSceneTitle();
			break;
		case SCENENO_STAGESELECT:
			gpScene = new CSceneStageSelect();
			break;
		case SCENENO_GAME:
			gpScene = new CSceneGame();
			break;
		case SCENENO_RESULT:
			gpScene = new CSceneResult();
			break;
		default:
			gpScene = new CSceneTitle();
			break;
		}
		gpScene->Initialize();
	}

#ifdef _DEBUG
	//F1�L�[�Ńf�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_bDebug = !m_bDebug;
	}
#endif // _DEBUG


	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//�V�[���̕`��
	gpScene->Render();
	//�V�[���̃f�o�b�O�`��
	if (m_bDebug)
	{
		gpScene->RenderDebug();
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	//�V�[���̉��
	if (gpScene)
	{
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}