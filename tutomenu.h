/**
* @file tutomenu.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TUTOMENU_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										// �^�C�g�����S�̍���


#define	TUTOMENUMAX		(2)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
	bool					use;
}TUTOMENU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutomenu(int type);
void ReInitTutomenu(void);
void UninitTutomenu(void);
void UpdateTutomenu(void);
void UpdateInTutomenu(void);
void DrawTutomenu(void);
void SetVertexTutomenu(void);
TUTOMENU *GetTutomenu(void);
