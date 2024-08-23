/*
 * 2024/08/10 updated.
 * coded by TEMMOTO Riku
 */

#ifndef __MAIN_HH__
#define __MAIN_HH__

#include <iostream>
#include <string>
#include <vector>
#include <thread>
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
bool processing;               // proccessed or not

/* invoke effectors */
std::vector<Effector *> effectors;
Gain volume;                // master-volume
Through through;
DigitalDelay digital_delay;
Gain gain;

/* for portaudio */
PaStreamParameters inputParameters, outputParameters;
PaStream *stream;
const PaDeviceInfo *inputInfo;
const PaDeviceInfo *outputInfo;

void dsp_loop();

extern "C" int main();

#endif
