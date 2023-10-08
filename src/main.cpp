#include <iostream>
#include <vector>
#include <sndfile.h>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {



    if (argc != 4) { // Checks if user input two files.
        std::cerr << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    const char* inputFileName = argv[1];
    const char* secInputFileName = argv[2];
    const char* fullOutputFileName = argv[3];
    
    SF_INFO fileInfo;
    SNDFILE* inputFile = sf_open(inputFileName, SFM_READ, &fileInfo);
    if (!inputFile) {
        std::cerr << "Error: Failed to open input file." << std::endl;
        return 1;
    }

    SNDFILE* secInputFile = sf_open(secInputFileName, SFM_READ, &fileInfo);
    if (!secInputFile) {
        std::cerr << "Error: Failed to open second input file." << std::endl;
        return 1;
    }

    // We need to add little delay, before seeding
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    std::srand(std::time(0));

    // Generate a random position to start cutting from
    sf_count_t startPosition = std::rand() % fileInfo.frames;

    // Set the position to the random start position
    sf_seek(inputFile, startPosition, SEEK_SET);
    sf_seek(secInputFile, startPosition, SEEK_SET);

    // Calculate the number of frames from the start position to the end of the file
    sf_count_t remainingFrames = fileInfo.frames - startPosition;


    // Create an output file with the same format as the input file
    SF_INFO outputFileInfo = fileInfo;
    outputFileInfo.frames = remainingFrames;


    SF_INFO fullFileInfo = fileInfo;
    SNDFILE* fullFile = sf_open(fullOutputFileName, SFM_WRITE, &outputFileInfo);
    if (!fullFile) {
        std::cerr << "Error: Failed to create full output file." << std::endl;
        sf_close(fullFile);
        return 1;
    }

    // Read and write audio data
    std::vector<double> buffer(fileInfo.channels);
    while (sf_readf_double(inputFile, buffer.data(), 1) > 0) {
        sf_writef_double(fullFile, buffer.data(), 1);

        sf_writef_double(fullFile, buffer.data(), 1);
    } 
    while (sf_readf_double(secInputFile, buffer.data(), 1) > 0){
        sf_writef_double(fullFile, buffer.data(), 1);

        sf_writef_double(fullFile, buffer.data(), 1);
    }
 
    // Close files
    sf_close(inputFile);
    sf_close(secInputFile);
    sf_close(fullFile);

    std::cout << "Audio cropped successfully." << std::endl;

    return 0;
}