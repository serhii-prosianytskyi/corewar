#include <ncurses.h>
#include <stdlib.h>
#define MEM_SIZE				(4*1024)

void create_main_window(WINDOW *main_win)
{
	WINDOW *task;
	short	ex;

	//system("resize -s 100 200");
	main_win = newwin(68, 192, 0, 0);
	task	 = newwin(68, 58, 0, 191);
	start_color();
	//init_color(COLOR_GREEN, 404,222,122);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
   	wattron(main_win, COLOR_PAIR(1));  //switch some function in this case color opposite wattroff
   	wborder(main_win, ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
   	wattron(task, COLOR_PAIR(1));
    wborder(task, ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
    wbkgd(task, COLOR_PAIR(1)); //set backgroubnd
    int x = 2;
    int y = 2;
  	wattron(main_win, COLOR_PAIR(2));
   	for(int j = 0; j < 64; j++)
	{  
   		x = 2;
   		for (int i = 0; i < 64; i++)
   		{
   			if ( x < 191 )
   				mvwprintw(main_win,y, x,"%d%d", 0,0);
   			x += 3;
   		}
   		y++;

   	}
	wrefresh(main_win);
	wrefresh(task);

}





int main()
{
	WINDOW *main_win;

	initscr();
	create_main_window(main_win);
	while(1)
	{

	}
	endwin();
}