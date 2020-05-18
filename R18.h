/**
* @file R18.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_R18SELECT01		_T("data/TEXTURE/sozai/select/heart01.png")			
#define	TEXTURE_R18SELECT02		_T("data/TEXTURE/sozai/select/heart02.png")			
#define	TEXTURE_R18SELECT03		_T("data/TEXTURE/sozai/select/NotR18.png")			


#define TEXTURE_R18SELECT_SIZE_X		(200)								// �^�C�g�����S�̕�
#define TEXTURE_R18SELECT_SIZE_Y		(100)								// �^�C�g�����S�̍���



#define R18SELECT_PY1_POS_Y						(SCREEN_CENTER_Y-150)		// �|���S���̏����ʒuX
#define R18SELECT_PY2_POS_Y						(SCREEN_CENTER_Y+100)		// �|���S���̏����ʒuX

#define R18SELECT_PX1_POS_X						(SCREEN_CENTER_X-250)		// ����
#define R18SELECT_PX2_POS_X						(SCREEN_CENTER_X+250)		// ����

#define	R18SELECTMAX		(3)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}R18SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitR18select(int type);
void ReInitR18select(void);
void UninitR18select(void);
void UpdateR18select(void);
void DrawR18select(void);
void SetVertexR18select(void);
R18SELECT *GetR18select(void);
