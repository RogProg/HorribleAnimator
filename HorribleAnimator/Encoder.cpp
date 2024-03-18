#include "framework.h"



#include "Encoder.h"


Encoder::Encoder(MainWindow* _mw) {

    mw = _mw;


    

}


void Encoder::encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt, FILE *outfile)
{
    int ret;
 
    /* send the frame to the encoder */
    if (frame)
        printf("Send frame %d\n", frame->pts);
 
    ret = avcodec_send_frame(enc_ctx, frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding\n");
        exit(1);
    }
 
    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            exit(1);
        }
 
        printf("Write packet %d %d)\n", pkt->pts, pkt->size);
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}

int Encoder::init(CHAR* filename,int _width, int _height) {

    width = _width;
    height = _height;
 
    /* find the mpeg1video encoder */
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
    if (!codec) {
        fprintf(stderr, "Codec '%s' not found\n", codec_name);
        exit(1);
    }
 
    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }
 
    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);
 
    /* put sample parameters */
    c->bit_rate = 800000;
    /* resolution must be a multiple of two */
    c->width = width;
    c->height = height;
    /* frames per second */
    c->time_base = {1, 25};
    c->framerate = {25, 1};
 
    /* emit one intra frame every ten frames
     * check frame pict_type before passing frame
     * to encoder, if frame->pict_type is AV_PICTURE_TYPE_I
     * then gop_size is ignored and the output of encoder
     * will always be I frame irrespective to gop_size
     */
    c->gop_size = 10;
    c->max_b_frames = 1;
    c->pix_fmt = AV_PIX_FMT_YUV420P;
 
    if (codec->id == AV_CODEC_ID_H264)
        av_opt_set(c->priv_data, "preset", "slow", 0);
 
    /* open it */
    ret = avcodec_open2(c, codec, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec:  \n");
        exit(1);
    }
 
    fopen_s(&f , filename, "wb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }
 
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
    frame->format = c->pix_fmt;
    frame->width  = c->width;
    frame->height = c->height;
 
    ret = av_frame_get_buffer(frame, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate the video frame data\n");
        exit(1);
    }
 
return 0;

}


void Encoder::encode_frame(byte* videodata , int i ) {

    
     ret = av_frame_make_writable(frame);
        if (ret < 0)
            exit(1);
 

    struct SwsContext* ctx;

    ctx = sws_getContext(width, height,
        AV_PIX_FMT_RGB24, width, height,
        AV_PIX_FMT_YUV420P, 0, 0, 0, 0);


    int inLinesize[1] = { 3 * width }; // RGB stride
    sws_scale(ctx, &videodata, inLinesize, 0, height, frame->data, frame->linesize);

    frame->pts = i;
 
    
    encode(c, frame, pkt, f);
    
}
 

void Encoder::close() {

    uint8_t endcode[] = { 0, 0, 1, 0xb7 };

    /* flush the encoder */
    encode(c, NULL, pkt, f);
 
    /* Add sequence end code to have a real MPEG file.
       It makes only sense because this tiny examples writes packets
       directly. This is called "elementary stream" and only works for some
       codecs. To create a valid file, you usually need to write packets
       into a proper file format or protocol; see mux.c.
     */
    if (codec->id == AV_CODEC_ID_MPEG1VIDEO || codec->id == AV_CODEC_ID_MPEG2VIDEO)
        fwrite(endcode, 1, sizeof(endcode), f);
    fclose(f);
 
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);
 
    
}



