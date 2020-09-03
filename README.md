# Double Shot Audio Multitool

Multitool developed for a few video-audio related workflow as a C++ learning project. **Please pardon all the beginner programmer's mistake!**
At this moment this is a Windows-Only application. MacOS will follow in the future hopefully.

***You have to have ffmpeg installed and configured to be used as a command in the command line to make this program to work.***
FFMpeg Download and setup in Windows: [Link](https://video.stackexchange.com/questions/20495/how-do-i-set-up-and-use-ffmpeg-in-windows)

## Features
1. Video converter for Cubase / Nuendo to accomodate frame-per-frame scrubbing
    - Does not change the original codec nor the resolution thus avoiding re-encoding
    - Will set B Frames number to zero and set every frame as a keyframe with `-bf 0` and `-g 1`

2. Audio Extractor
    - Will extract audio out of a video file in WAV 24 bit format

3. Audio Replacer for Video (MOV container with WAV)
    - will replace audio in the video with PCM 24bit codec quality regardless of source audio file
    - will change the video container to MOV to accomodate PCM codec

4. Audio Replacer for Video (MP4 container with AAC)
    - will replace audio in the video with AAC codec regardless of source audio file
    - will use MP4 video container

## Planned Feature
1. Ambisonic Audio to Video embedder
2. MacOS Build

-----------------------------------------------------------------------
Best,
Indra
Double Shot Audio
indra@doubleshot-audio.com