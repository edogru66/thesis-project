//
// Created by emre on 8.10.2018.
//

#include "../H/Utility.h"
#include <boost/algorithm/string.hpp>
#include <fstream>

Gene Utility::createGeneFromLine(std::string line) {
    std::vector<std::string> result;
    boost::split(result, line, boost::is_any_of("\t"));

    return Gene(result[0], stoi(result[1]), stoi(result[2]), stod(result[3]), stod(result[4]));
}

std::set<Gene> Utility::readGeneFile(std::string filename) {
    std::set<Gene> result;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            result.insert(createGeneFromLine(line));
        }
        file.close();
    }
    return result;
}

SegmentalDuplication Utility::createSegmentalDuplicationFromString(std::string str) {
    std::vector<std::string> result;
    boost::split(result, str, boost::is_any_of(":"));

    return SegmentalDuplication(result[0], stoi(result[1]), stoi(result[2]));
}

DuplicationSet Utility::createDuplicationSetFromLine(std::string line) {
    DuplicationSet result;
    std::vector<std::string> splitArray;
    boost::split(splitArray, line, boost::is_any_of("\t"));
    for (int j = 0; j < splitArray.size(); ++j) {
        result.push_back(createSegmentalDuplicationFromString(splitArray[j]));
    }
    return result;
}

std::set<SegmentalDuplication> Utility::readDuplicationsFile(std::string filename) {
    std::set<SegmentalDuplication> result;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int group = 0;
        while (std::getline(file, line)) {
            boost::trim(line);
            auto tmp = createDuplicationSetFromLine(line);
            for (SegmentalDuplication s: tmp) {
                s.setGroupId(group);
                result.insert(s);
            }
            group++;
        }
        file.close();
    }
    return result;
}
