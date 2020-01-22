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

int partition(int nums[], int low, int high, int isAscending)
{
    int pivot = nums[high];
    int last_smallest = low - 1;

    for (int current_index = low; current_index <= high - 1; current_index++)
    {
        if (isAscending)
        {
            if (nums[current_index] <= pivot)
            {
                last_smallest++;
                swap(&nums[current_index], &nums[last_smallest]);
            }
        }
        else
        {
            if (nums[current_index] >= pivot)
            {
                last_smallest++;
                swap(&nums[current_index], &nums[last_smallest]);
            }
        }
    }
    last_smallest++;
    swap(&nums[last_smallest], &nums[high]);
    return last_smallest;
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
    int* nums = (int *)malloc(sizeof(int)*size);
    srand(time(NULL)); // generate different sede everytime the program is ran
    generate_numbers(nums, size);
    // printf("Before sorting\n");
    // print_array(nums, size);
    quicksort(nums, 0, size - 1, true);
    quicksort(nums, (size/2), size - 1, false);
    // printf("After sorting\n");
    // print_array(nums, size);
    free(nums);
    return 0;
}