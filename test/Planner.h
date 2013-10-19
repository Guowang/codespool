#ifndef CS20232_PLANNER_HEADER
#define CS20232_PLANNER_HEADER

#include "Map.h"

/*CLASS: Planner
 *  Description:
 *    Provides an interface for objects that perform path planning in this assignment.
 */
class Planner{
public:
   /*FUNCTION: Planner::setMap
    * Description:
    *    Saves a pointer to the map object for use in this assignment
    * Throws:
    *    Nothing
    * Input Args:
    *    Nothing
    * Returns:
    *    Nothing
    */ 
   virtual void setMap(Map* m) = 0;
  

   /*FUNCTION: Planner::step
    * Description:
    *    Performs one iteration of whatever path planning algorithm is being used. 
    *    After each call to step(), the main code will call draw map to see what new
    *    nodes have been explored.
    * Throws:
    *    Nothing
    * Input Args:
    *    Nothing
    * Returns:
    *    Nothing
    */  
   virtual void step() = 0;
  

   /*FUNCTION: Planner::done
    * Description:
    *    Checks to see if the path planning algorithm is done. This will be called 
    *    repeatedly by the main code.
    * Throws:
    *    Nothing
    * Input Args:
    *    Nothing
    * Returns:
    *    True - If the planning algorithm has found the goal
    *    False - otherwise
    */
    virtual bool done() = 0;
  

   /*FUNCTION: Map::getPath
    * Description:
    *    Provides an array of Point objects that represent the path from the start to the goal.
    *    This array is returned by copying it to the specified location.
    * Throws:
    *    Nothing
    * Input Args:
    *    The address where the Point array should be placed
    * Returns:
    *    The number of points in the Point array
    */
    virtual int getPath(Point* points) = 0;
};


/*CLASS: DumbPlanner
 *  Description:
 *     A very simple path planner that tries to get to the goal using as few nodes as possible.
 *     This is provided only for demonstration of how to interact with the Map object
 */
class DumbPlanner : public Planner{
  Map* map;
  bool planningComplete;
  Point* points;
  int pcount;
  
public:

  DumbPlanner();
  void setMap( Map* m);
  void step();
  bool done();
  int getPath(Point* points);

};

#endif
