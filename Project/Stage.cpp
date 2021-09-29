/*************************************************************************//*!

					@file	Stage.cpp
					@brief	�X�e�[�W�B

															@author	�r��@����
*//**************************************************************************/
#include "Stage.h"
#include <sys/stat.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
CStage::CStage() :
m_ChipTexture(),
m_BackTexture(),
m_ChipSize(0),
m_ChipCnt(0,0),
m_pChipData(NULL),
m_Scroll(0,0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_pEnemyData(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_pItemData(NULL),
m_ItemCount(0) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CStage::~CStage() {
}

/// <summary>
/// �ǂݍ���
/// ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ���
/// </summary>
/// <param name="pName">�X�e�[�W�t�@�C���̖��O</param>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CStage::Load(char* pName) {
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C�������ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//�`�b�v�T�C�Y
	m_ChipSize = atof(strtok(NULL, ","));

	//�}�b�v�̃`�b�v��
	m_ChipCnt.x = atoi(strtok(NULL, ","));
	m_ChipCnt.y = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃��������m��
	m_pChipData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			m_pChipData[y * (int)m_ChipCnt.x + x] = atoi(strtok(NULL, ","));
		}
	}

	//�G�̃e�N�X�`���̓ǂݍ���
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//�z�u�f�[�^�̓ǂݍ���
	m_pEnemyData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);
	m_EnemyCount = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			m_pEnemyData[y * (int)m_ChipCnt.x + x] = atoi(strtok(NULL, ","));
			if (m_pEnemyData[y * (int)m_ChipCnt.x + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	//�A�C�e���̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//�z�u�f�[�^�̓ǂݍ���
	m_pItemData = (char*)malloc(m_ChipCnt.x * m_ChipCnt.y);
	m_ItemCount = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			pstr = strtok(NULL, ",");
			m_pItemData[y * (int)m_ChipCnt.x + x] = atoi(pstr);
			if (m_pItemData[y * (int)m_ChipCnt.x + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}

	//�t�@�C�������
	fclose(fp);
	free(pBuffer);

	return true;
}

/// <summary>
/// ������
/// </summary>
/// <param name="pEnemy">�G</param>
/// <param name="pItem">�A�C�e��</param>
void CStage::Initialize(CEnemy* pEnemy, CItem* pItem) {
	m_Scroll = Vector2(10, m_ChipSize * m_ChipCnt.y - g_pGraphics->GetTargetHeight());
	int n = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pEnemyData[y * (int)m_ChipCnt.x + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(Vector2(x * m_ChipSize, y * m_ChipSize), on);
		}
	}

	n = 0;
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//�z�u�ԍ�
			//�ԍ��O�͔z�u���Ȃ�
			char on = m_pItemData[y * (int)m_ChipCnt.x + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(Vector2(x * m_ChipSize, y * m_ChipSize), on);
		}
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="pl">�v���C���[�B�X�N���[���̔���Ɏg�p�B</param>
void CStage::Update(CPlayer& pl) {
	CRectangle prec = pl.GetRect();											//�v���C���[�̋�`
	float sh = CGraphicsUtilities::GetGraphics()->GetTargetHeight();		//�X�N���[���̍���
	float stgh = m_ChipSize * m_ChipCnt.y;									//�X�e�[�W�S�̂̍���
	if (prec.Top - m_Scroll.y < STAGESCROLL)
	{
		m_Scroll.y -= STAGESCROLL - (prec.Top - m_Scroll.y);
		if (m_Scroll.y <= 0)
		{
			m_Scroll.y = 0;
		}
	}
	else if (prec.Bottom - m_Scroll.y > sh - STAGESCROLL)
	{
		m_Scroll.y += (prec.Bottom - m_Scroll.y) - (sh - STAGESCROLL);
		if (m_Scroll.y >= stgh - sh)
		{
			m_Scroll.y = stgh - sh;
		}
	}
}

/// <summary>
/// �`��
/// </summary>
void CStage::Render() {
	//���i�̕`��
	int sch = g_pGraphics->GetTargetHeight();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_Scroll.y % hn) - hn; y < sch; y += hn)
	{
		m_BackTexture.Render(0, y);
	}

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_ChipCnt.y; y++)
	{
		for (int x = 0; x < m_ChipCnt.x; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͕`�悵�Ȃ�
			char cn = m_pChipData[y * (int)m_ChipCnt.x + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(
				m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), 
				m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_ChipTexture.Render(-m_Scroll.x + x * m_ChipSize, -m_Scroll.y + y * m_ChipSize, cr);
		}
	}
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CStage::RenderDebug() {
	CGraphicsUtilities::RenderString(10, 100, "�X�N���[�� X : %.0f , Y : %.0f", m_Scroll.x, m_Scroll.y);
}

/// <summary>
/// ���
/// </summary>
void CStage::Release() {
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}
	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
}

/// <summary>
/// �����蔻��
/// </summary>
/// <param name="r">���肷���`</param>
/// <param name="buried">���܂��</param>
/// <returns>�������Ă����true, �������Ă��Ȃ����false</returns>
bool CStage::Collision(CRectangle r, Vector2& buried) {
	bool re = false;

	//�����蔻�肷���`�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_ChipCnt.x) { rc = m_ChipCnt.x - 1; }
	if (bc >= m_ChipCnt.y) { bc = m_ChipCnt.y - 1; }

	//�����蔻��������`�̍��ォ��E���͈̔͂̂ݓ����蔻��������Ȃ�
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂ŁA���肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ��O�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * (int)m_ChipCnt.x + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̋�`
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//�����蔻��p�̃L�����N�^��`
			//���Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//���̋�`�͏㑤�����Ɠ����l�ɂ���
			brec.Expansion(-6, 0);				//���͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(brec))
			{
				re = true;
				//�`�b�v���X�΂̏ꍇ�A�����̗����ʒu���獂���̊��������߂�
				if (cn == LEFTSLOPE)
				{
					float sp = (brec.Right - cr.Left) / cr.GetWidth();
					if (sp < 0.0f) { sp = 0.0f; }
					else if (sp > 1.0f) { sp = 1.0f; }
					//�Ζʂ̏�̈ʒu�����߂�
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					//���߂���ӂ���ɂ���ꍇ�͖��܂��Ă��Ȃ�
					if (brec.Bottom < cTop) { continue; }
					//���̖��܂�Ȃ̂ŁA���[�����`�̉��[�̒l���������l�����܂�̒l
					buried.y += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//���̖��܂�Ȃ̂ŁA�`�b�v��[�����`�̉��[�̒l���������l�����܂�̒l
					buried.y += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}
			//�`�b�v���Ζʂ̏ꍇ�A�ǁE�V��Ƃ��Ă̓����蔻��������Ȃ�Ȃ�
			if (cn == LEFTSLOPE) { continue; }

			//�����蔻��p�̃L�����N�^��`
			//���A�E���ꂼ��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;		//���̋�`�͉E�������Ɠ����l�ɂ���
			lrec.Expansion(0, -6);				//�c�͈̔͂��������߂�
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;		//�E�̋�`�͍������E�Ɠ����l�ɂ���
			rrec.Expansion(0, -6);				//�c�͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//���̖��܂�Ȃ̂ŁA�`�b�v�E�[�����`�̍��[�̒l���������l�����܂�̒l
				buried.x += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//�E�̖��܂�Ȃ̂ŁA�`�b�v���[�����`�̉E���̒l���������l�����܂�̒l
				buried.x += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//�����蔻��p�̃L�����N�^��`
			//��Ŕ͈͂����肵����p�̋�`���쐬����B
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;		//��̋�`�͉�������Ɠ����l�ɂ���
			trec.Expansion(-6, 0);				//���͈̔͂��������߂�
			//��Ɠ����蔻��
			if (cr.CollisionRect(trec))
			{
				re = true;
				//��̖��܂�Ȃ̂ŁA�`�b�v���[�����`�̏�[�̒l���������l�����܂�̒l
				buried.y += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
		}
	}

	return re;
}