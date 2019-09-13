//
//  Dir.hpp
//  sp
//
//  Created by Nikita Pekurin on 9/13/19.
//  Copyright © 2019 Nikita Pekurin. All rights reserved.
//

#ifndef Dir_hpp
#define Dir_hpp

#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include "DirIter.hpp"

class Dir {
    public:
        Dir(const std::string& path);
        ~Dir();
        DirIter begin();
        DirIter end();
    private:
        DIR* m_dir;
        DirIter m_iter;
};

#endif /* Dir_hpp */
