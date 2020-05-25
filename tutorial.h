/**
* @file tutorial.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIALF1		_T("data/TEXTURE/tutorial/tutorialF1.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIALF2		_T("data/TEXTURE/tutorial/tutorialF2.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIALF3		_T("data/TEXTURE/tutorial/tutorialF3.png")			//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TUTORIAL_POS_X			(0)													//!< �^�C�g���̕\���ʒuX
#define	TUTORIAL_POS_Y			(0)													//!< �^�C�g���̕\���ʒuY
#define	TUTORIAL_SIZE_X			(SCREEN_W)											//!< �^�C�g���̕�X
#define	TUTORIAL_SIZE_Y			(SCREEN_H)											//!< �^�C�g���̍���Y
#define TUTORIAL_GOUKEI			(3)													//!< �^�C�g���̍��v

/**
*�@@struct TITLE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;										//!< �e�N�X�`���ւ̃|���S��
	VERTEX_2D				vertexWk[NUM_VERTEX];									//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;													//!< �e�N�X�`���ւ̃|���S��
}TUTO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief R18�������֐� InitR18select
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitTutorial(int type);
/**
* @brief R18�J���֐� UninitR18select
*/
void UninitTutorial(void);
/**
* @brief R18�X�V�֐� UpdateR18select
*/
void UpdateTutorial(void);
/**
* @brief R18�`��֐� DrawR18select
*/
void DrawTutorial(void);

