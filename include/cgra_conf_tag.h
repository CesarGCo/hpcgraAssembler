#ifndef CGRA_CONF_TAG_H
#define CGRA_CONF_TAG_H

#include <vector>
#include <string>
#include <utils.h>

class ConfTag {
public:
    std::string reset;
    std::string alu;
    std::vector<std::string> constant;
    std::string router;
    int bits;
    ConfTag(bool hasRouter, int numConsts);

    void conf(bool hasRouter, int numConsts);

};

#endif 