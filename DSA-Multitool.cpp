// LearningCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <sstream>
#include <string>       // std::string
#include <algorithm>    // std::search
#include <vector>
#include <windows.h>


// Variable Init
char                cStringCheck = '\"';
std::string         sVideoFile = "init";
std::string         sAudioFile = "init";

std::string sResultFile(std::string sSourceFile, std::string sAppend)
{
	return sSourceFile.insert(sSourceFile.length() - 5, sAppend);
}
std::string sResultFileNewFormat(std::string sSourceFile, std::string sAppend)
{
	sSourceFile.erase(sSourceFile.length() - 5); // erasing the original video file format extension (e.g. .mp4) from the length - 5 to the end
	return sSourceFile.insert(sSourceFile.length(), sAppend);
}


void showTitle()
{
	std::cout << R"(
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                                                           
             ((((                                                                          
            ((((     _______       _______.     ___                                        
             ))))   |       \     /       |    /   \                                       
          _ .---.   |  .--.  |   |   (----`   /  ^  \                                      
         ( |`---'|  |  |  |  |    \   \      /  /_\  \    _                                
          \|     |  |  '--'  |.----)   |    /  _____  \  /   _   _|  _        _  ._ |   _  
          : .___, : |_______/ |_______/    /__/     \__\ \_ (_) (_| (/_ \/\/ (_) |  |< _>  
           `-----'                                                                         
                                                                                           
        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
)";
	std::cout << '\n';
}


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

bool CheckFfmpeg()
{
	std::string sSearchString = "ffmpeg";
	char* pValue;
	size_t len;

	errno_t err = _dupenv_s(&pValue, &len, "path");

	// if (err) return -1; NOT SURE WHY IS THIS HERE?

	std::string sToSearch(pValue);

	std::for_each(sToSearch.begin(), sToSearch.end(), [](char& c)
		{
			c = ::tolower(c); // make PATH completely lowercase to be searchable
		});

	std::size_t found = sToSearch.find(sSearchString);
	if (found != std::string::npos)
	{
		std::cout << "FFmpeg Found!" << '\n' << '\n';
		free(pValue); // free buffer again
		return true;
	}

	else std::cout << "ERROR: FFmpeg not found, please install FFmpeg first." << '\n' << '\n';
	free(pValue); // free buffer again
	return false;

}

int main()
{
	int iSelection = 0;

	showTitle();

	std::cout << "                                 Double Shot Audio Multi Tool v0.1\n";
	std::cout << "                       Only use if you have ffmpeg installed and configured in cmd\n\n";

	if (CheckFfmpeg())
	{


		std::cout << "Tools selection: \n";
		std::cout << "1. Video Converter for Nuendo / Cubase \n";
		std::cout << "2. Audio Extractor \n";
		std::cout << "3. Audio Replacer for Video (MOV container with WAV) \n";
		std::cout << "4. Audio Replacer for Video (MP4 container with AAC) \n\n";

		std::cout << "Input your selection : ";

		while (!(std::cin >> iSelection) || (iSelection < 1 || iSelection > 5)) // Input validation
		{
			std::cout << "ERROR: Please enter a valid number : ";
			std::cin.clear();
			std::cin.ignore();
		}

		std::cin.ignore(); // to ignore the \n character after enter!

		switch (iSelection)
		{
		case 1:
			ConvertVideo();
			break;
		case 2:
			ExtractAudio();
			break;
		case 3:
			CombineVideoAudioWav();
			break;
		case 4:
			CombineVideoAudioAac();
			break;
		case 5:
			CheckFfmpeg();
			break;
		}



		std::cout << "Program has ended. \n";
		system("pause");
		return 0;
	}
	else
	{
		std::cout << "Program has ended. \n";
		system("pause");
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
