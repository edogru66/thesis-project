//
//  GCCorrection.cpp
//  
//
//  Created by emre on 3.03.2019.
//

#include "GCCorrection.h"
#include "polyfit.hpp"

GCCorrection::GCCorrection(uint32_t size, const char* aFasta):
window_size(size),
fasta(aFasta)
{
    
}

void GCCorrection::addNewRead(string chr, int pos, int len)
{
    gc_correction_window_t tmp(chr, window_size * (pos / window_size));
    auto related_window = active_windows.insert(tmp);
    if (related_window.second) {
        calculateGCPercentForWindows(&(*related_window.first));
    }
    
    if (pos + len > related_window.first->pos + window_size) {
        gc_correction_window_t tmp2(chr, window_size * (pos / window_size + 1));
        auto related_window2 = active_windows.insert(tmp2);
        if (related_window2.second) {
            calculateGCPercentForWindows(&(*related_window2.first));
        }
        related_window.first->total_read_depth += tmp2.pos - pos;
        related_window2.first->total_read_depth += pos + len - tmp2.pos;
    } else {
        related_window.first->total_read_depth += len;
    }
}

vector<double> GCCorrection::calculateCoefficients()
{
    vector<double> gc_percentage, read_depth;
    for (auto ptr : active_windows) {
        gc_percentage.push_back(ptr.gc_percentage);
        read_depth.push_back((double)ptr.total_read_depth/window_size);
    }
    return polyfit(gc_percentage, read_depth, 1);
}


double GCCorrection::getGcPercentAt(string region)
{
    return gc_percent_by_region[region];
}

void GCCorrection::calculateGCPercentForWindows(const gc_correction_window_t *ptr)
{
    string region = ptr->chr + ":" + to_string(ptr->pos) + "-" + to_string(ptr->pos + window_size - 1);
    ptr->gc_percentage = get_gc_percent(fasta, region.c_str());
    gc_percent_by_region[region] = ptr->gc_percentage;
    auto key = round(ptr->gc_percentage * 10);
    read_depth_table[key].emplace_back(ptr);
}

void GCCorrection::printWindows()
{
    for (auto ptr : active_windows) {
        cout << ptr.chr << ":" << ptr.pos << "-" << (ptr.pos + window_size - 1) << "\t" << ptr.gc_percentage << "\t" << ((double)ptr.total_read_depth/window_size) << endl;
    }
}
