/*
Given two sorted lists of non overlapping intervals, produce their merge.
Definitions are unsurprising, let's proceed.
*/
#include <algorithm>
#include <assert.h>
#include <vector>

struct Pair {
  int begin;
  int end;
  bool operator==(const Pair &other) const {
    return begin == other.begin && end == other.end;
  }
};

typedef std::vector<Pair> Vector;

Vector merge(const Vector &a, const Vector &b) {
  Vector result;
  struct Proxy {
    size_t size;
    Vector::const_iterator position;
    void pop() {
      ++position;
      --size;
    }
  } ap{a.size(), a.begin()}, bp{b.size(), b.begin()};
  while (ap.size || bp.size) {
    if (auto *min = !ap.size                                    ? &bp
                    : !bp.size                                  ? &ap
                    : (ap.position->begin < bp.position->begin) ? &ap
                    : (bp.position->begin < ap.position->begin) ? &bp
                                                                : nullptr) {
      if (result.empty() || min->position->begin > result.back().end)
        result.push_back(*min->position);
      result.back().end = std::max(result.back().end, min->position->end);
      min->pop();
    } else // a.front.begin == a.front.end
    {
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
  {
    Vector a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});

    Vector result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");
  }

  {
    Vector a, b;
    a.push_back(Pair{1, 10});
    a.push_back(Pair{12, 20});

    b.push_back(Pair{5, 11});
    b.push_back(Pair{15, 25});
    b.push_back(Pair{30, 31});

    Vector result = merge(a, b);

    for (auto &i : result)
      printf("[%d,%d]\n", i.begin, i.end);
    printf("\n");

    assert(merge(a, b) != a);
    assert(merge(a, b) != b);
    assert(merge(a, a) == a);
    assert(merge(b, b) == b);
  }
}
