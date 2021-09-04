//
// Created by kiper220 on 30.07.2021.
//

#ifndef REDTEXTAPPLICATION_ITERATOR_H
#define REDTEXTAPPLICATION_ITERATOR_H

namespace RTF{
    namespace Types{
        template<typename T>
        class Iterator{
        public:
            virtual Iterator& StepBack() = 0;
            virtual Iterator& StepForward() = 0;

            virtual Iterator& StepBackBy(uint64_t steps) = 0;
            virtual Iterator& StepForwardBy(uint64_t steps) = 0;

            virtual T& GetValue() = 0;
            virtual Iterator& SetValue(T value) = 0;
            virtual Iterator& SetValue(T& value) = 0;
            virtual Iterator& SetValue(const T& value) = 0;

            virtual ~Iterator() = default;
        };
    }
}

#endif //REDTEXTAPPLICATION_ITERATOR_H
