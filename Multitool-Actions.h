#ifndef MULTITOOL_ACTIONS_H
#define MULTITOOL_ACTIONS_H

#include <iostream>

namespace GlobalVariable
{
	extern std::string		sVideoFile;
	extern std::string		sAudioFile;
	extern char				cStringCheck;
	extern std::string		sResultFile;
	extern std::string		sResultFileNewFormat;

}

void ConvertVideo();
void ExtractAudio();
void CombineVideoAudioWav();
void CombineVideoAudioAac();
void ConvertAudioToMp3();



#endif  MULTITOOL_ACTIONS_H
