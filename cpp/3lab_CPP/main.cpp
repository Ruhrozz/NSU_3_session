#include "Utility/parser.h"
#include "Utility/Applier.h"

int main() {
    char name[] = "../text.txt";
    Parser a;
    a.general(name);
    apply(a.blocks, a.chain);
    return 0;
}



