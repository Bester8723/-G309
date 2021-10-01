/*************************************************************************//*!

					@file	SceneGame.cpp
					@brief	�Q�[����ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneGame.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneGame::CSceneGame() : 
CSceneBase(),
m_Player(),
m_Stage(),
m_EnemyArray(),
m_ItemArray(),
m_EffectManager() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneGame::~CSceneGame() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneGame::Load() {
	//�v���C���[�f�ނ̓ǂݍ���
	if (!m_Player.Load()) { return FALSE; }
	//�X�e�[�W�f�ނ̓ǂݍ���
	if (!m_Stage.Load("Stage1.txt")) { return FALSE; }
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//�G�t�F�N�g�̑f�ޓǂݍ���
	if (!m_EffectManager.Load()) { return FALSE; }
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CSceneGame::Initialize() {
	Load();
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray, m_ItemArray);
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize(m_Stage.GetScroll());
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
}

/// <summary>
/// �X�V
/// </summary>
void CSceneGame::Update() {
	//�v���C���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	Vector2 buried = Vector2(0, 0);
	if (m_Stage.Collision(m_Player.GetRect(), buried))
	{
		m_Player.CollisionStage(buried);
	}
	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		Vector2 buried = Vector2(0, 0);
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), buried))
		{
			m_EnemyArray[i].CollisionStage(buried);
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		Vector2 buried = Vector2(0, 0);
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), buried))
		{
			m_ItemArray[i].CollisionStage(buried);
		}
	}
	//�����蔻��̎��s
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy(m_EnemyArray[i]);
	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);
	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

	//�Q�[���I���m�F
	if (CGmeEndManager::Instance().IsGameEnd())
	{
		SetGameEnd(SCENENO_RESULT);
	}

	//�f�o�b�O�X�V
	if (CDebugManager::Instance().GetDebugFlg())
	{
		UpdateDebug();
	}
}

/// <summary>
/// �f�o�b�O�X�V
/// </summary>
void CSceneGame::UpdateDebug() {
	//F2�L�[�ŃQ�[���V�[��������
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		SetGameEnd(SCENENO_GAME);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneGame::Render() {
	//�X�N���[����
	Vector2 scroll = m_Stage.GetScroll();
	//�X�e�[�W�̕`��
	m_Stage.Render();
	//�v���C���[�̕`��
	m_Player.Render(scroll);
	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(scroll);
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].Render(scroll);
	}
	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(scroll);
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneGame::RenderDebug() {
	//�X�N���[����
	Vector2 scroll = m_Stage.GetScroll();
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(scroll);
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(scroll);
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(scroll);
	}
	//�G�t�F�N�g�̃f�o�b�O�`��
	m_EffectManager.RenderDebug(scroll);
}

/// <summary>
/// ���
/// </summary>
void CSceneGame::Release() {
	//�X�e�[�W�̉��
	m_Stage.Release();
	//�v���C���[�̉��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�G�t�F�N�g�̉��
	m_EffectManager.Release();
}

/// <summary>
/// �Q�[���I����ݒ肷��
/// </summary>
/// <param name="sceneNo">���ɑJ�ڂ���V�[���ԍ�</param>
void CSceneGame::SetGameEnd(int sceneNo) {
	m_bEnd = true;
	m_bChange = true;
	m_NextScene = sceneNo;
}