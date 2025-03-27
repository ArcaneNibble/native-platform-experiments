#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    while (1) {
        unsigned int dice_max;
        while (1) {
            printf("Dice max? ");
            int ret = scanf("%u", &dice_max);
            if (ret == 1) break;
        }
        if (!dice_max) {
            printf("Invalid!\n");
            continue;
        }
        
        unsigned int rand_div = (RAND_MAX + 1u) / dice_max;
        unsigned int rand_cap = rand_div * dice_max;
        unsigned int rand_roll;
        do {
            rand_roll = rand();
        } while (rand_roll >= rand_cap);

        printf("Rolled: %u\n", rand_roll / rand_div + 1);
    }
}
