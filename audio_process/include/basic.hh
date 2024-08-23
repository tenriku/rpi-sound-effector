#ifndef __BASIC_HH__
#define __BASIC_HH__

#include "config.hh"

/*
class LineIn : public Effector {};
class LineOut : public Effector {};
*/

class Through : public Effector {
public:
    Through();
    void set(const dsp_config *cfg, ...) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class DigitalDelay : public Effector {
    int t_Delay;
    int L;
public:
    DigitalDelay();
    void set(const dsp_config *cfg, ...) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class Gain : public Effector {
    float value;
public:
    Gain();
    void set(const dsp_config *cfg, ...) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

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

#endif
