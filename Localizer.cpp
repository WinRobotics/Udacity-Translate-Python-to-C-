/**
	localizer.cpp

	Purpose: implements a 2-dimensional histogram filter
	for a robot living on a colored cyclical grid by 
	correctly implementing the "initialize_beliefs", 
	"sense", and "move" functions.

	This file is incomplete! Your job is to make these
	functions work. Feel free to look at localizer.py 
	for working implementations which are written in python.
*/

#include "localizer.h"
#include "helpers.cpp"
#include <stdlib.h>
#include <iostream>
#include "debugging_helpers.cpp"

using namespace std;



/**
	TODO - implement this function 
    
    Initializes a grid of beliefs to a uniform distribution. 

    @param grid - a two dimensional grid map (vector of vectors 
    	   of chars) representing the robot's world. For example:
    	   
    	   g g g
    	   g r g
    	   g g g
		   
		   would be a 3x3 world where every cell is green except 
		   for the center, which is red.

    @return - a normalized two dimensional grid of floats. For 
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
*/
vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) 
{
 	
	vector< vector <float> > newGrid; //variable newGrid
	//find the sum of elements inside this vector
    //Each vector element = 1/sum of elements
	
  	 
	// your code here
  
  //vector < vector <float> > newGrid {{0.01,0.02},{0.03,0.04}}; //testing the test functions

    float sum =0;

    sum = 1/ (float)(grid.size() * grid[0].size());
    //printf("%3f \n",sum);
    for(int i =0; i < grid.size(); i++)
    {

        newGrid.push_back(vector <float>());
        for(int j =0; j < grid[i].size();j++)
        {

            //cout<<our_matrix[i][j]<<" ";
            newGrid[i].push_back(sum);
            //printf("%3f\n",newGrid[i][j]);
        }

    }
  
  
	
	return newGrid;
}

/**
  TODO - implement this function 
    
    Implements robot motion by updating beliefs based on the 
    intended dx and dy of the robot. 

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00 

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00 

  @param dy - the intended change in y position of the robot

  @param dx - the intended change in x position of the robot

    @param beliefs - a two dimensional grid of floats representing
         the robot's beliefs for each cell before sensing. For 
         example, a robot which has almost certainly localized 
         itself in a 2D world might have the following beliefs:

         0.01 0.98
         0.00 0.01

    @param blurring - A number representing how noisy robot motion
           is. If blurring = 0.0 then motion is noiseless.

    @return - a normalized two dimensional grid of floats 
         representing the updated beliefs for the robot. 
*/
vector< vector <float> > move(int dy, int dx, 
  vector < vector <float> > beliefs,
  float blurring) 
{
  
  //Sample python code
  /*
  def move(dy, dx, beliefs, blurring):
    height = len(beliefs)
    width = len(beliefs[0])
    new_G = [[0.0 for i in range(width)] for j in range(height)]
    for i, row in enumerate(beliefs):
        for j, cell in enumerate(row):
            new_i = (i + dy ) % height #swap
            new_j = (j + dx ) % width
            #pdb.set_trace()
            new_G[int(new_i)][int(new_j)] = cell
    return blur(new_G, blurring)
    */
  

  vector < vector <float> > newGrid;
  

  // your code here
  
  int height = beliefs.size();
  int width = beliefs[0].size();
  
  //init new grid with zeros
  newGrid = zeros(height, width);
    
  	for(int i =0 ; i < height ; i ++)
      {
			for(int j=0;j<width;j++)
            {
              int new_i = (i + dy) % height;
              int new_j = (j + dx) % width;
              newGrid[new_i][new_j]+= beliefs[i][j];
            }
      }

  return blur(newGrid, blurring);
}


/**
	TODO - implement this function 
    
    Implements robot sensing by updating beliefs based on the 
    color of a sensor measurement 

	@param color - the color the robot has sensed at its location

	@param grid - the current map of the world, stored as a grid
		   (vector of vectors of chars) where each char represents a 
		   color. For example:

		   g g g
    	   g r g
    	   g g g

   	@param beliefs - a two dimensional grid of floats representing
   		   the robot's beliefs for each cell before sensing. For 
   		   example, a robot which has almost certainly localized 
   		   itself in a 2D world might have the following beliefs:

   		   0.01 0.98
   		   0.00 0.01

    @param p_hit - the RELATIVE probability that any "sense" is 
    	   correct. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

   	@param p_miss - the RELATIVE probability that any "sense" is 
    	   incorrect. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

    @return - a normalized two dimensional grid of floats 
    	   representing the updated beliefs for the robot. 
*/
vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss) 
{
	vector< vector <float> > newGrid;
  
  /*for i in range(len(grid)):
        for k in range(len(grid[i])):
            hit = (color == grid[i][k])
            beliefs[i][k]= (beliefs[i][k] * (hit * p_hit + (1-hit) * p_miss))*/
  
  int height = grid.size();
  int width = grid[0].size();
  float sum = 0;
  
  for( int i =0; i < height ; i++)
  {
   		for(int j =0; j<width; j++)
        {
          if(color == grid[i][j])
          {
            int hit =1;
            beliefs[i][j]= (beliefs[i][j] * (hit * p_hit + (1-hit) * p_miss));
          }
        }
  }
 

	// your code here
	//passing beliefs instead of newgrid based on review comments, unit test passed
	return normalize(beliefs);
}
