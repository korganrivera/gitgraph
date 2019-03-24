/* Display timestamp and value table as a github-style heatmap.
   Still to do:
   * make month heatmap on top.
   * make code less ugly.
   * get data from a file instead of an array.
   * get it to work with cyclecoach.
 */
#include <stdio.h>
#include <time.h>
#include <math.h>

#define M 48

typedef struct {
    time_t ts;
    double value;
} _data;

void year_loop(unsigned m);

int main(void){
    unsigned graph[7][48]; // contains digit 0-3 to indicate colour.
    unsigned left[7];      // indicates heat of each day of week.
    char *colour[] = {"░","▒","▓","█"};
    unsigned i, j;

    _data data[M] = {
        { 1549298690, 12.54  },
        { 1549378095, 19.249 },
        { 1549471626, 17.9   },
        { 1549566316, 21.092 },
        { 1549670308, 25.234 },
        { 1549670400, 0.000  },
        { 1549756800, 0.000  },
        { 1549905412, 7.987  },
        { 1549991837, 19.504 },
        { 1550080712, 18.104 },
        { 1550102400, 0.000  },
        { 1550261354, 16.859 },
        { 1550275200, 0.000  },
        { 1550361600, 0.000  },
        { 1550448000, 0.000  },
        { 1550534400, 0.000  },
        { 1550620800, 0.000  },
        { 1550707200, 0.000  },
        { 1550793600, 0.000  },
        { 1550941338, 14.791 },
        { 1551026562, 14.839 },
        { 1551117097, 17.103 },
        { 1551139200, 0.000  },
        { 1551225600, 0.000  },
        { 1551312000, 0.000  },
        { 1551398400, 0.000  },
        { 1551484800, 0.000  },
        { 1551571200, 0.000  },
        { 1551657600, 0.000  },
        { 1551744000, 0.000  },
        { 1551830400, 0.000  },
        { 1551916800, 0.000  },
        { 1552083556, 34.376 },
        { 1552089600, 0.000  },
        { 1552176000, 0.000  },
        { 1552262400, 0.000  },
        { 1552348800, 0.000  },
        { 1552435200, 0.000  },
        { 1552603881, 12.978 },
        { 1552679349, 16.006 },
        { 1552752597, 17.105 },
        { 1552780800, 0.000  },
        { 1552875565, 16.415 },
        { 1552953600, 0.000  },
        { 1553040000, 0.000  },
        { 1553126400, 0.000  },
        { 1553212800, 0.000  },
        { 1553299200, 0.000  }
    };

    // find max value in data[].value
    double max = data[0].value;
    for(i = 1; i < M; i++){
        if(data[i].value > max)
            max = data[i].value;
    }

    //  initialise graph.
    for(i = 0; i < 7; i++){
        left[i] = 0;
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
    for(j = 47; ; j--){
        for(i = row_start; ; i--){
            graph[i][j] = ceil(data[index].value / (max / 3));
            if(index == 0 || i == 0)
                break;
            row_start = 6;
            index--;
        }
        if(index == 0 || j == 0)
            break;
        index--;
    }

    // set heat for each day of the week.
    // sum values for each weekday.
    for(i = 0; i < 7; i++){
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
        left[i] = ceil(left[i] / (u_max / 3));
    }

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
}

// Given a month index, will print a year of months beginning with that month.
// 0=jan, 1=feb, etc.
void year_loop(unsigned m){
    char year_loop[] = " Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec";

    printf("      ");
    unsigned i, index = 4 * (m + 1);
    for(i = index; i < 48; i++){
        putchar(year_loop[i]);
    }
    for(i = 0; i < index; i++){
        putchar(year_loop[i]);
    }
    putchar('\n');
}
