/*************************************************************************//*!
					
					@file	GLShaderBind_2DPrimitiveBase.h
					@brief	��{�v���~�e�B�u�V�F�[�_�[�o�C���h�B<br>
							�W���I�ȃv���~�e�B�u�`��V�F�[�_�[�Ƀp�����[�^�[���֘A�t���邽�߂̃N���X�B

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__GLSHADERBIND_2DPRIMITIVEBASE__H__

#define		__GLSHADERBIND_2DPRIMITIVEBASE__H__

//INCLUDE
#include	"../ShaderBindBase.h"

namespace Mof {

	/*******************************//*!
	@brief	�V�F�[�_�[�o�C���h���C���^�[�t�F�C�X

			�V�F�[�_�[�̂��߂̃o�b�t�@�̐ݒ���s���C���^�[�t�F�C�X�B

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CGLShaderBind_2DPrimitiveBase : public CShaderBindBase {
	public:
		/*******************************//*!
		@brief	�X�v���C�g�`����͒��_�o�b�t�@��

		@author	CDW
		*//********************************/
		enum VertexAttribute
		{
			ATTRIBUTE_POSITION,
			ATTRIBUTE_COLOR,

			ATTRIBUTE_COUNT,
		};
		/*******************************//*!
		@brief	�v���~�e�B�u�`����̓R���X�^���g�o�b�t�@��

		@author	CDW
		*//********************************/
		enum ConstParam
		{
			PARAM_SCENE,
			PARAM_MESH,

			PARAM_MAX,
		};
		/*******************************//*!
		@brief	�v���~�e�B�u�`��V�[�������̓R���X�^���g�o�b�t�@

		@author	CDW
		*//********************************/
		struct ConstSceneParam
		{
			Matrix44	mtxView;
			Matrix44	mtxProj;
		};
		/*******************//*!
		�v���~�e�B�u�`��V�[�����ݒ�
		*//********************/
		ConstSceneParam							m_SceneParam;
		/*******************************//*!
		@brief	�v���~�e�B�u�`��v���~�e�B�u�����̓R���X�^���g�o�b�t�@

		@author	CDW
		*//********************************/
		struct ConstMeshParam
		{
			Vector4		cbvOffset;
			Vector4		cbvSize;
			Vector4		cbColor1;
			Vector4		cbColor2;
			Vector4		cbColor3;
			Vector4		cbColor4;
			Matrix44	mtxWorld;
		};
		/*******************//*!
		�v���~�e�B�u�`��v���~�e�B�u���ݒ�
		*//********************/
		ConstMeshParam							m_MeshParam;
	protected:
		/*******************//*!
		�V�F�[�_�[ID
		*//********************/
		GLuint									m_ShaderID;
		/*******************//*!
		���_���P�[�V����
		*//********************/
		GLuint									m_Attribute[ATTRIBUTE_COUNT];
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_OffsetLocation;
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_SizeLocation;
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_Color1Location;
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_Color2Location;
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_Color3Location;
		/*******************//*!
		�v���~�e�B�u�p�����[�^���P�[�V����
		*//********************/
		GLuint									m_Color4Location;
		/*******************//*!
		���[���h�}�g���N�X���P�[�V����
		*//********************/
		GLuint									m_WorldLocation;
		/*******************//*!
		�r���[�}�g���N�X���P�[�V����
		*//********************/
		GLuint									m_ViewLocation;
		/*******************//*!
		�v���W�F�N�V�����}�g���N�X���P�[�V����
		*//********************/
		GLuint									m_ProjectionLocation;
	public:
		/*************************************************************************//*!
				@brief			�R���X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		CGLShaderBind_2DPrimitiveBase();
		/*************************************************************************//*!
				@brief			�R�s�[�R���X�g���N�^
				@param			pObj		�R�s�[�V�F�[�_�[

				@return			None
		*//**************************************************************************/
		CGLShaderBind_2DPrimitiveBase(const CGLShaderBind_2DPrimitiveBase& pObj);
		/*************************************************************************//*!
				@brief			�f�X�g���N�^
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CGLShaderBind_2DPrimitiveBase();
		
		/*************************************************************************//*!
				@brief			�o�C���_�̐���
				@param[in]		pShader		�V�F�[�_�[
				
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool Create(LPShader pShader);
		/*************************************************************************//*!
				@brief			�o�C���_�̐���
				@param[in]		pvb			���_�o�b�t�@�z��
				@param[in]		Cnt			���_�o�b�t�@�z��
				
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool CreateVertexLayout(LPVertexBuffer* pvb, MofU32 Cnt = 0);

		/*************************************************************************//*!
				@brief			�o�C���h�̎��s
				@param[in]		pGeom		�W�I���g��
				
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool Bind(LPGeometry pGeom = NULL);

		/*************************************************************************//*!
				@brief			���
				@param[in]		pData			����ǉ��f�[�^

				@return			TRUE			����I��<br>
								����ȊO		����G���[�A�G���[�R�[�h��Ԃ��B
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
	
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			�o�b�t�@�̐ݒ�
				@param[in]		n			�ԍ�
					
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool SetBuffer(MofU32 n);
		/*************************************************************************//*!
				@brief			�o�b�t�@�̐ݒ�
				@param[in]		n			�ԍ�
				@param[in]		pData		�f�[�^
					
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool SetBuffer(MofU32 n,LPMofVoid pData);
		/*************************************************************************//*!
				@brief			�T���v���̐ݒ�<br>
								OpenGL�Ŏ��s���̂ݗL��<br>
								DirectX9�̏ꍇ�̓V�F�[�_�[�ł̎w�肪�AOpenGL�n�̏ꍇ�̓e�N�X�`���ł̎w�肪�L���ɂȂ�B
				@param[in]		n			�ԍ�
				@param[in]		st			�T���v���^�C�v
					
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool SetSamplerType(MofU32 n,MofU32 st);
		/*************************************************************************//*!
				@brief			�T���v���̐ݒ�<br>
								OpenGL�Ŏ��s���̂ݗL��<br>
								DirectX9�̏ꍇ�̓V�F�[�_�[�ł̎w�肪�AOpenGL�n�̏ꍇ�̓e�N�X�`���ł̎w�肪�L���ɂȂ�B
				@param[in]		n			�ԍ�
				@param[in]		pSamp		�T���v��
					
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool SetSamplerState(MofU32 n,MofSamplerState pSamp);
		/*************************************************************************//*!
				@brief			�e�N�X�`���̐ݒ�
				@param[in]		n			�ԍ�
				@param[in]		pTex		�e�N�X�`��
					
				@return			TRUE		����<br>
								����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
		*//**************************************************************************/
		virtual MofBool SetTexture(MofU32 n,LPTexture pTex);
		
		/*************************************************************************//*!
				@brief			�`��p�s���ݒ肷��
				@param[in]		wMat			�s��

				@return			None
		*//**************************************************************************/
		virtual void SetWorldMatrix(const Matrix44& wMat);
		/*************************************************************************//*!
				@brief			�`��p�s���ݒ肷��
				@param[in]		pMotion		���[�V�����R���g���[��
				@param[in]		pGeom		�W�I���g��
				
				@return			None
		*//**************************************************************************/
		virtual void SetWorldMatrix(LPMeshMotionController pMotion,LPGeometry pGeom);
		/*************************************************************************//*!
				@brief			�`��p�}�e���A����ݒ肷��
				@param[in]		pMat			�}�e���A��

				@return			None
		*//**************************************************************************/
		virtual void SetMaterial(LPMaterial pMat);
		/*************************************************************************//*!
				@brief			�`��p�v���~�e�B�u�p�����[�^�[��ݒ肷��
				@param[in]		pPar			�e�N�X�`���p�����[�^�[

				@return			None
		*//**************************************************************************/
		virtual void SetPrimitiveParameter(LPPrimitiveRenderParameter pPar);
		/*************************************************************************//*!
				@brief			�`��p�e�N�X�`���p�����[�^�[��ݒ肷��
				@param[in]		pPar			�e�N�X�`���p�����[�^�[

				@return			None
		*//**************************************************************************/
		virtual void SetTextureParameter(LPTextureRenderParameter pPar);
		/*************************************************************************//*!
				@brief			�`��p�J������ݒ肷��
				@param[in]		pc				�J����

				@return			None
		*//**************************************************************************/
		virtual void SetCamera(LPCamera pc);
		/*************************************************************************//*!
				@brief			�`��p�J������ݒ肷��
				@param[in]		mv				�J����
				@param[in]		mp				�v���W�F�N�V����

				@return			None
		*//**************************************************************************/
		virtual void SetCamera(Matrix44& mv,Matrix44& mp);
		/*************************************************************************//*!
				@brief			�`��p��{���C�g��ݒ肷��
				@param[in]		pl				���C�g

				@return			None
		*//**************************************************************************/
		virtual void SetDirectionalLight(LPDirectionalLight pl);
		
		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			�ݒ�p�����[�^�[�����擾����
				@param			None

				@return			�p�����[�^�[�̐�
		*//**************************************************************************/
		virtual MofS32 GetParamCount(void) const { return PARAM_MAX; }

		//�N���X��{��`
		MOF_LIBRARYCLASS(CGLShaderBind_2DPrimitiveBase,MOF_GLSHADERBIND2DPRIMITIVEBASECLASS_ID);
	};

	#include	"GLShaderBind_2DPrimitiveBase.inl"

	//�u������
	typedef CGLShaderBind_2DPrimitiveBase		CShaderBind_2DPrimitiveBase;
	typedef CShaderBind_2DPrimitiveBase*		LPShaderBind_2DPrimitiveBase;
}

#endif

//[EOF]