#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    const char *pname;
    if (argc > 1)
        pname = argv[0];
    else
        pname = "dice";     // apparently this is possible?
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s max_dice_value\n", pname);
        return 1;
    }

    unsigned int dice_max = strtol(argv[1], 0, 10);
    if (!dice_max) {
        fprintf(stderr, "%s: max_dice_value invalid\n", pname);
        return 1;
    }

    srand(time(0));
    // work better on MacOS
    rand();

    unsigned int rand_div = (RAND_MAX + 1u) / dice_max;
    unsigned int rand_cap = rand_div * dice_max;
    unsigned int rand_roll;
    do {
        rand_roll = rand();
    } while (rand_roll >= rand_cap);

    printf("%u\n", rand_roll / rand_div + 1);
    
    return 0;
}
