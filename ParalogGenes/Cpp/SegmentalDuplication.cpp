//
// Created by emre on 8.10.2018.
//

#include "../H/SegmentalDuplication.h"

SegmentalDuplication::SegmentalDuplication(const std::string &chr, int start_index, int end_index)
        :
        DnaSeq(chr,
               start_index,
               end_index),
        genes(),
        groupId(-1) {}

void SegmentalDuplication::AddGene(const Gene &gene) const {
    genes.insert(gene);
}

const Gene *SegmentalDuplication::Find(const Gene &gene) const {
    auto it = genes.find(gene);
    if (it != genes.end()) return &(*it);
    return nullptr;
}

void SegmentalDuplication::setGroupId(int groupId) {
    SegmentalDuplication::groupId = groupId;
}

std::set<Gene> &SegmentalDuplication::getGenes() const {
    return genes;
}

int SegmentalDuplication::getGroupId() const {
    return groupId;
}

SegmentalDuplication::SegmentalDuplication(const SegmentalDuplication &obj)
        :
        DnaSeq(obj.getChr(),
               obj.getStart_index(),
               obj.getEnd_index()
        ),
        genes(obj.getGenes()),
        groupId(obj.getGroupId()) {
}
