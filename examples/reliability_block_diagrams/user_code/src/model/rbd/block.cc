#include "block.h"
#include <iostream>
#include <sstream>

using namespace std;

unsigned long int Block::max_allocated = 0;
set<unsigned long int>* Block::reclaimed_ids = NULL;
function<unsigned long int, unsigned long int>* Block::references = NULL;

// ----------------------------------------------------------------------------------

ostream& operator<< (ostream& in_ostream, const Block& in_block)
{
  ostringstream temp_string;
  temp_string << in_block.id;

  in_ostream << temp_string.str();

  return in_ostream;
}

// ----------------------------------------------------------------------------------

Block::Block()
{
  // Allocate the static members if necessary
  if (references == NULL)
  {
    references = new function<unsigned long int, unsigned long int>;
    reclaimed_ids = new set<unsigned long int>;
  }

  if ((*reclaimed_ids).empty())
  {
    id = max_allocated;
    max_allocated++;
  }
  else
  {
    id = *((*reclaimed_ids).begin());
    (*reclaimed_ids).erase((*reclaimed_ids).begin());
  };

  Increase_Reference_Count();
}

// ----------------------------------------------------------------------------------

Block::Block(const Block &in_block)
{
  id = in_block.id;

  Increase_Reference_Count();
}

// ----------------------------------------------------------------------------------

Block::~Block()
{
  Decrease_Reference_Count();

  // Delete the static members if we don't need them any more. This is
  // somewhat inefficient if repeatedly create and destroy only one instance
  // of this class (but that is rare).
  if ((*references).size() == 0)
  {
    delete references;
    references = NULL;
    delete reclaimed_ids;
    reclaimed_ids = NULL;
  }
}
