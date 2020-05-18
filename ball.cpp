/**
* @file ball.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "game.h"
#include "collision.h"
#include "ball.h"

//*****************************************************************************
// ?�N����?
//*****************************************************************************


//*****************************************************************************
// �v���g?�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O��?�o���ϐ�
//*****************************************************************************
BALL g_ball[BALL_MAX];
BALLCURSOR g_ballcursor;
BALLSHADOW g_ballshadow[BALL_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBall(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�N�X?���̓ǂݍ���  
	if (type == 0)	// ����̂ݓǂݍ���
	{
		for (int i = 0; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
				TEXTURE_GAME_BALLTYPE0,				// �t?�C���̖��O
				&g_ball[i].pD3DTexture);			// �ǂݍ��ރ�������?�C��?
		}
		for (int i = 0; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
				TEXTURE_GAME_BALLTYPE1,				// �t?�C���̖��O
				&g_ball[i].pD3DTextureEffect);			// �ǂݍ��ރ�������?�C��?
		}
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
			TEXTURE_GAME_BALLTYPE0,				// �t?�C���̖��O
			&g_ballcursor.pD3DTexture);			// �ǂݍ��ރ�������?�C��?

			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
				TEXTURE_GAME_BALLTYPE0,				// �t?�C���̖��O
				&g_ballshadow[0].pD3DTexture);			// �ǂݍ��ރ�������?�C��?
		for (int i = 1; i < BALL_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X��?�C��?
				TEXTURE_GAME_BALLTYPE1,				// �t?�C���̖��O
				&g_ballshadow[i].pD3DTextureEffect);			// �ǂݍ��ރ�������?�C��?
		}
	}

	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ball[i].use = false;									//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�
		g_ball[i].OorD = true;									//�^�����ł��ꂽ�@�U�����ł���Ă��Ȃ�
		g_ball[i].tuto = true;									//�^�`���[�g���A�����@�U�Q�[����
		g_ball[i].effect = false;								//�^�`���[�g���A�����@�U�Q�[����
		g_ball[i].diffflag = false;								//�^�g�U�e�Q�b�gflag�@�U�g�U�e�����Ė���
		g_ball[i].diffsignal = false;							//�^�g�U�e���@�U�g�U�e��
		g_ball[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].move = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldpos = D3DXVECTOR3(-100, -100, 0);
		for (int j = 0; j < 4; j++)
		{
			g_ball[i].effectoldpos[j] = D3DXVECTOR3(-100, -100, 0);
		}
		g_ball[i].oldrot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldmove = D3DXVECTOR3(0, 0, 0);

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BALL_SIZE_X, TEXTURE_BALL_SIZE_Y);
		g_ball[i].rad = D3DXVec2Length(&temp);
		g_ball[i].BaseAngle = atan2f(TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X);

		g_ball[i].changeVal = 1.0f;
		g_ball[i].changeValTypeA = 0;
		g_ball[i].penetcount = 0;
		g_ball[i].diffcount = 0;
		g_ball[i].effectcount = 0;
	}

	g_ballcursor.use = false;							//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�
	g_ballcursor.pos = D3DXVECTOR3(-100, -100, 0);
	g_ballcursor.rot = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.move = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.oldmove = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.direction = 0;
	g_ballcursor.changeVal = 0;
	g_ballcursor.movecount = 0;
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ballshadow[i].use = false;						  //�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�
		g_ballshadow[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ballshadow[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].move = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].oldmove = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].changeVal = 1.0f;
	}
	MakeVertexBall();

	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitBall(void)
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ball[i].use = false;									//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�
		g_ball[i].OorD = true;									//�^�����ł��ꂽ�@�U�����ł���Ă��Ȃ�
		g_ball[i].effect = false;								//�^�`���[�g���A�����@�U�Q�[����
		g_ball[i].tuto = true;									//�^�`���[�g���A�����@�U�Q�[����
		g_ball[i].diffflag = false;								//�^�g�U�e�Q�b�gflag�@�U�g�U�e�����Ė���
		g_ball[i].diffsignal = false;							//�^�A�C�e���Q�b�g���@�U�A�C�e�������Ė���
		g_ball[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].move = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldpos = D3DXVECTOR3(-100, -100, 0);
		g_ball[i].oldrot = D3DXVECTOR3(0, 0, 0);
		g_ball[i].oldmove = D3DXVECTOR3(0, 0, 0);
		for (int j = 0; j < 4; j++)
		{
			g_ball[i].effectoldpos[j] = D3DXVECTOR3(-100, -100, 0);
		}
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BALL_SIZE_X, TEXTURE_BALL_SIZE_Y);
		g_ball[i].rad = D3DXVec2Length(&temp);
		g_ball[i].BaseAngle = atan2f(TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X);
		g_ball[i].changeVal = 1.0f;
		g_ball[i].changeValTypeA = 0;
		g_ball[i].penetcount = 0;
		g_ball[i].diffcount = 0;
		g_ball[i].effectcount = 0;
	}

	g_ballcursor.use = false;
	g_ballcursor.pos = D3DXVECTOR3(-100, -100, 0);
	g_ballcursor.rot = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.move = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.oldmove = D3DXVECTOR3(0, 0, 0);
	g_ballcursor.changeVal = 0;
	for (int i = 0; i < BALL_MAX; i++)
	{
		g_ballshadow[i].use = false;
		g_ballshadow[i].pos = D3DXVECTOR3(-100, -100, 0);
		g_ballshadow[i].rot = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].move = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].oldmove = D3DXVECTOR3(0, 0, 0);
		g_ballshadow[i].changeVal = 1.0f;
	}
	SetVertexBall();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBall(void)
{
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].pD3DTexture != NULL)
		{	// �e�N�X?���̊J��
			g_ball[i].pD3DTexture->Release();
			g_ball[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].pD3DTextureEffect != NULL)
		{	// �e�N�X?���̊J��
			g_ball[i].pD3DTextureEffect->Release();
			g_ball[i].pD3DTextureEffect = NULL;
		}
	}
	if (g_ballcursor.pD3DTexture != NULL)
	{	// �e�N�X?���̊J��
		g_ballcursor.pD3DTexture->Release();
		g_ballcursor.pD3DTexture = NULL;
	}
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ballshadow[i].pD3DTexture != NULL)
		{	// �e�N�X?���̊J��
			g_ballshadow[i].pD3DTexture->Release();
			g_ballshadow[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBall(void)
{
	if (g_ball[0].use == true) Ball();
	if (g_ball[0].diffflag == true && g_ball[0].use == false && g_ball[1].use == false && g_ball[2].use == false)
	{
		g_ball[0].diffsignal = true;
		g_ball[0].diffflag = false;
	}
	if (g_ball[0].diffsignal == true)
	{
		g_ball[0].diffcount++;
		if (g_ball[0].diffcount >= 600)//10s
		{
			g_ball[0].diffsignal = false;
			g_ball[0].diffflag = false;
			g_ball[0].diffcount = 0;
			LoopInit();
		}
	}
	g_ball[0].rot.z += BALL_ROT;
	g_ball[1].rot.z += BALL_ROT;
	g_ball[2].rot.z += BALL_ROT;
	SetVertexBall();	// �ړ���̍��W�Œ�?��ݒ�
}

//=============================================================================
// ?�揈��
//=============================================================================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ��?�t�H??�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < BALL_MAX; i++)
	{
		if (g_ball[i].use == true)
		{
			if (g_ball[i].effect == true)
			{
				pDevice->SetTexture(0, g_ball[i].pD3DTextureEffect);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ball[i].vertexWk, sizeof(VERTEX_2D));

				pDevice->SetTexture(0, g_ballshadow[i].pD3DTextureEffect);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballshadow[i].vertexWk, sizeof(VERTEX_2D));
			}
			else
			{
				pDevice->SetTexture(0, g_ball[i].pD3DTexture);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ball[i].vertexWk, sizeof(VERTEX_2D));

				pDevice->SetTexture(0, g_ballshadow[i].pD3DTexture);
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballshadow[i].vertexWk, sizeof(VERTEX_2D));
			}
			pDevice->SetTexture(0, g_ballcursor.pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ballcursor.vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ��?�̍쐬
//=============================================================================
HRESULT MakeVertexBall(void)
{
	// ��?���W�̐ݒ�
	SetVertexBall();

	for (int i = 0; i < BALL_MAX; i++)
	{
		// rhw�̐ݒ�
		g_ball[i].vertexWk[0].rhw =
			g_ball[i].vertexWk[1].rhw =
			g_ball[i].vertexWk[2].rhw =
			g_ball[i].vertexWk[3].rhw = 1.0f;
		// ���ˌ��̐ݒ�  
		g_ball[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		g_ball[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 200);
		// �e�N�X?�����W�̐ݒ�  
		g_ball[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ball[i].vertexWk[1].tex = D3DXVECTOR2(1.0f , 0.0f);
		g_ball[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ball[i].vertexWk[3].tex = D3DXVECTOR2(1.0f , 1.0f );


		g_ballshadow[i].vertexWk[0].rhw =
		g_ballshadow[i].vertexWk[1].rhw =
		g_ballshadow[i].vertexWk[2].rhw =
		g_ballshadow[i].vertexWk[3].rhw = 1.0f;
		g_ballshadow[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 50);
		g_ballshadow[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ballshadow[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ballshadow[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ballshadow[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_ballcursor.vertexWk[0].rhw =
		g_ballcursor.vertexWk[1].rhw =
		g_ballcursor.vertexWk[2].rhw =
		g_ballcursor.vertexWk[3].rhw = 1.0f;
	g_ballcursor.vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	g_ballcursor.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_ballcursor.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_ballcursor.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_ballcursor.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


//=============================================================================
// ��?���W�̐ݒ�
//=============================================================================
void SetVertexBall(void)
{
	// ��?���W�̐ݒ� 
	for (int i = 0; i < BALL_MAX; i++)
	{
		//�p�x�g���Ɖ�]���y
		g_ball[i].vertexWk[0].vtx.x = g_ball[i].pos.x -(cosf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[0].vtx.y = g_ball[i].pos.y -(sinf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[0].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[1].vtx.x = g_ball[i].pos.x +(cosf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[1].vtx.y = g_ball[i].pos.y -(sinf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[1].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[2].vtx.x = g_ball[i].pos.x -(cosf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[2].vtx.y = g_ball[i].pos.y +(sinf(g_ball[i].BaseAngle - g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[2].vtx.z = 0.0f;			   															  
		g_ball[i].vertexWk[3].vtx.x = g_ball[i].pos.x +(cosf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[3].vtx.y = g_ball[i].pos.y +(sinf(g_ball[i].BaseAngle + g_ball[i].rot.z) * g_ball[i].rad)*g_ball[i].changeVal;
		g_ball[i].vertexWk[3].vtx.z = 0.0f;


		//g_ball[i].vertexWk[0].vtx.x = g_ball[i].pos.x - TEXTURE_BALL_SIZE_X - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[0].vtx.y = g_ball[i].pos.y - TEXTURE_BALL_SIZE_Y - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[0].vtx.z = 0.0f;
		//g_ball[i].vertexWk[1].vtx.x = g_ball[i].pos.x + TEXTURE_BALL_SIZE_X + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[1].vtx.y = g_ball[i].pos.y - TEXTURE_BALL_SIZE_Y - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[1].vtx.z = 0.0f;
		//g_ball[i].vertexWk[2].vtx.x = g_ball[i].pos.x - TEXTURE_BALL_SIZE_X - g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[2].vtx.y = g_ball[i].pos.y + TEXTURE_BALL_SIZE_Y + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[2].vtx.z = 0.0f;
		//g_ball[i].vertexWk[3].vtx.x = g_ball[i].pos.x + TEXTURE_BALL_SIZE_X + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[3].vtx.y = g_ball[i].pos.y + TEXTURE_BALL_SIZE_Y + g_ball[i].changeValTypeA;
		//g_ball[i].vertexWk[3].vtx.z = 0.0f;


		g_ballshadow[i].vertexWk[0].vtx.x = g_ballshadow[i].pos.x - TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[0].vtx.y = g_ballshadow[i].pos.y - TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[0].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[1].vtx.x = g_ballshadow[i].pos.x + TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[1].vtx.y = g_ballshadow[i].pos.y - TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[1].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[2].vtx.x = g_ballshadow[i].pos.x - TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[2].vtx.y = g_ballshadow[i].pos.y + TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[2].vtx.z = 0.0f;
		g_ballshadow[i].vertexWk[3].vtx.x = g_ballshadow[i].pos.x + TEXTURE_BALLSHADOW_SIZE_X;
		g_ballshadow[i].vertexWk[3].vtx.y = g_ballshadow[i].pos.y + TEXTURE_BALLSHADOW_SIZE_Y;
		g_ballshadow[i].vertexWk[3].vtx.z = 0.0f;
	}


	g_ballcursor.vertexWk[0].vtx.x = g_ballcursor.pos.x - TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[0].vtx.y = g_ballcursor.pos.y - TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[0].vtx.z = 0.0f;
	g_ballcursor.vertexWk[1].vtx.x = g_ballcursor.pos.x + TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[1].vtx.y = g_ballcursor.pos.y - TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[1].vtx.z = 0.0f;
	g_ballcursor.vertexWk[2].vtx.x = g_ballcursor.pos.x - TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[2].vtx.y = g_ballcursor.pos.y + TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[2].vtx.z = 0.0f;
	g_ballcursor.vertexWk[3].vtx.x = g_ballcursor.pos.x + TEXTURE_BALLCURSOR_SIZE_X;
	g_ballcursor.vertexWk[3].vtx.y = g_ballcursor.pos.y + TEXTURE_BALLCURSOR_SIZE_Y;
	g_ballcursor.vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// ??���̃A�h���X��Ԃ�.
//=============================================================================
BALL *GetBall(void)
{
	return &g_ball[0];
}

//=============================================================================
// ??���̃A�h���X��Ԃ�.
//=============================================================================
BALLCURSOR *GetBallcursor(void)
{
	return &g_ballcursor;
}

//=============================================================================
// ??���̃A�h���X��Ԃ�.
//=============================================================================
BALLSHADOW *GetBallshadow(void)
{
	return &g_ballshadow[0];
}

//=============================================================================
// ??���̐ݒ�
//=============================================================================
void SetBall(D3DXVECTOR3 pos)
{
	if (g_ball[0].use == false)
	{
		g_ball[0].pos = pos;
		g_ball[1].pos = pos;
		g_ball[2].pos = pos;
		g_ballcursor.pos = pos;
		g_ballshadow[0].pos = pos;
		g_ballcursor.pos.y = STRIKE_REFERENCE_Y;
		g_ballcursor.pos.x = STRIKE_REFERENCE_X;
		g_ballshadow[0].pos.y = BALL_SHADOW_REFARENCE_Y;
		g_ballshadow[0].pos.x = BALL_SHADOW_REFARENCE_X;
		g_ball[0].use = true;
	}
}
