# JGA22
## 開発環境
OS:Windows11
言語:C++ DXライブラリ

## 制作箇所
### cCamera
aqua_7_17_project\game\src\game\game_object\camera  
カメラクラス オブジェクトの描画位置をずらす。
### cUnitDataBase
aqua_7_17_project\game\src\game\game_object\database\chr_db  
ファイルからユニットのデータを読み込んでおくためのクラス。
### cEquipDataBase
aqua_7_17_project\game\src\game\game_object\database\equip_db  
ファイルから装備品のデータを読み込んでおくためのクラス。
### cItemDataBase
aqua_7_17_project\game\src\game\game_object\database\item_db  
ファイルからアイテムのデータを読み込んでおくためのクラス。
### cEffectManager
aqua_7_17_project\game\src\game\game_object\effect_manager  
エフェクトの表示・再生をするクラス。
### IEffect
aqua_7_17_project\game\src\game\game_object\effect_manager\effect  
エフェクト基底クラス
### cEffectCannon
aqua_7_17_project\game\src\game\game_object\effect_manager\effect\cannon  
大砲系武器の攻撃エフェクト。
### cEffectGunshot
aqua_7_17_project\game\src\game\game_object\effect_manager\effect\gunshot  
小火器系武器の攻撃エフェクト。
### cEffectMelee
aqua_7_17_project\game\src\game\game_object\effect_manager\effect\melee  
近接武器の攻撃エフェクト。
### cMapGenerator
aqua_7_17_project\game\src\game\game_object\scene_manager\scene\game_main\map_generator  
マップ生成器
### cMap
aqua_7_17_project\game\src\game\game_object\scene_manager\scene\game_main\map_generator\map  
マップクラス
### cGameMainScene
aqua_7_17_project\game\src\game\game_object\scene_manager\scene\game_main  
ゲームメインシーンクラス
### cResultScene
aqua_7_17_project\game\src\game\game_object\scene_manager\scene\result  
リザルトシーンクラス
### cTitleScene
aqua_7_17_project\game\src\game\game_object\scene_manager\scene\title  
タイトルシーンクラス
### cTextManager
aqua_7_17_project\game\src\game\game_object\text_manager  
テキストボックスを表示・生成するクラス。
### cText
aqua_7_17_project\game\src\game\game_object\text_manager\text  
テキストボックスクラス
### cUIManager
aqua_7_17_project\game\src\game\game_object\ui_manager  
UIを表示・生成するクラス。
### cButton
aqua_7_17_project\game\src\game\game_object\ui_manager\component\button  
ボタンクラス ラムダ式で機能を設定できる。
### cGauge
aqua_7_17_project\game\src\game\game_object\ui_manager\component\gauge  
ゲージクラス
### cSelection
aqua_7_17_project\game\src\game\game_object\ui_manager\component\select  
選択肢UIクラス
### cStatusUI
aqua_7_17_project\game\src\game\game_object\ui_manager\component\status  
ステータスUIクラス
### cValue
aqua_7_17_project\game\src\game\game_object\ui_manager\component\value  
数値UIクラス
### cWindow
aqua_7_17_project\game\src\game\game_object\ui_manager\component\window  
ウィンドウUIクラス
### cUnitManager
aqua_7_17_project\game\src\game\game_object\unit_manager  
ユニットの生成や戦闘処理をするクラス。
### IUnit
aqua_7_17_project\game\src\game\game_object\unit_manager\unit  
ユニット基底クラス
### cPlayer
aqua_7_17_project\game\src\game\game_object\unit_manager\unit\player  
プレイヤークラス
### cBot
aqua_7_17_project\game\src\game\game_object\unit_manager\unit\bot  
敵ユニットクラス
### Dice
aqua_7_17_project\game\src\game\tools  
ダイス名前空間 ダイスロール用データや処理を記述。
