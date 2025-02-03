#pragma once
#include <tchar.h>
// 本プログラムの全てのオブジェクトの基底クラス
class ObjectBase {
public:
    ObjectBase(); // コンストラクタ
    ObjectBase(const TCHAR* fileName); // コンストラクタは引数を変えれば何個でも作成可能
    virtual ~ObjectBase(); // デストラクタ

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetW() const { return w; }
    int GetH() const { return h; }

    int x;
    int y;
    int w;
    int h;

protected:
    // protected にして継承先クラスで使用可能にする
    // 下記のメンバh変数が、今回の基底に相応しい種類と設計する
    
};
