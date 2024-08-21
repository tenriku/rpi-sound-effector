/*
 * 2024/08/10 updated.
 * coded by TEMMOTO Riku
 */

#ifndef __MAIN_HH__
#define __MAIN_HH__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
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
Gain gain;

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

extern "C" int main();

extern "C" void stop_proc();

#endif
