/**
* @file title.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/title/title_logo.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TITLELOGO_POS_X		(SCREEN_CENTER_X)								//!< �^�C�g�����S�̕\���ʒuX
#define	TITLELOGO_POS_Y		(SCREEN_CENTER_Y)								//!< �^�C�g�����S�̕\���ʒuY
#define	TITLELOGO_SIZE_X	(SCREEN_CENTER_X/2)								//!< �^�C�g�����S�̕�X
#define	TITLELOGO_SIZE_Y	(SCREEN_CENTER_Y/2)								//!< �^�C�g�����S�̍���Y
#define	TITLE_GOUKEI		(1)												//!< �^�C�g���̍��v

/**
*�@@struct TITLE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;								//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];							//!< ���_���i�[���[�N
}TITLE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

/**
* @brief �^�C�g���������֐� InitTitle
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitTitle(int type);

/**
* @brief �^�C�g���J���֐� UninitTitle
*/
void UninitTitle(void);

/**
* @brief �^�C�g���X�V�֐� UpdateTitle
*/
void UpdateTitle(void);

/**
* @brief �^�C�g���`��֐� DrawTitle
*/
void DrawTitle(void);
