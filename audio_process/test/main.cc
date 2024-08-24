#include "main.hh"

using namespace std;

void dsp_loop() {
#ifdef RUN_BY_PYTHON
    is_command_set = false;
#endif

    /* set dsp-configuration */
    cfg.MEM_SIZE = 16000;
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
            
            /* voice processing */
            static size_t num_dsp = effectors.size();
            if(num_dsp == 0) {
                y[t] = s[t];
            } else if(num_dsp % 2 == 0) {
                effectors.front()->apply(&cfg, t, s, y_tmp);
                for(int i = 1; i < num_dsp - 1; i += 2) {
                    effectors.at(i)->apply(&cfg, t, y_tmp, y);
                    effectors.at(i+1)->apply(&cfg, t, y, y_tmp);
                }
                effectors.back()->apply(&cfg, t, y_tmp, y);
            } else {
                effectors.front()->apply(&cfg, t, s, y);
                for(int i = 1; i < num_dsp; i += 2) {
                    effectors.at(i)->apply(&cfg, t, y, y_tmp);
                    effectors.at(i+1)->apply(&cfg, t, y_tmp, y);
                }
            }
            // y[t] = atan(y[t])/(M_PI/2.0);
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

void control(Effector *effector, vector<string> &command_split) {
    string effector_name = command_split.at(0);
    string ope = command_split.at(1);
    vector<float> args;
    int err = 0;
    
    if(ope == "+") {                                                    // ADD
        // unimplemented
    } else if(ope == "-") {                                             // DELETE
        //　unimplemented
    } else if(ope == "*") {                                             // LIBRARY ( = exchange )
        //　unimplemented
    } else if(ope == "|") {                                             // toggle effector
        effector->toggle();
        cout << "\"" << effector_name << (effector->is_enabled ?  "\" is enabled." : "\" is disabled.") << endl;
    } else if(ope == "^") {                                             // set effector
        command_split.erase(command_split.begin(), command_split.begin() + 2);
        for(const string &v : command_split) {
            try {
                args.emplace_back(stof(v));
            } catch(const invalid_argument &e) {
                cout << "ERROR: An argument is invalid. " << e.what() << endl;
                err = -1;
            } catch(const out_of_range &e) {
                cout << "ERROR: An argument is out of range. " << e.what() << endl;
                err = -1;
            } 
        }
        if(!err) {
            effector->set(&cfg, args.begin());
            cout << "\"" << effector_name << "\" is newly set." << endl;
        }
    } else {
        cout << "ERROR: Invalid operator." << endl;
    }
    cin.clear();
    command_split.clear();
}

 /* dsp is contorolled via terminal. */
int main() {

#ifdef RUN_BY_PYTHON
    is_command_set = false;
#endif

    // ゆくゆくは保存用ファイルを作って、そこから各データのセットをする。
    // terminalからの方が簡単だし、Python側からやろっか
    volume.toggle();
    // through.toggle(); effectors.push_back(&through);
    // digital_delay.toggle(); effectors.push_back(&digital_delay);
    gain.toggle();  effectors.emplace_back(&gain);
    // irconvol.toggle(); effectors.push_back(&irconvol);
    // allpass.toggle(); effectors.push_back(&allpass);
    // notch.toggle(); effectors.push_back(&notch);
    // inv_notch.toggle(); effectors.push_back(&inv_notch);

    thread th(dsp_loop);

    ////////////////////////////////////////
    //                                    //
    //        [format of comannd]         //
    //                                    //
    //          ex) Gain,^,10,0           //
    //               |   |   |            //
    //              /    |    \           // 
    //   Effector_name   |   aruguments   //
    //                operator            //
    //                                    //
    ////////////////////////////////////////

    while(!processing);             // wait until processing is triggerd.
    while(processing) {
        static vector<string> cmd_split;

#ifdef RUN_BY_PYTHON
        while(!is_command_set);     // wait until is_command_set is triggerd.
        is_command_set = false;
#else
        cout << endl << "command here: ";
        getline(cin, cmd);
#endif
        stringstream ss(cmd);
        string item;
        while(getline(ss, item, ',')) cmd_split.emplace_back(item);
        // for(auto v : cmd_split) cout << v << endl;
        
        string name = cmd_split.front();
        if(name == "FIN") {
            cin.clear();
            cmd_split.clear();
            processing = false;
        }
        else if(name == "Volume")           control(&volume, cmd_split);
        else if(name == "Through")          control(&through, cmd_split);
        else if(name == "DigitalDelay")     control(&digital_delay, cmd_split);
        else if(name == "Gain")             control(&gain, cmd_split);
        else if(name == "IRconvol")         control(&irconvol, cmd_split);
        else if(name == "ALLpass")          control(&allpass, cmd_split);
        else if(name == "Notch")            control(&notch, cmd_split);
        else if(name == "InvNotch")         control(&inv_notch, cmd_split);
        else {
            cin.clear();
            cmd_split.clear();
            cout << "ERROR: No effector named \"" << name << "\"." << endl;
        }
    }
    th.join();
}

#ifdef RUN_BY_PYTHON

void set_command(const char *command) {
    cmd = command;
    is_command_set = true;
}

#endif
