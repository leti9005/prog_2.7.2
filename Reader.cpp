#include "Reader.h"

Reader::Reader() {
    _id= 0;
    _name = "";
}

Reader::Reader(unsigned int id) : _id(id), _name() {

}

unsigned int Reader::get_id() const {
    return _id;
}

std::string Reader::get_name() const {
    return _name;
}

Reader *Reader::from_raw_string(std::string line) {
    unsigned int id;
    std::string name;

    if(line.empty()) {
        return nullptr;
    }

    // _id
    size_t idx = line.find('|');
    if(idx == std::string::npos) {
        std::cerr << "from_raw_string() failed!" << std::endl;
        return nullptr;
    }
    id = std::atoi(line.substr(0, idx).c_str());
    line.erase(0, idx+1);

    // name
    name = line;

    Reader *result = new Reader();
    result->_id = id;
    result->_name = name;

    return result;
}

void Reader::println() const {
    std::cout << _id << " " << _name << std::endl;
}