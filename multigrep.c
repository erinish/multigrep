#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <regex.h>
#include <unistd.h>
#include "queue.h"

int check_reqs(short rlen, short *rb)
{
    short count;
    short check = 1;
    for (count = 0; count < rlen; count++) {
        if (rb[count] == 0) 
            check = 0;
    }
    if (check)
        return 1;
    else
        return 0;
}

void reset_reqs(short rlen, short *rb)
{
    short count;
    short check = 1;
    for (count = 0; count < rlen; count++) {
        rb[count] = 0;
    }
}

int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t size;
    char ch;
    regex_t start_n;
    regex_t end_n;
    regex_t reqs[9];
    short reqs_b[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int reti;
    int count;
    short start_b = 0;
    short end_b = 0;

    /* Process commandline args */
    while ((ch = getopt(argc, argv, "s:e:")) != EOF)
    {
        switch(ch) {
            case 's':
                reti = regcomp(&start_n, optarg, 0);
                break;
            case 'e':
                reti = regcomp(&end_n, optarg, 0);
                break;
            default:
                fprintf(stderr, "Unknown option: '%s'\n", optarg);
                return 1;
        }
    }

    argc -= optind; // optind is the index of the next arg
    argv += optind; // adding index to the pointer

    if (argc > 10) {
        fprintf(stderr, "No more than 10 requirements");
        return 1;
    }

    /* populate comp array for requirements */
    for (count = 0; count < argc; count++){
        reti = regcomp(&reqs[count], argv[count], 0);
    }
    /* End commandline args */
    
    while (getline(&line, &size, stdin) != -1) {
        if (!start_b) {
            reti = regexec(&start_n, line, 0, NULL, 0);
            if (!reti) {
                enque(line);
                start_b = 1;
            }
        } else {
            if (!end_b) {
                reti = regexec(&end_n, line, 0, NULL, 0);
                if (!reti) {
                    end_b = 1;
                }
            enque(line);
            /* look for required matches */
            for (count = 0; count < argc; count++)
            {
                reti = regexec(&reqs[count], line, 0, NULL, 0);
                if (!reti) {
                    reqs_b[count] = 1;
                }
            }
            } else {
                /* determine if we have all matches */
                if (check_reqs(argc, reqs_b))
                    printque(first);
                reset_queue();
                start_b = 0;
                end_b = 0;
                reset_reqs(argc, reqs_b);
            }
        }
    }
    /* catch last match */
    if (start_b && end_b && check_reqs(argc, reqs_b)) 
        printque(first);
    reset_queue();
    free(line); // getline calls malloc/realloc
    return 0;
}
