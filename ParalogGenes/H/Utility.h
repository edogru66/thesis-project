//
// Created by emre on 8.10.2018.
//

#ifndef PARALOGGENES_UTILITY_H
#define PARALOGGENES_UTILITY_H


#include <vector>
#include "Gene.h"
#include "SegmentalDuplication.h"
#include "TypeDefs.h"

class Utility {
public:
    static Gene createGeneFromLine(std::string line);

    static std::set<Gene> readGeneFile(std::string filename = "gene_mean_median_NA12878");

    static SegmentalDuplication createSegmentalDuplicationFromString(std::string str);

    static DuplicationSet createDuplicationSetFromLine(std::string line);

    static std::set<SegmentalDuplication> readDuplicationsFile(std::string filename = "result");

};


#endif //PARALOGGENES_UTILITY_H
