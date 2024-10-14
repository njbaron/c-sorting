#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

// https://www.sitepoint.com/best-sorting-algorithms/#allsortingalgorithmscompared

void write_num_array(int num_array_length, int *number_array)
{
    FILE *file_pointer;
    file_pointer = fopen("random_numbers.txt", "w");

    for (int index = 0; index < num_array_length; index++)
    {
        fprintf(file_pointer, "%d\n", number_array[index]);
    }

    fclose(file_pointer);
}

int read_num_array(int num_array_length, int *number_array)
{
    FILE *file_pointer;
    file_pointer = fopen("random_numbers.txt", "r");

    if (file_pointer == NULL)
    {
        printf("Not able to open the file.");
        return 1;
    }

    char myString[1024];
    int curr_array_index = 0;

    while (fgets(myString, 1024, file_pointer))
    {
        // printf("read string \"%s\"\n", myString);
        int number = atoi(myString);
        // printf("number read: %d\n", number);
        number_array[curr_array_index] = number;
        curr_array_index++;
    }

    fclose(file_pointer);
    return 0;
}

void print_array(int num_array_length, int *number_array)
{
    int new_num_array_length = num_array_length;
    if (new_num_array_length > 50)
    {
        new_num_array_length = 50;
    }
    for (int index = 0; index < new_num_array_length; index++)
    {
        printf("%d, ", number_array[index]);
    }
    printf("\n");
    for (int index = 0; index < new_num_array_length; index++)
    {
        printf("%d, ", number_array[num_array_length - index - 1]);
    }
    printf("\n");
}

int random_numbers(int max_number)
{

    int number_array[max_number];
    memset(number_array, 0, sizeof(number_array));

    int new_index_value_count = 0;

    for (int index = 0; index < max_number; index++)
    {

        int random_array_index = 0;
        int current_index_value = 1;

        while (current_index_value > 0)
        {
            new_index_value_count++;
            random_array_index = rand() % max_number;
            current_index_value = number_array[random_array_index];
        }

        number_array[random_array_index] = index;
    }

    printf("Max Number: %d\nNew index count: %d\n", max_number, new_index_value_count);

    write_num_array(max_number, number_array);

    return 0;
}

int swap_elements(int pos_1, int pos_2, int *number_array)
{
    int temp = number_array[pos_1];
    number_array[pos_1] = number_array[pos_2];
    number_array[pos_2] = temp;
}

// int swap_elements(int pos_1, int pos_2, int *number_array) {
//     number_array[pos_1] = number_array[pos_1] + number_array[pos_2];
//     number_array[pos_2] = number_array[pos_1] - number_array[pos_2];
//     number_array[pos_1] = number_array[pos_1] - number_array[pos_2];
// }

int bubble_sort(int max_number, int *number_array)
{
    // Bubble sort is a simple sorting algorithm that repeatedly steps through a given list of items,
    // comparing each pair of adjacent items and swapping them if they’re in the wrong order. The
    // algorithm continues until it makes a pass through the entire list without swapping any items. Bubble
    // sort is also sometimes referred to as “sinking sort”.

    printf("########################################\nBUBBLE SORT\n########################################\n");

    printf("Before\n");
    print_array(max_number, number_array);

    clock_t then = clock();
    bool sorted = false;

    while (!sorted)
    {
        bool changed_value = false;
        for (int i = 0; i < max_number - 1; i++)
        {
            if (number_array[i] > number_array[i + 1])
            {
                swap_elements(i, i + 1, number_array);
                changed_value = true;
            }
        }
        sorted = !changed_value;
    }

    clock_t now = clock();

    printf("After\n");
    print_array(max_number, number_array);
    printf("It took %f to run bubble sort with %d elements.\n", (double)(now - then) / CLOCKS_PER_SEC, max_number);
    return 0;
}

int insertion_sort(int max_number, int *number_array)
{
    // Insertion sort is another simple algorithm that builds the final sorted array one item at a time,
    // and it’s named like this for the way smaller elements are inserted into their correct positions
    // in the sorted array.

    printf("########################################\nINSERTION SORT\n########################################\n");

    printf("Before\n");
    print_array(max_number, number_array);

    clock_t then = clock();

    for (int i = 1; i < max_number; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (number_array[j] < number_array[j - 1])
            {
                swap_elements(j, j - 1, number_array);
            }
            else
            {
                break;
            }
        }
    }

    clock_t now = clock();

    printf("After\n");
    print_array(max_number, number_array);
    printf("It took %f to run insertion sort with %d elements.\n", (double)(now - then) / CLOCKS_PER_SEC, max_number);
    return 0;
}

void merge_sort_helper(int number_array_len, int *number_array)
{

    if (number_array_len <= 1)
    {
        return;
    }

    int left_num_array_len = number_array_len / 2;
    int right_num_array_len = (number_array_len / 2) + (number_array_len % 2);

    int left_num_array[left_num_array_len];
    int right_num_array[right_num_array_len];

    int left_num_array_bytes = (left_num_array_len * sizeof(left_num_array[0]));
    int right_num_array_bytes = (right_num_array_len * sizeof(right_num_array[0]));

    memcpy(left_num_array, number_array, left_num_array_bytes);
    memcpy(right_num_array, &number_array[left_num_array_len], right_num_array_bytes);

    merge_sort_helper(left_num_array_len, left_num_array);
    merge_sort_helper(right_num_array_len, right_num_array);

    memcpy(number_array, left_num_array, left_num_array_bytes);
    memcpy(&number_array[left_num_array_len], right_num_array, right_num_array_bytes);

    for (int i = 1; i < number_array_len; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (number_array[j] < number_array[j - 1])
            {
                swap_elements(j, j - 1, number_array);
            }
            else
            {
                break;
            }
        }
    }
}

int merge_sort(int max_number, int *number_array)
{
    // The basic idea of merge sort is to divide the input list in half, sort each half recursively using merge
    // sort, and then merge the two sorted halves back together. The merge step is performed by repeatedly
    // comparing the first element of each half and adding the smaller of the two to the sorted list. This process
    // is repeated until all elements have been merged back together.

    printf("########################################\nMERGE SORT\n########################################\n");

    printf("Before\n");
    print_array(max_number, number_array);

    clock_t then = clock();

    merge_sort_helper(max_number, number_array);

    clock_t now = clock();

    printf("After\n");
    print_array(max_number, number_array);
    printf("It took %f to run merge sort with %d elements.\n", (double)(now - then) / CLOCKS_PER_SEC, max_number);
    return 0;
}

int selection_sort(int max_number, int *number_array)
{
    // Selection sort repeatedly selects the smallest element from an unsorted portion of a list and swaps it with
    // the first element of the unsorted portion. This process continues until the entire list is sorted.

    printf("########################################\nSELECTION SORT\n########################################\n");

    printf("Before\n");
    print_array(max_number, number_array);

    clock_t then = clock();

    for (int i = 0; i < max_number - 1; i++)
    {
        int min_number = number_array[i];
        int min_index = i;
        for (int j = i + 1; j < max_number; j++)
        {
            if (number_array[j] < min_number)
            {
                min_number = number_array[j];
                min_index = j;
            }
        }
        swap_elements(i, min_index, number_array);
    }

    clock_t now = clock();

    printf("After\n");
    print_array(max_number, number_array);
    printf("It took %f to run selection sort with %d elements.\n", (double)(now - then) / CLOCKS_PER_SEC, max_number);
    return 0;
}

void quick_sort_helper(int number_array_len, int *number_array)
{

    if (number_array_len < 2)
    {
        return;
    }

    int pivot = number_array[0];

    int smaller[number_array_len];
    int smaller_len = 0;
    int larger[number_array_len];
    int larger_len = 0;

    for (int i = 1; i < number_array_len; i++)
    {
        if (number_array[i] > pivot)
        {
            larger[larger_len] = number_array[i];
            larger_len++;
        }
        else if (number_array[i] < pivot)
        {
            smaller[smaller_len] = number_array[i];
            smaller_len++;
        }
    }
    quick_sort_helper(smaller_len, smaller);
    quick_sort_helper(larger_len, larger);

    int smaller_len_byte = smaller_len * sizeof(smaller[0]);
    int larger_len_byte = larger_len * sizeof(larger[0]);

    memcpy(number_array, smaller, smaller_len_byte);
    number_array[smaller_len] = pivot;
    memcpy(&number_array[smaller_len + 1], larger, larger_len_byte);
}

int quick_sort(int max_number, int *number_array)
{
    // Quicksort is a popular divide-and-conquer sorting algorithm based on the principle of partitioning an array
    // into two sub-arrays — one containing elements smaller than a “pivot” element and the other containing elements
    // larger than the pivot element. The two sub-arrays are then sorted recursively.
    // The basic steps of quicksort include:
    // 1. Choose a pivot element from the array.
    // 2. Partition the array into two sub-arrays, one containing elements smaller than the pivot and the other containing elements larger than the pivot.
    // 3. Sort the two sub-arrays recursively using quicksort.
    // 4. Combine the two sorted sub-arrays.

    printf("########################################\nQUICK SORT\n########################################\n");

    printf("Before\n");
    print_array(max_number, number_array);

    clock_t then = clock();

    quick_sort_helper(max_number, number_array);

    clock_t now = clock();

    printf("After\n");
    print_array(max_number, number_array);
    printf("It took %f to run quick sort with %d elements.\n", (double)(now - then) / CLOCKS_PER_SEC, max_number);
    return 0;
}

int main(int argc, char *argv[])
{

    int max_number = 100000;
    // int max_number = 100;

    random_numbers(max_number);

    int number_array[max_number];
    read_num_array(max_number, number_array);

    int bubble_number_array[max_number];
    memcpy(bubble_number_array, number_array, sizeof(bubble_number_array));
    bubble_sort(max_number, bubble_number_array);

    int insert_number_array[max_number];
    memcpy(insert_number_array, number_array, sizeof(insert_number_array));
    insertion_sort(max_number, insert_number_array);

    int merge_number_array[max_number];
    memcpy(merge_number_array, number_array, sizeof(merge_number_array));
    merge_sort(max_number, merge_number_array);

    int selection_number_array[max_number];
    memcpy(selection_number_array, number_array, sizeof(selection_number_array));
    selection_sort(max_number, selection_number_array);

    int quick_number_array[max_number];
    memcpy(quick_number_array, number_array, sizeof(quick_number_array));
    quick_sort(max_number, quick_number_array);

    return 0;
}
