///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	tutorial.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIALF1		_T("data/TEXTURE/tutorial/tutorialF1.png")			
#define	TEXTURE_TUTORIALF2		_T("data/TEXTURE/tutorial/tutorialF2.png")			
#define	TEXTURE_TUTORIALF3		_T("data/TEXTURE/tutorial/tutorialF3.png")
#define	TUTORIAL_POS_X			(0)													// �`���[�g���A���̕\���ʒu
#define	TUTORIAL_POS_Y			(0)													// �`���[�g���A���̕\���ʒu
#define	TUTORIAL_SIZE_X			(SCREEN_W)												// �`���[�g���A���̕�
#define	TUTORIAL_SIZE_Y			(SCREEN_H)												// �`���[�g���A���̍���

#define TUTORIAL_GOUKEI			(3)

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}TUTO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

