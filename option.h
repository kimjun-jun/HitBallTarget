/**
* @file option.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_MODESELECT						_T("data/TEXTURE/sozai/select/ModeSet.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����		
#define	TEXTURE_R18								_T("data/TEXTURE/sozai/select/r18.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����		
#define TEXTURE_SENSITIV_SIZE_X					(200)											//!< �|���S���̕�
#define TEXTURE_SENSITIV_SIZE_Y					(100)											//!< �|���S���̍���
#define OPTION_PY1_POS_Y						(SCREEN_CENTER_Y-150)							//!< �|���S���̏����ʒuY1
#define OPTION_PY2_POS_Y						(SCREEN_CENTER_Y+100)							//!< �|���S���̏����ʒuY2
#define OPTION_PX1_POS_X						(SCREEN_CENTER_X-250)							//!< �|���S���̏����ʒuX1
#define OPTION_PX2_POS_X						(SCREEN_CENTER_X+250)							//!< �|���S���̏����ʒuX2
#define	OPTIONMAX								(4)												//!< ��ʂ̑I������		

/**
*�@@struct OPTION
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;												//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];											//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;															//!< �|���S���̈ړ���
}OPTION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Option�������֐� InitOption
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitOption(int type);

/**
* @brief Option�ď������֐� ReInitOption
*/
void ReInitOption(void);

/**
* @brief Option�J���֐� UninitOption
*/
void UninitOption(void);

/**
* @brief Option�X�V�֐� UpdateOption
*/
void UpdateOption(void);

/**
* @brief Option�`��֐� DrawOption
*/
void DrawOption(void);

/**
* @brief Option�擾�֐� GetOption
* @return OPTION
*/
OPTION *GetOption(void);
