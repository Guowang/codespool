#ifndef CSE20232_MAP_HEADER
#define CSE20232_MAP_HEADER

#include <curses.h>
#include <exception>
#define DEFAULT_INIT_MAP_VAL 10


/* STRUCT: Point
 *  Description:
 *     The Point struct represents a 2D coordinate in a map. This provides
 *     a convenient way of passing coordinates to/from functions.
 *  Member Data:
 *     r - The row coordinate (vertical location measured from the top)
 *     c - The column coordinate (horizontal location measured from the left)
 *  Constructors:
 *     Point(row, col) - Sets the coordinate to (row, col)
 *     Point() - Sets the coordinates to (0,0) 
 */
 struct Point{
  int r;
  int c;

  Point(int row, int col); 
  Point();
};



/* STRUCT: PointOutOfBounds_Exception
 *  Description:
 *     The purpose of this exception is to indicate that a requested point was 
 *     outside of the boundaries of the map
 *  Member Data:
 *     p - The offending point
 *  Constructors:
 *     PointOutOfBounds_Exception(Point bad_point) - Sets p to bad_point
 */
struct PointOutOfBounds_Exception : public std::exception{
   Point p;
   PointOutOfBounds_Exception(Point bad_point);
   virtual const char* what() const throw(); 
};


/* STRUCT: UnexplorablePoint_Exception
 *  Description:
 *     The purpose of this exception is to indicate that a requested point was 
 *     not adjacent to a previously explored point and is therefore unavailable
 *  Member Data:
 *     p - The offending point
 *  Constructors:
 *     UnexplorablePoint_Exception(Point bad_point) - Sets p to bad_point
 */
struct UnexplorablePoint_Exception : public std::exception{
   Point p;
   UnexplorablePoint_Exception(Point bad_point);
   virtual const char* what() const throw();
};


/* STRUCT: FileNotFound_Exception
 *  Description:
 *     This exception is thrown to indicate that a requested file could not opened
 *  Member Data:
 *     filename - The filename that was attempted
 *  Constructors:
 *     FileNotFound_Exception(char* filename) - Sets filename
 */
struct FileNotFound_Exception : public std::exception{
   char* filename;
   FileNotFound_Exception(char* filename);
   virtual const char* what() const throw();
};

/* STRUCT: FileCorrupted_Exception
 *  Description:
 *     This exception is thrown to indicate that a requested file does not conform
 *     to the proper syntax.
 *  Member Data:
 *     filename - The filename that was attempted
 *     line - The line number that caused a problem
 *  Constructors:
 *     FileCorrupted_Exception(char* filename) - Sets filename
 */
struct FileCorrupted_Exception : public std::exception{
   char* filename;
   int line;
   FileCorrupted_Exception(char* filename, int line);
   virtual const char* what() const throw();
};




/* CLASS: Map
 *  Description:
 *     This class manages a 2D map of movement cost values. These values are 
 *     stored as integers in the range (minval, maxval). The map also keeps 
 *     track of whether points have been explored and restricts access to points
 *     that are adjacent to explored points.
 */
class Map {
private:
   bool* exp_map; //Stores the map of explored and unexplored points
   int* cost_map; //Stores the cost map
   int rows;      //Number of rows in the map
   int cols;      //Number of columns in the map

   int maxval;    //Largest cost value in the map
   int minval;    //Smallest cost value in the map
 
   Point start;   //Start point for path planning
   Point goal;    //Goal point for path planning
 
   //Convenience access function for the exploration map
   bool& explored(int r, int c);

   //Convenience access function for cost map
   int& cost(int r, int c);

   //Returns the ASCII character to be painted on the screen
   char cost_char(int r, int c); 

   //Initialize map to a given value
   void initMap(int initval);

   //Allocate map storage space
   void allocMap(int width, int height);

   //Routine for random map generation 
   void randomizeMap(int roughness, int low, int high);
  
   //Box Filter routine used to smooth the topology of a map
   void smooth(int box_size); 
 
   //Constructor that allocates and initializes
   Map(int height, int width, int initval);
   
   //Constructor that just allocates
   Map(int height, int width);

public:
   //Returns the height of the map
   int getHeight();

   //Returns the width of the map
   int getWidth();

   //Returns the start point for path planning
   Point getStart();

   //Returns the goal point for path planning
   Point getGoal();
   
   /*FUNCTION: Map::explore
    * Description: 
    *    Attempts to explore a given location. The given location must be
    *    adjacent to previously explored areas. If the exploration is a 
    *    success, the given area will be marked as explored and adjacent
    *    locations will be open to exploration. 
    * Throws:
    *    PointOutOfBounds_Exception - if the requested point is outside map boundaries
    *    
    *    UnexplorablePoint_Exception - if the requested point is not adjacent to a
    *                                  previously explored point
    * Input Args: 
    *    (r, c) - The requested point given in row/column form
    *    (p) - The requested point given in Point struct form
    * Returns: 
    *    The movement cost of the requested coordinate
    */ 
   int explore(int r, int c);
   int explore(Point p);
   
   /*FUNCTION: Map::drawMap
    * Description:
    *    Uses the ncurses library to draw a ASCII version of the map in the given window
    * Throws:
    *    Nothing
    * Input Args:
    *    win - The ncurses window in which to draw the map
    * Returns:
    *    Nothing
    */
   void drawMap(WINDOW* win);
   
   /*FUNCTION: Map::drawPath
    * Description:
    *    Uses the ncurses library to draw a path over the ASCII version of the map in the given window
    * Throws:
    *    Nothing
    * Input Args:
    *    win - The ncurses window in which to draw the path
    * Returns:
    *    Nothing
    */
   int drawPath(WINDOW* win, Point* path, int length);

   /*FUNCTION: Map::printMap
    * Description:
    *    Prints the cost map out to standard out (FOR DEBUGGING ONLY)
    * Throws:
    *    Nothing
    * Input Args:
    *    Nothing
    * Returns:
    *    Nothing
    */ 
   void printMap();
   
   //Destructor
   ~Map();

    /*FUNCTION: Map::generateRandomMap
    * Description:
    *    Creates a map of the given size and then creates a random topology base on provided
    *    values.
    * Throws:
    *    Nothing
    * Input Args:
    *    height - The height of the desired map
    *    width - The width of the desired map
    *    roughness - The number of peaks on the map
    *    low - The path cost of the lowest elements on the map
    *    high - The approximate height of the peaks
    * Returns:
    *    The randomly generated map
    */
   static Map* generateRandomMap(int height, int width, int roughness, int low=10, int high=100);
   
   /*FUNCTION: Map::loadFromFile
    * Description:
    *    Opens a .map file and creates a map object based on that file. The exploration map is set to unexplored
    *    in every point except the start
    * Throws:
    *    FileNotFound_Exception - If the specified file cannot be opened
    *    FileCorrupted_Exception - If the specified file does not contain a readable map
    * Input Args:
    *    Nothing
    * Returns:
    *    Nothing
    */
   static Map* loadFromFile(char* filename);

   /*FUNCTION: Map::loadFromFile
    * Description:
    *    Creates a .map file from an existing Map object. The exploration map is not saved
    * Throws:
    *    FileNotFound_Exception - If the specified file cannot be opened opened for writing
    * Input Args:
    *    Nothing
    * Returns:
    *    Nothing
    */
   static void saveToFile(char* filename, Map* map); 
};
#endif
