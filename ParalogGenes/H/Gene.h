//
// Created by emre on 8.10.2018.
//

#ifndef PARALOGGENES_GENE_H
#define PARALOGGENES_GENE_H


#include <ostream>
#include "DnaSeq.h"

class Gene: public DnaSeq {
public:
    Gene(const std::string &chr, int start_index, int end_index, double mean, double median);

    double getMean() const {
        return mean;
    }
    double getMedian() const {
        return median;
    }
private:
    double mean, median;
public:
    friend std::ostream &operator<<(std::ostream &os, const Gene &gene);

    void setMean(double mean);

    void setMedian(double median);
};


#endif //PARALOGGENES_GENE_H
