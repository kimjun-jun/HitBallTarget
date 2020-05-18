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
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/title/title_logo.png")			// �ǂݍ��ރe�N�X�`���t�@�C����


#define	TITLELOGO_POS_X		(SCREEN_CENTER_X)								// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(SCREEN_CENTER_Y)								// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(SCREEN_CENTER_X/2)								// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(SCREEN_CENTER_Y/2)								// �^�C�g�����S�̍���

#define	TITLE_GOUKEI	(1)													// 

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N
}TITLE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

