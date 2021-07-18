#include <iostream>
#include <RedTextFramework>
#include <Implementation/RTD/Strings/String.h>


int main() {
    RTF::Types::String string =
            "Mnogi ljudi misle da je Ovog puta naš pseudo-latinski skupa reči uzeo sa stropa, ali to \n"
            "nije sasvim tačno. Njegovi korijeni se vraćaju na fragment klasičnog latinskog iz 45. reklame\n"
            ", to je, prije više od dva milenija. Richard McClintock, latino profesor na Hemden-Sydney Koledž, \n"
            "Virginia, uzeo jedan od najčudnijih riječi u Ovom Polju, \"consectetur\", i počeo je u potrazi za \n"
            "to u klasični latinski književnost. Kao rezultat toga, on našli su nepobitni primarni izvor na \n"
            "Ovom Polju u dijelove 1.10.32 i 1.10.33 knjige \"de Finibus Bonorum i Malorum \"(\"Na granice dobra i zla.\"), \n"
            "koju je napisao Ciceron u 45 OGLAS. Te rasprave o teoriji etike su bile veoma popularne u renesansi. \n"
            "Prva Lorem Ipsum, \" Lorem ipsum dolor sit amet..\", dolazi iz jedne od linija u odjeljku 1.10.32\n";
    string.ToLower();
    std::cout << string;
    return 0;
}
