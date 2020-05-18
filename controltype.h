/**
* @file controltype.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_DIGITAL			_T("data/TEXTURE/sozai/select/digital.png")		
#define	TEXTURE_ANALOG			_T("data/TEXTURE/sozai/select/analog.png")
#define	TEXTURE_CONTYPECURSOR	_T("data/TEXTURE/sozai/select/nowselect.png")		

#define TEXTURE_CONTYPEBROAD_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_CONTYPEBROAD_SIZE_Y		(100)										// �^�C�g�����S�̍���





#define	CONTYPEMAX		(3)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}CONTYPE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitContype(int type);
void ReInitContype(void);
void UninitContype(void);
void UpdateContype(void);
void UpdateTUTOContype(void);
void DrawContype(void);
void SetVertexContype(void);
int GetSCONkeypos(void);
