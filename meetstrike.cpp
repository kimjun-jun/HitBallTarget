/**
* @file meetstrike.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "ball.h"
#include "meetstrike.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief ���_�����֐� MakeVertexMeetStrike
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT MakeVertexMeetStrike(int type);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
STRIKE g_strike;									//!< �X�g���C�N�]�[���\���̕ϐ�
CURSOR g_cursor;									//!< �~�[�g�J�[�\���\���̕ϐ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeetStrike(int type)
{
	for (int i = 0; i < MEETSTRIKE_GOUKEI; i++)
	{
		switch (i)
		{
		case 0:
		{
			g_strike.s.use = true;								
			g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y+250.0f, 0.0f);
			g_strike.s.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			MakeVertexMeetStrike(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// �e�N�X�`���̓ǂݍ���  
			if (type == 0)	// ����̂ݓǂݍ���
			{
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
					TEXTURE_GAME_STRIKE,				// �t�@�C���̖��O
					&g_strike.s.pD3DTexture);			// �ǂݍ��ރ������̃|�C���^
			}
			break;
		}
		case 1:
		{
			g_cursor.c.use = true;
			g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
			g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
			g_cursor.c.meet = 0;
			MakeVertexMeetStrike(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
					TEXTURE_GAME_CURSOR,				// �t�@�C���̖��O
					&g_cursor.c.pD3DTexture);			// �ǂݍ��ރ������̃|�C���^
			}
			break;
		}
		}
	}
	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitMeetStrike(void)
{
	g_strike.s.use = true;
	g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
	g_strike.s.rot = D3DXVECTOR3(0, 0, 0);

	g_cursor.c.use = true;
	g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
	g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeetStrike(void)
{
	if (g_strike.s.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_strike.s.pD3DTexture->Release();
		g_strike.s.pD3DTexture = NULL;
	}
	if (g_cursor.c.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_cursor.c.pD3DTexture->Release();
		g_cursor.c.pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeetStrike(void)
{
	BALL *b = GetBall();
	if (b->OorD == true && IsButtonTriggered(0, BUTTON_X) || GetKeyboardTrigger(DIK_C))
	{
		g_cursor.c.meet++;
	}
	SetVertexMeetStrike(g_cursor.c.meet);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeetStrike(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_strike.s.use == true && g_cursor.c.use == true)
	{
		// �e�N�X�`���̐ݒ�  
		pDevice->SetTexture(0, g_strike.s.pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_strike.s.vertexWk, sizeof(VERTEX_2D));
		// �e�N�X�`���̐ݒ�  
		pDevice->SetTexture(0, g_cursor.c.pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_cursor.c.vertexWk, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexMeetStrike(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (type)
	{
	case 0:
		// ���_���W�̐ݒ�
		SetVertexMeetStrike(type);
		// rhw�̐ݒ�
		g_strike.s.vertexWk[0].rhw =
			g_strike.s.vertexWk[1].rhw =
			g_strike.s.vertexWk[2].rhw =
			g_strike.s.vertexWk[3].rhw = 1.0f;
		// ���ˌ��̐ݒ�  
		g_strike.s.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_strike.s.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// �e�N�X�`�����W�̐ݒ�  
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

	case 1:
		// ���_���W�̐ݒ�
		SetVertexMeetStrike(type);
		// rhw�̐ݒ�
		g_cursor.c.vertexWk[0].rhw =
			g_cursor.c.vertexWk[1].rhw =
			g_cursor.c.vertexWk[2].rhw =
			g_cursor.c.vertexWk[3].rhw = 1.0f;
		// ���ˌ��̐ݒ�  
		g_cursor.c.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cursor.c.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// �e�N�X�`�����W�̐ݒ�  
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMeetStrike(int CursorType)
{
	switch (CursorType %2)
	{
	case BIG:
		// ���_���W�̐ݒ� 
		g_cursor.c.vertexWk[0].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[0].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[0].vtx.z = 0.0f;							
		g_cursor.c.vertexWk[1].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[1].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[1].vtx.z = 0.0f;							
		g_cursor.c.vertexWk[2].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[2].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[2].vtx.z = 0.0f;							 
		g_cursor.c.vertexWk[3].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_BIG_SIZE_X;
		g_cursor.c.vertexWk[3].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_BIG_SIZE_Y;
		g_cursor.c.vertexWk[3].vtx.z = 0.0f;
		break;

	case SMALL:
		g_cursor.c.vertexWk[0].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[0].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[0].vtx.z = 0.0f;								  
		g_cursor.c.vertexWk[1].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[1].vtx.y = g_cursor.c.pos.y - TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[1].vtx.z = 0.0f;							 	  
		g_cursor.c.vertexWk[2].vtx.x = g_cursor.c.pos.x - TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[2].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[2].vtx.z = 0.0f;							 	  
		g_cursor.c.vertexWk[3].vtx.x = g_cursor.c.pos.x + TEXTURE_CURSOR_SMALL_SIZE_X;
		g_cursor.c.vertexWk[3].vtx.y = g_cursor.c.pos.y + TEXTURE_CURSOR_SMALL_SIZE_Y;
		g_cursor.c.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	g_strike.s.vertexWk[0].vtx.x = g_strike.s.pos.x - TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[0].vtx.y = g_strike.s.pos.y - TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[0].vtx.z = 0.0f;

	g_strike.s.vertexWk[1].vtx.x = g_strike.s.pos.x + TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[1].vtx.y = g_strike.s.pos.y - TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[1].vtx.z = 0.0f;

	g_strike.s.vertexWk[2].vtx.x = g_strike.s.pos.x - TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[2].vtx.y = g_strike.s.pos.y + TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[2].vtx.z = 0.0f;

	g_strike.s.vertexWk[3].vtx.x = g_strike.s.pos.x + TEXTURE_STRIKE_SIZE_X;
	g_strike.s.vertexWk[3].vtx.y = g_strike.s.pos.y + TEXTURE_STRIKE_SIZE_Y;
	g_strike.s.vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�g���C�N�̃A�h���X��Ԃ�
//=============================================================================
STRIKE *GetStrike(void)
{
	return &g_strike;
}

//=============================================================================
// �~�[�g�̃A�h���X��Ԃ�
//=============================================================================
CURSOR *Get_Cursor(void)
{
	return &g_cursor;
}

