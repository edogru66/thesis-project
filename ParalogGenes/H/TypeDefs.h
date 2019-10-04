//
// Created by emre on 10.10.2018.
//

#ifndef PARALOGGENES_TYPEDEFS_H
#define PARALOGGENES_TYPEDEFS_H

#include <vector>
#include "SegmentalDuplication.h"

typedef std::vector<SegmentalDuplication> DuplicationSet;
typedef std::vector<DuplicationSet> Duplications;
typedef std::set<Gene> Genes;

#endif //PARALOGGENES_TYPEDEFS_H
