#include "../include/basic.hh"

Through::Through() {}
void Through::set(const dsp_config *cfg, ...) {}
void Through::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    y[t] = s[t];
}

DigitalDelay::DigitalDelay() {}
void DigitalDelay::set(const dsp_config *cfg, ...) {
    va_list ap;
    va_start(ap, cfg);
    this->L = va_arg(ap, int);
    va_end(ap);
}
void DigitalDelay::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    if(this->is_enable) {
        this->t_Delay = (t-this->L+cfg->MEM_SIZE)%cfg->MEM_SIZE;
        y[t] = s[this->t_Delay];
    } else {
        y[t] = s[t];
    }
}

Gain::Gain() {}
void Gain::set(const dsp_config *cfg, ...) {
    va_list ap;
    va_start(ap, cfg);
    this->value = va_arg(ap, double);
    va_end(ap);
}
void Gain::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    if(is_enable) y[t] = this->value * s[t];
    else          y[t] = s[t];
}

/*
// 未実装
class IRconvol : public DSP {
public:
    void set(const dsp_config &cfg, ...) override {}

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = s[t];
    }
};

class ALLpass : public DSP {
    float x, u0, u1, u2;
    float a, r;
    float fN;

public:
    ALLpass(const dsp_config &cfg, const float &r, const float &fn) {
        set(cfg, r, fn);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        r = va_arg(ap, double);
        fN = va_arg(ap, double);
        va_end(ap);

        fN /= cfg.Fs;
        a = -(1+r)*cos(2.0*M_PI*fN);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        u0 = s[t] - a * u1 - r * u2;
        x = r * u0 + a * u1 + u2;
        u2 = u1;
        u1 = u0;
        y[t] = x;
    }
};

class Notch : public DSP {
    float x, u0, u1, u2;
    float a, r;
    float fN;

public:
    Notch(const dsp_config &cfg, const float &r, const float &fn) {
        set(cfg, r, fn);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        r = va_arg(ap, double);
        fN = va_arg(ap, double);
        va_end(ap);

        fN /= cfg.Fs;
        a = -(1+r)*cos(2.0*M_PI*fN);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        u0 = s[t] - a * u1 - r * u2;
        x = r * u0 + a * u1 + u2;
        y[t] = (s[t]+x)/2.0;
        u2 = u1;
        u1 = u0;
    }
};

class InvNotch : public DSP {
    float x, u0, u1, u2;
    float a, r;
    float fN;

public:
    InvNotch(const dsp_config &cfg, const float &r, const float &fn) {
        set(cfg, r, fn);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        r = va_arg(ap, double);
        fN = va_arg(ap, double);
        va_end(ap);

        fN /= cfg.Fs;
        a = -(1+r)*cos(2.0*M_PI*fN);
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        u0 = s[t] - a * u1 - r * u2;
        x = r * u0 + a * u1 + u2;
        y[t] = (s[t]-x)/2.0;
        u2 = u1;
        u1 = u0;
    }
};
*/
