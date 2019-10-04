//
//  Common.h
//  test
//
//  Created by emre on 2.03.2019.
//  Copyright © 2019 emre. All rights reserved.
//

#ifndef Common_h
#define Common_h

#include <iostream>
#include <set>
#include <fstream>
#include <map>
#include <ctime>
#include <vector>
#include <cstring>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

struct gc_correction_window_t {
    string chr;
    int pos;
    mutable double gc_percentage;
    mutable int total_read_depth;
    
    gc_correction_window_t(string chr0, const int pos0)
    :
    chr(std::move(chr0)),
    pos(pos0),
    total_read_depth(0) {
    }
    
    gc_correction_window_t() {}
    
    bool operator<(const gc_correction_window_t &obj) const {
        if (this->chr != obj.chr) return this->chr < obj.chr;
        return this->pos < obj.pos;
    }
    
    friend ostream &operator<<(ostream &os, const gc_correction_window_t &window) {
        os << "chr: " << window.chr << " pos: " << window.pos << " gc_percentage: " << window.gc_percentage
        << " total_read_depth: " << window.total_read_depth;
        return os;
    }
};

struct singly_unique_nucleotide {
    string chr;
    char nucleotide;
    int idx;
    mutable string region;
    
    singly_unique_nucleotide(string chr0, const int index0, const char nucleotide) :
    chr(std::move(chr0)), idx(index0), nucleotide(nucleotide), region("") {}
    
    explicit singly_unique_nucleotide(string line) {
        size_t s_pos = 0;
        size_t e_pos = line.find(':');
        chr = line.substr(s_pos, e_pos - s_pos);
        s_pos = e_pos + 1;
        e_pos = line.find(':', e_pos + 1);
        idx = stoi(line.substr(s_pos, e_pos - s_pos));
        nucleotide = line[e_pos + 1];
    }
    
    bool operator<(const singly_unique_nucleotide &location) const {
        if (this->chr != location.chr) return this->chr < location.chr;
        if (this->idx != location.idx) return this->idx < location.idx;
        return false;
    }
    
    bool operator==(const singly_unique_nucleotide &location) const {
        return this->chr == location.chr && this->idx == location.idx;
    }
    
    bool operator>(const singly_unique_nucleotide &location) const {
        return !(*this == location || *this < location);
    }
    
    string ToString() const {
        string result;
        result.append(this->chr);
        result.append("\t");
        result.append(to_string(this->idx));
        
        return result;
    }
    
    friend ostream &operator<<(ostream &o, const singly_unique_nucleotide &sun) {
        return o << sun.ToString();
    }
};

struct gene {
    string chr;
    int start;
    int end;
    vector<double> sun_read_depth;
    
    gene(string &chr0, int start0, int end0) : chr(std::move(chr0)), start(start0), end(end0) {}
    
    string ToString() const {
        string result;
        result.append(this->chr);
        result.append("\t");
        result.append(to_string(this->start));
        result.append("\t");
        result.append(to_string(this->end));
        
        return result;
    }
    
    friend ostream &operator<<(ostream &o, const gene &gene1) {
        return o << gene1.ToString();
    }
};

template<typename T>
ostream &operator<<(ostream &o, const vector<T> &v) {
    for (T t:v) {
        o << t << "\t";
    }
    return o;
}

map<singly_unique_nucleotide, int> sun_read(const string &filename);

vector<gene> gene_read(const string &filename);

double get_gc_percent(const char *fasta, const char *region);

double mean(vector<double> input);

double median(vector<double> input);

char* convert_id_to_nucleotide(int32_t len, uint8_t *q);

double calculate_gcCorrected_read_depth(const vector<double> coefficients, const double mean, const double gc_percent, const double read_depth);
#endif /* Common_h */
