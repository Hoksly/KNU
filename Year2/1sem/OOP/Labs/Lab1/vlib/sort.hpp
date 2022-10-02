#include "def.hpp"

#ifndef _SORT_H
#define _SORT_H

template <class Container>
void insertion_sort(Container &arr)
{

    int n = arr.size();
    if (n == 0)
        return;

    int i, j;

    auto key = arr[0];

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template <class Container>
void __merge(Container &arr, const int left, const int mid, const int right)
{
    int n_left = mid - left + 1, n_right = right - mid;

    Container leftV(n_left);
    Container rightV(n_right);

    for (int i = 0; i < n_left; ++i)
        leftV.push_back(arr[left + i]);

    for (int i = 0; i < n_right; ++i)
        rightV.push_back(arr[mid + 1 + i]);

    int index_cur_at_left = 0, index_cur_at_right = 0, index_of_merged = left;

    while (index_cur_at_left < n_left && index_cur_at_right < n_right)
    {

        if (leftV[index_cur_at_left] <= rightV[index_cur_at_right])
        {

            arr[index_of_merged] = leftV[index_cur_at_left];
            index_cur_at_left++;
        }

        else
        {

            arr[index_of_merged] = rightV[index_cur_at_right];
            index_cur_at_right++;
        }

        index_of_merged++;
    }

    while (index_cur_at_left < n_left)
    {
        arr[index_of_merged] = leftV[index_cur_at_left];
        index_cur_at_left++;
        index_of_merged++;
    }

    while (index_cur_at_right < n_right)
    {
        arr[index_of_merged] = rightV[index_cur_at_right];
        index_cur_at_right++;
        index_of_merged++;
    }
}

template <class Container>
void __merge_sort(Container &arr, const int begin, const int end)
{

    if (begin >= end)
        return;

    int mid = (begin + (end - begin) / 2);
    __merge_sort(arr, begin, mid);
    __merge_sort(arr, mid + 1, end);
    __merge(arr, begin, mid, end);
}

template <class Container>
void merge_sort(Container &arr)
{
    __merge_sort(arr, 0, arr.size() - 1);
}

template <class Container>
void bucket_sort(Container &arr)
{
    int n = arr.size();
}

template <class Container>
v_size __partition(Container &arr, v_size low, v_size high)
{
    auto pivot = arr[high];
    v_size i = low - 1;

    auto tmp = arr[low]; // just init

    for (v_size j = low; j <= high; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            // std::swap(&arr[i], &arr[j]);
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    // no iterators, so i need make swap myself
    // std::swap(&arr[i + 1], &arr[high]);
    tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return (i + 1);
}

template <class Container>
void quick_sort(Container &arr, v_size low, v_size high)
{
    if (low >= high)
        return;

    v_size pi = __partition(arr, low, high);

    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
}

#endif
