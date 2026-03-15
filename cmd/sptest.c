/*
 * Copyright (c) 2026 YohanesOktanio. All rights reserved.
 * Octa Core Utils - Utility commands for Windows.
 */
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <math.h>

#pragma comment(lib, "winmm.lib")

#define SAMPLE_RATE 44100
#define DURATION 1
#define FREQ 440

void play_channel(int left, int right) {
    HWAVEOUT hWave;
    WAVEFORMATEX format;

    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 2;
    format.nSamplesPerSec = SAMPLE_RATE;
    format.wBitsPerSample = 16;
    format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    format.cbSize = 0;

    waveOutOpen(&hWave, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL);

    int samples = SAMPLE_RATE * DURATION;
    short *buffer = malloc(samples * 2 * sizeof(short));

    for (int i = 0; i < samples; i++) {
        double t = (double)i / SAMPLE_RATE;
        short sample = (short)(sin(2 * 3.1415926535 * FREQ * t) * 30000);

        buffer[i*2]     = left  ? sample : 0;
        buffer[i*2 +1 ] = right ? sample : 0;
    }

    WAVEHDR header;
    header.lpData = (LPSTR)buffer;
    header.dwBufferLength = samples * 2 * sizeof(short);
    header.dwFlags = 0;

    waveOutPrepareHeader(hWave, &header, sizeof(header));
    waveOutWrite(hWave, &header, sizeof(header));

    Sleep(DURATION * 1000);

    waveOutUnprepareHeader(hWave, &header, sizeof(header));
    waveOutClose(hWave);

    free(buffer);
}

int main() {

    printf("LEFT speaker\n");
    play_channel(1,0);

    Sleep(500);

    printf("RIGHT speaker\n");
    play_channel(0,1);

    return 0;
}