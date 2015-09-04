/*

This example reads from the default PCM device
and writes to standard output for 5 seconds of data.

*/

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>
#include <stdint.h>
#include "wav_builder.h"

#define TIME_TO_RECORD_IN_US	(5000000)

#define TIME_TO_RECORD_IN_S	(TIME_TO_RECORD_IN_US/1000000)

int main(int argc, char *argv[]) 
{
    int32_t dwLoopsToRecord;
    int32_t dwStatus;
    int32_t dwAudioBufferSize;
    snd_pcm_t *AlsaHandle;
    snd_pcm_hw_params_t *AlsaParams;
    uint32_t dwSamplingRate;
    int32_t dwDirection;
    snd_pcm_uframes_t AlsaFrames;
    int8_t *bAudioBuffer;
    uint32_t dwChannels;
    wave_t WavFile;
    
    /* confirm there are enough parameters */
    if(argc < 4)
    {
        printf("Usage: alsa_record <interface> <sampling_rate> <channels>");
        exit(1);
    }
    
    printf("Alsa Record Opening device: %s\n",argv[1]);
    
    /* Open PCM device for recording (capture). */
    dwStatus = snd_pcm_open(&AlsaHandle, argv[1],
                    SND_PCM_STREAM_CAPTURE, 0);
    if (dwStatus < 0) 
    {
        fprintf(stderr,"unable to open pcm device: %s\n",snd_strerror(dwStatus));
        exit(1);
    }

    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&AlsaParams);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(AlsaHandle, AlsaParams);

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    snd_pcm_hw_params_set_access(AlsaHandle, AlsaParams,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(AlsaHandle, AlsaParams,
                              SND_PCM_FORMAT_S16_LE);

    /* Get the channels from the parameter */
    dwChannels = atoi(argv[3]);

    printf("Alsa Record Recording %d channels\n",dwChannels);    
    
    /* assign the channels for the wav file */     
    WavFile.wChannels = dwChannels;
    
    /* set channels to ALSA */	
    snd_pcm_hw_params_set_channels(AlsaHandle, AlsaParams, dwChannels);

    /* bits/second sampling rate */
    dwSamplingRate = atoi(argv[2]);
    
    printf("Alsa Record Sampling rate: %i\n", dwSamplingRate);

    /* Set the sampling rate for the wav file */
    WavFile.dwSampleRate = dwSamplingRate;

    /* Set the sampling rate to ASLA */
    snd_pcm_hw_params_set_rate_near(AlsaHandle, AlsaParams,
                                  &dwSamplingRate, &dwDirection);
    
    
    /* Set period size to 32 frames. */
    AlsaFrames = 32;
    snd_pcm_hw_params_set_period_size_near(AlsaHandle,
                              AlsaParams, &AlsaFrames, &dwDirection);

    /* Write the parameters to the driver */
    dwStatus = snd_pcm_hw_params(AlsaHandle, AlsaParams);
    if (dwStatus < 0) 
    {
        fprintf(stderr,"unable to set hw parameters: %s\n",snd_strerror(dwStatus));
        exit(1);
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(AlsaParams,
                                      &AlsaFrames, &dwDirection);
    /* 2 bytes/sample, 2 channels */	
    dwAudioBufferSize = AlsaFrames * 2 * dwChannels; 
    bAudioBuffer = (int8_t *) malloc(dwAudioBufferSize);

    /* We want to loop for 5 seconds */
    snd_pcm_hw_params_get_period_time(AlsaParams,
                                         &dwSamplingRate, &dwDirection);
    /* Will record 5 seconds, get the amount of frames required */
    dwLoopsToRecord = TIME_TO_RECORD_IN_US / dwSamplingRate;

    printf("SoundCard enabled and configured...\n");

    printf("Opening output file\n");
    
    /* Open the file and configure the wav header */
    WavFile.dwWaveFileDescriptor = open("audio_mic.wav", O_WRONLY|O_CREAT,S_IRUSR|S_IRGRP|S_IROTH);

    WavFile.dwSeconds = TIME_TO_RECORD_IN_S;

    WavBuilder_vfnSetHeader(&WavFile);

    printf("Recording\n");

    while (dwLoopsToRecord) 
    {
        dwLoopsToRecord--;
	
	/* Read an audio frame */
        dwStatus = snd_pcm_readi(AlsaHandle, bAudioBuffer, AlsaFrames);
        
        if (dwStatus == -EPIPE) 
        {
            /* EPIPE means overrun */
            fprintf(stderr, "overrun occurred\n");
            snd_pcm_prepare(AlsaHandle);
        } 
        else if (dwStatus < 0) 
        {
            fprintf(stderr,"error from read: %s\n",snd_strerror(dwStatus));
        } 
        else if (dwStatus != (int32_t)AlsaFrames) 
        {
            fprintf(stderr, "short read, read %d AlsaFrames\n", dwStatus);
        }

	/* Take the buffer and write it to the file */
        WavBuilder_vfnWriteData(&WavFile,bAudioBuffer, dwAudioBufferSize);
        
    }

    printf("Done\n");
    /* Once everything is done, close and release all resources */
    snd_pcm_drain(AlsaHandle);
    snd_pcm_close(AlsaHandle);
    close(WavFile.dwWaveFileDescriptor);
    free(bAudioBuffer);

  return 0;
}
