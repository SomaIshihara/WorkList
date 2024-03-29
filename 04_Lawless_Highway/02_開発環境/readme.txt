//=======================================================================================================
//
// [ゲームタイトル] Lawless Highway
//
// [制作者名] 石原颯馬
//
// [開発環境] Visual Studio 2019, DirectX9
// [使用言語] C++
//
// [GithubURL] https://github.com/SomaIshihara/Lawless_Highway.git
//
// [実装内容] < タイトル >
//			  背景はゲームのマップを使用。
//			  スタートはどのボタンでも始められるようになっている。
//			  
//			  < チュートリアル（ゲーム内） >
//			  スタート地点に移動しながら基本的な操作を表示。
//			  途中から自動操縦に切り替わり、スタート地点についたらタイマースタートと手動操縦。
//			  
//			  < ゲーム >
//			  プレイヤー:方向転換・加減速・移動・ドリフト
//			  ゲームパッド優先で使用。接続されていなければキーボードに切り替わる。
//			  タイマー:ミリ秒単位も含めて表示（厳密なものではないが）
//			  ゲージ:プレイヤーのブーストと連動し、ブーストしていないときは回復、
//			  ドリフト中はさらに回復、ブースト時すべて使い切る
//			  道路:メッシュフィールド継承のもの。次に配置する方向指定で座標設定。
//			  当たり判定（上下重なっていても対応可能）
//			  ミニマップ:上から見たものを表示
//			  スピードメーター:プレイヤーの速度と連動
//			  ブースト時の炎エフェクト
//			  BGM/SE追加
//
//			  < リザルト（ゲーム内） >
//			  かかった時間を表示
//			  
//			  < ランキング >
//			  1～5位まで表示
//
//=======================================================================================================