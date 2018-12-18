//
// Created by XiaokaiZhan on 2018/5/31.
//

#ifndef AAC_CODEC_FDK_AACDECODER_H
#define AAC_CODEC_FDK_AACDECODER_H

#include "fdk-aac/aacdecoder_lib.h"
#include "fdk-aac/machine_type.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

/**
 * https://github.com/jgfntu/libav/blob/master/libavcodec/libfdk-aacdec.c
 */
class AACDecoder {
private:
    HANDLE_AACDECODER m_decoderHandle;
    int m_pcm_pkt_size;
    byte* m_SpecInfo;
    UINT m_SpecInfoSize;

public:
    AACDecoder();
    ~AACDecoder();

/***
 * https://blog.csdn.net/carryinfo/article/details/54375611?utm_source=blogxgwz1
 * decoder主要有两种模式， RAW和ADTS
 * RAW模式： 需要在初始化decoder的时候传入AudioSpecInfo，表明即将送入的rawdata的samplerate, channel等;
 * 送数据的时候把ADTS头去掉
 ***/

    /**
     * 如果使用raw模式，一定要每次传递进来一个完整独立的ES包
     */
    bool InitWithRAWFormat(byte* m_SpecInfo, UINT m_SpecInfoSize);
    /**
     * 使用ADTS模式，可以随意传递AAC的数据，因为可以使用ADTS作为分隔符
     */
    bool InitWithADTSFormat();
    int Decode(byte *packetBuffer, int len, byte** frameBuffer);
    void Destroy();

private:
    void PrintAACInfo();
    int fdkDecodeAudio(INT_PCM *output_buf, int *output_size, byte *buffer, int size);

    void initFrameSize();
};


#endif //AAC_CODEC_FDK_AACDECODER_H
