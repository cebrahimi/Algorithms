///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// Please Update!

// State of one disk, either light or dark.
enum disk_color { DISK_DARK, DISK_LIGHT };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:

  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_DARK) {

      assert(light_count > 0);

      for (size_t i = 1; i < _colors.size(); i += 2) {
        _colors[i] = DISK_LIGHT;
      }
  }

  // Equality operator for unit tests.
  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index)
  {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is dark, the second disk at index 1
  // is light, and so on for the entire row of disks.
  bool is_alternating() const
  {
      for(size_t   i = 0; i < total_count(); i++)
      {
        if(_colors[i] == DISK_DARK && _colors[i + 1] == DISK_DARK)
        {
          return false;
        }
      }
    // TODO: Write code for this function, including rewriting the return
    // statement, and then delete these comments.
    return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks
  // on the right (high indices) and all dark disks on the left (low
  // indices).
  bool is_sorted() const
  {
    size_t i = dark_count();
    std::string s = to_string();
//    std::cout << "\nAMOUNT OF DARKS: " << i << "  " << s;
    for(size_t count = 0; count < i; count++)
    {
      if(_colors[count] != DISK_DARK)
      {
      //  std::cout << "\nCOUNT: " << count;
        return false;
      }
    }
     i = total_count();
//     std::cout << "\nAMOUNT OF LIGHTS: " << i << "  " << s;
    for(size_t count = dark_count(); count < total_count(); count++)
    {
      if(_colors[count] != DISK_LIGHT)
      {
        return false;
      }
    }
    // TODO: Write code for this function, including rewriting the return
    // statement, and then delete these comments.
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the left-to-right algorithm.
sorted_disks sort_left_to_right(const disk_state& before) {
  // TODO: Write code for this function, including rewriting the return
  // statement, and then delete these comments.

	disk_state local = before;
	int swaps = 0;
  int end = local.total_count();

	for (int i = 0; i < end - 1; i++) {
		for (int j = 0; j < end - i-1; j++) {
			if (local.get(j) == DISK_LIGHT && local.get(j + 1) == DISK_DARK)
      {
    
				local.swap(j);
				swaps++;
			}
		}
	}


	assert(before.is_alternating());

  // TODO
  return sorted_disks(local, swaps);
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  // TODO: Write code for this function, including rewriting the return
  // statement, and then delete these comments.
  // check that the input is in alternating format
  size_t end = before.total_count();
  int swaps = 0;
  bool sorted = false;

  disk_state local = before;
  std::string s = local.to_string();
//  std:: cout << "\n" << s;

  while(!sorted)
  {

  for(size_t i = 0; i < end - 1; i++)
  {
      if(local.get(i) == DISK_LIGHT && local.get(i+1) == DISK_DARK)
      {
          local.swap(i);
          swaps++;
      }

  }

  for(size_t index = end-1; index > 0; index--)
  {
      if(local.get(index) == DISK_DARK && local.get(index-1) == DISK_LIGHT)
      {
          local.swap(index-1);
          swaps++;
      }

  }

  sorted = local.is_sorted();
}

s = local.to_string();
//std:: cout << "\n" << s;


  assert(before.is_alternating());

  // TODO
  return sorted_disks(local, swaps);
}
