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
#define	TUTORIAL_POS_X			(0)													//!< �|���S���̕\���ʒuX
#define	TUTORIAL_POS_Y			(0)													//!< �|���S���̕\���ʒuY
#define	TUTORIAL_SIZE_X			(SCREEN_W)											//!< �|���S���̕�X
#define	TUTORIAL_SIZE_Y			(SCREEN_H)											//!< �|���S���̍���Y
#define TUTORIAL_GOUKEI			(3)													//!< �`���[�g���A���\���̂̍��v

/**
*�@@struct TUTO
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;										//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];									//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;													//!< �|���S���̍��W
}TUTO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Tutorial�������֐� InitTutorial
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitTutorial(int type);

/**
* @brief Tutorial�J���֐� UninitTutorial
*/
void UninitTutorial(void);

/**
* @brief Tutorial�X�V�֐� UpdateTutorial
*/
void UpdateTutorial(void);

/**
* @brief Tutorial�`��֐� DrawTutorial
*/
void DrawTutorial(void);

