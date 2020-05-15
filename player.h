///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	player.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once


//*****************************************************************************
//* ?���̒�?
//******************************************************************************* /
typedef struct // �v���C��??����
{
	CHARACTER pp;
} PLAYER_PIT;

typedef struct // �v���C��??����
{
	CHARACTER pb;
} PLAYER_BAT;


//*****************************************************************************
// �v���g?�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void ReInitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

HRESULT MakeVertexPlayer(int i);
void SetTexturePlayer(int cntPattern, int i);	// 
void SetVertexPlayer(int i);					// 

PLAYER_PIT *GetPlayerPit(void);
PLAYER_BAT *GetPlayerBat(void);
