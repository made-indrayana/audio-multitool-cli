#include <iostream>
#include <sstream>
#include <string>

namespace GlobalVariable
{
	std::string sVideoFile;
	std::string sAudioFile;
	char cStringCheck = '\"';

	std::string sResultFile(std::string sSourceFile, std::string sAppend)
	{
		return sSourceFile.insert(sSourceFile.length() - 5, sAppend);
	}
	std::string sResultFileNewFormat(std::string sSourceFile, std::string sAppend)
	{
		sSourceFile.erase(sSourceFile.length() - 5); // erasing the original video file format extension (e.g. .mp4) from the length - 5 to the end
		return sSourceFile.insert(sSourceFile.length(), sAppend);
	}
}

using namespace GlobalVariable;

// FUNCTIONS START HERE -------------------------------------------------------------------------------------------------------------------------------

void ConvertVideo()
{
	std::string sAppend = "-Nuendo";

	std::cout << "Please drag and drop the video file to convert :\n";
	std::getline(std::cin, sVideoFile);


	while ((sVideoFile.at(0) != cStringCheck) || sVideoFile.length() < 4)
	{
		std::cout << "ERROR: Invalid input \n" << "Please drag and drop the video file to convert :\n";
		std::cin.clear();

		std::getline(std::cin, sVideoFile);
	}

	system(("ffmpeg -i " + sVideoFile + " -bf 0 -g 1 " + sResultFile(sVideoFile, sAppend)).c_str());
}

void ExtractAudio()
{
	std::string sAppend = "-WavAudio.wav\"";

	std::cout << "Please drag and drop the video file to extract audio track :\n";
	std::getline(std::cin, sVideoFile);

	while ((sVideoFile.at(0) != cStringCheck) || sVideoFile.length() < 4)
	{
		std::cout << "ERROR: Invalid input \n" << "Please drag and drop the video file to convert :\n";
		std::cin.clear();

		std::getline(std::cin, sVideoFile);
	}

	system(("ffmpeg -i " + sVideoFile + " -vn -c:a pcm_s24le " + sResultFileNewFormat(sVideoFile, sAppend)).c_str());
}

void CombineVideoAudioWav()
{
	std::string sAppend = "-NewAudio.mov\"";

	std::cout << "Please drag and drop the video file :\n";
	std::getline(std::cin, sVideoFile);

	while ((sVideoFile.at(0) != cStringCheck) || sVideoFile.length() < 4)
	{
		std::cout << "ERROR: Invalid input \n" << "Please drag and drop the video file to convert :\n";
		std::cin.clear();

		std::getline(std::cin, sVideoFile);
	}

	std::cout << "\nPlease drag and drop the audio file (WAV only!) : \n";
	std::getline(std::cin, sAudioFile);

	while ((sAudioFile.at(0) != cStringCheck) || sAudioFile.length() < 4)
	{
		std::cout << "ERROR: Invalid input \n" << "Please drag and drop the video file to convert :\n";
		std::cin.clear();

		std::getline(std::cin, sVideoFile);
	}

	system(("ffmpeg -i " + sVideoFile + " -i " + sAudioFile + " -map 0:v:0 -map 1:a:0 -c:v copy -c:a copy " + sResultFileNewFormat(sVideoFile, sAppend)).c_str());
}

void CombineVideoAudioAac()
{
	std::string sVideoFile = "init";
	std::string sAudioFile = "init";
	std::string sAppend = "-NewAudio.mp4\"";

	std::cout << "Please drag and drop the video file :\n";
	std::getline(std::cin, sVideoFile);
	std::cout << "\nPlease drag and drop the audio file : \n";
	std::getline(std::cin, sAudioFile);

	system(("ffmpeg -i " + sVideoFile + " -i " + sAudioFile + " -map 0:v:0 -map 1:a:0 -c:v copy -c:a aac " + sResultFileNewFormat(sVideoFile, sAppend)).c_str());
}

void ConvertAudioToMp3()
{
	std::string sAppend = ".mp3\"";

	std::cout << "Please drag and drop the audio file to convert to mp3 :\n";
	std::getline(std::cin, sAudioFile);

	while ((sAudioFile.at(0) != cStringCheck) || sAudioFile.length() < 4)
	{
		std::cout << "ERROR: Invalid input \n" << "Please drag and drop the video file to convert :\n";
		std::cin.clear();

		std::getline(std::cin, sAudioFile);
	}

	system(("ffmpeg -i " + sAudioFile + " -c:a libmp3lame -q:a 2 " + sResultFileNewFormat(sAudioFile, sAppend)).c_str());
}
