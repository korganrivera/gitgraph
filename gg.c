/* Display timestamp and value table as a github-style heatmap.
   Still to do:
   * make code less ugly.
   *
   * I can use sed and awk to get the data I want like this:
   *
   * awk '{print $1, $6}' ../silvercheetah/tss.log | sed 1d
   * should gg be able to handle piped data?
   *
   * Fri Feb 26 10:06:55 AM CST 2021
   * Adding a weekly heatmap. Want a monthly heatmap but weekly will serve for
   * weeks and month.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    time_t ts;
    double value;
} _data;

void year_loop(unsigned m);

int main(int argc, char **argv){
    unsigned graph[7][48]; // contains digit 0-4 to indicate colour.
    unsigned left[7];      // indicates heat of each day of week.
    unsigned top[48];      // indicates heat of each week.
    char c, *colour[] = {"░","▒","▓","█", " "};
    unsigned i, j, M;      // i, j are loop variables. M is line count.
    FILE *fp;
    _data *data;

    // check argc.
    if(argc != 2){
        printf("USAGE: %s <csv file>\nfile should have two columns where the first"
             " is timestamps and the second is some float value.\n", argv[0]);
        exit(0);
    }

    // open file.
    if((fp = fopen(argv[1], "r")) == NULL){
        printf("can't open %s\n", argv[1]);
        exit(1);
    }

    // count lines in file.
    // I think this fails if last line in file doesn't end with a newline :/
    M = 0;
    while(!feof(fp)){
        c = fgetc(fp);
        if(c == '\n')
            M++;
    }
    rewind(fp);

    // if file is empty, we're done.
    if(M == 0){
        puts("file is empty :/");
        fclose(fp);
        exit(0);
    }

    // otherwise, malloc some space.
    if((data = malloc(M * sizeof(_data))) == NULL){ puts("malloc failed"); exit(1); }

    // read file into array.
    for(i = 0; i < M; i++){
        if((fscanf(fp, "%llu %lf", &data[i].ts, &data[i].value)) != 2){
            printf("\nproblem reading the file. :/");
            exit(1);
       }
    }
    fclose(fp);

    // find max value in data[].value
    double max = data[0].value;
    for(i = 1; i < M; i++){
        if(data[i].value > max)
            max = data[i].value;
    }

    //  initialise graph[].
    for(i = 0; i < 7; i++){
        for(j = 0; j < 48; j++){
            graph[i][j] = 0;
        }
    }
    // get day and month name of last timestamp.
    struct tm *buf = gmtime(&(data[M - 1].ts));
    unsigned dow = buf->tm_wday;
    unsigned mon = buf->tm_mon;

    // set graph value.
    unsigned index = M - 1;
    unsigned row_start = dow;
    double divisor = max / 3;
    for(j = 47; ; j--){
        for(i = row_start; ; i--){
            graph[i][j] = ceil(data[index].value / divisor);
            if(index == 0 || i == 0){
                row_start = 6;
                break;
            }
            index--;
        }
        if(index == 0 || j == 0)
            break;
        index--;
    }

    free(data);

    // set heat for each day of the week.
    // sum values for each weekday.
    for(i = 0; i < 7; i++){
        left[i] = 0;
        for(j = 0; j < 48; j++){
            left[i] += graph[i][j];
        }
    }

    // find highest sum.
    unsigned u_max = left[0];
    for(i = 1; i < 7; i++){
        if(left[i] > u_max)
            u_max = left[i];
    }

    // set left[]'s correct value.
    for(i = 0; i < 7; i++){
        if(u_max)
            left[i] = 3 * left[i] / u_max;
        else
            left[i] = 0;
    }

    // set heat for each week.
    // sum values for each week of the year.
    for(i = 0; i < 48; i++){
        top[i] = 0;
        for(j = 0; j < 7; j++)
            top[i] += graph[j][i];
    }

    // find highest sum.
    u_max = top[0];
    for(i = 1; i < 48; i++){
        if(top[i] > u_max)
            u_max = top[i];
    }

    // set top[]'s correct value.
    for(i = 0; i < 48; i++){
        if(u_max)
            top[i] = 3 * top[i] / u_max;
        else
            top[i] = 0;
    }

    // blank out future days.
    for(i = dow + 1; i < 7; i++)
        graph[i][47] = 4;

    // display the weekly heatmap.
    printf("      ");
    for(i = 0; i < 48; i++){
        printf("%s", colour[top[i]]);
    }
    putchar('\n');

    // display the month on top.
    year_loop(mon);

    // display the graph.
    for(i = 0; i < 7; i++){
        // display heat for each here.
        printf("%s ", colour[left[i]]);

        // display the day on the left.
        if(!(i % 2))
            printf("    ");
        else{
            if(i == 1)
                printf("Mon ");
            else if(i == 3)
                printf("Wed ");
            else if(i == 5)
                printf("Fri ");
        }

        for(j = 0; j < 48; j++){
            printf("%s", colour[graph[i][j]]);
        }
        putchar('\n');
    }
    putchar('\n');
}

// Given a month index, will print a year of months beginning with that month.
// 0=jan, 1=feb, etc.
void year_loop(unsigned m){
    char year_loop[] = " Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec";

    printf("      ");
    unsigned i, index = 4 * (m + 1);
//  printf(&(year_loop[index]));
    for(i = index; i < 48; i++){
        putchar(year_loop[i]);
    }
    for(i = 0; i < index; i++){
        putchar(year_loop[i]);
    }
    putchar('\n');
}
