#include "solution.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input_file.txt" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    
    solution::simulation(inputFile);

    return 0;
}