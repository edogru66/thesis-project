//
// Created by emre on 8.10.2018.
//

#include "../H/Gene.h"


Gene::Gene(const std::string &chr, int start_index, int end_index, double mean, double median) : DnaSeq(chr,
                                                                                                        start_index,
                                                                                                        end_index),
                                                                                                 mean(mean),
                                                                                                 median(median) {}

void Gene::setMean(double mean) {
    Gene::mean = mean;
}

void Gene::setMedian(double median) {
    Gene::median = median;
}

std::ostream &operator<<(std::ostream &os, const Gene &gene) {
    os << gene.getChr() << "\t" << gene.getStart_index() << "\t" << gene.getEnd_index() << "\t" << gene.median << "\t"
       << gene.mean;
    return os;
}
