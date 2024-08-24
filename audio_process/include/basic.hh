#ifndef __BASIC_HH__
#define __BASIC_HH__

#include "config.hh"

class Through : public Effector {
public:
    Through();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class DigitalDelay : public Effector {
    int t_Delay;
    int L;
public:
    DigitalDelay();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class Gain : public Effector {
    float value;
public:
    Gain();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

// 未実装
class IRconvol : public Effector {
public:
    IRconvol();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class ALLpass : public Effector {
    float x, u0, u1, u2;
    float a, r;
    float fN;
public:
    ALLpass();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class Notch : public Effector {
    float x, u0, u1, u2;
    float a, r;
    float fN;
public:
    Notch();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

class InvNotch : public Effector {
    float x, u0, u1, u2;
    float a, r;
    float fN;
public:
    InvNotch();
    void set(const dsp_config *cfg, const std::vector<float>::iterator &it) override;
    void apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) override;
};

#endif
