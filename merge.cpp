/*
Given two sorted lists of non overlapping intervals, produce their merge.
Definitions are unsurprising, let's proceed.
*/
#include <algorithm>
#include <deque>
struct Pair {
  int begin;
  int end;
};
typedef std::deque<Pair> Queue;

Queue merge(Queue a, Queue b) {
  Queue result;
  while (!a.empty() || !b.empty()) {
    Queue *min = nullptr;

    if (a.empty())
      min = &b;
    else if (b.empty())
      min = &a;
    else if (a.front().begin < b.front().begin)
      min = &a;
    else if (b.front().begin < a.front().begin)
      min = &b;

    if (min) {
      if (result.empty() || min->front().begin > result.back().end)
        result.push_back(min->front());
      result.back().end = std::max(result.back().end, min->front().end);
      min->pop_front();
    } else // a.front.begin == a.front.end
    {
      if (result.empty() || a.front().begin > result.back().end)
        result.push_back(a.front());
      result.back().end =
          std::max(result.back().end, std::max(a.front().end, b.front().end));
      a.pop_front();
      b.pop_front();
    }
  }

  return result;
}

#include <stdio.h>

int main() {
  {
    Queue a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});

    Queue result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");
  }

  {
    Queue a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});
    b.push_back(Pair{30, 31});

    Queue result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
  }
}
