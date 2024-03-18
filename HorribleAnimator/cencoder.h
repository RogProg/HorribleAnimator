#pragma once




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>



#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>


typedef struct OutputStream {
    AVStream* st;
    AVCodecContext* enc;

    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;

    AVFrame* frame;
    AVFrame* tmp_frame;

    AVPacket* tmp_pkt;

    float t, tincr, tincr2;

    struct SwsContext* sws_ctx;
    struct SwrContext* swr_ctx;
} OutputStream;




int width,height,soundpos, wavlength;

OutputStream video_st = { 0 }, audio_st = { 0 };
const AVOutputFormat* fmt;
//const char* filename;
AVFormatContext* oc;
const AVCodec* audio_codec, * video_codec;
int ret;
int have_video = 0, have_audio = 0;
int encode_video = 0, encode_audio = 0;
AVDictionary* opt = NULL;


int16_t* audio;
char* video;