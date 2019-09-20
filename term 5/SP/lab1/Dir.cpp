#include "Dir.hpp"
#include <errno.h>
#include <dirent.h>
#include "DirIter.hpp"

Dir::Dir(const std::string& path) : m_iter(nullptr) {
    m_dir = opendir(path.c_str());
    if (!m_dir) {
        std::string msg = "Error: opendir: ";
        msg += strerror(errno);
        throw std::runtime_error(msg.c_str());
    }    
    m_iter = DirIter(m_dir);
}

Dir::~Dir() { closedir(m_dir); }

DirIter Dir::begin() {
    auto iter = DirIter(m_dir);
    return iter++;
}

DirIter Dir::end() {
    return DirIter(nullptr);
}
