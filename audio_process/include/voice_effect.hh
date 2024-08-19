#ifndef __VOICE_EFFECT_HH__
#define __VOICE_EFFECT_HH__

#include "_dsp.hh"

class RingMod : public DSP {
    float p, r;

public:
    RingMod(const dsp_config &cfg, const float &r) {
        set(cfg, r);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        r = va_arg(ap, double);
        va_end(ap);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        p += r;
        if(p >= cfg.MEM_SIZE) p-= cfg.MEM_SIZE;
        y[t] = s[(int)p];
    }
};

class RingMod_Interpolation : public DSP {
    float p;
    float r;
    int j; 
    float ln;   
    int ll, LL;
    float *d;
    int MM;
    float w;

public:
    RingMod_Interpolation(const dsp_config &cfg, const float &r, const int &LL) : d(NULL) {
        set(cfg, r, LL);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        r = va_arg(ap, double);
        LL = va_arg(ap, int);
        va_end(ap);

        if(d != NULL) delete[] d;
        d = new float[LL];
        MM = cfg.MEM_SIZE - LL; 
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        p += r;
        if(p >= MM) p -= MM;
        j = (int)p;
        ln = p - j;
        y[t] = s[j];
        ll = (t - j + MM) % MM;
        if(ll < LL) {
            w = (ll+1.0) / (LL+1.0);
            y[t] = w*s[j] + (1.0-w)*d[((t%LL)-ll+LL)%LL]; 
        }
    }

    ~RingMod_Interpolation() {
        delete[] d;
    }
};

class AMvoiceChanger : public DSP {
    long l;
    float f;

public:
    AMvoiceChanger(const dsp_config &cfg, const float &f) {
        set(cfg, f);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        f = va_arg(ap, double);
        va_end(ap);

        f /= cfg.Fs;
        l = 0;
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = s[t]*cos(2*M_PI*f*l);
        l = (l+1)%(10*cfg.Fs);
    }
};

class TVAMvoiceChanger : public DSP {
    long l;
    float f;

public:
    TVAMvoiceChanger(const dsp_config &cfg, const float &f) {
        set(cfg, f);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        f = va_arg(ap, double);
        va_end(ap);

        f /= cfg.Fs;
        l = 0;
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        f += 0.2/cfg.Fs; 
        if(f > 1) f = 0;
        y[t] = s[t]*cos(2*M_PI*f*l);
        l = (l+1)%(10*cfg.Fs);
    }
};

#endif
