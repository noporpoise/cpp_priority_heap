#ifndef PRIORITY_HEAP_HDR
#define PRIORITY_HEAP_HDR

#include <vector>
#include <unordered_map>

// A priority heap with updatable priorities
// implemented with using a heap and an unordered_map.

// Priority Heap (by default max-heap, pass Cmp as std::less<P> to make min-heap)
template<class K, class P, class Cmp=std::greater<P>>
class PriorityHeap
{
public:
  // Get top element as tuple, key only or priority only
  std::tuple<K,P> top() const;
  K top_k() const;
  P top_p() const;

  // Pop top element off the heap, return tuple, key or priority
  std::tuple<K,P> pop();
  K pop_k();
  P pop_p();

  size_t size() const; // return number of elements in the heap
  void add(K key, P priority); // add an element to the heap
  void update(K key, P priority); // update the priority of an element
  bool contains(K key) const; // check if the heap contains an element
  P get_priority(K key) const; // get the priority of an element

private:
  class PriorityEntry {
  private:
    PriorityEntry(K key, P priority):key(key),priority(priority){}
    K key;
    P priority;
    friend class PriorityHeap;
  };

  std::vector<PriorityEntry> heap;
  std::unordered_map<K,size_t> indices;

  size_t parentidx(size_t idx) { return (idx-1)/2; }
  size_t childidx(size_t idx) { return idx*2+1; }
  size_t swap_up(size_t idx);
  size_t swap_down(size_t idx);
};

// Place implementation into .tpp and include in header
// Can't put in .cpp since we are using templates which need to appear in
// the header file
#include "PriorityHeap.tpp"

#endif /* PRIORITY_HEAP_HDR */
