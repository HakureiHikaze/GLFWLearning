//
// Created by Hikaze on 2021/9/14 0:31.
// 
//


#include "Util.hpp"

std::string Util::readStringFromText(const std::string & fileFullPath){
    std::ifstream ifStream(fileFullPath);
    if(!ifStream.is_open()){
        std::cerr<<"Error opening file."<<std::endl;
        exit(-1);
    }
    std::istreambuf_iterator<char> begin(ifStream);
    std::istreambuf_iterator<char> end;
    std::string rtn(begin,end);
    return rtn;
}
