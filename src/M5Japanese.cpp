#include"M5Japanese.h"

void M5Japanese::begin(int sdPin){
  //style
  textSize = defaultTextSize = 8;
  textColor = defaultTextColor = WHITE;
  backgroundColor = defaultBackgroundColor = BLACK;
  drawBackground = defaultDrawBackground = false;
  //print
  cursorX = cursorY = 0;
  //sdfonts
  SDfonts.init(4);
  //get LF in utf-16
  sdfonts::charUFT8toUTF16(&LF,"\n");
}

//スタイル

void M5Japanese::setTextSize(uint8_t size){
  textSize = size;
}

void M5Japanese::setTextColor(uint16_t color){
  textColor = color;
}

void M5Japanese::setBackgroundColor(uint16_t color){
  backgroundColor = color;
}

void M5Japanese::setDrawBackground(bool flag){
  drawBackground = flag;
}

void M5Japanese::setColor(uint16_t textColor,uint16_t backgroundColor){
  setTextColor(textColor);
  setBackgroundColor(backgroundColor);
}

void M5Japanese::setStyle(uint8_t textSize,uint16_t textColor,bool drawBackground,uint16_t backgroundColor){
  setTextSize(textSize);
  setColor(textColor,backgroundColor);
  setDrawBackground(drawBackground);
}

//デフォルトのスタイル

void M5Japanese::setDefaultTextSize(uint8_t size){
  defaultTextSize = size;
}

void M5Japanese::setDefaultTextColor(uint16_t color){
  defaultTextColor = color;
}

void M5Japanese::setDefaultBackgroundColor(uint16_t color){
  defaultBackgroundColor = color;
}

void M5Japanese::setDefaultDrawBackground(bool flag){
  defaultDrawBackground = flag;
}

void M5Japanese::setDefaultColor(uint16_t textColor,uint16_t backgroundColor){
  setDefaultTextColor(textColor);
  setDefaultBackgroundColor(backgroundColor);
}

void M5Japanese::setDefaultStyle(uint8_t textSize,uint16_t textColor,bool drawBackground,uint16_t backgroundColor){
  setDefaultTextSize(textSize);
  setDefaultColor(textColor,backgroundColor);
  setDefaultDrawBackground(drawBackground);
}

//リセット

void M5Japanese::resetTextSize(){
  textSize = defaultTextSize;
}

void M5Japanese::resetTextColor(){
  textColor = defaultTextColor;
}

void M5Japanese::resetBackgroundColor(){
  backgroundColor = defaultBackgroundColor;
}

void M5Japanese::resetDrawBackground(){
  drawBackground = defaultDrawBackground;
}

void M5Japanese::resetColor(){
  resetTextColor();
  resetBackgroundColor();
  resetDrawBackground();
}

void M5Japanese::resetStyle(){
  resetTextSize();
  resetTextColor();
  resetBackgroundColor();
  resetDrawBackground();
};

//文字列描画
int M5Japanese::getCursorX(){
  return cursorX;
}

int M5Japanese::getCursorY(){
  return cursorY;
}

void M5Japanese::setCursor(int x,int y){
  cursorX = x;
  cursorY = y;
}

int M5Japanese::textWidth(char *str){
  uint8_t buf[MAXFONTLEN];
  SDfonts.open();
  SDfonts.setFontSize(textSize);
  int maxX = 0;
  int sumX = 0;
  
  while(str = SDfonts.getFontData(buf,str)){
    if(SDfonts.getCode() == LF){
      sumX = 0;
      continue;
    }

    sumX += SDfonts.getWidth();
    maxX = (maxX < sumX)? sumX : maxX;
  }

  SDfonts.close();
  return maxX;
}

int M5Japanese::textWidth(String str){
  return textWidth(const_cast<char*>(str.c_str()));
}

int M5Japanese::textHeight(char *str){
  uint8_t buf[MAXFONTLEN];
  SDfonts.open();
  SDfonts.setFontSize(textSize);

  int sumY = textSize;
  
  while(str = SDfonts.getFontData(buf,str)){
    if(SDfonts.getCode() == LF){
      sumY += SDfonts.getHeight();
    }
  }

  SDfonts.close();
  return sumY;
}

int M5Japanese::textHeight(String str){
  return textHeight(const_cast<char*>(str.c_str()));
}

void M5Japanese::print(char *str){
  drawStringOnCursor(str);
}

void M5Japanese::print(String str){
  print(const_cast<char*>(str.c_str()));
}

void M5Japanese::println(char *str){
  drawStringOnCursor(str,true);
}

void M5Japanese::println(String str){
  println(const_cast<char*>(str.c_str()));
}

void M5Japanese::printf(const char *format,...){
  char str[128];
  va_list args;
  
  va_start(args,format);
  vsprintf(str,format,args);
  va_end(args);

  print(str);
}

void M5Japanese::drawString(char *str,int startX,int startY){
  uint8_t buf[MAXFONTLEN];
  SDfonts.open();
  SDfonts.setFontSize(textSize);

  int originalStartX = startX;  
  
  while(str = SDfonts.getFontData(buf,str)){
    if(SDfonts.getCode() == LF){
      startX = originalStartX;
      startY += SDfonts.getHeight();
      continue;
    }
    
    int y=startY;
    uint8_t bl = SDfonts.getRowLength();
    for(uint8_t i=0;i<SDfonts.getLength();i+=bl){
      int x=startX;
      for(uint8_t j=0;j<bl;j++){
        drawByte(buf[i+j],x,y);
        x+=8;
      }
      y++;
    }
    startX += SDfonts.getWidth();
  }
  SDfonts.close();
}

void M5Japanese::drawString(String str,int startX,int startY){
  drawString(const_cast<char*>(str.c_str()),startX,startY);
}

void M5Japanese::drawCentreString(char *str,int centerX,int centerY){
  int width = textWidth(str);
  int height = textHeight(str);
  drawString(str,centerX - width/2,centerY - height/2);
}

void M5Japanese::drawCentreString(String str,int centerX,int centerY){
  drawCentreString(const_cast<char*>(str.c_str()),centerX,centerY);
}

void M5Japanese::drawRightString(char *str,int rightX,int startY){
  int width = textWidth(str);
  drawString(str,rightX - width,startY);
}

void M5Japanese::drawRightString(String str,int rightX,int startY){
  drawRightString(const_cast<char*>(str.c_str()),rightX,startY);
}

void M5Japanese::drawByte(uint8_t d,int x,int y){
  for(uint8_t i=0;i<8;++i){
    if(d & 0x80>>i){
      M5.Lcd.drawPixel(x+i,y,textColor);
    }else{
      if(drawBackground)M5.Lcd.drawPixel(x+i,y,backgroundColor);
    }
  }
}

void M5Japanese::drawStringOnCursor(char *str,bool newLine){
  uint8_t buf[MAXFONTLEN];
  SDfonts.open();
  SDfonts.setFontSize(textSize);
  
  int tmpX = cursorX;
  int tmpY = cursorY;
  
  while(str = SDfonts.getFontData(buf,str)){
    if(SDfonts.getCode() == LF){
      cursorX=0;
      tmpY = cursorY+= SDfonts.getHeight();
      continue;
    }
    
    uint8_t bl = SDfonts.getRowLength();
    for(uint8_t i=0;i<SDfonts.getLength();i+=bl){
      int tmpX = cursorX;
      for(uint8_t j=0;j<bl;j++){
        drawByte(buf[i+j],tmpX,cursorY);
        tmpX+=8;
      }
      cursorY++;
    }
    cursorX += SDfonts.getWidth();
    cursorY = tmpY;
  }

  if(newLine){
    cursorX = 0;
    cursorY += SDfonts.getHeight();
  }
  
  SDfonts.close();
}

M5Japanese M5J;