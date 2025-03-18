#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

int main(int argc, char** argv) {

    FILE* fp;
    char line[80];
    int coords[2] = {0, 0};
    int action;

    if(argc <= 1) {
        printf("Please specify file\n");
        exit(1);
    }

    fp = fopen(argv[1], "a+");

    if(!fp) {
        printf("Error opening file\n");
        exit(1);
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    while(fgets(line, 80, fp) != NULL) {
        printw("%s", line);
    }

    move(coords[0], coords[1]);

    action = getch();

    while(action != 'Q') {
        // printf("%c", action);
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
            default:
                coords[1]++;
                insch((char)action);
                break;
        }
        if(coords[0] < 0) coords[0] = 0;
        if(coords[1] < 0) coords[1] = 0;
        move(coords[0], coords[1]);
        refresh();
        action = getch();
    }

    refresh();
    endwin();

    return 0;

}
