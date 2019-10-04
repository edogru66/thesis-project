//
// Created by emre on 2019-02-17.
//

#include "FastaGenerator.h"

#include <htslib/sam.h>
#include <htslib/faidx.h>
#include <vector>

using std::vector;
using std::cout;
using std::endl;


bool FastaGenerator::GenerateFastaFile(const char* bamFilePath, const char* fastaFilePath) {
    samFile *fp = hts_open(bamFilePath, "r");
    bam_hdr_t *bam_hdr = sam_hdr_read(fp);
    bam1_t *aln = bam_init1();
    string current_chr = "chr1";
    ofstream FastaFile;
    FastaFile.open(fastaFilePath);

    string region;
    vector<int> read_depth;
    while (sam_read1(fp, bam_hdr, aln) >= 0) {
        int32_t pos = aln->core.pos + 1; //left most position of alignment in zero based coordianate (+1)
        if (aln->core.tid < 0)
        {
            break;
        }
        string chr(bam_hdr->target_name[aln->core.tid]); //contig name (chromosome)
        auto len = static_cast<uint32_t>(aln->core.l_qseq); //length of the read.

        uint8_t *q = bam_get_seq(aln); //quality string
        //uint32_t q2 = aln->core.qual ; //mapping quality
        if (chr.find("chr") == string::npos) {
            chr = "chr" + chr;
        }

        char *qseq = (char *) malloc(len);
        bool flag = current_chr != chr;
        if (flag) {
            if (FastaFile.is_open())
            {
                FastaFile << ">" << current_chr << " dna:chromosome " << current_chr << ":" << 1 << ":" << region.size()
                          << "\n";
                for (size_t i = 0; i < region.size(); i += 60) {
                    FastaFile << region.substr(i, 60) << endl;
                }
                current_chr = chr;
                region.clear();
                read_depth.clear();
            }
            else
            {
                return false;
            }
        }

        for (int i = 0; i < len; i++) {
            qseq[i] = seq_nt16_str[bam_seqi(q, i)]; //gets nucleotide id and converts them into IUPAC id.
            while (region.size() < pos + i) {
                region.push_back('N');
                read_depth.push_back(0);
            }
            if (region.size() == pos + i) {
                region.push_back(qseq[i]);
                read_depth.push_back(1);
            } else {
                if (region[(pos + i)] == 'N' || region[(pos + i)] == qseq[i]) {
                    region[(pos + i)] = qseq[i];
                    read_depth[(pos + i)]++;
                } else if (region[(pos + i)] != qseq[i]) {
                    if (read_depth[(pos + i)] == 0) {
                        region[(pos + i)] = qseq[i];
                        read_depth[(pos + i)]++;
                    } else {
                        read_depth[(pos + i)]--;
                    }
                }
            }
        }
        free(qseq);
    }
    bam_destroy1(aln);
    hts_close(fp);
    FastaFile.close();
    return true;
}
