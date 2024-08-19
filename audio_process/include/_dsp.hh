#ifndef __DSP_HH__
#define __DSP_HH__

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
    unsigned MEM_SIZE;          // 音声メモリのサイズ
    unsigned Fs;                // リアルタイム処理のサンプリング周波数
    unsigned BUF_SIZE;          // 各バッファのサイズ
    unsigned FFT_SIZE;          // FFT点数
    unsigned OL;                // フレームシフト ＝ FFT_SIZE / OL
} dsp_config;

class DSP {
    bool enable;
public:
    virtual void set(const dsp_config &cfg, ...) {};
    virtual void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) {};
};

class FFT final {
    FFT() {}
    ~FFT() { release(); }
    static void hold();
    static void release();
    static void bitr();
    static void Wnk();
public:
    static unsigned FFT_SIZE;          // FFT点数
    static float *Wr, *Wi;             // FFT 重み
    static float *Fr, *Fi, *Xr, *Xi;   // 実部と虚部
    static float *xin, *z;             // FFT入力と出力
    static float *Xamp;                // 振幅スペクトル
    static float omega;                // FFT角周波数
    static int St, *br;                // FFTステージ番号，ビット反転
    static void init(const unsigned &fft_size);
    static void fft();
    static void ifft();
};

#endif
