#ifndef DirIter_hpp
#define DirIter_hpp

#include <stdio.h>
#include <dirent.h>

class DirIter {
    public:
        DirIter(DIR* dir);
        DirIter(const DirIter& other);
        DirIter& operator=(const DirIter& other);
        DirIter& operator++();
        DirIter& operator++(int);
        dirent operator*();
        dirent* operator->();
        bool operator==(const DirIter& other);
        bool operator!=(const DirIter& other);
    
    private:
        DIR* m_dir;
        dirent* m_current;
};

#endif /* DirIter_hpp */
