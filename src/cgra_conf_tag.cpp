#include <cgra_conf_tag.h>

ConfTag::ConfTag(bool hasRouter, int numConsts) {
    conf(hasRouter, numConsts);
}

void ConfTag::conf(bool hasRouter, int numConsts) {
    int baseBits = 2;
    if (hasRouter) {
        baseBits = 3;
    }
    this->bits = bitsFunct(baseBits+numConsts);

    this->reset = formatToBinary(0, this->bits);
    this->alu = formatToBinary(1, this->bits);
    this->constant.clear();
    for (int i = 0; i < numConsts; ++i) {
        this->constant.push_back(formatToBinary(2 + i, this->bits));
    }
    this->router = formatToBinary(2 + numConsts, this->bits);
}
