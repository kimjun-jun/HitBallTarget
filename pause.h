///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	pause.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_HAJIMEKARA		_T("data/TEXTURE/sozai/select/hajimekara.png")		
#define	TEXTURE_OPTIONMARK		_T("data/TEXTURE/sozai/select/option.png")
#define	TEXTURE_END				_T("data/TEXTURE/sozai/select/akirameru.png")		

#define TEXTURE_RESTART_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_RESTART_SIZE_Y		(100)										// �^�C�g�����S�̍���






#define	PAUSEMAX		(3)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
	bool					use;
}PAUSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPause(int type);
void ReInitPause(void);
void UninitPause(void);
void UpdatePause(void);
void UpdateInPause(void);
void DrawPause(void);
void SetVertexPause(void);
PAUSE *GetPause(void);
