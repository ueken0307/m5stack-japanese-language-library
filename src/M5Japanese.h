#ifndef ___M5JAPANESE___
#define ___M5JAPANESE___

#include<Arduino.h>
#include<M5Stack.h>
#include<sdfonts.h>

class M5Japanese{
public:
  void begin(int sdPin = 4);

  //スタイル
  void setTextSize(uint8_t size);
  void setTextColor(uint16_t color);
  void setBackgroundColor(uint16_t color);
  void setDrawBackground(bool flag);
  void setColor(uint16_t textColor,uint16_t backgroundColor);
  void setStyle(uint8_t textSize,uint16_t textColor,bool drawBackground = false,uint16_t backgroundColor = BLACK);

  //デフォルトのスタイル
  void setDefaultTextSize(uint8_t size);
  void setDefaultTextColor(uint16_t color);
  void setDefaultBackgroundColor(uint16_t color);
  void setDefaultDrawBackground(bool flag);
  void setDefaultColor(uint16_t textColor,uint16_t backgroundColor);
  void setDefaultStyle(uint8_t textSize,uint16_t textColor,bool drawBackground = false,uint16_t backgroundColor = BLACK);
  
  //リセット(スタイルをデフォルトの設定値にする)
  void resetTextSize();
  void resetTextColor();
  void resetBackgroundColor();
  void resetDrawBackground();
  void resetColor();
  void resetStyle();

  //文字列描画
  int getCursorX();
  int getCursorY();
  void setCursor(int x,int y);
  int textWidth(char *str);
  int textWidth(String str);
  int textHeight(char *str);
  int textHeight(String str);
  void print(char *str);
  void print(String str);
  void println(char *str);
  void println(String str);
  void printf(const char *format,...);
  void drawString(char *str,int startX,int startY);
  void drawString(String str,int startX,int startY);
  void drawCentreString(char *str,int centerX,int centerY);
  void drawCentreString(String str,int centerX,int centerY);
  void drawRightString(char *str,int rightX,int startY);
  void drawRightString(String str,int rightX,int startY);
  
private:
  void drawByte(uint8_t d,int x,int y);
  void drawStringOnCursor(char *str,bool newLine = false);

  //style
  uint8_t textSize, defaultTextSize;
  uint16_t textColor, defaultTextColor;
  uint16_t backgroundColor, defaultBackgroundColor;
  bool drawBackground, defaultDrawBackground;

  //LF
  uint16_t LF;

  //print
  int cursorX, cursorY;
};

extern M5Japanese M5J;

#endif