#include "word.h"
#include "winmain.h"
#include "scenegamemain.h"

//菊池担当箇所　ファイル全て

Word::Word()
{
	
}

Word::~Word() 
{

}

//言葉の移動
void Word::Move(int wordType, int chapter)
{
	//チャプターごとに設定された速度で動く
	switch (wordType) {
		case 1://暴言		
			switch (chapter)
			{
				//チュートリアル
				case 0:
					y += THOUGHTLESSWORDS_SPEED_CHAPT0;
					break;
				//チャプター１
				case 1:
					y += THOUGHTLESSWORDS_SPEED_CHAPT1;
					break;
				//チャプター２
				case 2:
					y += THOUGHTLESSWORDS_SPEED_CHAPT2;
					break;
				//チャプター３
				case 3:
					y += THOUGHTLESSWORDS_SPEED_CHAPT3;
					break;
				//チャプター４
				case 4:
					y += THOUGHTLESSWORDS_SPEED_CHAPT4;
					break;
				//チャプター５
				case 5:
					y += THOUGHTLESSWORDS_SPEED_CHAPT5;
					break;
			}
		//文字の拡大
		scale += THOUGHTLESSWORDS_SCALE;
		break;

		case 2:	//証言		
			switch (chapter)
			{
				//チュートリアル
				case 0:
					y += TESTIMONY_SPEED_CHAPT0;
					break;
				//チャプター１
				case 1:
					y += TESTIMONY_SPEED_CHAPT1;
					break;
				//チャプター２
				case 2:
					y += TESTIMONY_SPEED_CHAPT2;
					break;
				//チャプター３
				case 3:
					y += TESTIMONY_SPEED_CHAPT3;
					break;
				//チャプター４
				case 4:
					y += TESTIMONY_SPEED_CHAPT4;
					break;
				//チャプター５
				case 5:
					y += TESTIMONY_SPEED_CHAPT5;
					break;
			}
		//文字の拡大
		scale += TESTIMONY_SCALE;
		break;
	}

}

//使用した言葉の消去
void Word::EraseWord()
{
	use = 0;
}
