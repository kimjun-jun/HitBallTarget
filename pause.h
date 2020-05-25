/**
* @file pause.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_HAJIMEKARA					_T("data/TEXTURE/sozai/select/hajimekara.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_OPTIONMARK					_T("data/TEXTURE/sozai/select/option.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_END							_T("data/TEXTURE/sozai/select/akirameru.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_RESTART_SIZE_X				(200)												//!< �|���S���̕�
#define TEXTURE_RESTART_SIZE_Y				(100)												//!< �|���S���̍���
#define	PAUSEMAX							(3)													//!< ��ʂ̑I������

/**
*�@@struct PAUSE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																//!< �|���S���̈ړ���
	bool					use;
}PAUSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Pause�������֐� InitPause
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitPause(int type);

/**
* @brief Pause�ď������֐� ReInitPause
*/
void ReInitPause(void);

/**
* @brief Pause�J���֐� UninitPause
*/
void UninitPause(void);

/**
* @brief Pause�|�[�Y�V�[���X�V�֐� UpdatePause
*/
void UpdatePause(void);


/**
* @brief Pause�Q�[���V�[���X�V�֐� UpdateInPause
*/
void UpdateInPause(void);

/**
* @brief Pause�`��֐� DrawPause
*/
void DrawPause(void);

/**
* @brief Pause�擾�֐� GetPause
* @return PAUSE
*/
PAUSE *GetPause(void);
