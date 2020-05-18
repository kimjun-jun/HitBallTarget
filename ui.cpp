/**
* @file ui.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "ball.h"
#include "ui.h"

//*****************************************************************************
// ?�N����?
//*****************************************************************************


//*****************************************************************************
// �v���g?�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O��?�o���ϐ�
//*****************************************************************************
STRIKE g_strike;
CURSOR g_cursor;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUi(int type)
{
	for (int i = 0; i < UI_GOUKEI; i++)
	{
		switch (i)
		{
		case 0:
		{
			g_strike.s.use = true;								
			g_strike.s.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y+250.0f, 0.0f);
			g_strike.s.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_strike.s.nCountAnim = 0;
			g_strike.s.nPatternAnim = 0;
			MakeVertexUi(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// �e�N�X?���̓ǂݍ���  
			if (type == 0)	// ����̂ݓǂݍ���
			{
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
					TEXTURE_GAME_STRIKE,				// �t?�C���̖��O
					&g_strike.s.pD3DTexture);			// �ǂݍ��ރ�������?�C��?
			}
			break;
		}
		case 1:
		{
			g_cursor.c.use = true;
			g_cursor.c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
			g_cursor.c.rot = D3DXVECTOR3(0, 0, 0);
			g_cursor.c.nCountAnim = 0;
			g_cursor.c.nPatternAnim = 0;
			g_cursor.c.meet = 0;
			MakeVertexUi(i);
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// �e�N�X?���̓ǂݍ���  
			if (type == 0)	// ����̂ݓǂݍ���
			{
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
					TEXTURE_GAME_CURSOR,				// �t?�C���̖��O
					&g_cursor.c.pD3DTexture);			// �ǂݍ��ރ�������?�C��?
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
void ReInitUi(void)
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
void UninitUi(void)
{
	if (g_strike.s.pD3DTexture != NULL)
	{	// �e�N�X?���̊J��
		g_strike.s.pD3DTexture->Release();
		g_strike.s.pD3DTexture = NULL;
	}
	if (g_cursor.c.pD3DTexture != NULL)
	{	// �e�N�X?���̊J��
		g_cursor.c.pD3DTexture->Release();
		g_cursor.c.pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUi(void)
{
	BALL *b = GetBall();
	if (b->OorD == true && IsButtonTriggered(0, BUTTON_X) || GetKeyboardTrigger(DIK_C))
	{
		g_cursor.c.meet++;
	}
	SetVertexUi(g_cursor.c.meet);
}

//=============================================================================
// ?�揈��
//=============================================================================
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ��?�t�H??�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (g_strike.s.use == true && g_cursor.c.use == true)
	{
		// �e�N�X?���̐ݒ�  
		pDevice->SetTexture(0, g_strike.s.pD3DTexture);
		// ?���S����?��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_strike.s.vertexWk, sizeof(VERTEX_2D));

		// �e�N�X?���̐ݒ�  
		pDevice->SetTexture(0, g_cursor.c.pD3DTexture);
		// ?���S����?��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_cursor.c.vertexWk, sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ��?�̍쐬
//=============================================================================
HRESULT MakeVertexUi(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (i)
	{
	case 0:
		// ��?���W�̐ݒ�
		SetVertexUi(i);
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
		// �e�N�X?�����W�̐ݒ�  
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2(1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2(1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y);
		break;

	case 1:
		// ��?���W�̐ݒ�
		SetVertexUi(i);
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
		// �e�N�X?�����W�̐ݒ�  
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2(1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2(1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X, 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y);
		break;
	}
	return S_OK;
}

//=============================================================================
// �e�N�X?�����W�̐ݒ�
//=============================================================================
void SetTextureUi(int cntPattern,int i)
{
	switch (i)
	{
	case 0:
	{
		int x_s = cntPattern % STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		int y_s = cntPattern / STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX_s = 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY_s = 1.0f / STRIKE_TEXTURE_PATTERN_DIVIDE_Y;

		// �e�N�X?�����W�̐ݒ�
		g_strike.s.vertexWk[0].tex = D3DXVECTOR2((float)(x_s)* sizeX_s, (float)(y_s)* sizeY_s);
		g_strike.s.vertexWk[1].tex = D3DXVECTOR2((float)(x_s)* sizeX_s + sizeX_s, (float)(y_s)* sizeY_s);
		g_strike.s.vertexWk[2].tex = D3DXVECTOR2((float)(x_s)* sizeX_s, (float)(y_s)* sizeY_s + sizeY_s);
		g_strike.s.vertexWk[3].tex = D3DXVECTOR2((float)(x_s)* sizeX_s + sizeX_s, (float)(y_s)* sizeY_s + sizeY_s);
		break;
	}
	case 1:
	{
		int x_c = cntPattern % CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		int y_c = cntPattern / CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX_c = 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY_c = 1.0f / CURSOR_TEXTURE_PATTERN_DIVIDE_Y;

		// �e�N�X?�����W�̐ݒ�
		g_cursor.c.vertexWk[0].tex = D3DXVECTOR2((float)(x_c)* sizeX_c, (float)(y_c)* sizeY_c);
		g_cursor.c.vertexWk[1].tex = D3DXVECTOR2((float)(x_c)* sizeX_c + sizeX_c, (float)(y_c)* sizeY_c);
		g_cursor.c.vertexWk[2].tex = D3DXVECTOR2((float)(x_c)* sizeX_c, (float)(y_c)* sizeY_c + sizeY_c);
		g_cursor.c.vertexWk[3].tex = D3DXVECTOR2((float)(x_c)* sizeX_c + sizeX_c, (float)(y_c)* sizeY_c + sizeY_c);
		break;
	}
	}

}

//=============================================================================
// ��?���W�̐ݒ�
//=============================================================================
void SetVertexUi(int i)
{
	switch (i%2)
	{
	case BIG:
		// ��?���W�̐ݒ� 
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
// ??���̃A�h���X��Ԃ�.
//=============================================================================
STRIKE *GetStrike(void)
{
	return &g_strike;
}

//=============================================================================
// ??���̃A�h���X��Ԃ�.
//=============================================================================
CURSOR *Get_Cursor(void)
{
	return &g_cursor;
}

