#pragma once

#include "aqua.h"
#include "../button/button.h"
#include <vector>

class cSelection :public aqua::IGameObject
{
public:

	//コンストラクタ
	cSelection(aqua::IGameObject* parent);
	
	//デストラクタ
	~cSelection() = default;

	//初期化
	void Initialize(std::vector<int> number, std::vector<std::string>name, std::vector<std::string>desc, aqua::CVector2 pos);

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Finalize() override;

	//選択されたか
	bool Pressed();

	//値取得
	int GetNum();

private:
	static const int m_selection_per_page; //１ページあたりの選択肢表示数
	static const int m_width;	//ウィンドウ幅
	static const int m_height;	//ウィンドウ高さ

	aqua::CVector2 m_Position; //ウィンドウ位置

	int m_PrevFramePage; //前フレームでの表示ページ
	int m_Page; //表示中ページ
	int m_MaxPage; //合計ページ数

	bool m_ButtonPressed; //選択肢ボタンが押されたか

	std::vector<int> m_Number; //選択肢番号配列
	std::vector<std::string> m_DescText; //説明文配列

	int m_CurNum; //現在の選択肢番号

	IGameObject* m_UIManager; //UIマネージャのポインタ

	IGameObject* m_PageTextWindow; //現在ページ数背景
	IGameObject* m_PageTextObj; //現在ページ数表示
	IGameObject* m_DescWindow; //選択肢説明文背景
	IGameObject* m_DescObj; //選択肢説明文表示
	IGameObject* m_Window; //ウィンドウ
	cButton* m_NextPage; //「前のページ」ボタン
	cButton* m_PrevPage; //「次のページ」ボタン
	std::vector<cButton*> m_ButtonList; //選択肢ボタン配列
};