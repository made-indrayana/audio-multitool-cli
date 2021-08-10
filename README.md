# Double Shot Audio Multitool

Multitool is a ffmpeg-wrapper developed for a few video-audio related workflow as a C++ learning project.
At this moment this is a Windows-Only application.

***You have to have ffmpeg installed and configured to be used as a command in the command line to make this program to work.***
FFMpeg Download and setup in Windows: [Link](https://video.stackexchange.com/questions/20495/how-do-i-set-up-and-use-ffmpeg-in-windows)

## Features
1. Video converter for Cubase / Nuendo to accomodate frame-per-frame scrubbing
   * Does not change the original codec nor the resolution thus avoiding re-encoding
   * Sets B Frames number to zero and makes every frame as a keyframe with `-bf 0` and `-g 1`
2. Audio Extractor
   * Extracts audio out of a video file in WAV 24 bit format
3. Audio Replacer for Video (MOV container with WAV)
   * Replaces audio in the video with PCM 24bit codec quality regardless of source audio file
   * Changes the video container to MOV to accomodate PCM codec
4. Audio Replacer for Video (MP4 container with AAC)
   * Replaces audio in the video with AAC codec regardless of source audio file
   * Use MP4 video container
5. WAV to MP3 converter (VBR 192k Quality)

## Planned Feature
1. Ambisonic Audio to Video embedder
