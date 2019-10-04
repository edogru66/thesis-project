//
// Created by emre on 8.10.2018.
//

#include "../H/DnaSeq.h"

const std::string &DnaSeq::getChr() const {
    return chr;
}

void DnaSeq::setChr(const std::string &chr) {
    DnaSeq::chr = chr;
}

int DnaSeq::getStart_index() const {
    return start_index;
}

void DnaSeq::setStart_index(int start_index) {
    DnaSeq::start_index = start_index;
}

int DnaSeq::getEnd_index() const {
    return end_index;
}

void DnaSeq::setEnd_index(int end_index) {
    DnaSeq::end_index = end_index;
}

DnaSeq::DnaSeq(const std::string &chr, int start_index, int end_index) : chr(chr), start_index(start_index),
                                                                         end_index(end_index) {}

DnaSeq::~DnaSeq() {

}

std::ostream &operator<<(std::ostream &os, const DnaSeq &seq) {
    os << "chr: " << seq.chr << " start_index: " << seq.start_index << " end_index: " << seq.end_index;
    return os;
}

bool DnaSeq::operator<(const DnaSeq &rhs) const {
    if (chr < rhs.chr)
        return true;
    if (rhs.chr < chr)
        return false;
    if (start_index < rhs.start_index)
        return true;
    if (rhs.start_index < start_index)
        return false;
    return end_index < rhs.end_index;
}

bool DnaSeq::operator>(const DnaSeq &rhs) const {
    return rhs < *this;
}

bool DnaSeq::operator<=(const DnaSeq &rhs) const {
    return !(rhs < *this);
}

bool DnaSeq::operator>=(const DnaSeq &rhs) const {
    return !(*this < rhs);
}

int DnaSeq::Compare(const DnaSeq &rhs) const {
    if (this->getChr() != rhs.getChr()) return this->getChr().compare(rhs.getChr());
    if (this->getStart_index() > rhs.getStart_index()) return this->getStart_index() - rhs.getStart_index();
    if (this->getStart_index() <= rhs.getStart_index() && this->getEnd_index() >= rhs.getEnd_index()) return 0;
    if (this->getEnd_index() <= rhs.getEnd_index()) return this->getEnd_index() - rhs.getEnd_index();
}
