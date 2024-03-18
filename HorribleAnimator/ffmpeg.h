#pragma once

#ifndef FFMPEGFIL_H
#define FFMPEGFIL_H

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
#include <libswscale/swscale.h>

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


int InWidth, InHeight;

OutputStream video_st = { 0 }, audio_st = { 0 };
const AVOutputFormat* fmt;

AVFormatContext* oc;
const AVCodec* audio_codec = NULL;
const AVCodec* video_codec = NULL;
int ret;
int have_video = 0, have_audio = 0;
int encode_video = 0, encode_audio = 0;
AVDictionary* opt = NULL;
int i,k;

//int init_mpeg(char* filename);

#endif