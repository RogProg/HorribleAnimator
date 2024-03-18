#pragma once


class MainWindow;

class Encoder
{

public:

	Encoder(MainWindow* _mw);

    int init(CHAR* filename,int _width, int _heigth);
    
    void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt, FILE *outfile);
    

    void encode_frame(byte* videodata, int i);
    void close();

    MainWindow* mw;


    const char *codec_name;
    const AVCodec *codec;
    AVCodecContext *c= NULL;
    int i, ret, x, y;
    FILE *f;
    AVFrame *frame;
    AVPacket *pkt;

    
    int width, height;
    


};