/*
Prior question solved also: https://github.com/jaykrell/stock/blob/main/stock.cpp

Restated problem statement:
Given two sorted lists of non overlapping intervals, produce their merge.
Definitions are unsurprising, let's proceed.

Original problem statement:
Merge Two Sorted Interval Arrays
Problem Statement

Given two sorted, non-overlapping interval lists, return a 3rd interval list
that is the union of the input interval lists.

Example

Input:
{[1,2], [3,9]}
{[4,6], [8,10], [11,12]}

Output should be:
{[1,2], [3,10], [11,12]}


0   1   2   3   4   5   6   7   8   9  10  11  12
   [---]   [-----------------------]
               [-------]       [------]   [----]
   [---]   [--------------------------]   [----]
*/
#include <algorithm>
#include <assert.h>
#include <deque>
#include <vector>

struct Pair {
  int begin;
  int end;
  bool operator==(const Pair &other) const {
    return begin == other.begin && end == other.end;
  }
};

template <typename Container>
Container merge(const Container &a, const Container &b) {
  Container result;
  // "Proxy" as in, "avoid mutating or copying the inputs".
  struct Proxy {
    size_t size;
    Container::const_iterator position;
    void pop() {
      ++position;
      --size;
    }
  } ap{a.size(), a.begin()}, bp{b.size(), b.begin()};
  while (ap.size || bp.size) {
    // Get the minimum of a and b.
    // If one is empty, the other is the minimum.
    // At least one is not empty.
    // If they are equal, there is no minimum, use different path.
    if (auto *min = !ap.size                                    ? &bp
                    : !bp.size                                  ? &ap
                    : (ap.position->begin < bp.position->begin) ? &ap
                    : (bp.position->begin < ap.position->begin) ? &bp
                                                                : nullptr) {
      // If result is empty, initialize it with the minimum of a and b.
      // If the result is not empty and there is no overlap, push minimum of a
      // and b. If result is not empty and there is overlap, extend the end to
      // the maximum of the (end of the) result and the minimum of a and b. Some
      // cases are combined.
      if (result.empty() || min->position->begin > result.back().end)
        result.push_back(*min->position);
      result.back().end = std::max(result.back().end, min->position->end);
      min->pop();
    } else // a.front.begin == b.front.begin
    {
      // They have equal start. Initialize result if it is empty,
      // with that start, and the maximum of the ends, and pop both.
      // If result is not empty and there is overlap, extend the end.
      // If result is empty, or there is no overlap, push new element.
      // Some cases are combined.
      if (result.empty() || ap.position->begin > result.back().end)
        result.push_back(*ap.position);
      result.back().end = std::max(
          result.back().end, std::max(ap.position->end, bp.position->end));
      ap.pop();
      bp.pop();
    }
  }

  return result;
}

#include <stdio.h>

int main() {

  // vector

  {
    std::vector<Pair> a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});

    std::vector<Pair> result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");
  }

  {
    std::vector<Pair> a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});
    b.push_back(Pair{30, 31});

    std::vector<Pair> result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");

    assert(merge(a, b) != a);
    assert(merge(a, b) != b);
    assert(merge(a, a) == a);
    assert(merge(b, b) == b);
  }

  // deque

  {
    std::deque<Pair> a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});

    std::deque<Pair> result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");
  }

  {
    std::deque<Pair> a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});
    b.push_back(Pair{30, 31});

    std::deque<Pair> result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");

    assert(merge(a, b) != a);
    assert(merge(a, b) != b);
    assert(merge(a, a) == a);
    assert(merge(b, b) == b);
  }

  // Test original.
  {
    std::deque<Pair> a, b;
    a.push_back(Pair{1, 2});
    a.push_back(Pair{3, 9});

    b.push_back(Pair{4, 6});
    b.push_back(Pair{8, 10});
    b.push_back(Pair{11, 12});

    std::deque<Pair> result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");
  }
}
