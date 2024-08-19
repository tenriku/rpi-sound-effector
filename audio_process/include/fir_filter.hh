#ifndef __FIR_FILTER_HH__
#define __FIR_FILTER_HH__

#include "_dsp.hh"

class LPF : public DSP {
    int N;
    float *h;
    float fc;

public:
    LPF(const dsp_config &cfg, const int &N, const float &fc) : h(NULL) {
        set(cfg, N, fc);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        N = va_arg(ap, int);
        fc = va_arg(ap, double);
        va_end(ap);

        if(h != NULL) delete[] h;
        h = new float[N + 1];

        fc /= cfg.Fs;
        for(int i = -N/2; i <= N/2; ++i) {
            if(i == 0) {
                h[N/2+i] = 2.0*fc;
            } else {
                h[N/2+i] = 2.0*fc*sin(2.0*M_PI*fc*i)/(2.0*M_PI*fc*i);
            }
            h[N/2+i] *= 0.5*(1.0-cos(2.0*M_PI*(N/2+i)/N));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = 0;
        for(int i = 0; i <= N; ++i) y[t] += s[(t-i+cfg.MEM_SIZE)%cfg.MEM_SIZE]*h[i];
    }

    ~LPF() {
        delete[] h;
    }
};

class HPF : public DSP {
    int N;
    float *h;
    float fc;

public:
    HPF(const dsp_config &cfg, const int &N, const float &fc) : h(NULL) {
        set(cfg, N, fc);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        N = va_arg(ap, int);
        fc = va_arg(ap, double);
        va_end(ap);

        if(h != NULL) delete[] h;
        h = new float[N + 1];

        fc /= cfg.Fs;
        for(int i = -N/2; i <= N/2; ++i) {
            if(i == 0) {
                h[N/2+i] = 1.0-2.0*fc;
            } else {
                h[N/2+i] = sin(M_PI*i)/(M_PI*i)-2.0*fc*sin(2.0*M_PI*fc*i)/(2.0*M_PI*fc*i);
            }
            h[N/2+i] *= 0.5*(1.0-cos(2.0*M_PI*(N/2+i)/N));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = 0;
        for(int i = 0; i <= N; ++i) y[t] += s[(t-i+cfg.MEM_SIZE)%cfg.MEM_SIZE]*h[i];
    }

    ~HPF() {
        delete[] h;
    }
};

class BPF : public DSP {
    int N;
    float *h;
    float fc1, fc2;

public:
    BPF(const dsp_config &cfg, const int &N, const float &fc1, const float &fc2) : h(NULL) {
        set(cfg, N, fc1, fc2);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        N = va_arg(ap, int);
        fc1 = va_arg(ap, double);
        fc2 = va_arg(ap, double);
        va_end(ap);

        if(h != NULL) delete[] h;
        h = new float[N + 1];

        fc1 /= cfg.Fs;
        fc2 /= cfg.Fs;
        for(int i = -N/2; i <= N/2; ++i){
            if(i == 0) {
                h[N/2+i] = 2.0*fc2-2.0*fc1;
            } else {
                h[N/2+i] = 2.0*fc2*sin(2.0*M_PI*fc2*i)/(2.0*M_PI*fc2*i)-2.0*fc1*sin(2.0*M_PI*fc1*i)/(2.0*M_PI*fc1*i);
            }
            h[N/2+i] *= 0.5*(1.0-cos(2.0*M_PI*(N/2+i)/N));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = 0;
        for(int i = 0; i <= N; ++i) y[t] += s[(t-i+cfg.MEM_SIZE)%cfg.MEM_SIZE]*h[i];
    }

    ~BPF() {
        delete[] h;
    }
};

class BEF : public DSP {
    int N;
    float *h;
    float fc1, fc2;

public:
    BEF(const dsp_config &cfg, const int &N, const float &fc1, const float &fc2) : h(NULL){
        set(cfg, N, fc1, fc2);
    }
    
    void set(const dsp_config &cfg, ...) override {
        va_list ap;
        va_start(ap, cfg);
        N = va_arg(ap, int);
        fc1 = va_arg(ap, double);
        fc2 = va_arg(ap, double);
        va_end(ap);

        if(h != NULL) delete[] h;
        h = new float[N + 1];

        fc1 /= cfg.Fs;
        fc2 /= cfg.Fs;
        for(int i = -N/2; i <= N/2; ++i){
            if(i == 0) {
                h[N/2+i] = 1-2.0*fc2+2.0*fc1;
            } else {
                h[N/2+i] = -2.0*fc2*sin(2.0*M_PI*fc2*i)/(2.0*M_PI*fc2*i)+2.0*fc1*sin(2.0*M_PI*fc1*i)/(2.0*M_PI*fc1*i);
            }
            h[N/2+i] *= 0.5*(1.0-cos(2.0*M_PI*(N/2+i)/N));
        }
    }

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = 0;
        for(int i = 0; i <= N; ++i) y[t] += s[(t-i+cfg.MEM_SIZE)%cfg.MEM_SIZE]*h[i];
    }

    ~BEF() {
        delete[] h;
    }
};

class Echo : public DSP {
public:
    void set(const dsp_config &cfg, ...) override {}

    void apply(const dsp_config &cfg, const unsigned &t, float *s, float *y) override {
        y[t] = s[t] + 0.8 * s[(t-2000+cfg.MEM_SIZE)%cfg.MEM_SIZE]
                    + 0.7 * s[(t-4000+cfg.MEM_SIZE)%cfg.MEM_SIZE]
                    + 0.6 * s[(t-6000+cfg.MEM_SIZE)%cfg.MEM_SIZE];
    }
};

#endif
