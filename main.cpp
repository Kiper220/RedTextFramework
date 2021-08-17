#include <RTF/Tests.h>
#include <RTF.h>
#include <iostream>

int main() {
    if(RTF::Tests::RunAllTestAndLog())
        return 0;
    return 1;
}
