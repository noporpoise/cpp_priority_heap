#ifndef PRIORITY_HEAP_TPP
#define PRIORITY_HEAP_TPP

template<class K, class P, class Cmp>
std::tuple<K,P> PriorityHeap<K,P,Cmp>::top() const {
  return std::make_tuple(heap[0].key, heap[0].priority);
}

template<class K, class P, class Cmp>
K PriorityHeap<K,P,Cmp>::top_k() const {
  return heap[0].key;
}

template<class K, class P, class Cmp>
K PriorityHeap<K,P,Cmp>::pop_k() {
  std::tuple<K,P> t = pop(); return t.first;
}

template<class K, class P, class Cmp>
P PriorityHeap<K,P,Cmp>::top_p() const {
  return heap[0].priority;
}

template<class K, class P, class Cmp>
P PriorityHeap<K,P,Cmp>::pop_p() {
  std::tuple<K,P> t = pop(); return t.second;
}

template<class K, class P, class Cmp>
size_t PriorityHeap<K,P,Cmp>::size() const { return heap.size(); }

template<class K, class P, class Cmp>
bool PriorityHeap<K,P,Cmp>::contains(K key) const { return (indices.find(key) != indices.end()); }

template<class K, class P, class Cmp>
P PriorityHeap<K,P,Cmp>::get_priority(K key) const { return heap.at(indices.at(key)).priority; }

// This function does not update the index of heap[idx] in the indices hashmap
// (the element we're moving). It does update the indices in the hash of other
// elements that are moved.
template<class K, class P, class Cmp>
size_t PriorityHeap<K,P,Cmp>::swap_down(size_t idx)
{
  Cmp cmp = Cmp(); // (a,b) returns true if a should be above b in tree
  size_t child;
  for(child = childidx(idx); child < heap.size(); idx = child, child = childidx(idx)) {
    // get index of smaller child
    child += (child+1 < heap.size() && cmp(heap[child+1].priority, heap[child].priority));
    if(!cmp(heap[child].priority, heap[idx].priority)) break;
    std::swap(heap[child], heap[idx]);
    indices[heap[idx].key] = idx;
  }
  return idx;
}

// This function does not update the index of heap[idx] in the indices hashmap
// (the element we're moving). It does update the indices in the hash of other
// elements that are moved.
template<class K, class P, class Cmp>
size_t PriorityHeap<K,P,Cmp>::swap_up(size_t idx)
{
  Cmp cmp = Cmp(); // (a,b) returns true if a should be above b in tree
  size_t parent;
  for(parent = parentidx(idx);
      idx > 0 && cmp(heap[idx].priority, heap[parent].priority);
      idx = parent, parent = parentidx(idx))
  {
    std::swap(heap[idx], heap[parent]);
    indices[heap[idx].key] = idx;
  }
  return idx;
}

template<class K, class P, class Cmp>
void PriorityHeap<K,P,Cmp>::add(K key, P priority)
{
  heap.push_back(PriorityEntry(key,priority));
  size_t idx = swap_up(heap.size()-1);
  indices[key] = idx;
}


template<class K, class P, class Cmp>
std::tuple<K,P> PriorityHeap<K,P,Cmp>::pop()
{
  PriorityEntry t = heap[0];

  // copy last element into first position, drop last entry
  heap[0] = heap[heap.size()-1];
  heap.pop_back(); // drop last entry
  indices.erase(t.key);
  size_t idx = swap_down(0);
  indices[heap[idx].key] = idx;

  return std::make_tuple(t.key, t.priority);
}

template<class K, class P, class Cmp>
void PriorityHeap<K,P,Cmp>::update(K key, P priority)
{
  size_t idx = indices.at(key);
  heap[idx] = PriorityEntry(key, priority);
  // try swap up/down into place
  idx = swap_up(idx);
  idx = swap_down(idx);
  indices[key] = idx;
}

#endif /* PRIORITY_HEAP_TPP */
