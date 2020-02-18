///////////////////////////////////////////////////////////////////////////////



// pipes_algs.hpp



//



// Algorithms that solve the ecomomical pipes problem.



//



// All of the TODO sections for this project reside in this file.



//



// This file builds on pipes_types.hpp, so you should familiarize yourself



// with that file before working on this file.



//



///////////////////////////////////////////////////////////////////////////////







#pragma once







#include <cassert>

#include <bitset>

#include <math.h>







#include "pipes_types.hpp"







namespace pipes {







// Solve the economical pipes problem for the given grid, using an exhaustive



// search algorithm.



//



// This algorithm is expected to run in exponential time, so the grid's



// width+height must be small enough to fit in a 64-bit int; this is enforced



// with an assertion.



//



// The grid must be non-empty.



path econ_pipes_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  const size_t total_steps = setting.rows() + setting.columns() - 2;
  assert(total_steps < 64);
  path best(setting);
  for (long unsigned int bits = 0; bits <= pow(2, total_steps) - 1; bits++)
  {
	  path candidate(setting);
	  for (long unsigned int k = 0; k <= total_steps - 1; k++)
	  {
      int bit = (bits >> k) & 1;
		  if (bit == 1)
		  {
        if (candidate.is_step_valid(STEP_DIRECTION_RIGHT))
        {
          candidate.add_step(STEP_DIRECTION_RIGHT);
        }
      } else
      {
        if (candidate.is_step_valid(STEP_DIRECTION_DOWN))
        {
          candidate.add_step(STEP_DIRECTION_DOWN);
        }
	     }

		if (candidate.total_open() > best.total_open())
    {
		    best = candidate;
	}
  }
}
  return best;
}



// Solve the economical pipes problem for the given grid, using a dynamic

// programming algorithm.

//

// The grid must be non-empty.

path econ_pipes_dyn_prog(const grid& setting) {
// grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.
  using cell_type = std::optional<path>;
  std::vector<std::vector<cell_type>> A(setting.rows(),
                               std::vector<cell_type>(setting.columns()));
  A[0][0] = path(setting);
  assert(A[0][0].has_value());
  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {
      if (setting.get(r, c) != CELL_ROCK)
      {
        auto best = A[r][c];
       }
       cell_type from_above(setting);
       cell_type from_left(setting);
       from_above.reset();
       from_left.reset();
      if (r > 0 && A[r-1][c].has_value())
      {
        from_above = A[r-1][c];
         from_above.value().add_step(STEP_DIRECTION_DOWN);
      }
    
     if (c> 0 && A[r][c -1].has_value())

     {
        from_left = A[r][c -1];
       from_left.value().add_step(STEP_DIRECTION_RIGHT);
      }
       if(from_above.has_value() && from_left.has_value())
       {
         if(from_above.value().total_open() > from_left.value().total_open())
         {
            A[r][c] = from_above;
         }
         else
         {
            A[r][c] = from_left;
         }
       }
       else if(from_above.has_value() && !from_left.has_value())
       {
          A[r][c] = from_above;
       }
       else if(!from_above.has_value() && from_left.has_value())
       {
          A[r][c] = from_left;
       }
      else
      {
        continue;
      }
     }
}
     
  coordinate r = setting.rows()-1;
  coordinate c = setting.columns()-1;
  cell_type * best = &(A[r][c]);
  assert(best->has_value());
  return **best;



}

