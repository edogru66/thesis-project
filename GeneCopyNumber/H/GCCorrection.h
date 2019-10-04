//
//  GCCorrection.hpp
//  
//
//  Created by emre on 3.03.2019.
//

#ifndef GCCorrection_h
#define GCCorrection_h

#include <vector>
#include <set>
#include <map>
#include <string>
#include "Common.h"
using namespace std;

class GCCorrection
{
public:
    GCCorrection(uint32_t, const char*);
    void addNewRead(string chr, int pos, int len);
    vector<double> calculateCoefficients();
    double getGcPercentAt(string region);
    void printWindows();
private:
    uint32_t window_size;
    const char *fasta;
    map<int, vector<const gc_correction_window_t*>> read_depth_table;
    std::map<string, double> gc_percent_by_region;
    set<gc_correction_window_t> active_windows;
    
    void calculateGCPercentForWindows(const gc_correction_window_t*);
};

#endif /* GCCorrection_hpp */
