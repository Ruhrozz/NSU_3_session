//
// Created by ruhrozz on 28/10/2021.
//

#include "Applier.h"
#include "../Blocks/Blocks.h"


int apply(std::map<int, std::string> blocks, std::list<int> chain) {
    while(chain.size()) {
        int i;
        int g = chain.front();
        chain.pop_front();
        std::string s;
        std::string str = blocks[g];

        for(i = 0; i < str.size(); ++i)
            if(str[i] == ' ') {
                std::copy(str.begin(), str.begin() + i, std::inserter(s, s.begin()));
                i = 0;
                break;
            }
        if(i) {
            std::copy(str.begin(), str.begin() + i, std::inserter(s, s.begin()));
        }

        Blocks* p;
        p = Blocks::makeProduct(s);
        p->work(blocks[g]);
        delete p;
    }
    return 0;
}
