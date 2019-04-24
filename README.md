M5Stack用日本語ライブラリ
====

## 概要
[Arduino用漢字フォントライブラリ](https://github.com/Tamakichi/Arduino-KanjiFont-Library-SD)をM5Stack上で簡単に使えるようにするライブラリ。なるべく公式ライブラリの仕様に合わせるようにした。ほぼ自分用。
![IMG_3796](https://user-images.githubusercontent.com/16350703/56672837-11e74a00-66f2-11e9-90bd-93fd046dc73d.JPG)

## インストール

1. Tamakichiさんの [Arduino用漢字フォントライブラリ](https://github.com/Tamakichi/Arduino-KanjiFont-Library-SD) をダウンロードし、  
tarontさんの [M5Stackで日本語表示](https://qiita.com/taront/items/7900c88b9e9782c33b08) を参考にしてM5Stackで使えるように変更して、  
ライブラリのREADMEを参考にしてインストールする。

2. 本ライブラリをダウンロードしてArduinoのライブラリフォルダに配置する。  
例: 

```
libraries
  └──M5Japanese/
          ├── README.md
          ├── keywords.txt
          ├── library.properties
          └── src
              ├── M5Japanese.cpp
              └── M5Japanese.h
```

## 使い方
`M5Japanese.h`をインクルードする。  
`M5.begin()`後に`M5J.begin()`で初期化を行うと使えるようになる。  
フォントサイズは `8 10 12 14 16 20 24` のみ。(今後自由に指定できるようにしたい)  
関数一覧はこちらから [M5Japanese.h](https://github.com/ueken0307/m5stack-japanese-language-library/blob/master/src/M5Japanese.h)  

## サンプル
```c
#include<M5Stack.h>
#include<WiFi.h>
#include<M5Japanese.h>

void setup(){
  M5.begin();
  M5J.begin();
  M5J.setTextSize(16);

  M5J.setDefaultStyle(12,WHITE);
  M5J.setStyle(16,BLUE,true,WHITE);
  M5J.println("Arduino用漢字フォントライブラリ");
  M5J.resetStyle();
  M5J.println("をM5Stack上で簡単に使えるようにするライブラリ。");
  M5J.setTextColor(RED);
  M5J.println("なるべく公式ライブラリの仕様に合わせるようにした。");
  M5J.setTextColor(WHITE);
  M5J.setTextSize(24);
  char *me = "自分";
  M5J.printf("ほぼ%s用\n",me);
}

void loop() {
}

```

## 今後
- サンプルプログラムを書く
- M5Stackの仕様に依存しすぎてる部分が多いのでもう少し柔軟にする  
- ダブルバッファリングなどにも対応できるようにする  
- フォントサイズをsdfontsに用意されているサイズ以外も可能にする  
- drawRightStringを適切な挙動に変更する  
- drawCentreStringを適切な挙動に変更する  
- 文字列内の改行で `\n` しか対応してないから必要があればそれ以外も対応する。  