//
// Created by emre on 8.10.2018.
//

#ifndef PARALOGGENES_DNASEQ_H
#define PARALOGGENES_DNASEQ_H

#include <string>
#include <ostream>

class DnaSeq {

private:
    std::string chr;
    int start_index, end_index;

public:
    DnaSeq(const std::string &chr, int start_index, int end_index);

    virtual ~DnaSeq();

    const std::string &getChr() const;

    void setChr(const std::string &chr);

    int getStart_index() const;

    void setStart_index(int start_index);

    int getEnd_index() const;

    void setEnd_index(int end_index);

    friend std::ostream &operator<<(std::ostream &os, const DnaSeq &seq);

    bool operator==(const DnaSeq &rhs) const {
        return chr == rhs.chr &&
               start_index == rhs.start_index &&
               end_index == rhs.end_index;
    }

    bool operator!=(const DnaSeq &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const DnaSeq &rhs) const;

    bool operator>(const DnaSeq &rhs) const;

    bool operator<=(const DnaSeq &rhs) const;

    bool operator>=(const DnaSeq &rhs) const;

    int Compare(const DnaSeq &rhs) const;
};


#endif //PARALOGGENES_DNASEQ_H
