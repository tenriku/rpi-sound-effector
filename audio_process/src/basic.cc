#include "../include/basic.hh"

using namespace std;

Through::Through() {}
void Through::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {}
void Through::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    y[t] = s[t];
}

DigitalDelay::DigitalDelay() : L(0) {}
void DigitalDelay::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {
    L = (int)(*it);
}
void DigitalDelay::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    if(is_enabled) {
        t_Delay = (t-L+cfg->MEM_SIZE)%cfg->MEM_SIZE;
        y[t] = s[t_Delay];
    } else {
        y[t] = s[t];
    }
}

Gain::Gain() : value(1.0) {}
void Gain::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {
    value = *it;
}
void Gain::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    if(is_enabled) y[t] = value * s[t];
    else           y[t] = s[t];
}

// 未実装
IRconvol::IRconvol() {}
void IRconvol::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {}
void IRconvol::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    y[t] = s[t];
}


ALLpass::ALLpass() : u1(0), u2(0), a(0), r(1) {}
void ALLpass::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {
    r = *it;
    fN = *(it+1);

    fN /= cfg->Fs;
    a = -(1+r)*cos(2.0*M_PI*fN);
}
void ALLpass::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    u0 = s[t] - a * u1 - r * u2;
    x = r * u0 + a * u1 + u2;
    u2 = u1;
    u1 = u0;
    y[t] = x;
}

Notch::Notch() : u1(0), u2(0), a(0), r(1) {}
void Notch::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {
    r = *it;
    fN = *(it+1);

    fN /= cfg->Fs;
    a = -(1+r)*cos(2.0*M_PI*fN);
}
void Notch::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    u0 = s[t] - a * u1 - r * u2;
    x = r * u0 + a * u1 + u2;
    y[t] = (s[t]+x)/2.0;
    u2 = u1;
    u1 = u0;
}

InvNotch::InvNotch() : u1(0), u2(0), a(0), r(-1) {}
void InvNotch::set(const dsp_config *cfg, const std::vector<float>::iterator &it) {
    r = *it;
    fN = *(it+1);

    fN /= cfg->Fs;
    a = -(1+r)*cos(2.0*M_PI*fN);
}
void InvNotch::apply(const dsp_config *cfg, const unsigned &t, float *s, float *y) {
    u0 = s[t] - a * u1 - r * u2;
    x = r * u0 + a * u1 + u2;
    y[t] = (s[t]-x)/2.0;
    u2 = u1;
    u1 = u0;
}
