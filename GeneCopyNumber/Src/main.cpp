//
//  main.cpp
//  test
//
//  Created by emre on 9.08.2018.
//  Copyright © 2018 emre. All rights reserved.
//

#include <iostream>
#include <htslib/faidx.h>
#include <htslib/sam.h>
#include "Logger.h"
#include "FastaGenerator.h"
#include "GCCorrection.h"
#include "Common.h"
#include "polyfit.hpp"

using std::vector;
using std::ifstream;
using std::stringstream;
using std::map;

const int WINDOW_SIZE = 1000;
const char *fasta = "/Users/emre/Documents/NA18507.fa";
const char *bamFilePath = "/Users/emre/Documents/NA18507.bam";
const char *geneFilePath = "/Users/emre/Documents/MATLAB/hg19_genes";

#define DEBUG_PRINT(sth) printf(sth)

int main(int argc, const char * argv[]) {
    // insert code here...
    LOG(info) << "Log started";
    
    ifstream fastaStream(fasta);
    if (!fastaStream.good()) {
        FastaGenerator::GenerateFastaFile(bamFilePath, fasta);
    }
    map<singly_unique_nucleotide, int> sun_set = sun_read("/Users/emre/CLionProjects/untitled/cmake-build-debug/test");
    LOG(info) << "Sunset size: " << sun_set.size();
    
    
    // properties
    long long unsigned int denom = 0, num = 0;
    int p = 0;
    int start_pos = 0, end_pos = 0;
    string current_chr;
    string region;
    
    GCCorrection gcCorrection(WINDOW_SIZE, fasta);
    clock_t begin = clock();
    // htslib bamfile initialization
    samFile *fp = hts_open(bamFilePath, "r");
    //    samFile *fp = hts_open(argv[1], "r");
    bam_hdr_t *bam_hdr = sam_hdr_read(fp);
    bam1_t *aln = bam_init1();
    
    
    while (sam_read1(fp, bam_hdr, aln) >= 0) {
        int32_t pos = aln->core.pos + 1; //left most position of alignment in zero based coordianate (+1)
        int32_t len = aln->core.l_qseq;
        string chr = "";

        if (aln->core.tid < 0) {
            cout << "aln->core.tid=" << aln->core.tid << endl;
            continue;
        }
        chr.append(bam_hdr->target_name[aln->core.tid]); //contig name (chromosome)
        uint8_t *q = bam_get_seq(aln); //quality string
        //uint32_t q2 = aln->core.qual ; //mapping quality
        
        char *qseq = convert_id_to_nucleotide(len, q);
        
        if (current_chr != chr) {
            current_chr = chr;
            denom += (end_pos - start_pos);
            start_pos = pos;
            end_pos = pos;
            
//            if (chr == "chr2") {
//                break;
//            }
        } else if (end_pos < pos + len - 1) {
            end_pos = pos + len - 1;
        }
        
        gcCorrection.addNewRead(chr, pos, len);
        
        singly_unique_nucleotide start_sun(chr, pos, qseq[0]),
        end_sun(chr, pos + len, qseq[len-1]);
        
        if (start_sun > sun_set.rbegin()->first) break;
        
        auto it = sun_set.lower_bound(start_sun);
        
        while (it != sun_set.end() && (it->first < end_sun || it->first == end_sun)) {
            if (qseq[it->first.idx - pos - 1] == it->first.nucleotide) {
                it->second++;
            } else {
                // TODO
                it = sun_set.erase(it);
            }
            int index = WINDOW_SIZE * (it->first.idx / WINDOW_SIZE);
            it->first.region =
            it->first.chr + ":" + to_string(index) + "-" + to_string(index + WINDOW_SIZE - 1);
            it++;
        }
        num += len;
        p++;
        if (p % 1000000 == 0) {
            LOG(info) << (end_sun.ToString());
        }
        
        free(qseq);
    }
    clock_t end = clock();
    LOG(info) << "Time elapsed " << to_string(double(end - begin) / CLOCKS_PER_SEC);
    bam_destroy1(aln);
    hts_close(fp);
    
//    gcCorrection.printWindows();
    
    auto gc_correction_coefficients = gcCorrection.calculateCoefficients();
    
    double genome_wide_read_depth = (double) num / denom;
    
    vector<gene> Genes = gene_read(geneFilePath);
    for (auto it = Genes.begin(); it != Genes.end(); ++it) {
        LOG(info) << it->ToString();
        singly_unique_nucleotide start_sun(it->chr, it->start, ' '),
        end_sun(it->chr, it->end, ' ');
        auto ptr = sun_set.lower_bound(start_sun);
        while (ptr->first < end_sun || ptr->first == end_sun) {
            
            LOG(info) << "\t" + ptr->first.ToString() + "\t" + to_string(ptr->second);
            
            if (ptr->second > 0) {
//                it->sun_read_depth.push_back(calculate_gcCorrected_read_depth(gc_correction_coefficients, genome_wide_read_depth, gcCorrection.getGcPercentAt(ptr->first.region),
//                                                                              ptr->second/genome_wide_read_depth));
                
                it->sun_read_depth.emplace_back(ptr->second/genome_wide_read_depth);
            }
            ptr++;
        }
        
        if (!it->sun_read_depth.empty())
            cout << *it << "\t" << mean(it->sun_read_depth) << "\t" << median(it->sun_read_depth) << endl;
    }
    
    return 0;
}
