#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bits/stdc++.h"

using namespace std;

void SelectionSort(vector<int>& v) {
  auto n{v.size()};
  for (int i{0}; i < n; i++) {
    auto mini{v[i]};
    auto mini_pos{i};
    for (int j{i + 1}; j < n; j++) {
      if (v[j] < mini) {
        mini = v[j];
        mini_pos = j;
      }
    }
    swap(v[i], v[mini_pos]);
  }
}

void InsertionSort(vector<int>& v) {
  for (int i{1}; i < v.size(); i++) {
    for (int j{i}; j > 0; j--) {
      if (v[j - 1] <= v[j]) {
        break;
      }
      swap(v[j], v[j - 1]);
    }
  }
}

void Merge(vector<int>& v, int left, int mid, int right) {
  auto i{left}, j{mid};
  vector<int> v_aux;
  v_aux.reserve(right - left);
  while (i < mid || j < right) {
    if (i >= mid) {
      v_aux.emplace_back(v[j]);
      j++;
    } else if (j >= right) {
      v_aux.emplace_back(v[i]);
      i++;
    } else if (v[i] <= v[j]) {
      v_aux.emplace_back(v[i]);
      i++;
    } else {
      v_aux.emplace_back(v[j]);
      j++;
    }
  }

  for (int k{0}; k < v_aux.size(); k++) {
    v[left + k] = v_aux[k];
  }
}

void MergeSort(vector<int>& v, int left, int right) {
  if (left + 1 >= right) {
    return;
  }

  auto mid = (right + left) / 2;
  MergeSort(v, left, mid);
  MergeSort(v, mid, right);
  Merge(v, left, mid, right);
}

int Partition(vector<int>& v, int left, int right) {
  auto pivot{v[right]};
  auto p{left};
  for (auto i{left}; i < right; i++) {
    if (v[i] < pivot) {
      swap(v[p], v[i]);
      p++;
    }
  }
  swap(v[right], v[p]);
  return p;
}

void QuickSort(vector<int>& v, int left, int right) {
  if (left >= right) {
    return;
  }
  auto p = Partition(v, left, right);
  QuickSort(v, left, p - 1);
  QuickSort(v, p + 1, right);
}

vector<int> GenerateRandomVector() {
  constexpr int max_n{1'000};
  auto n = rand() % max_n;
  vector<int> vector(n);
  for (auto& element : vector) {
    element = rand();
  }
  return vector;
}

MATCHER(IsSorted, "A sorted iterable container") {
  for (int i{1}; i < arg.size(); i++) {
    if (arg[i] < arg[i - 1]) {
      return false;
    }
  }
  return true;
}

TEST(Sort, SelectionSort) {
  int number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    SelectionSort(v);
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, InsertionSort) {
  int number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    InsertionSort(v);
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, MergeSort) {
  int number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    MergeSort(v, 0, v.size());
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, QuickSort) {
  int number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    QuickSort(v, 0, v.size() - 1);
    EXPECT_THAT(v, IsSorted());
  }
}
