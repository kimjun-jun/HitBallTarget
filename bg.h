/**
* @file bg.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLEBG		_T("data/TEXTURE/bg000.jpg")					//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIALBG	_T("data/TEXTURE/tutorial/tutobg.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAMEBG		_T("data/TEXTURE/BG/bg.png")					//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAMEBGR1801	_T("data/TEXTURE/sozai/R1801.png")				//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAMEBGR1802	_T("data/TEXTURE/sozai/R1802.png")				//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSETBG	_T("data/TEXTURE/sozai/textbg.png")				//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define BG_SIZE_W			(SCREEN_W)										//!< �e�N�X�`���T�C�YX
#define BG_SIZE_H			(SCREEN_H)										//!< �e�N�X�`���T�C�YY
#define BG_POS_X			(0)												//!< �|���S���̏������WX(����)
#define BG_POS_Y			(0)												//!< �|���S���̏������WY(����)
#define BG_MAX				(15)											//!< �w�i��ނ̍��v
#define GAMER18BG_MAX		(3)												//!< 

/**
*�@@struct BG
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;								//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];							//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;											//!< �w�i�̍��W
} BG;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief R18�������֐� InitBG
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitBG(int type);

/**
* @brief BG�ď������֐� ReInitBG
*/
void ReInitBG(void);

/**
* @brief BG�J���֐� UninitBG
*/
void UninitBG(void);

/**
* @brief BG�X�V�֐� UpdateBG
*/
void UpdateBG(void);

/**
* @brief BG�`��֐� DrawBG
*/
void DrawBG(void);

/**
* @brief BG�ݒ�֐� SetGameBGtype
* @param[in] num -1�W��,0�������q,1�X�C�[�c
*/
void SetGameBGtype(int num);
