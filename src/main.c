#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#define CTRL_Q 17
#define CTRL_S 19

int main(int argc, char** argv) {

    FILE* fp;
    char* line; 
    int coords[2] = {0, 0};
    int action;
    int maxx;

    if(argc <= 1) {
        printf("Please specify file\n");
        exit(1);
    }

    fp = fopen(argv[1], "r+");

    if(!fp) {
        fp = fopen(argv[1], "w+");
        if(!fp) {
            printf("Error opening file\n");
            exit(1);
        }
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    maxx = getmaxx(stdscr);

    line = malloc(sizeof(char) * maxx);

    while(fgets(line, maxx, fp) != NULL) {
        printw("%s", line);
    }

    move(coords[0], coords[1]);

    action = getch();

    while(action != CTRL_Q) {
        switch (action) {
            case KEY_UP:
                coords[0]--;
                break;
            case KEY_DOWN:
                coords[0]++;
                break;
            case KEY_RIGHT:
                coords[1]++;
                break;
            case KEY_LEFT:
                coords[1]--;
                break;
            case KEY_BACKSPACE:
                if(coords[1] <= 0) break;
                mvdelch(coords[0], --coords[1]);
                break;
            case KEY_DC:
                delch();
                break;
            case 10:
                break;
            case CTRL_S:
                fseek(fp, 0, SEEK_SET);
                for(int y = 0; y < getmaxy(stdscr); y++) {
                    mvinstr(y, 0, line);
                    fprintf(fp, "%s\n", line);
                }
                break;
            default:
                coords[1]++;
                insch((char)action);
                break;
        }
        if(coords[0] < 0) coords[0] = 0;
        if(coords[1] < 0) coords[1] = 0;
        if(coords[1] > maxx - 1) coords[1] = maxx - 1;
        move(coords[0], coords[1]);
        refresh();
        action = getch();
    }

    endwin();

    return 0;

}
