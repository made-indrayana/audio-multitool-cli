#include <iostream>
#include <sstream>
#include <string>       // std::string
#include <algorithm>    // std::search or size_t
#include "Multitool-Actions.h"

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
		std::cout << "4. Audio Replacer for Video (MP4 container with AAC) \n";
		std::cout << "5. WAV to MP3 converter (VBR 192k) \n\n";

		std::cout << "Input your selection : ";

		while (!(std::cin >> iSelection) || (iSelection < 1 || iSelection > 100)) // Input validation
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
			ConvertAudioToMp3();
			break;
		default:
			std::cout << "This is not a valid option! \n";
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
