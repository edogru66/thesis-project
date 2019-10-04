//
// Created by emre on 2019-02-17.
//

#ifndef THESIS_PROJECT_FASTAGENERATOR_H
#define THESIS_PROJECT_FASTAGENERATOR_H

#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

class FastaGenerator {
public:
    static bool GenerateFastaFile(const char* bamFilePath, const char* fastaFilePath);

private:
    FastaGenerator();
    ~FastaGenerator();
};


#endif //THESIS_PROJECT_FASTAGENERATOR_H
