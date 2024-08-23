#include "main.hh"

using namespace std;

void dsp_loop() {
    /* load config */
    // ゆくゆくは保存用ファイルを作って、そこから各データのセットをする。
    volume.set(&cfg, 1.0);
    volume.enable();

    through.set(&cfg);
    through.enable();
    effectors.push_back(&through);

    digital_delay.set(&cfg, 0);
    digital_delay.enable();
    effectors.push_back(&digital_delay);

    gain.set(&cfg, 1.0);
    gain.enable();
    effectors.push_back(&gain);

    cfg.MEM_SIZE = 400;
    cfg.Fs = 48000;
    cfg.BUF_SIZE = 160;
    cfg.FFT_SIZE = 64;
    cfg.OL = 8;

    /* initialize variables and pa_stream */
    in_buf = new float[cfg.BUF_SIZE];
    out_buf = new float[cfg.BUF_SIZE];

    t = 0;
    to = 0;
    s = new float[cfg.MEM_SIZE];
    y = new float[cfg.MEM_SIZE];
    y_tmp = new float[cfg.MEM_SIZE];

    int err = Pa_Initialize();
    if(err != paNoError) goto error;

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
    if(err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if(err != paNoError) goto error;

    /* loop pa_stream */
    processing = true;
    while(processing) {
        /* input processing */
        err = Pa_ReadStream(stream, in_buf, cfg.BUF_SIZE);
        if(err) goto xrun;

        for(int n = 0; n < cfg.BUF_SIZE; ++n) {
            t = (t+1) % cfg.MEM_SIZE;
            s[t] = in_buf[n];
            // s[t] += 0.1*sin(2*M_PI*1e3/cfg.Fs*t);
            y[t] = s[t];
            
            /* voice processing */
            static size_t num_dsp = effectors.size();
            if(num_dsp != 0 && num_dsp % 2 == 0) {
                effectors.front()->apply(&cfg, t, s, y_tmp);
                for(int i = 1; i < num_dsp - 1; i += 2) {
                    effectors.at(i)->apply(&cfg, t, y_tmp, y);
                    effectors.at(i+1)->apply(&cfg, t, y, y_tmp);
                }
                effectors.back()->apply(&cfg, t, y_tmp, y);
            }
            else if(num_dsp % 2 == 1) {
                effectors.front()->apply(&cfg, t, s, y);
                for(int i = 1; i < num_dsp; i += 2) {
                    effectors.at(i)->apply(&cfg, t, y, y_tmp);
                    effectors.at(i+1)->apply(&cfg, t, y_tmp, y);
                }
            }
            y[t] = atan(y[t])/(M_PI/2.0);
            volume.apply(&cfg, t, y, y);
        }

        /* output processing */
        for(int n = 0; n < cfg.BUF_SIZE; ++n) {
            to = (to+1) % cfg.MEM_SIZE;
            out_buf[n] = y[to];
        }

        err = Pa_WriteStream(stream, out_buf, cfg.BUF_SIZE);
        if(err) goto xrun;
    }

    /* finalize variables and pa_stream */
    err = Pa_StopStream(stream);
    if(err != paNoError) goto error;
    Pa_Terminate();
    delete[] s;
    delete[] y;
    delete[] y_tmp;
    delete[] in_buf;
    delete[] out_buf;

    exit(EXIT_SUCCESS);

xrun:
    printf("err = %d\n", err);
    fflush(stdout);
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
}

int main() {
    thread th(dsp_loop);

    while(!processing);     // wait until processing is triggerd.
    while(processing) {
        static string cmd, effector_name;

        cout << "cmmand here: ";
        getline(cin, cmd);

        stringstream ss(cmd);
        getline(ss, effector_name, ',');

    if(tag == "FIN") {
        cin.clear();
        processing = false;
    } else if(tag == "A00") {
        if(ope == "+") {
            through.enable();
            cout << "through is enabled." << endl;
        } else if(ope == "-") {
            through.disable();
            cout << "through is disabled." << endl;
        } else {
            through.set(cfg);
            cout << "through is newly set." << endl;
        } cin.clear();
    } else if(tag == "A01") {
        if(ope == "+") {
            digital_delay.enable();
            cout << "digital_delay is enabled." << endl;
        } else if(ope == "-") {
            digital_delay.disable();
            cout << "digital_delay is disabled." << endl;
        } else {
            int argc = stoi(ope);
            digital_delay.set(cfg);
            cout << "digital_delay is newly set." << endl;
        } cin.clear();
    } else if(tag == "A02") {
        //
    } else {
        cin.clear();   
        cout << "ERROR: no effector tagged \"" << tag  << "\"." << endl;
    }
    }

    th.join();
}
