#ifndef __FFT_FILTER_HH__
#define __FFT_FILTER_HH__

#include "_dsp.hh"

class Through : public DSP {
    long l;
    int SHIFT;
    float OV;
    float *x;
    float *yf;
    float *w;

public:
    Through(const dsp_config &cfg) : x(NULL), yf(NULL), w(NULL) {
        set(cfg);
    }
    
    void set(const dsp_config &cfg, ...) override {
        FFT::init(cfg.FFT_SIZE);
        l = 0;
        SHIFT = cfg.FFT_SIZE/cfg.OL;
        OV = 2.0*SHIFT/cfg.FFT_SIZE;

        if(x != NULL) delete[] x;
        x = new float[cfg.FFT_SIZE];
        if(yf != NULL) delete[] yf;
        yf = new float[cfg.FFT_SIZE];
        if(w != NULL) delete[] w;
        w = new float[cfg.FFT_SIZE];

        for(int i = 0; i < cfg.FFT_SIZE; ++i){
            w[i] = 0.5*(1.0-cos(2.0*M_PI*i/(float)cfg.FFT_SIZE));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        x[l] = s[t];
        l = (l+1) % cfg.FFT_SIZE;
        if(l % SHIFT == 0) {
            for(int i = 0; i < cfg.FFT_SIZE; ++i) {
                FFT::xin[i] = x[(l+i) % cfg.FFT_SIZE] * w[i];
            }

            FFT::fft();
            for(int i = 0; i < cfg.FFT_SIZE; ++i){
                FFT::Xr[i] = FFT::Xr[i];
                FFT::Xi[i] = FFT::Xi[i];
            }
            
            FFT::ifft();
            for(int i = 0; i < cfg.FFT_SIZE; ++i){
                if(i >= cfg.FFT_SIZE-SHIFT) yf[(l+i)%cfg.FFT_SIZE] = FFT::z[i] / cfg.FFT_SIZE * OV;
                else yf[(l+i)%cfg.FFT_SIZE] = yf[(l+i)%cfg.FFT_SIZE] + FFT::z[i] / cfg.FFT_SIZE * OV;
            }
        }
        y[t] = yf[l];
    }

    ~Through() {
        delete[] x;
        delete[] yf;
        delete[] w;
    }
};

class BPF : public DSP {
    long l;
    int SHIFT;
    float OV;
    float *x;
    float *yf;
    float *w;
    int FL;
    int FH;

public:
    BPF(const dsp_config &cfg, const float &fl, const float &fh) : x(NULL), yf(NULL), w(NULL) {
        set(cfg, fl, fh);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        FL = va_arg(ap, double);
        FH = va_arg(ap, double);
        va_end(ap);

        FFT::init(cfg.FFT_SIZE);
        l = 0;
        SHIFT = cfg.FFT_SIZE/cfg.OL;
        OV = 2.0*SHIFT/cfg.FFT_SIZE;

        if(x != NULL) delete[] x;
        x = new float[cfg.FFT_SIZE];
        if(yf != NULL) delete[] yf;
        yf = new float[cfg.FFT_SIZE];
        if(w != NULL) delete[] w;
        w = new float[cfg.FFT_SIZE];

        for(int i = 0; i < cfg.FFT_SIZE; ++i){
            w[i] = 0.5*(1.0-cos(2.0*M_PI*i/(float)cfg.FFT_SIZE));
        }

        FL = (float)FL / cfg.Fs * cfg.FFT_SIZE;
        FH = (float)FH / cfg.Fs * cfg.FFT_SIZE;
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        x[l] = s[t];
        l = (l+1) % cfg.FFT_SIZE;
        if(l % SHIFT == 0) {
            for(int i = 0; i < cfg.FFT_SIZE; ++i) {
                FFT::xin[i] = x[(l+i) % cfg.FFT_SIZE] * w[i];
            }

            FFT::fft();
            for(int i = 0; i < cfg.FFT_SIZE / 2; ++i){
                if(i < FL || i > FH){
                    FFT::Xr[i] = FFT::Xi[i] = 0;
                }
                FFT::Xr[cfg.FFT_SIZE - i] = FFT::Xr[i];
                FFT::Xi[cfg.FFT_SIZE - i] = -FFT::Xi[i];   
            }
            
            FFT::ifft();
            for(int i = 0; i < cfg.FFT_SIZE; ++i){
                if(i >= cfg.FFT_SIZE-SHIFT) yf[(l+i)%cfg.FFT_SIZE] = FFT::z[i] / cfg.FFT_SIZE * OV;
                else yf[(l+i)%cfg.FFT_SIZE] = yf[(l+i)%cfg.FFT_SIZE] + FFT::z[i] / cfg.FFT_SIZE * OV;
            }
        }
        y[t] = yf[l];
    }

    ~BPF() {
        delete[] x;
        delete[] yf;
        delete[] w;
    }
};

class MAXfreq : public DSP {
    long l;
    int SHIFT;
    float OV;
    float *x;
    float *yf;
    float *w;
    float pitch, max;
    int max_pos;
    
public:
    MAXfreq(const dsp_config &cfg) : x(NULL), yf(NULL), w(NULL) {
        set(cfg);
    }
    
    void set(const dsp_config &cfg, ...) override {
        FFT::init(cfg.FFT_SIZE);
        l = 0;
        SHIFT = cfg.FFT_SIZE/cfg.OL;
        OV = 2.0*SHIFT/cfg.FFT_SIZE;

        if(x != NULL) delete[] x;
        x = new float[cfg.FFT_SIZE];
        if(yf != NULL) delete[] yf;
        yf = new float[cfg.FFT_SIZE];
        if(w != NULL) delete[] w;
        w = new float[cfg.FFT_SIZE];

        for(int i = 0; i < cfg.FFT_SIZE; ++i){
            w[i] = 0.5*(1.0-cos(2.0*M_PI*i/(float)cfg.FFT_SIZE));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        x[l] = s[t];
        l = (l+1) % cfg.FFT_SIZE;
        if(l % SHIFT == 0) {
            for(int i = 0; i < cfg.FFT_SIZE; ++i) {
                FFT::xin[i] = x[(l+i) % cfg.FFT_SIZE] * w[i];
            }

            max = 0;
            max_pos = 0;
            for(int i = 0; i < cfg.FFT_SIZE / 2; ++i){
                if(max < FFT::Xamp[i]) {
                    max = FFT::Xamp[i];
                    max_pos = i;
                }
            }
            pitch = cfg.Fs*(float)max_pos/cfg.FFT_SIZE;
            printf("pitch = %f[Hz]\n", pitch);
            
            FFT::ifft();
            for(int i = 0; i < cfg.FFT_SIZE; ++i){
                if(i >= cfg.FFT_SIZE-SHIFT) yf[(l+i)%cfg.FFT_SIZE] = FFT::z[i] / cfg.FFT_SIZE * OV;
                else yf[(l+i)%cfg.FFT_SIZE] = yf[(l+i)%cfg.FFT_SIZE] + FFT::z[i] / cfg.FFT_SIZE * OV;
            }
        }
        y[t] = yf[l];
    }

    ~MAXfreq() {
        delete[] x;
        delete[] yf;
        delete[] w;
    }
};

#endif
