
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"

const unsigned int  CGame::m_clear_color = 0xff808080;
const float         CGame::m_gravity = 9.8f;

/*
 *  コンストラクタ
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    m_Sprite.Create("data\\abe.png");
}

/*
 *  更新
 */
void
CGame::
Update(void)
{
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        m_Accelerator.y += -500.0f;
    }

    m_Accelerator.y += m_gravity * aqua::GetDeltaTimeScale();

    m_Velocity += m_Accelerator * aqua::GetDeltaTime();

    m_Sprite.position += m_Velocity * aqua::GetDeltaTime();

    float h = (float)(aqua::GetWindowHeight() - m_Sprite.GetTextureHeight());

    if (m_Sprite.position.y > h)
    {
        m_Sprite.position.y = h;

        m_Accelerator.y = 0.0f;
        m_Velocity.y = 0.0f;
    }
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_clear_color);

    m_Sprite.Draw();
}

/*
 *  解放
 */
void
CGame::
Finalize(void)
{
    m_Sprite.Delete();
}
