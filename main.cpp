#include <iostream>
#include <sys/resource.h>
#include <list>
#include <ctime>
#include <Implementation/RTD/Strings/SharedString.h>
#include <Implementation/RTD/Containers/SharedList.h>

using namespace RTF;

int main() {
    __mode_t test;
    clock_t t0;
    double time1, time2;
    struct rusage usage{};
    {
        t0 = clock();
        Container::SharedList<Strings::SharedString>::ListType list;
        for (uint64_t i = 0; i < 80000; i++) {
            list.PushBack("String1\n");
            list.PushBack("String2\n");
            list.PushBack("String3\n");
            list.PushBack("String4\n");
            list.PushBack("String5\n");
            list.PushBack("String6\n");
            list.PushBack("String7\n");
            list.PushBack("String8\n");
            list.PushBack("String9\n");
            list.PushBack("String10\n");
            list.PushBack("String11\n");
            list.PushBack("String12\n");
            list.PushBack("String13\n");
            list.PushBack("String14\n");
            list.PushBack("String15\n");
            list.PushBack("String16\n");
            list.PushBack("String17\n");
            list.PushBack("String18\n");
            list.PushBack("String19\n");
            list.PushBack("String20\n");
            list.PushBack("String21\n");
            list.PushBack("String22\n");
            list.PushBack("String23\n");
            list.PushBack("String24\n");
            list.PushBack("String25\n");
            list.PushBack("String26\n");
            list.PushBack("String27\n");
            list.PushBack("String28\n");
            list.PushBack("String29\n");
            list.PushBack("String30\n");
        }
        getrusage(RUSAGE_SELF, &usage);
        std::cout << "Container::SharedList() " << 800000 * 30 << ": " << (time1 = (double) (clock() - t0) / CLOCKS_PER_SEC) << '\n'
                  << "Usage: " << usage.ru_nswap << '\n' << '\n';
    }
    {
        t0 = clock();
        std::list<std::string> list;
        for (uint64_t i = 0; i < 80000; i++) {
            list.push_back("String1\n");
            list.push_back("String2\n");
            list.push_back("String3\n");
            list.push_back("String4\n");
            list.push_back("String5\n");
            list.push_back("String6\n");
            list.push_back("String7\n");
            list.push_back("String8\n");
            list.push_back("String9\n");
            list.push_back("String10\n");
            list.push_back("String11\n");
            list.push_back("String12\n");
            list.push_back("String13\n");
            list.push_back("String14\n");
            list.push_back("String15\n");
            list.push_back("String16\n");
            list.push_back("String17\n");
            list.push_back("String18\n");
            list.push_back("String19\n");
            list.push_back("String20\n");
            list.push_back("String21\n");
            list.push_back("String22\n");
            list.push_back("String23\n");
            list.push_back("String24\n");
            list.push_back("String25\n");
            list.push_back("String26\n");
            list.push_back("String27\n");
            list.push_back("String28\n");
            list.push_back("String29\n");
            list.push_back("String30\n");
        }
        getrusage(RUSAGE_SELF, &usage);
        std::cout << "std::list() " << 800000 * 30 << ": " << (time2 = (double) (clock() - t0) / CLOCKS_PER_SEC) << '\n'
                  << "Usage: " << usage.ru_nswap << '\n';
    }
    std::cout << "std::list and std::string win Container::SharedList and Strings::SharedString with: " << time1 / time2; // Middle - 5.5;

    return 0;
}
