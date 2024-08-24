#ifndef __CONFIG_HH__
#define __CONFIG_HH__

#include <stdio.h>
#include <math.h>
#include <vector>

struct dsp_config {
    unsigned MEM_SIZE;          // 音声メモリのサイズ
    unsigned Fs;                // リアルタイム処理のサンプリング周波数
    unsigned BUF_SIZE;          // 各バッファのサイズ
    unsigned FFT_SIZE;          // FFT点数
    unsigned OL;                // フレームシフト ＝ FFT_SIZE / OL
};

struct Effector {
    bool is_enabled;
    Effector();
    bool toggle();
    virtual void set(const dsp_config *cfg, const std::vector<float>::iterator &it);
    virtual void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y);
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
