#include <cgra.h>

CGRA::CGRA(const std::string& jsonFilePath) {
    Json::Value jsonData;
    std::ifstream ifs;
    ifs.open(jsonFilePath);
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &jsonData, &errs)) {
       throw std::runtime_error(errs);
    }

    ifs.close();

    dataWidth = jsonData["data_width"].asInt();
    confBusWidth = jsonData["conf_bus_width"].asInt();
    pe_id_width = (jsonData["pe"]).size()+1;
    conf_raw_bits = 0;
    
    for (auto PeData : jsonData["pe"]) {
        int id = PeData["id"].asInt();
        int numIstream = PeData["num_istream"].asInt();
        int numOstream = PeData["num_ostream"].asInt();
        int numRoutes = PeData["routes"].asInt();
        std::vector<int> neighbors;
        std::vector<int> elastic_queue;
        std::vector<std::string> isa;


        for(auto &n : PeData["neighbors"]){
            neighbors.push_back(n.asInt());
        }

        std::vector<int> neighbors_out = neighbors;
        std::vector<int> neighbors_in;
        for(auto PeInfo : jsonData["pe"]){
            int peId = PeInfo["id"].asInt();
            if(peId != id){
                for(auto &n : PeInfo["neighbors"]){
                    if(n == id){
                        neighbors_in.push_back(n.asInt());
                    }
                }
            }
        }


        for(auto &n : PeData["elastic_queue"]){
            elastic_queue.push_back(n.asInt());
        }

        for(auto &n : PeData["isa"]){
            isa.push_back(n.asString());
        }

        int maxNumInputs = 0;
        int maxNumConst = 0;

        for(std::string op : isa){
            auto element = operations.find(op);
            if(element != operations.end()){
                int num_inputs = element->second.first;
                if(num_inputs > maxNumInputs){
                    maxNumInputs = num_inputs;
                }

                int num_const = element ->second.second;
                if(num_const > maxNumConst){
                    maxNumConst = num_const;
                }

            } else {
                 throw std::runtime_error("The " + op +  " operation was not found!");
            }
        }
        
        std::vector<int> input_reg;
        for(std::size_t i = 0; i < (neighbors_in.size()); i++){
            input_reg.push_back(dataWidth+1);
        }

        std::vector<int> mux_alu_inputs;
        std::vector<int> stream_in_reg;
        for(int i = 0; i < numIstream; i++){
            stream_in_reg.push_back(dataWidth+1);
            mux_alu_inputs.push_back(stream_in_reg[i]);
        }
        mux_alu_inputs.push_back((maxNumInputs+maxNumConst)*(dataWidth+1));
        
        for(int i : input_reg){
            mux_alu_inputs.push_back(i);
        }

        int mux_alu_bits = bitsFunct(mux_alu_inputs.size());

        int num_opcode = isa.size();
        int opcode_width = bitsFunct(num_opcode);
        
        std::vector<int> sel_mux_alu;
        for(int i = 0; i < maxNumInputs; i++){
            sel_mux_alu.push_back(mux_alu_bits);
        }

        std::vector<int> conf_array_alu;
        conf_array_alu[0] = opcode_width;
        for(std::size_t i = 0; i < (sel_mux_alu.size()); i++){
            conf_array_alu[i+1] = sel_mux_alu[i];
        }
        

        std::string sel_elastic_pipeline;

        for(int i = 0; i < maxNumInputs; i++){
            if(elastic_queue[i] > 0){
                
                int aux = bitsFunct(elastic_queue[i]+1);
                sel_elastic_pipeline += std::to_string(aux);
            }
        }


       // ConfTag conf_tag(numRoutes > 0, maxNumInputs+maxNumConst);
        //int conf_tag_bits = conf_tag.bits;


        PE pe(id, numIstream, numOstream, neighbors_in, neighbors_out, numRoutes, elastic_queue, isa, maxNumInputs, maxNumConst, opcode_width);
        PEs[id] = pe;
    }
}

PE CGRA::getPE(int id) const {

    auto elem = PEs.find(id);
    if(elem != PEs.end()){
        return elem->second;
    }
    throw std::runtime_error("The PE with ID " + std::to_string(id) + " doesn't exist");
}

int CGRA::getDataWidth() const{
    return dataWidth;
}

int CGRA::getConfBusWidth() const{
    return confBusWidth;
}

int CGRA::getPeIdWidth() const{
    return pe_id_width;
}

int PE::getNumInputs() const {
    return numIstream;
}

int PE::getNumOutputs() const{
    return numOstream;
}

std::vector<int> PE::getNeighborsIn() const{
    return neighborsIn;
}

std::vector<int> PE::getNeighborsOut() const{
    return neighborsOut;
}

int PE::getNumRoutes() const{
    return numRoutes;
}

std::vector<int> PE::getElasticQueue() const{
    return elasticQueue;
}

std::vector<std::string> PE::getISA() const{
    return isa;
}

int PE::getNumAluInputs() const {
    return numAluInputs;
}

int PE::getNumAluConst() const {
    return numAluConst;
}


