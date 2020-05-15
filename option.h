///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	option.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_MODESELECT			_T("data/TEXTURE/sozai/select/ModeSet.png")		
#define	TEXTURE_R18					_T("data/TEXTURE/sozai/select/r18.png")


#define TEXTURE_SENSITIV_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_SENSITIV_SIZE_Y		(100)										// �^�C�g�����S�̍���

#define OPTION_PY1_POS_Y						(SCREEN_CENTER_Y-150)		// �|���S���̏����ʒuX
#define OPTION_PY2_POS_Y						(SCREEN_CENTER_Y+100)		// �|���S���̏����ʒuX

#define OPTION_PX1_POS_X						(SCREEN_CENTER_X-250)		// ����
#define OPTION_PX2_POS_X						(SCREEN_CENTER_X+250)		// ����


#define	OPTIONMAX		(4)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}OPTION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitOption(int type);
void ReInitOption(void);
void UninitOption(void);
void UpdateOption(void);
void DrawOption(void);
void SetVertexOption(void);
OPTION *GetOption(void);
