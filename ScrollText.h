/************************************************************
概要
	text fileを読み込み、単にscrollする。
	単純だが、syphonでunity側へ送るなどすれば、coolなtextureとして汎用性が高いので、まとめておく。
	
tips
	fbo background
		draw to fboで、
		ofClear(0); vs ofBackground(0); で差異あり : ofBackground(0) の方が綺麗だった
	
	text 表示位置関連の変数は、doubleでなくintの方が動くがsmooth
		doubleにすることで、ユラユラしながら動作するようになってしまった。
		
		これは直感的にはわかりにくいが、以下のように考えるとわかり易い。
		表示位置固定(analogue的にoffsetを動かすのでなく)で文字の内容を一列ずつDigitalに動かして行く(L10にあった文字列を次の瞬間、L9に表示する、というように)と、
		カタカタ感はあるが、ユラユラせず、カッチリした動きになる。
		offsetをdoubleでなく、intで持つことは、この動きに近くなると言うことなので、カッチリ動作するように見える。
	
参考URL
	C++ 文字列の検索を行う方法【std::string｜find／find_first_of／search】
		https://marycore.jp/prog/cpp/std-string-find-search/
		
	std::string 中の"\n"を改行コードに変換する関数。
		http://d.hatena.ne.jp/p95095yy/20050222/1109119001
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class SCROLL_TEXT : private Noncopyable{
private:
	/****************************************
	****************************************/
	enum{
		FBO_WIDTH		= 1280,
		FBO_HEIGHT		= 720,
	};
	enum{
		NUM_TEXT_LINES = 30,
	};
	
	/****************************************
	****************************************/
	bool b_BackClear = false;
	
	ofFbo fbo;
	int TopId = 0;
	string str_Text[NUM_TEXT_LINES];
	FILE* fp = NULL;
	
	ofTrueTypeFont font;
	const double ProceedSpeedPerSec = 50;
	int TextOffset;
	int LastINT = 0;
	
	/****************************************
	****************************************/
	int get_FontHeight();
	void draw_fbo();
	void clear_fbo(ofFbo& fbo);
	void TabToSpacex4(string& s);
	void Read_1Line_FromFile(string& str_Line);
	int NthNextin_strText(int from, int Nth);
	void YennToCR(string& s);
	void str_replace(string& str, const string str_from, const string str_to);
	
public:
	/****************************************
	****************************************/
	SCROLL_TEXT();
	~SCROLL_TEXT();
	void setup();
	void update();
	void draw();
	
	void Toggle_BackClear();
};


