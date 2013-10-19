#include <cstdio>
#include "Map.h"
#include "Planner.h"
#include <curses.h>
#include <unistd.h>
#include <typeinfo>

WINDOW* scr;

void initCurses();

int main(int argc, char* argv[]){

  //load the specified map
   if(argc < 2){
      printf("You need to specifiy the map file that you'd like to open\n");
      return 0;
   }
   char* filename = argv[1];
   Map* map = Map::loadFromFile(filename);

try{
  //initialize the curses library and setup colors
   scr = initscr();
   start_color();
   init_pair(1, COLOR_WHITE, COLOR_BLACK);
   init_pair(2, COLOR_BLUE, COLOR_BLACK);
   init_pair(3, COLOR_RED, COLOR_BLACK);
   init_pair(4, COLOR_GREEN, COLOR_BLACK);
   init_pair(5, COLOR_GREEN, COLOR_BLUE);
   init_pair(6, COLOR_BLACK, COLOR_YELLOW);
   init_pair(7, COLOR_BLACK, COLOR_RED);
   curs_set(0);
   noecho(); 
 
  //create windows to draw the map
   refresh(); 
   WINDOW* win = derwin(scr, map->getHeight()+2, 2*map->getWidth()+2, 1, 1);
   WINDOW* win_map = derwin(win, map->getHeight(), 2*map->getWidth(), 1, 1);

   if(win == NULL || win_map == NULL){
      endwin();
      printf("Error opening screen for map drawing, try making your console bigger\n");
      return 0;
   }

   attrset(COLOR_PAIR(1));
   mvwprintw(scr, 0, 0, "Welcome to the path planning map environment, press 'q' to quit");
   wattrset(win, COLOR_PAIR(2));
   box(win, '|', '-');
   wrefresh(win);
   wattron(win_map, COLOR_PAIR(3)); 
   map->drawMap(win_map);
   
   //create path planner to find the path between start and goal
   Planner* p = new DumbPlanner();
   p->setMap(map);
   char c;
   int i = 0;
   bool quit_program = false;
   while((c = getch()) && !p->done()){
      if(c == 'q'){ 
         quit_program = true;
         break;
      }
      p->step();
      map->drawMap(win_map);
   }

   if(quit_program != true){
      Point pts[1000];
      int path_length = p->getPath(pts);
      int path_cost = map->drawPath(win_map, pts, path_length);
   
      refresh();
      getch();   
      endwin();

      printf("Path Cost = %d\n", path_cost);
   } else {
     endwin();
     printf("Program aborted\n");
   }
} catch(const std::exception& e){
  endwin();  
  printf("Caught exception of type %s\n", typeid(e).name());
  printf("what(): %s\n", e.what());
}


}


