//
//  Common.cpp
//  test
//
//  Created by emre on 2.03.2019.
//  Copyright © 2019 emre. All rights reserved.
//

#include "Common.h"
#include <htslib/faidx.h>
#include <htslib/sam.h>


map<singly_unique_nucleotide, int> sun_read(const string &filename)
{
    map<singly_unique_nucleotide, int> result;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        char delimiter = '\t';
        while (getline(file, line)) {
            size_t s_pos = line.find(delimiter) + 1;
            size_t e_pos = line.find(delimiter, s_pos);
            string token;
            while (e_pos != string::npos) {
                singly_unique_nucleotide sun(line.substr(s_pos, e_pos - s_pos));
                result.insert(make_pair(sun, 0));
                s_pos = e_pos + 1;
                e_pos = line.find(delimiter, e_pos + 1);
            }
        }
    }
    return result;
}

vector<gene> gene_read(const string &filename)
{
    vector<gene> result;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            vector<std::string> results((istream_iterator<string>(iss)),
                                        istream_iterator<string>());
            
            gene gene1(results[0], stoi(results[1]), stoi(results[2]));
            result.push_back(gene1);
        }
    }
    return result;
}

double get_gc_percent(const char *fasta, const char *region)
{
    int length;
    double sum = 0;
    
    faidx_t *fasta_index = fai_load(fasta);
    char *seq = fai_fetch(fasta_index, region, &length);
    
    if (length > 0) {
        for (int i = 0; i < length; ++i) {
            if (seq[i] == 'G' || seq[i] == 'C') {
                sum++;
            }
        }
    }
    fai_destroy(fasta_index);
    delete[]seq;
    
    return 100 * (sum / length);
}

double mean(vector<double> input)
{
    double sum = 0;
    for (double &i: input) {
        sum += i;
    }
    return sum / input.size();
}

double median(vector<double> input)
{
    sort(input.begin(), input.end());
    size_t size = input.size();
    return (size % 2 == 1) ? (input[size / 2]) : ((input[size / 2 - 1] + input[size / 2]) / 2);
}

char* convert_id_to_nucleotide(int32_t len, uint8_t *q)
{
    char *qseq = (char *) malloc(len);
    for (int i = 0; i < len; i++) {
        qseq[i] = seq_nt16_str[bam_seqi(q, i)]; //gets nucleotide id and converts them into IUPAC id.
    }
    
    return qseq;
}

double calculate_gcCorrected_read_depth(const vector<double> coefficients, const double mean, const double gc_percent, const double read_depth)
{
    double coefficient = mean / (coefficients[0]*gc_percent+coefficients[1]);
    return read_depth*coefficient;
}
