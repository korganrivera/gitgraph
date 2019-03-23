/*
 * You know that contributions graph on github?  I want to see if it looks good
 * in the terminal and, if so, maybe use one for cycle training.
 *
 * Characters to use:
 *   █ ▓ ▒ ░
 * Change intensity to express how high TSS was.
 * Other option is to make this code generic, so that I can push whatever table to it
 * and it'll figure out it's own rendering with the given data.
 *
 *      Apr May Jun Jul Aug Sep Oct Nov Dec Jan Feb Mar
 *      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒
 *  Tue ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒░
 *      ░░░░░░░░░░░░░░░░░░█▓▒░░░░░░░░░░░░░░░░░░░░░░▒░░░░
 *  Thu ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█░░░░░
 *      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒░░█░░
 *  Sat ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒░█░▒▓
 *      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
 *
 *      Printing these grey boxes is clunky and I probably need to handle multibyte characters.
 *      Instead, I'm going to stick my fingers in my ears and pretend I'm working with strings.
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LIGHTEST "█"
#define LIGHT "▓"
#define DARK "▒"
#define DARKEST "░"
#define ROWS 7
#define COLS 48

void year_loop(unsigned m);

int main(int argc, char **argv){
    unsigned graph[ROWS][COLS];
    unsigned i, j;

    srand(time(NULL));

    // initialise graph with darkest color
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            graph[i][j] = 0;
            if(rand() % 100 < 33)
                graph[i][j] = rand() % 3 + 1;
        }
    }

    // display graph.
    printf("    ");
    year_loop(6);
    for(i = 0; i < ROWS; i++){
        if(!(i % 2))
            printf("    ");
        else{
            if(i == 1)
                printf("Tue ");
            else if(i == 3)
                printf("Thu ");
            else if(i == 5)
                printf("Sat ");
        }

        for(j = 0; j < COLS; j++){
            if(graph[i][j] == 0)
                printf(DARKEST);
            else if(graph[i][j] == 1)
                printf(DARK);
            else if(graph[i][j] == 2)
                printf(LIGHT);
            else if(graph[i][j] == 3)
                printf(LIGHTEST);
            else printf("X");
        }
        putchar('\n');
    }
}

// Given a month index, will print a year of months beginning with that month.
// 0=jan, 1=feb, etc.
void year_loop(unsigned m){
    char year_loop[] = "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";

    unsigned i, index = 4 * m;
    for(i = index; i < 48; i++){
        putchar(year_loop[i]);
    }
    for(i = 0; i < index; i++){
        putchar(year_loop[i]);
    }
    putchar('\n');
}

