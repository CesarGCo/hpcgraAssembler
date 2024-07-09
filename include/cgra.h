#ifndef CGRA_H
#define CGRA_H

#include <utility>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <json/json.h>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utils.h>
#include <cgra_conf_tag.h>

class PE {
public:
    int id{};
    int numIstream{};
    int numOstream{};
    int numRoutes{};
    std::vector<int> elasticQueue;
    std::vector<int> neighborsIn;
    std::vector<int> neighborsOut;
    std::vector<std::string> isa;
    int pe_id_width{};
    int numAluInputs{};
    int numAluConst{};
    int opcode_width{};

    PE()= default;

    PE(int id, int numIstream, int numOstream, std::vector<int> neighborsIn, std::vector<int> neighborsOut, int routes, 
          std::vector<int> elasticQueue, std::vector<std::string> isa, int numAluInputs, int numAluConst, int opcode_width)
        : id(id), numIstream(numIstream), numOstream(numOstream), numRoutes(routes), 
          elasticQueue(std::move(elasticQueue)), neighborsIn(std::move(neighborsIn)), neighborsOut(std::move(neighborsOut)), isa(std::move(isa)), 
          numAluInputs(numAluInputs), numAluConst(numAluConst), opcode_width(opcode_width) {}

    PE(const PE &pe){
        id = pe.id;
        numIstream = pe.numIstream;
        numOstream = pe.numOstream;
        numRoutes = pe.numRoutes;
        elasticQueue = pe.elasticQueue;
        neighborsIn = pe.neighborsIn;
        neighborsOut = pe.neighborsOut;
        isa = pe.isa;
        numAluInputs = pe.numAluInputs;
        numAluConst = pe.numAluConst;
        opcode_width = pe.opcode_width;


    }
    PE &operator=(const PE &pe)= default;

    int getNumInputs() const;

    int getNumOutputs() const;

    std::vector<int> getNeighborsIn() const;

    std::vector<int> getNeighborsOut() const;

    int getNumRoutes() const;

    std::vector<int> getElasticQueue() const;

    std::vector<std::string> getISA() const;

    int getNumAluInputs() const;

    int getNumAluConst() const;

    int getOpcodeWidth() const;

};

class CGRA {
private:
    std::unordered_map<int, PE> PEs;
    int dataWidth;
    int confBusWidth;
    int pe_id_width;
    int conf_raw_bits;

    std::map<std::string, std::pair<int,int>> operations{
        {"add",{2,0}},
        {"sub",{2,0}},
        {"mul",{2,0}},
        {"or",{2,0}},
        {"xor",{2,0}},
        {"and",{2,0}},
        {"not",{1,0}},
        {"abs",{1,0}},
        {"pass",{1,0}},
        {"reg",{1,0}},  
        {"muladd",{3,0}},
        {"mulsub",{3,0}},
        {"addadd",{3,0}},
        {"subsub",{3,0}},
        {"addsub",{3,0}},
        {"mux",{3,0}},
        {"slt",{2,0}},
        {"sgt",{2,0}},
        {"seq",{2,0}},
        {"sne",{2,0}},
        {"shl",{2,0}},
        {"shr",{2,0}},
        {"max",{2,0}},
        {"min",{2,0}},
        {"const",{1,0}},
        {"acc",{2,0}},
        {"macc",{4,0}},
        {"merge",{2,0}}
    };

public:
    explicit CGRA(const std::string& jsonFilePath);

    PE getPE(int id) const;

    int getDataWidth() const;

    int getConfBusWidth() const;

    int getPeIdWidth() const;

    int getConfRawBits() const;

};

#endif 
