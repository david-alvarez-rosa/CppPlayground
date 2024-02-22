#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bits/stdc++.h"

using namespace std;

void PrintVector(const vector<int>& v) {
  for (const auto e : v) cout << e << ' ';
  cout << endl;
}

void SelectionSort(vector<int>& v) {
  auto n{v.size()};
  for (size_t i{0}; i < n; i++) {
    auto mini{v[i]};
    auto mini_pos{i};
    for (size_t j{i + 1}; j < n; j++) {
      if (v[j] < mini) {
        mini = v[j];
        mini_pos = j;
      }
    }
    swap(v[i], v[mini_pos]);
  }
}

void InsertionSort(vector<int>& v) {
  for (size_t i{1}; i < v.size(); i++) {
    for (size_t j{i}; j > 0; j--) {
      if (v[j - 1] <= v[j]) {
        break;
      }
      swap(v[j], v[j - 1]);
    }
  }
}

void Merge(vector<int>& v, size_t left, size_t mid, size_t right) {
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

  for (size_t k{0}; k < v_aux.size(); k++) {
    v[left + k] = v_aux[k];
  }
}

void MergeSort(vector<int>& v, size_t left, size_t right) {
  if (left >= right - 1) {
    return;
  }

  auto mid = (right + left) / 2;
  MergeSort(v, left, mid);
  MergeSort(v, mid, right);
  Merge(v, left, mid, right);
}

void QuickSort(vector<int>& v, size_t left, size_t right) {
  if (left >= right - 1) {
    return;
  }
  auto pivot{v[left]};
  auto i{left}, j{right - 1};
  while (i < j) {
    if (v[i] <= pivot) {
      ++i;
    } else if (v[i] > pivot) {
      swap(v[i], v[j]);
      --j;
    }
  }
  QuickSort(v, left, i);
  QuickSort(v, i, right);
  MergeSort(v, left, right);
}

vector<int> GenerateRandomVector() {
  constexpr size_t max_n{1'000};
  auto n = rand() % max_n;
  vector<int> vector(n);
  for (auto& element : vector) {
    element = rand();
  }
  return vector;
}

MATCHER(IsSorted, "A sorted iterable container") {
  for (size_t i{1}; i < arg.size(); i++) {
    if (arg[i] < arg[i - 1]) {
      return false;
    }
  }
  return true;
}

TEST(Sort, SelectionSort) {
  size_t number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    SelectionSort(v);
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, InsertionSort) {
  size_t number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    InsertionSort(v);
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, MergeSort) {
  size_t number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    MergeSort(v, 0, v.size());
    EXPECT_THAT(v, IsSorted());
  }
}

TEST(Sort, QuickSort) {
  size_t number_iterations{25};
  while (number_iterations--) {
    auto v = GenerateRandomVector();
    QuickSort(v, 0, v.size());
    EXPECT_THAT(v, IsSorted());
  }
}
