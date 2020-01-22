#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Fills an array with random numbers.
 * @param nums pointer to an array
 * @param size size of array
 */
void generate_numbers(int nums[], int size)
{
    for (int index = 0; index < size; index++)
    {
        nums[index] = rand();
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int nums[], int low, int high, bool isAscending)
{
    int pivot = nums[high];
    int last_smallest = low - 1;

    for (int current_index = low; current_index <= high - 1; current_index++)
    {
        if (isAscending)
        {
            if (nums[current_index] < pivot)
            {
                last_smallest++;
                swap(&nums[current_index], &nums[last_smallest]);
            }
        }
        else
        {
            if (nums[current_index] > pivot)
            {
                last_smallest++;
                swap(&nums[current_index], &nums[last_smallest]);
            }
        }
    }
    swap(&nums[last_smallest + 1], &nums[high]);
    return last_smallest + 1;
}

void quicksort(int nums[], int low, int high, bool isAscending)
{

    if (low < high)
    {
        int partition_index = partition(nums, low, high, isAscending);
        quicksort(nums, low, partition_index - 1, isAscending);
        quicksort(nums, partition_index + 1, high, isAscending);
    }
}

void merge(int nums[], int left, int middle, int right, bool is_ascending)
{
    int left_index, right_index, merge_index;
    int size_left = middle - left + 1;
    int size_right = right - middle;

    int left_array[size_left], right_array[size_right];

    for (int index = 0; index < size_left; index++)
    {
        left_array[index] = nums[left + index];
    }
    for (int index = 0; index < size_right; index++)
    {
        right_array[index] = nums[middle + 1 + index];
    }

    left_index = 0;
    right_index = 0;
    merge_index = left;

    while (left_index < size_left && right_index < size_right)
    {
        if (is_ascending)
        {
            if (left_array[left_index] <= right_array[right_index])
            {
                nums[merge_index] = left_array[left_index];
                left_index++;
            }
            else
            {
                nums[merge_index] = right_array[right_index];
                right_index++;
            }
        }
        else
        {
            if (left_array[left_index] >= right_array[right_index])
            {
                nums[merge_index] = left_array[left_index];
                left_index++;
            }
            else
            {
                nums[merge_index] = right_array[right_index];
                right_index++;
            }
        }

        merge_index++;
    }

    while (left_index < size_left)
    {
        nums[merge_index] = left_array[left_index];
        left_index++;
        merge_index++;
    }

    while (right_index < size_right)
    {
        nums[merge_index] = right_array[right_index];
        right_index++;
        merge_index++;
    }
}

void mergesort(int nums[], int left, int right, bool ascending)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergesort(nums, left, middle, ascending);
        mergesort(nums, middle + 1, right, ascending);

        merge(nums, left, middle, right, ascending);
    }
}

void print_array(int nums[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main()
{

    int size = 1000000; // size of array
    int *nums = (int *)malloc(sizeof(int) * size);
    srand(time(NULL)); // generate different sede everytime the program is ran
    generate_numbers(nums, size);
    mergesort(nums, 0, size - 1, true);
    mergesort(nums, size / 2, size - 1, false);
    /**
     * Initially, the code was run using the quicksort algortithm but it was seg faulting,
     * after changing to mergesort, the code worked properly and much faster
    // quicksort(nums, 0, size - 1, true);
    // quicksort(nums, size / 2, size - 1, false);
    */
    // print_array(nums, size);
    free(nums);
    return 0;
}