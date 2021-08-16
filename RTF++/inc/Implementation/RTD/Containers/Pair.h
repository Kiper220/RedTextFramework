//
// Created by kiper220 on 14.08.2021.
//

#ifndef REDTEXTAPPLICATION_PAIR_H
#define REDTEXTAPPLICATION_PAIR_H

namespace RTF{
    namespace Containers{
        template<typename T1, typename T2>
        struct Pair {
            T1 first;
            T2 second;
        };
    }
}

#endif //REDTEXTAPPLICATION_PAIR_H
