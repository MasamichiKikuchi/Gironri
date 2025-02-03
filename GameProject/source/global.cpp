#include	"DxLib.h"
#include	"global.h"
#include	<string>

Global::Global()
{
	// 変数初期化
	
	// ---会話パート（SceneTalk）---
	// アニメーション
	for (int n = 0; n < 5; n++) {
		for (int i = 0; i < 24; i++) {
			cg_anim[n][i] = -1;
		}
	}
	
	// エフェクト
	for (int i = 0; i < 45; i++)
	{
		break_efffect[i] = -1;
	}

	// ---怪しい箇所を睨むパート---
	for (int i = 0; i < tblLPSize; i++)
	{
		tblLookPoint[i].img = -1;
	}

	// ---偽証議論パート（SceneGameMain）---

	// 議論パート
	// 証言
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				cgTestimony[i][j][k] = -1;
			}
		}
	}
	// 罵詈雑言
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			for (int k = 0; k < TW_LENGTH; k++)
			{
				cgRedThoughtlessWords[i][j][k] = -1;		// 赤
				cgGreenThoughtlessWords[i][j][k] = -1;		// 緑
				cgYellowThoughtlessWords[i][j][k] = -1;		// 黄
				cgBlueThoughtlessWords[i][j][k] = -1;		// 青
				cgPinkThoughtlessWords[i][j][k] = -1;		// ピンク
				cgSetsunaThoughtlessWords[i][j][k] = -1;	// セツナ（自傷議論）
			}
		}
	}

	// 反論パート
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				cgStockCard[i][j][k] = -1;
				cgCounterCard[i][j][k] = -1;
			}
		}
	}

	//
	// SE・BGM
	//
	
	// ---偽証議論パート---
	//音声
	seDamage = -1;
	seBGM1 = -1;
	seBGM2 = -1;

	//
	// エフェクト
	//
	
	// 防御エフェクト
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++) { LockEffect[i][j] = -1; }
	}
}

Global::~Global()
{
	// データ解放
	
	// 審議会メンバー
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		DeleteGraph(gikai[i].cg);
	}

	// ---会話パート（SceneTalk）---
	// アニメーション
	for (int n = 0; n < 5; n++) {
		for (int i = 0; i < 24; i++) {
			DeleteGraph(cg_anim[n][i]);
		}
	}

	// エフェクト
	for (int i = 0; i < 45; i++)
	{
		DeleteGraph(break_efffect[i]);
	}

	// ---怪しい箇所を睨むパート（SceneLook）---
	for (int i = 0; i < tblLPSize; i++)
	{
		if (tblLookPoint[i].img != -1) { DeleteGraph(tblLookPoint[i].img); }
	}

	DeleteGraph(cgLookButtonUI);	// 睨むパートボタンUI

	// ---偽証議論パート（SceneGameMain）---
	
	//　動画
	DeleteGraph(mvGiron_ikou);
	DeleteGraph(mvJishou_ikou);
	
	// 背景
	for (int i = 0; i < CGBGANIM_PATTERN_MAX; i++) { DeleteGraph(_cgBg[i]); }
	for (int i = 0; i < CG_JISHOU_BGANIM_PATTERN_MAX; i++) { DeleteGraph(_cgJishouBg[i]); }

	//カットイン
	for (int i = 0; i < 30; i++) { DeleteGraph(cgCutIn[i]); }

	// 議論パート
	// 証言
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++) { DeleteGraph(cgTestimony[i][j][k]); }
		}
	}
	// 罵詈雑言
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			for (int k = 0; k < TW_LENGTH; k++)
			{
				DeleteGraph(cgRedThoughtlessWords[i][j][k]);		// 赤
				DeleteGraph(cgGreenThoughtlessWords[i][j][k]);		// 緑
				DeleteGraph(cgYellowThoughtlessWords[i][j][k]);		// 黄
				DeleteGraph(cgBlueThoughtlessWords[i][j][k]);		// 青
				DeleteGraph(cgPinkThoughtlessWords[i][j][k]);		// ピンク
				DeleteGraph(cgSetsunaThoughtlessWords[i][j][k]);	// セツナ（自傷議論）
			}
		}
	}

	DeleteGraph(cgCounter);		//反論への遷移(土台)
	DeleteGraph(cgCounter_x);	//反論への遷移(ｘボタン)

	DeleteGraph(cgPlayguide);	//操作説明

	// 反論パート
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				DeleteGraph(cgStockCard[i][j][k]);
				DeleteGraph(cgCounterCard[i][j][k]);
				DeleteGraph(cgReturnCard[i][j][k]);
			}
		}
	}

	// 取得前の手札配置の画像（黒）・取得直後の手札配置の画像（白）
	DeleteGraph(cgStockBrankCard);
	DeleteGraph(cgStockWhiteCard);

	// 裏返し用画像
	cgTurnCard.clear();

	// 反論パート正解時エフェクト
	//偽証議論
	for (int i = 0; i < ENDEFFECT_PATTERN_MAX; i++)
	{
		DeleteGraph(cgEndEffect[i]);
	}
	//自傷議論
	for (size_t i = 0; i < JISYOU_ENDEFFECT_PATTERN_MAX; i++)
	{
		DeleteGraph(cgJisyou_EndEffect[i]);
	}

	// 間違った場合の画像
	//偽証議論
	DeleteGraph(cgHanronMiss);
	DeleteGraph(cgJishouHanronMiss);

	//
	// SE・BGM
	//
	
	// ---会話パート---
	for (int i = 0; i < 5; i++) {
		DeleteSoundMem(seBGM[i]);
	}

	// ---怪しい箇所を睨むパート---
	DeleteSoundMem(seLookClear);
	DeleteSoundMem(seLookDamage);
	DeleteSoundMem(seLookHazure);
	DeleteSoundMem(seLookSeikai);

	// ---偽証議論パート---
	//音声
	DeleteSoundMem(seDamage);
	DeleteSoundMem(seBGM1);
	DeleteSoundMem(seBGM2);
	DeleteSoundMem(seTestimonyBreak);
	DeleteSoundMem(seGetTestimony);
	DeleteSoundMem(seCardGathering);
	DeleteSoundMem(seCardOpening);
	DeleteSoundMem(seCardSelecting);
	DeleteSoundMem(seHazure);
	DeleteSoundMem(seCutin);
	DeleteSoundMem(seCardTurning);
	DeleteSoundMem(seHitTestimony);
	DeleteSoundMem(seGard);
	DeleteSoundMem(seRedLaugh);
	DeleteSoundMem(seGreenLaugh);
	DeleteSoundMem(seYellowLaugh);
	DeleteSoundMem(seBlueLaugh);
	DeleteSoundMem(sePinkLaugh);
	DeleteSoundMem(seSetsunaRough);
	DeleteSoundMem(seSay);
	DeleteSoundMem(seCutinVoice);
	DeleteSoundMem(seTitleBGM);
	DeleteSoundMem(seDecide);
	DeleteSoundMem(seCursor);
	DeleteSoundMem(seGameOverBGM);

	// ---自傷推理パート---
	for (int i = 0; i < 6; i++) {
		DeleteSoundMem(se_choiceBGM[i]);
	}

	//
	// エフェクト
	//
	
	// ダメージエフェクト
	for (int i = 0; i < EFFECT_TYPE_MAX; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			DeleteGraph(cgEffect[i][j]);
		}
	}

	// 防御エフェクト
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 11; j++) { DeleteGraph(LockEffect[i][j]); }
	}

	// 防御回復エフェクト
	for (int i = 0; i < 9; i++)
	{
		DeleteGraph(gateReset[i]);
	}

	// 自傷推理中背景
	for (int i = 0; i < 72; i++)
	{
		DeleteGraph(jisyou_cgBg[i]);
	}
}

// 読み込み
void Global::Load()
{
	// 画像
	
	// 審議会メンバーの設定
	gikai[0].cg = LoadGraph("res/enemy/red.png");
	gikai[1].cg = LoadGraph("res/enemy/green.png");
	gikai[2].cg = LoadGraph("res/enemy/yellow.png");
	gikai[3].cg = LoadGraph("res/enemy/blue.png");
	gikai[4].cg = LoadGraph("res/enemy/pink.png");
	
	// ---会話パート（SceneTalk）---
	// アニメーション
	// 0：黄, 1：青
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/kiiro/kiiro_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[0][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/blue_anim/mizuiro_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[1][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/midori/midori_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[2][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/aka/aka_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[3][n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 24; n++)
	{
		std::string img = "res/talkpart/pink/pink_anime";
		img += std::to_string(n + 1);
		img += ".png";
		cg_anim[4][n] = LoadGraph(img.c_str());
	}

	// エフェクト
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/break/effect_break_00";
		img += std::to_string(n + 1);
		img += ".png";
		break_efffect[n] = LoadGraph(img.c_str());
	}

	for (int n = 10; n < 45; n++)
	{
		std::string img = "res/break/effect_break_0";
		img += std::to_string(n + 1);
		img += ".png";
		break_efffect[n] = LoadGraph(img.c_str());
	}

	// ---怪しい箇所を睨むパート（SceneLook）---
	char lookImgPath[][128] = {
		"res/lookdata/part1.png",
		"res/lookdata/part2.png",
		"res/lookdata/part3.png",
		"res/lookdata/part4.png",
		"res/lookdata/part5.png",
		"res/lookdata/part6.png",
	};
	for (int i = 0; i < tblLPSize; i++)
	{
		//cgLook[i] = LoadGraph(lookImgPath[i]);
		tblLookPoint[i].img = LoadGraph(lookImgPath[i]);
	}

	cgLookButtonUI = LoadGraph("res/lookdata/UI_niramu.png");	// 睨むパートボタンUI

	// ---偽証議論パート（SceneGameMain）---
	// 背景画像のループでのロード
	std::string img_path;
	// 偽証議論
	img_path = "res/cgBg_Gironpart_jpg/gironpart";
	anim.GetCG(img_path, 1, CGBGANIM_PATTERN_MAX, _cgBg);	// jpg画像

	//自傷議論
	img_path = "res/cgBg_JisyouGironpart_jpg/girongame_setuna";
	anim.GetCG(img_path, 1, CG_JISHOU_BGANIM_PATTERN_MAX, _cgJishouBg);	// jpg画像

	// カットイン
	//efectType 0:ダメージエフェクト 1:ダメージ演出 2:ガード演出
	for (int i = 0; i < 30; i++)
	{
		img_path = "res/effect/cutin/cutin" + std::to_string(i) + ".png";
		cgCutIn[i] = LoadGraph(img_path.c_str());
	}

	// 議論パート
	// 証言の画像パス（赤, 緑, 黄, 青, ピンクの順番に, ない場合は空""に）
	std::string testimonyPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1回目の偽証議論
		{
			{"res/cards/giron1/card_red.png",	""},	// 赤
			{"",								""},	// 緑
			{"",								""},	// 黄
			{"",								""},	// 青
			{"res/cards/giron1/card_pink.png",	""}		// ピンク
		},
		// 2回目の偽証議論
		{
			{"res/cards/giron2/card_r.png",	""},
			{"",							""},
			{"res/cards/giron2/card_y.png",	""},
			{"",							""},
			{"res/cards/giron2/card_p.png",	""}
		},
		// 3回目の偽証議論
		{
			{"res/cards/giron3/card_r.png",	""},
			{"res/cards/giron3/card_g.png",	""},
			{"res/cards/giron3/card_y.png",	""},
			{"res/cards/giron3/card_b.png",	""},
			{"",							""}
		},
		// 4回目の偽証議論
		{
			{"",	""},
			{"",	""},
			{"",	""},
			{"",	""},
			{"",	""}
		},
		// 5回目の偽証議論
		{
			{"",														""},
			{"res/cards/giron5/card_g.png",	"res/cards/giron5/card_g2.png"},
			{"",														""},
			{"res/cards/giron5/card_b.png",								""},
			{"res/cards/giron5/card_p.png",								""}
		},
		// 6回目の偽証議論
		{
			{"res/cards/giron6/card_1.png",""},
			{"res/cards/giron6/card_2.png",""},
			{"res/cards/giron6/card_3.png",""},
			{"res/cards/giron6/card_4.png",""},
			{"res/cards/giron6/card_5.png",""}
		}
	};
	// 証言の画像のロード
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				if (!testimonyPath[i][j][k].empty()) { cgTestimony[i][j][k] = LoadGraph(testimonyPath[i][j][k].c_str()); }
			}
		}
	}

	// 罵詈雑言
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < TW_NUM; j++)
		{
			// 赤
			LoadDivGraph(redTW[i][j].imgPath, redTW[i][j].allNum, redTW[i][j].xNum, redTW[i][j].yNum,
				redTW[i][j].xSize, redTW[i][j].ySize, cgRedThoughtlessWords[i][j]);
			// 緑
			LoadDivGraph(greenTW[i][j].imgPath, greenTW[i][j].allNum, greenTW[i][j].xNum, greenTW[i][j].yNum,
				greenTW[i][j].xSize, greenTW[i][j].ySize, cgGreenThoughtlessWords[i][j]);
			// 黄
			LoadDivGraph(yellowTW[i][j].imgPath, yellowTW[i][j].allNum, yellowTW[i][j].xNum, yellowTW[i][j].yNum,
				yellowTW[i][j].xSize, yellowTW[i][j].ySize, cgYellowThoughtlessWords[i][j]);
			// 青
			LoadDivGraph(blueTW[i][j].imgPath, blueTW[i][j].allNum, blueTW[i][j].xNum, blueTW[i][j].yNum,
				blueTW[i][j].xSize, blueTW[i][j].ySize, cgBlueThoughtlessWords[i][j]);
			// ピンク
			LoadDivGraph(pinkTW[i][j].imgPath, pinkTW[i][j].allNum, pinkTW[i][j].xNum, pinkTW[i][j].yNum,
				pinkTW[i][j].xSize, pinkTW[i][j].ySize, cgPinkThoughtlessWords[i][j]);
			// セツナ（自傷議論）
			LoadDivGraph(setsunaTW[i][j].imgPath, setsunaTW[i][j].allNum, setsunaTW[i][j].xNum, setsunaTW[i][j].yNum,
				setsunaTW[i][j].xSize, setsunaTW[i][j].ySize, cgSetsunaThoughtlessWords[i][j]);
		}
	}

	cgCounter = LoadGraph("res/Scenegamemain/cutin_counter.png");		//反論への遷移(土台)
	cgCounter_x = LoadGraph("res/Scenegamemain/cutin_counter_X.png");	//反論への遷移(ｘボタン)

	cgPlayguide = LoadGraph("res/Scenegamemain/guide_play.png");		//操作説明

	cgGironButtonUI = LoadGraph("res/Scenegamemain/UI_guard.png");		// 議論パートボタンUI
	cgHanronButtonUI = LoadGraph("res/Scenegamemain/UI_hanron.png");	// 反論パートボタンUI

	// 反論パート
	// 取得カードの画像パス（赤, 緑, 黄, 青, ピンクの順番に, ない場合は空""に）
	std::string stockCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1回目の偽証議論
		{
			{"res/cards/giron1/stockcard_red.png",	""},	// 赤
			{"",									""},	// 緑
			{"",									""},	// 黄
			{"",									""},	// 青
			{"res/cards/giron1/stockcard_pink.png",	""}		// ピンク
		},
		// 2回目の偽証議論
		{
			{"res/cards/giron2/stock_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/stock_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/stock_card_p.png",	""}
		},
		// 3回目の偽証議論
		{
			{"res/cards/giron3/stock_card_r.png",	""},
			{"res/cards/giron3/stock_card_g.png",	""},
			{"res/cards/giron3/stock_card_y.png",	""},
			{"res/cards/giron3/stock_card_b.png",	""},
			{"",									""}
		},
		// 4回目の偽証議論
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5回目の偽証議論
		{
			{"",																	""},
			{"res/cards/giron5/stock_card_g.png",	"res/cards/giron5/stock_card_g2.png"},
			{"",																	""},
			{"res/cards/giron5/stock_card_b.png",									""},
			{"res/cards/giron5/stock_card_p.png",									""}
		},
		// 6回目の偽証議論
		{
			{"res/cards/giron6/stock_card_1.png",	""},
			{"res/cards/giron6/stock_card_2.png",	""},
			{"res/cards/giron6/stock_card_3.png",	""},
			{"res/cards/giron6/stock_card_4.png",	""},
			{"res/cards/giron6/stock_card_5.png",	""}
		}
	};
	// 反論カードの画像パス（赤, 緑, 黄, 青, ピンクの順番に, ない場合は空""に）
	std::string counterCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1回目の偽証議論
		{
			{"res/cards/giron1/countercard_red.png",	""},	// 赤
			{"",										""},	// 緑
			{"",										""},	// 黄
			{"",										""},	// 青
			{"res/cards/giron1/countercard_pink.png",	""}		// ピンク
		},
		// 2回目の偽証議論
		{
			{"res/cards/giron2/counter_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/counter_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/counter_card_p.png",	""}
		},
		// 3回目の偽証議論
		{
			{"res/cards/giron3/counter_card_r.png",	""},
			{"res/cards/giron3/counter_card_g.png",	""},
			{"res/cards/giron3/counter_card_y.png",	""},
			{"res/cards/giron3/counter_card_b.png",	""},
			{"",									""}
		},
		// 4回目の偽証議論
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5回目の偽証議論
		{
			{"",																		""},
			{"res/cards/giron5/counter_card_g.png",	"res/cards/giron5/counter_card_g2.png"},
			{"",																		""},
			{"res/cards/giron5/counter_card_b.png",										""},
			{"res/cards/giron5/counter_card_p.png",										""}
		},
		// 6回目の偽証議論
		{
			{"res/cards/giron6/counter_card_1.png",	""},
			{"res/cards/giron6/counter_card_2.png",	""},
			{"res/cards/giron6/counter_card_3.png",	""},
			{"res/cards/giron6/counter_card_4.png",	""},
			{"res/cards/giron6/counter_card_5.png",	""}
		}
	};
	// 反転カードの画像パス（赤, 緑, 黄, 青, ピンクの順番に, ない場合は空""に）
	std::string returnCardPath[GIRON_MAX][ENEMY_MAX][TESTIMONY_MAX] = {
		// 1回目の偽証議論
		{
			{"res/cards/giron1/countercard_return_red.png",		""},	// 赤
			{"",												""},	// 緑
			{"",												""},	// 黄
			{"",												""},	// 青
			{"res/cards/giron1/countercard_return_pink.png",	""}		// ピンク
		},
		// 2回目の偽証議論
		{
			{"res/cards/giron2/return_card_r.png",	""},
			{"",									""},
			{"res/cards/giron2/return_card_y.png",	""},
			{"",									""},
			{"res/cards/giron2/return_card_p.png",	""}
		},
		// 3回目の偽証議論
		{
			{"res/cards/giron3/return_card_r.png",	""},
			{"res/cards/giron3/return_card_g.png",	""},
			{"res/cards/giron3/return_card_y.png",	""},
			{"res/cards/giron3/return_card_b.png",	""},
			{"",									""}
		},
		// 4回目の偽証議論
		{
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""},
			{"",									""}
		},
		// 5回目の偽証議論
		{
			{"",																		""},
			{"res/cards/giron5/return_card_g.png",	"res/cards/giron5/return_card_g2.png"},
			{"",																		""},
			{"res/cards/giron5/return_card_b.png",										""},
			{"res/cards/giron5/return_card_p.png",										""}
		},
		// 6回目の偽証議論
		{
			{"res/cards/giron6/return_card_1.png",	""},
			{"res/cards/giron6/return_card_2.png",	""},
			{"res/cards/giron6/return_card_3.png",	""},
			{"res/cards/giron6/return_card_4.png",	""},
			{"res/cards/giron6/return_card_5.png",	""}
		}
	};
	// 取得・反論・反転カード画像のロード
	for (int i = 0; i < GIRON_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			for (int k = 0; k < TESTIMONY_MAX; k++)
			{
				if (!stockCardPath[i][j][k].empty()) { cgStockCard[i][j][k] = LoadGraph(stockCardPath[i][j][k].c_str()); }
				if (!counterCardPath[i][j][k].empty()) { cgCounterCard[i][j][k] = LoadGraph(counterCardPath[i][j][k].c_str()); }
				if (!returnCardPath[i][j][k].empty()) { cgReturnCard[i][j][k] = LoadGraph(returnCardPath[i][j][k].c_str()); }
			}
		}
	}

	// 取得前の手札配置の画像（黒）・取得直後の手札配置の画像（白）
	cgStockBrankCard = LoadGraph("res/cards/stock/stockcard_brank.png");
	cgStockWhiteCard = LoadGraph("res/cards/stock/stockcard_white.png");

	// 裏返し用画像
	img_path = "res/cards/counter/card_turn";
	anim.GetCG(img_path, 0, TURN_CARD_MAX, cgTurnCard);	// png画像

	// 反論パート正解時エフェクト
	// 偽証議論
	img_path = "res/Gironpartover/gironover";
	anim.GetCG(img_path, 1, ENDEFFECT_PATTERN_MAX, cgEndEffect);	// jpg画像
	//自傷議論
	img_path = "res/Jisyoupartover/jisyou";
	anim.GetCG(img_path, 1, JISYOU_ENDEFFECT_PATTERN_MAX, cgJisyou_EndEffect);	// jpg画像
	
	// 間違った場合の画像
	//偽証議論
	cgHanronMiss = LoadGraph("res/Scenegamemain/gisyou_miss_text.png");
	//自傷議論
	cgJishouHanronMiss = LoadGraph("res/Scenegamemain/jisyou_miss_text.png");

	//
	// SE・BGM
	//
	// ---タイトル---
	seTitleBGM = LoadSoundMem("res/sound/title_fo.mp3");

	// ---会話パート---
	seBGM[0] = LoadSoundMem("res/sound/kaiwa.mp3");
	seBGM[1] = LoadSoundMem("res/sound/kaiwa_bad.mp3");
	seBGM[2] = LoadSoundMem("res/sound/kaiwa_gironclear_fo.mp3");
	seBGM[3] = LoadSoundMem("res/sound/kaiwa_true.mp3");

	// ---怪しい箇所を睨むパート---
	seLookClear = LoadSoundMem("res/se/seLook/se_clear.mp3");
	seLookDamage = LoadSoundMem("res/se/seLook/se_damage.mp3");
	seLookHazure = LoadSoundMem("res/se/seLook/se_hazure.mp3");
	seLookSeikai = LoadSoundMem("res/se/seLook/se_seikai.mp3");
	seLookBGM = LoadSoundMem("res/se/seLook/look.mp3");

	// ---偽証議論パート---
	//音声
	seDamage = LoadSoundMem("res/sound/damage.mp3");
	seBGM1 = LoadSoundMem("res/sound/giron_bgm_oneloop.mp3");
	seBGM2 = LoadSoundMem("res/sound/gisyou-giron_cut.mp3");
	seTestimonyBreak = LoadSoundMem("res/se/se_testimony_break2.mp3");
	seGetTestimony = LoadSoundMem("res/se/se_get_testimony_db.mp3");
	seCardGathering = LoadSoundMem("res/se/se_card_gathering.mp3");
	seCardOpening = LoadSoundMem("res/se/se_card_opening.mp3");
	seCardSelecting = LoadSoundMem("res/se/se_card_selecting.mp3");
	seHazure = LoadSoundMem("res/se/se_hazure2.mp3");
	seCutin = LoadSoundMem("res/se/se_cutin.mp3");
	seCardTurning = LoadSoundMem("res/se/se_card_turning_dbcut.mp3"); //証言反転時
	seHitTestimony = LoadSoundMem("res/se/se_hit_testimony2.mp3"); //正解証言ヒット時
	seGard = LoadSoundMem("res/se/se_gard.mp3");
	seRedLaugh = LoadSoundMem("res/voice/r_1.wav");
	seGreenLaugh = LoadSoundMem("res/voice/g_1.wav");
	seYellowLaugh = LoadSoundMem("res/voice/y_1.wav");
	seBlueLaugh = LoadSoundMem("res/voice/b_1.wav");
	sePinkLaugh = LoadSoundMem("res/voice/p_1.wav");
	seSetsunaRough = LoadSoundMem("res/voice/s_22.wav");
	seSay = LoadSoundMem("res/sound/sound.mp3");
	seCutinVoice = LoadSoundMem("res/voice/s_13_2.wav");
	seDecide = LoadSoundMem("res/se/se_seikai.mp3");
	seCursor = LoadSoundMem("res/se/se_cursor_move.mp3");

	// ---自傷推理パート---
	for (int n = 0; n < 72; n++)
	{
		std::string img = "res/JishouChoicepart/jisyou_BG/zisyou_BG" + std::to_string(n) + ".jpg";
		jisyou_cgBg[n] = LoadGraph(img.c_str());
	}
	se_choiceBGM[0] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q1.mp3");
	se_choiceBGM[1] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q2.mp3");
	se_choiceBGM[2] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q3.mp3");
	se_choiceBGM[3] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q4.mp3");
	se_choiceBGM[4] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q5.mp3");
	se_choiceBGM[5] = LoadSoundMem("res/sound/jisyouBGM/maou_bgm_piano17_q6.mp3");


	// ---クレジット---
	_cgBgCredit = LoadGraph("res/CG_credit.png");
	seCregit = LoadSoundMem("res/sound/endcredit.mp3");

	// ---ゲームオーバー画面---
	seGameOverBGM = LoadSoundMem("res/sound/gameover_timeshift.mp3");;	// BGM;

	//音量調整
	ChangeVolumeSoundMem(255 * 70 / 100, sePinkLaugh);
	ChangeVolumeSoundMem(255 * 60 / 100, seCursor);
	ChangeVolumeSoundMem(255 * 75 / 100, seDecide);
	ChangeVolumeSoundMem(255 * 70 / 100, seCardTurning);

	//動画
	mvGiron_ikou = LoadGraph("res/movie/haikei_ikou.mp4");
	mvJishou_ikou = LoadGraph("res/movie/jishou_seni.mp4");

	//
	// エフェクト
	//

	// ダメージエフェクト
	std::string effect_path;
	//efectType 0:ダメージエフェクト 1:ダメージ演出 2:ガード演出
	for (int efectType = 0; efectType < EFFECT_TYPE_MAX; efectType++)
	{
		switch (efectType)
		{
		case 0:
			for (int i = 0; i < DAMAGE_EFFECT_ANINAM_NAM; i++)
			{
				effect_path = "res/effect/damage_effect_000" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
			}
			break;
		case 1:

			for (int i = 0; i < DAMAGE_DIRECTION_ANINAM_NAM; i++)
			{

				effect_path = "res/effect/effect_damage_0" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
				if (i == DAMAGE_DIRECTION_ANINAM_NAM - 1)
				{
					for (int ii = 0; ii < DAMAGE_DIRECTION_ANINAM_NAM; ii++)
					{
						effect_path = "res/effect/effect_damage_0" + std::to_string(i - ii) + ".png";
						cgEffect[efectType][i + ii] = LoadGraph(effect_path.c_str());
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++)
			{
				effect_path = "res/card_break/10" + std::to_string(i) + ".png";
				cgEffect[efectType][i] = LoadGraph(effect_path.c_str());
			}
			break;
		case 3:
			for (int i = 0; i < 8; i++)
			{
				LoadDivGraph("res/effect/hit_effect.png", 5, 5, 1, 250, 250, cgEffect[efectType]);
			}
			break;
		}
	}

	// 防御エフェクト
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/gate/gate/gate" + std::to_string(n) + ".png";
		LockEffect[0][n + 1] = LoadGraph(img.c_str());
	}
	for (int p = 1; p < 5; p++) {
		for (int n = 0; n < 10; n++)
		{
			std::string img = "res/gate/gate_breaking_00" + std::to_string(p) + "/gate" + std::to_string(n) + ".png";
			LockEffect[p][n + 1] = LoadGraph(img.c_str());
		}
	}

	// 防御回復エフェクト
	for (int i = 0; i < 9; i++)
	{
		effect_path = "res/gate/reset/gate_reset_" + std::to_string(i) + ".png";
		gateReset[i] = LoadGraph(effect_path.c_str());
	}
}

// 読み込みが終了してたら1、まだなら0
int Global::IsLoadFinish()
{
	if (GetASyncLoadNum() > 0)
	{
		return 0;	// 読み込みがまだ途中
	}
	return 1;		// 読み込み終了してる
}
