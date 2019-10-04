//
// Created by emre on 8.10.2018.
//

#ifndef PARALOGGENES_SEGMENTALDUPLICATION_H
#define PARALOGGENES_SEGMENTALDUPLICATION_H

#include <set>
#include <vector>
#include "Gene.h"

class SegmentalDuplication : public DnaSeq {

public:
    SegmentalDuplication(const std::string &chr, int start_index, int end_index);
    SegmentalDuplication(const SegmentalDuplication& obj);

    void AddGene(const Gene &gene) const;

    const Gene *Find(const Gene &gene) const;

    std::set<Gene> &getGenes() const;

    int getGroupId() const;

    void setGroupId(int groupId);

private:
    mutable std::set<Gene> genes;
    int groupId;
};


#endif //PARALOGGENES_SEGMENTALDUPLICATION_H
