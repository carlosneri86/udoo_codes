#ifndef WAV_BUILDER_H
#define WAV_BUILDER_H  

#include <stdint.h>

typedef struct
{
    int32_t dwWaveFileDescriptor;
    uint32_t dwSampleRate;
    uint16_t wChannels;
    uint32_t dwSeconds;

}wave_t;

void WavBuilder_vfnSetHeader(wave_t * WaveHeader);

void WavBuilder_vfnWriteData(wave_t * WaveHeader, int8_t * pbAudioDataBuffer, uint16_t wBytes);

#endif /* WAV_BUILDER_H */

