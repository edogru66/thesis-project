#include <iostream>
#include <map>
#include <sstream>
#include "../H/Utility.h"


int main() {

    std::set<SegmentalDuplication> d = Utility::readDuplicationsFile("result");
    std::cout << "readDuplicationsFile: " << d.size() << std::endl;
    Genes g = Utility::readGeneFile("gene_mean_median_reference");
    std::cout << "readGeneFile: " << g.size() << std::endl;

    auto genePtr = g.begin();
    auto segmentPtr = d.begin();
    while (segmentPtr != d.end()) {

        while (genePtr != g.end() && segmentPtr->Compare(*genePtr) > 0)
            genePtr++;

//        std::cout << *segmentPtr << std::endl;
        while (genePtr != g.end() && genePtr->getStart_index() < segmentPtr->getEnd_index()) {
            if (segmentPtr->Compare(*genePtr) == 0)
            {
                segmentPtr->AddGene(*genePtr);
//                std::cout << *genePtr << std::endl;
            }
            genePtr++;
        }
        genePtr = g.begin();
        segmentPtr++;
    }

    int index = 0;
    int segmentCount = 0;
    int count = 0;
    Duplications duplications(static_cast<size_t>(16262));
    for (const auto &ptr : d) {
        if (ptr.getGenes().empty()) continue;
        duplications[ptr.getGroupId()].push_back(ptr);
    }

    std::vector<Gene> totalCNVs;

    for (const auto &ptr : duplications) {
        if (ptr.empty()) continue;
        double totalCnvParalog = 0;
        std::stringstream ss;
        std::vector<Gene> gene_vector;
//        ss << ptr[0].getGroupId() << "\n";
        for (const SegmentalDuplication &segmentalDuplication : ptr) {
            segmentCount++;
            ss << "\t" << segmentalDuplication << std::endl;
            for (const Gene &gene : segmentalDuplication.getGenes()) {
                count++;
                totalCnvParalog += gene.getMean();
                ss << "\t\t" << gene << std::endl;
            }
            for (Gene gene : segmentalDuplication.getGenes()) {
                gene.setMean(totalCnvParalog);
                gene_vector.push_back(gene);
            }
        }
        totalCNVs.insert(totalCNVs.end(), gene_vector.begin(), gene_vector.end());
        std::cout << ss.str() << std::endl;
    }

    for (Gene g : totalCNVs) {
        std::cout << g << std::endl;
    }
    std::cout << "There are " << segmentCount << " segment" << std::endl;
    std::cout << count << " many genes in segment" << std::endl;

    return 0;
}