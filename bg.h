///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	bg.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

// �}�N����`
#define	TEXTURE_TITLEBG		_T("data/TEXTURE/bg000.jpg")					// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIALBG	_T("data/TEXTURE/tutorial/tutobg.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAMEBG		_T("data/TEXTURE/BG/bg.png")	// �T���v���p�摜
#define TEXTURE_GAMEBGR1801	_T("data/TEXTURE/sozai/R1801.png")	// �T���v���p�摜
#define TEXTURE_GAMEBGR1802	_T("data/TEXTURE/sozai/R1802.png")	// �T���v���p�摜
#define	TEXTURE_PAUSETBG	_T("data/TEXTURE/sozai/textbg.png")		
#define BG_SIZE_W			(SCREEN_W)	// �e�N�X�`���T�C�Yl
#define BG_SIZE_H			(SCREEN_H)	// ����
#define BG_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BG_POS_Y			(0)		// ����

#define BG_MAX			(15)
#define GAMEBG_MAX		(3)

typedef struct // �L�����N�^�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �w�i�̈ʒu
} BG;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void ReInitBG(void);
void UpdateBG(void);
void DrawBG(void);
HRESULT MakeVertexBG(void);
void SetVertexBG(void);
void SetGameBGtype(int num);
