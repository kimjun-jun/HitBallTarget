/**
* @file register.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

// �}�N����`
#define SAVE_TEXTURE_FILE_00		_T("data/TEXTURE/SAVE/save.png")	// �T���v���p�摜
#define SAVE_SIZE_W			(880)	// �e�N�X�`���T�C�Y
#define SAVE_SIZE_H			(660)	// ����
#define SAVE_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define SAVE_POS_Y			(0)		// ����

/*******************************************************************************
* �\���̒�`
*******************************************************************************/
typedef struct					// �Z�[�u�f�[�^�̍\����
{
	int ftime;
	int fscore;
} SAVEDATA;

typedef struct					// �Z�[�u�f�[�^�̍\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �w�i�̈ʒu
}SAVE;

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitSave(int type);
void UninitSave(void);
void UpdateSave(void);
void DrawSave(void);
HRESULT MakeVertexSave(void);
void SetVertexSave(void);
void SaveData(void);
void LoadData(void);
