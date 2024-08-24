/*
 * 2024/08/10 updated.
 * coded by TEMMOTO Riku
 */

#ifndef __MAIN_HH__
#define __MAIN_HH__

#define RUN_BY_PYTHON           // When run by itself, comment this out.

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <thread>
#include <portaudio.h>
#include "../include/basic.hh"


// class LineIn : public Effector {};
// class LineOut : public Effector {};


/* for voice processing */
dsp_config cfg;
float *in_buf;              // input buffer    
float *out_buf;             // output buffer
int t;                      // input time
int to;                     // output time
float *s;                   // will-be-proccesed data
float *y;                   // already-proccesed data
float *y_tmp;               // temporary already-proccesed
bool processing;            // is-proccessing or not

/* invoke effectors */
std::vector<Effector *> effectors;
Gain volume;                // master-volume
Through through;
DigitalDelay digital_delay;
Gain gain;
IRconvol irconvol;
ALLpass allpass;
Notch notch;
InvNotch inv_notch;

/* for portaudio */
PaStreamParameters inputParameters, outputParameters;
PaStream *stream;
const PaDeviceInfo *inputInfo;
const PaDeviceInfo *outputInfo;

/* for commander */
std::string cmd;

void dsp_loop();

void control(Effector *effector, std::vector<std::string> &command_split);

extern "C" int main();

#ifdef RUN_BY_PYTHON

bool is_command_set;
extern "C" void set_command(const char *command);

#endif

#endif
