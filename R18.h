/**
* @file R18.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_R18SELECT01						_T("data/TEXTURE/sozai/select/heart01.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����		
#define	TEXTURE_R18SELECT02						_T("data/TEXTURE/sozai/select/heart02.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����		
#define	TEXTURE_R18SELECT03						_T("data/TEXTURE/sozai/select/NotR18.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����		
#define TEXTURE_R18SELECT_SIZE_X				(200)										//!< �|���S���̕�
#define TEXTURE_R18SELECT_SIZE_Y				(100)										//!< �|���S���̍���
#define R18SELECT_PY1_POS_Y						(SCREEN_CENTER_Y-150)						//!< �|���S���̏����ʒuY1
#define R18SELECT_PY2_POS_Y						(SCREEN_CENTER_Y+100)						//!< �|���S���̏����ʒuY2
#define R18SELECT_PX1_POS_X						(SCREEN_CENTER_X-250)						//!< �|���S���̏����ʒuX1
#define R18SELECT_PX2_POS_X						(SCREEN_CENTER_X+250)						//!< �|���S���̏����ʒuX2
#define	R18SELECTMAX							(3)											//!< ��ʂ̑I������

/**
*�@@struct R18SELECT
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;												//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];											//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;															//!< �|���S���̍��W
}R18SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief R18�������֐� InitR18select
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitR18select(int type);

/**
* @brief R18�ď������֐� ReInitR18select
*/
void ReInitR18select(void);

/**
* @brief R18�J���֐� UninitR18select
*/
void UninitR18select(void);

/**
* @brief R18�X�V�֐� UpdateR18select
*/
void UpdateR18select(void);

/**
* @brief R18�`��֐� DrawR18select
*/
void DrawR18select(void);

/**
* @brief R18�擾�֐� GetR18select
* @return R18SELECT
*/
R18SELECT *GetR18select(void);
