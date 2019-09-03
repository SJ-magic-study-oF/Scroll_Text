/************************************************************
************************************************************/
#include "ScrollText.h"

/************************************************************
************************************************************/

/******************************
******************************/
SCROLL_TEXT::SCROLL_TEXT(){
	/********************
	********************/
	fp = fopen("../../../data/sample.cpp", "r");
	if(fp == NULL) { ERROR_MSG(); std::exit(1); }
	
	/********************
	********************/
	 font.load("font/RictyDiminishedDiscord-Bold.ttf", 12, true, true, true);
	// font.load("font/RictyDiminished-Regular.ttf", 12, true, true, true);
	
	TextOffset = get_FontHeight();
}

/******************************
******************************/
SCROLL_TEXT::~SCROLL_TEXT(){
}

/******************************
******************************/
int SCROLL_TEXT::get_FontHeight()
{
	return int(font.stringHeight("0123456789abcdefghijklmnopqrstuvwxyz") * 1.5);
}

/******************************
******************************/
void SCROLL_TEXT::Read_1Line_FromFile(string& str_Line)
{
	/********************
	********************/
	char buf[BUF_SIZE_S];
	
	if(fgets(buf, BUF_SIZE_S, fp) == NULL){
		fseek(fp, 0, SEEK_SET);
		
		if(fgets(buf, BUF_SIZE_S, fp) == NULL){
			printf("No Contents in File\n");
			std::exit(1);
		}else{
			/*
			printf("File Loop\n");
			fflush(stdout);
			*/
		}
	}
	
	/********************
	********************/
	str_Line = buf;
	// TabToSpacex4(str_Line); // 改めて動作checkの結果、不要だった。
	// str_replace(str_Line, "static", "SAIJO");
}

/******************************
description
	font.drawString(str_line.c_str(), 0, 0);
	では、str_line.c_str()に"\t"が入っていても無視される.
	そこで、space x 4にreplaceしておく.
	
	2019.09.03
		動作checkしてみたら、"\t"は、きちんと描画に反映されていた : よって本methodは不要だけど、一応残しておく。
******************************/
void SCROLL_TEXT::TabToSpacex4(string& s)
{
	string Tab = "\t";
	string Space   = "    ";
	
	// size_t pos = s.find_first_of(YenN, 0); // NG. don't use find_first_of here.
	size_t pos = s.find(Tab, 0);

	while(pos != string::npos){
		s.replace(pos, Tab.length(), Space);
		pos = s.find(Tab, pos);
	}
}

/******************************
description
	外部fileから文字列を読み込んだ時、
	string文字列中の"\n"は実は"\\n"(\\ + n の２文字)、改行文字のリテラルではない.
	本methodは、これを変換するためのmethod.
	
参考
	http://d.hatena.ne.jp/p95095yy/20050222/1109119001
	注意)
		本URLでは、find_first_of を使っているが、間違い.
		find_first_of()は、「列挙された1文字ずつを」探しに行く.
		正解は、「文字列」を探しに行く find().
******************************/
void SCROLL_TEXT::YennToCR(string& s)
{
	string YenN = "\\n";
	string CR   = "\n";
	
	// size_t pos = s.find_first_of(YenN, 0); // NG. don't use find_first_of here.
	size_t pos = s.find(YenN, 0);

	while(pos != string::npos){
		s.replace(pos, YenN.length(), CR);
		pos = s.find(YenN, pos);
	}
}

/******************************
******************************/
void SCROLL_TEXT::str_replace(string& str, const string str_from, const string str_to)
{
	// size_t pos = s.find_first_of(YenN, 0); // NG. don't use find_first_of here.
	size_t pos = str.find(str_from, 0);

	while(pos != string::npos){
		str.replace(pos, str_from.length(), str_to);
		pos = str.find(str_from, pos);
	}
}

/******************************
******************************/
void SCROLL_TEXT::setup(){
	fbo.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGBA, 4);
	// fbo.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGBA);
	clear_fbo(fbo);
	
	TopId = 0;
	for(int i = 0; i < NUM_TEXT_LINES; i++){
		Read_1Line_FromFile(str_Text[TopId + i]);
	}
}

/******************************
******************************/
void SCROLL_TEXT::update(){
	/********************
	********************/
	int now = ofGetElapsedTimeMillis();
	
	/********************
	********************/
	TextOffset -= int(ProceedSpeedPerSec * (now - LastINT) / 1000);
	if(TextOffset <= 0){
		int NumProceed = abs(TextOffset) / get_FontHeight() + 1;
		
		for(int i = 0; i < NumProceed; i++){
			int id = NthNextin_strText(TopId, i);
			Read_1Line_FromFile(str_Text[id]);
		}
		
		TopId += NumProceed;
		TextOffset += int(NumProceed * get_FontHeight());
	}
	
	/********************
	********************/
	draw_fbo();
	
	/********************
	********************/
	LastINT = now;
}

/******************************
******************************/
int SCROLL_TEXT::NthNextin_strText(int from, int Nth){
	int ret = from + Nth;
	return ret % NUM_TEXT_LINES;
}

/******************************
******************************/
void SCROLL_TEXT::Toggle_BackClear()
{
	if(b_BackClear)	b_BackClear = false;
	else			b_BackClear = true;
	
	printf("b_BackClear = %d\n", b_BackClear);
	fflush(stdout);
}

/******************************
******************************/
void SCROLL_TEXT::draw(){
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

/******************************
******************************/
void SCROLL_TEXT::draw_fbo(){
	fbo.begin();
		ofDisableAlphaBlending();
		ofEnableSmoothing();
		// ofDisableSmoothing();
		/********************
		clearのmethodで差異あり。
			ofClear(0);
		より
			ofBackground(0)
		の方がtextが綺麗だった。
		********************/
		if(b_BackClear) ofClear(0);
		else			ofBackground(0);
		
		ofSetColor(180);
		
		int stringHeight = get_FontHeight();
		
		for(int i = 0; i < NUM_TEXT_LINES; i++){
			int id = NthNextin_strText(TopId, i);
			font.drawString(str_Text[id].c_str(), 0, int(TextOffset + i * stringHeight));
		}
	fbo.end();
}

/******************************
******************************/
void SCROLL_TEXT::clear_fbo(ofFbo& fbo)
{
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();
}





