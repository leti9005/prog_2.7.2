#include "Book.h"

Book *Book::from_raw_string(std::string line) {
    unsigned int id;
    unsigned int avail;
    std::string title;
    std::string author;

    if(line.empty()) {
        return nullptr;
    }

    size_t idx = line.find('|');
    if(idx == std::string::npos) {
        std::cerr << "from_raw_string() failed!" << std::endl;
        return nullptr;
    }
    id = std::atoi(line.substr(0, idx).c_str());
    line.erase(0, idx+1);

    idx = line.find('|');
    if(idx == std::string::npos) {
        std::cerr << "from_raw_string() failed!" << std::endl;
        return nullptr;
    }
    author = line.substr(0, idx);
    line.erase(0, idx+1);

    idx = line.find('|');
    if(idx == std::string::npos) {
        std::cerr << "from_raw_string() failed!" << std::endl;
        return nullptr;
    }
    title = line.substr(0, idx);
    line.erase(0, idx+1);

    avail = std::atoi(line.substr(0, idx).c_str());

    Book *result = new Book();
    result->_id = id;
    result->_avail = avail;
    result->_title = std::string(title);
    result->_author = std::string(author);

    return result;
}

void Book::give() {
    if(_avail > 0) {
        _avail--;
    } else {
        std::cerr << "Нет экземпляров для выдачи!" << std::endl;
    }
}

void Book::ret() {
    _avail++;
}

void Book::println() const {
    std::cout << _id << "," << _author << "," << _title << "," << _avail << std::endl;
}

unsigned int Book::get_id() const {
    return _id;
}

std::string Book::get_title() const {
    return _title;
}

std::string Book::get_author() const {
    return _author;
}

unsigned int Book::get_avail() const {
    return _avail;
}
