#ifndef CGRA_CONFIGURATION_H
#define CGRA_CONFIGURATION_H

#include <cgra.h>
#include <cgra_conf_tag.h>
#include <utils.h>

class CgraConfiguration {

    private:
        CGRA m_cgra;

    public:
        CgraConfiguration(CGRA &cgra);

        bool create_reset_conf(int id, std::string &rawConf, std::string &err);

};

#endif
