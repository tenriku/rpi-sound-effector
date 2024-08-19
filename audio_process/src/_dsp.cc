#include "../include/_dsp.hh"

unsigned FFT::FFT_SIZE = 0;
float * FFT::Wr = NULL;
float * FFT::Wi = NULL;
float * FFT::Fr = NULL;
float * FFT::Fi = NULL;
float * FFT::Xr = NULL;
float * FFT::Xi = NULL;
float * FFT::xin = NULL;
float * FFT::z = NULL;
float * FFT::Xamp = NULL;
float FFT::omega = 0.0;
int FFT::St = 0;
int * FFT::br = NULL;

void FFT::hold() {
    if(Wr != NULL) delete[] Wr;
    Wr = new float[FFT_SIZE];
    if(Wi != NULL) delete[] Wi;
    Wi = new float[FFT_SIZE];
    if(Fr != NULL) delete[] Fr;
    Fr = new float[FFT_SIZE];
    if(Fi != NULL) delete[] Fi;
    Fi = new float[FFT_SIZE];
    if(Xr != NULL) delete[] Xr;
    Xr = new float[FFT_SIZE];
    if(Xi != NULL) delete[] Xi;
    Xi = new float[FFT_SIZE];
    if(xin != NULL) delete[] xin;
    xin = new float[FFT_SIZE];
    if(z != NULL) delete[] z;
    z = new float[FFT_SIZE];
    if(Xamp != NULL) delete[] Xamp;
    Xamp = new float[FFT_SIZE];
    if(br != NULL) delete[] br;
    br = new int[FFT_SIZE];
}

void FFT::release() {
    delete[] Wr;
    delete[] Wi;
    delete[] Fr;
    delete[] Fi;
    delete[] Xr;
    delete[] Xi;
    delete[] xin;
    delete[] z;
    delete[] Xamp;
    delete[] br;
}

void FFT::init(const unsigned &fft_size) {
    FFT_SIZE = fft_size;
    hold();
    int i;
    St=log((float)FFT_SIZE)/log(2.0)+0.5;
    omega=2.0*M_PI/FFT_SIZE;
    bitr();Wnk();
}

void FFT::bitr() {
    int loop,i,j;
    br[0]=0;
    br[1]=FFT_SIZE/2;
    loop=1;
    for(j=0;j<St-1;j++){
        br[loop*2]=br[loop]/2;
        loop=loop*2;
        for(i=1;i<loop;i++){
            br[loop+i]=br[loop]+br[i];
        }
    }
}
    
void FFT::Wnk() {
    int i;
    for(i=0;i<FFT_SIZE/2;i++){
        Wr[i]=cos(omega*i);
        Wi[i]=sin(omega*i);
    }
}

void FFT::fft() {
    int _2_s,_2_s_1,roop,l,m,p;
    int s,j,k;
    float Wxmr,Wxmi;
    for(j=0;j<FFT_SIZE;j++){                                        // FFT入力の設定
        Fr[br[j]]=xin[j];                                           // 入力
        Fi[br[j]]=0.0;
    }
    _2_s=1;
    for(s=1;s<=St;s++){                                             // ステージ回繰り返し
        _2_s_1=_2_s;
        _2_s=_2_s*2;
        roop=FFT_SIZE/_2_s;
        for(j=0;j<roop;j++){                                        // DFT繰り返し
            for(k=0;k<_2_s_1;k++){                                  // BF演算繰り返し
                l=_2_s*j+k;                                         // BFの上入力番号
                m=_2_s_1*(2*j+1)+k;                                 // BFの下入力番号
                p=roop*k;                                           // 下入力への重み番号
                Wxmr=Fr[m]*Wr[p]+Fi[m]*Wi[p];                       // 重み×下入力の実部
                Wxmi=Fi[m]*Wr[p]-Fr[m]*Wi[p];                       // 重み×下入力の虚部
                Xr[m]=Fr[m]=Fr[l]-Wxmr;                             // BFの下出力の実部
                Xi[m]=Fi[m]=Fi[l]-Wxmi;                             // BFの下出力の虚部
                Xr[l]=Fr[l]=Fr[l]+Wxmr;                             // BFの上出力の実部
                Xi[l]=Fi[l]=Fi[l]+Wxmi;                             // BFの上出力の虚部
            }
        }
    }

    for(j=0;j<FFT_SIZE;j++){
        Xamp[j]=sqrt(Fr[j]*Fr[j]+Fi[j]*Fi[j]);                      // 振幅スペクトルの算出
    }
}

void FFT::ifft() {                                                  // 逆フーリエ変換
    int _2_s,_2_s_1,roop,l,m,p;
    int s,j,k;
    float Wxmr,Wxmi;

    for(j=0;j<FFT_SIZE;j++){                                        // 逆FFT入力の設定
        Fr[br[j]]=Xr[j];
        Fi[br[j]]=Xi[j];
    }
    _2_s=1;
    for(s=1;s<=St;s++){                                             // ステージ回繰り返し
        _2_s_1=_2_s;
        _2_s=_2_s*2;
        roop=FFT_SIZE/_2_s;
        for(j=0;j<roop;j++){                                        // FFT繰り返し
            for(k=0;k<_2_s_1;k++){                                  // BF演算繰り返し
                l=_2_s*j+k;                                         // BFの上入力番号
                m=_2_s_1*(2*j+1)+k;                                 // BFの下入力番号
                p=roop*k;                                           // 下入力への重み番号
                Wxmr=Fr[m]*Wr[p]-Fi[m]*Wi[p];                       // 重み×下入力の実部
                Wxmi=Fi[m]*Wr[p]+Fr[m]*Wi[p];                       // 重み×下入力の虚部
                z[m]=Fr[m]=Fr[l]-Wxmr;                              // BFの下出力の実部
                Fi[m]=Fi[l]-Wxmi;                                   // BFの下出力の虚部
                z[l]=Fr[l]=Fr[l]+Wxmr;                              // BFの上出力の実部
                Fi[l]=Fi[l]+Wxmi;                                   // BFの上出力の虚部
            }
        }
    }
}
