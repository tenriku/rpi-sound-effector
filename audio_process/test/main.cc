/*
 * 2024/08/10 updated.
 * coded by TEMMOTO Riku
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
// #include <thread>
#include <vector>
#include <portaudio.h>
#include "../include/basic.hh"

/* for voice processing */
dsp_config cfg;
float *in_buf;              // input buffer    
float *out_buf;             // output buffer
int t;                      // input time
int to;                     // output time
float *s;                   // will-be-proccesed data
float *y;                   // already-proccesed data
float *y_tmp;               // temporary already-proccesed
bool is_applied;            // effects applied or not
bool is_proc;               // proccessed or not

/* invoke effectors */
std::vector<DSP *> dsp;
// BASIC::Through through;
// BASIC::Delay delay(cfg, 20000);
Gain gain(cfg, 10.0);
// BASIC::IRconvol irconvol;
// BASIC::ALLpass allpass(cfg, 0.8, 1e3);
// BASIC::Notch notch(cfg, 0.8, 5e2);
// BASIC::InvNotch invnotch(cfg, 0.9, 1e3);
// FIR::LPF fir_lpf(cfg, 64, 4e3);
// FIR::HPF fir_hpf(cfg, 64, 3e3);
// FIR::BPF fir_bpf(cfg, 64, 1e3, 3e3);
// FIR::BEF fir_bef(cfg, 64, 1e3, 3e3);
// FIR::Echo fir_echo;
// SPECTRUM::Through fft_through(cfg);
// SPECTRUM::BPF fft_bpf(cfg, 100.0, 16000.0);
// SPECTRUM::MAXfreq fft_max_freq(cfg);
// VOICE::RingMod ringmod(cfg, 2.1);
// VOICE::RingMod_Interpolation ringmod_interpolation(cfg, 2.7, 160);
// VOICE::AMvoiceChanger am_voice_changer(cfg, 1e3);
// VOICE::TVAMvoiceChanger tvam_voice_changer(cfg, 1e3);
// EFFECT::Echo delay_echo(cfg, 4000, 12, 0.7);
// EFFECT::Reverb reverb(cfg, 4000, 0.7);
// EFFECT::Compressor compressor(cfg, 0.2, 0.1);

/* for portaudio */
PaStreamParameters inputParameters, outputParameters;
PaStream *stream;
const PaDeviceInfo *inputInfo;
const PaDeviceInfo *outputInfo;

/* voice processing functions */
extern "C" int proc_initialize();

extern "C" int proc_terminate();

extern "C" void proc_loop();

extern "C" void proc_error(int err);

int main() {
    // std::thread audio(proc_loop);

    /* set effectors */
    // ゆくゆくはプリセット保存用ファイルを作って、そこからエフェクタのセットをする。
    // dsp.push_back(&through);
    // dsp.push_back(&delay);
    dsp.push_back(&gain);
    // dsp.push_back(&irconvol);
    // dsp.push_back(&allpass);
    // dsp.push_back(&notch);
    // dsp.push_back(&invnotch);
    // dsp.push_back(&fir_lpf);
    // dsp.push_back(&fir_hpf);
    // dsp.push_back(&fir_bpf);
    // dsp.push_back(&fir_bef);
    // dsp.push_back(&fir_echo);
    // dsp.push_back(&fft_through);
    // dsp.push_back(&fft_bpf);
    // dsp.push_back(&fft_max_freq);
    // dsp.push_back(&ringmod);
    // dsp.push_back(&ringmod_interpolation);
    // dsp.push_back(&am_voice_changer);
    // dsp.push_back(&tvam_voice_changer);
    // dsp.push_back(&delay_echo);
    // dsp.push_back(&reverb);
    // dsp.push_back(&compressor);

    proc_loop();

    sleep(5);
    is_proc = false;

    return EXIT_SUCCESS;
}

int proc_initialize() {
    cfg.MEM_SIZE = 400;
    cfg.Fs = 48000;
    cfg.BUF_SIZE = 160;
    cfg.FFT_SIZE = 64;
    cfg.OL = 8;

    in_buf = new float[cfg.BUF_SIZE];
    out_buf = new float[cfg.BUF_SIZE];

    t = 0;
    to = 0;
    s = new float[cfg.MEM_SIZE];
    y = new float[cfg.MEM_SIZE];
    y_tmp = new float[cfg.MEM_SIZE];
    is_applied = false;

    int err = Pa_Initialize();
    if(err != paNoError) return -1;

    inputParameters.device = Pa_GetDefaultInputDevice();
    printf("Input device # %d.\n", inputParameters.device);
    inputInfo = Pa_GetDeviceInfo(inputParameters.device);
    printf("    Name: %s\n", inputInfo->name);
    printf("      LL: %g s\n", inputInfo->defaultLowInputLatency);
    printf("      HL: %g s\n", inputInfo->defaultHighInputLatency);
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = inputInfo->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice();
    printf("Output device # %d.\n", outputParameters.device);
    outputInfo = Pa_GetDeviceInfo(outputParameters.device);
    printf("   Name: %s\n", outputInfo->name);
    printf("     LL: %g s\n", outputInfo->defaultLowOutputLatency);
    printf("     HL: %g s\n", outputInfo->defaultHighOutputLatency);
    outputParameters.channelCount = 1;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = outputInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        cfg.Fs,
        cfg.BUF_SIZE,
        paClipOff,
        NULL,
        NULL
    );
    if(err != paNoError) return -1;

    err = Pa_StartStream(stream);
    if(err != paNoError) return -1;

    return 0;
}

int proc_terminate() {
    int err = Pa_StopStream(stream);
    if(err != paNoError) return -1;
    Pa_Terminate();
    delete[] s;
    delete[] y;
    delete[] y_tmp;
    delete[] in_buf;
    delete[] out_buf;

    return 0;
}

void proc_loop() {
    std::size_t num_dsp;

    int err = proc_initialize();
    proc_error(err);
    
    is_proc = true;
    while(is_proc) {
        /* input processing */
        err = Pa_ReadStream(stream, in_buf, cfg.BUF_SIZE);
        if(err) proc_error(-2);

        for(int n = 0; n < cfg.BUF_SIZE; ++n) {
            t = (t+1) % cfg.MEM_SIZE;
            s[t] = in_buf[n];
            // s[ti] += 0.1*sin(2*M_PI*1e3/Fs*ti);
            
            if(!is_applied) {
                y[t] = s[t];
            } else {

                /* voice processing */
                num_dsp = dsp.size();
                if(num_dsp != 0 && num_dsp % 2 == 0) {
                    dsp.front()->apply(cfg, t, s, y_tmp);
                    for(int i = 1; i < num_dsp - 1; i += 2) {
                        dsp.at(i)->apply(cfg, t, y_tmp, y);
                        dsp.at(i+1)->apply(cfg, t, y, y_tmp);
                    }
                    dsp.back()->apply(cfg, t, y_tmp, y);
                }
                else if(num_dsp % 2 == 1) {
                    dsp.front()->apply(cfg, t, s, y);
                    for(int i = 1; i < num_dsp; i += 2) {
                        dsp.at(i)->apply(cfg, t, y, y_tmp);
                        dsp.at(i+1)->apply(cfg, t, y_tmp, y);
                    }
                }
                y[t] = atan(y[t])/(M_PI/2.0);
            }
        }

        /* output processing */
        for(int n = 0; n < cfg.BUF_SIZE; ++n) {
            to = (to+1) % cfg.MEM_SIZE;
            out_buf[n] = y[to];
        }

        err = Pa_WriteStream(stream, out_buf, cfg.BUF_SIZE);
        if(err) proc_error(-2);
    }

    err = proc_terminate();
    proc_error(err);
}

void proc_error(int err) {
    if(err == -2)      goto xrun;
    else if(err == -1) goto error;
    else               return;
xrun:
    printf("err = %d\n", err); fflush(stdout);
    if(stream) {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
    delete[] s;
    delete[] y;
    delete[] y_tmp;
    delete[] in_buf;
    delete[] out_buf;
    if(err & paInputOverflow)
        fprintf(stderr, "Input Overflow.\n");
    if(err & paOutputUnderflow)
        fprintf(stderr, "Output Underflow.\n");
    exit(EXIT_FAILURE);
error:
    if(stream) {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
    }
    Pa_Terminate();
    delete[] s;
    delete[] y;
    delete[] y_tmp;
    delete[] in_buf;
    delete[] out_buf;
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
    exit(EXIT_FAILURE);
};
