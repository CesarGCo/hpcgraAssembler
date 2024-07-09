#include <cgra_configuration.h>

CgraConfiguration::CgraConfiguration(CGRA& cgra) : m_cgra(cgra) {}

bool CgraConfiguration::create_reset_conf(int id, std::string &rawConf, std::string &err){

    try{
        auto isa = m_cgra.getPE(id).getISA();
        int alu_num_inputs = m_cgra.getPE(id).getNumInputs();
        int routes = m_cgra.getPE(id).getNumRoutes();
        ConfTag conf_tag(routes>0,alu_num_inputs);
        int conf_bits = 2;
        std::string id_bits = formatToBinary((id+1), m_cgra.getPeIdWidth());
        rawConf = formatToBinary(binaryStringToInt(conf_tag.reset)+binaryStringToInt(id_bits), conf_bits);
        return true;

    }catch(const std::runtime_error &e){
        err = e.what();
        return false;
    }

}
