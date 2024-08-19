#ifndef __INSTRUMENT_EFFECT_HH__
#define __INSTRUMENT_EFFECT_HH__

#include "_dsp.hh"

class Echo : public DSP {
    int t_Delay;
    int L;
    int M;
    float a;

public:
    Echo(const dsp_config &cfg, const int &L, const int &M, const float &a) {
        set(cfg, L, M, a);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        L = va_arg(ap, int);
        M = va_arg(ap, int);
        a = va_arg(ap, double);
        va_end(ap);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = 0;
        for(int i = 0; i <= M; ++i) {
            t_Delay = (t - i*L + cfg.MEM_SIZE) % cfg.MEM_SIZE;
            y[t] += pow(a,i)*s[t_Delay];
        }
    }
};

class Reverb : public DSP {
    int L;
    int t_Delay;
    float a;

public:
    Reverb(const dsp_config &cfg, const int &L, const float &a) {
        set(cfg, L, a);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        L = va_arg(ap, int);
        a = va_arg(ap, double);
        va_end(ap);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        t_Delay = (t-L+cfg.MEM_SIZE)%cfg.MEM_SIZE;
        y[t] = s[t] + a * y[t_Delay];
    }
};

class Compressor : public DSP {
    float Th;
    float ratio;
    float gain;      

public:
    Compressor(const dsp_config &cfg, const float &Th, const float &ratio) {
        set(cfg, Th, ratio);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        Th = va_arg(ap, double);
        ratio = va_arg(ap, double);
        va_end(ap); 
        
        gain = 0.7 / (Th+(1.0-Th)*ratio);     
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        if(s[t] > Th) s[t] = Th + (s[t]-Th) * ratio;
        else if (s[t] < -Th) s[t] = -Th + (s[t]+Th) * ratio;
        s[t] *= gain;
        y[t] = s[t];
    }
};

#endif
