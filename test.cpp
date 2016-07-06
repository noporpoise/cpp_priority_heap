#include <iostream>
#include <string>
#include "PriorityHeap.h"

int main()
{
  // Strings with priority given by ints
  PriorityHeap<std::string,int,std::less<int>> minheap;
  PriorityHeap<std::string,int,std::greater<int>> maxheap;

  minheap.add("x",-2);
  minheap.add("y",-3);
  minheap.add("z",-4);
  minheap.add("a",1);
  minheap.add("b",3);
  minheap.add("c",2);
  minheap.add("d",4);
  minheap.update("x",5);
  minheap.update("y",6);
  minheap.update("z",7);

  maxheap.add("a",1);
  maxheap.add("b",3);
  maxheap.add("c",2);
  maxheap.add("d",4);
  maxheap.add("x",1);
  maxheap.add("y",2);
  maxheap.add("z",3);
  maxheap.update("x",5);
  maxheap.update("y",6);
  maxheap.update("z",7);

  // throws out_of_range exception
  // std::cout << maxheap.get_priority("asdf") << std::endl;

  while(minheap.size() > 0) {
    std::cout << minheap.top_k() << " = " << minheap.top_p() << std::endl;
    minheap.pop();
  }
  std::cout << "--\n";
  while(maxheap.size() > 0) {
    std::cout << maxheap.top_k() << " = " << maxheap.top_p() << std::endl;
    maxheap.pop();
  }

  return EXIT_SUCCESS;
}
