#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "wav_builder.h"

#define WAVE_BUILDER_BITS_PER_SAMPLE            (16)

#define WAVE_BUILDER_SAMPLES_SIZE               (WAVE_BUILDER_BITS_PER_SAMPLE/8)

#define WAVE_BUILDER_SUBCHUNK1_SIZE             (0x10UL)

#define WAVE_BUILDER_CHUNK_FIXED_SIZE           (36)

#define WAVE_BUILDER_PCM_DATA_FORMAT            (0x01)



void WavBuilder_vfnSetHeader(wave_t * WaveHeader)
{
    uint32_t dwChunkSize = 0;
    uint32_t dwSubChunk2Size = 0;
    uint32_t dwByteRate = 0;
    uint16_t wBlockAlign = 0;
    uint32_t dwMiscParameter = 0;    

    

    printf("Wav Sampling: %d\nWav Channels: %d\n",WaveHeader->dwSampleRate,WaveHeader->wChannels);
    /* http://soundfile.sapp.org/doc/WaveFormat/ */
    /* chunk descriptor */
    /* Write the chunk ID */ 
    write(WaveHeader->dwWaveFileDescriptor,"RIFF",4);

    /* subchunk2 size is the amount of samples of the file */
    /* amount_samples * bytes_per_sample * channels */
    wBlockAlign = WAVE_BUILDER_SAMPLES_SIZE * WaveHeader->wChannels;

    dwSubChunk2Size = ((WaveHeader->dwSampleRate * WaveHeader->dwSeconds)*wBlockAlign);

    /* Calculate the chunk size and write it*/
    dwChunkSize = WAVE_BUILDER_CHUNK_FIXED_SIZE + dwSubChunk2Size;

    printf("\nChink Size: %d\nSubchunk2 size: %d\n",dwChunkSize,dwSubChunk2Size);

    /* write the ChunkSize */
    write(WaveHeader->dwWaveFileDescriptor,&dwChunkSize,4);

    write(WaveHeader->dwWaveFileDescriptor,"WAVE",4);    
    
    /* FMT subchunk */
    
    write(WaveHeader->dwWaveFileDescriptor,"fmt ",4);

    /* SubChunk2 size */
    dwMiscParameter = WAVE_BUILDER_SUBCHUNK1_SIZE;
    write(WaveHeader->dwWaveFileDescriptor,&dwMiscParameter,4);
    
    /* PCM as data Format */
    dwMiscParameter = WAVE_BUILDER_PCM_DATA_FORMAT;
    write(WaveHeader->dwWaveFileDescriptor,&dwMiscParameter,2);

    /* Channels */

    write(WaveHeader->dwWaveFileDescriptor,&WaveHeader->wChannels,2);

    /* Sample Rate */

    write(WaveHeader->dwWaveFileDescriptor,&WaveHeader->dwSampleRate,4);

    /* Byte rate */    
    dwByteRate = WaveHeader->dwSampleRate * WAVE_BUILDER_SAMPLES_SIZE * WaveHeader->wChannels;

    write(WaveHeader->dwWaveFileDescriptor,&dwByteRate,4);

    /* Block Align */

    write(WaveHeader->dwWaveFileDescriptor,&wBlockAlign,2);

    /* Bits per sample */
    dwMiscParameter = WAVE_BUILDER_BITS_PER_SAMPLE;
    write(WaveHeader->dwWaveFileDescriptor,&dwMiscParameter,2);

    /* Data subchunk */
    write(WaveHeader->dwWaveFileDescriptor,"data",4);
    
    /* Subchunk2size */

    write(WaveHeader->dwWaveFileDescriptor,&dwSubChunk2Size,4);

    /* up to this point, just audio data must be written */
}

void WavBuilder_vfnWriteData(wave_t * WaveHeader, int8_t * pbAudioDataBuffer, uint16_t wBytes)
{

    write(WaveHeader->dwWaveFileDescriptor,pbAudioDataBuffer, wBytes);

}
