#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct
  Array *new_array = malloc(sizeof(Array));

  // Set initial values for capacity and count
  new_array->capacity = capacity;
  new_array->count = 0;

  // Allocate memory for elements
  new_array->elements = calloc(0, sizeof(char *) * capacity);

  return new_array;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{
  // Free all elements
  if (arr->elements != NULL)
  {
    free(arr->elements);
  }

  // Free array
  if (arr != NULL)
  {
    free(arr);
  }
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{
  // calculate new capacity
  arr->capacity = arr->capacity * 2;

  // realloc to new capacity
  arr->elements = realloc(arr->elements, sizeof(char *) * arr->capacity);
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{
  // Throw an error if the index is greater than the current count
  if (index >= arr->count)
  {
    return NULL;
  }

  // Otherwise, return the element at the given index
  else
  {
    return arr->elements[index];
  }
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index)
{
  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    fprintf(stderr, "Index not found");
  }
  else
  {
    // Resize the array if the number of elements is over capacity
    if (arr->count == arr->capacity)
    {
      resize_array(arr);
    }

    // Move every element after the insert index to the right one position
    int position = arr->count - 1;
    while (position >= index)
    {
      arr->elements[position + 1] = arr->elements[position];
      position--;
    }

    // Copy the element and add it to the array
    arr->elements[index] = strdup(element);

    // Increment count by 1
    arr->count = arr->count + 1;
  }
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{
  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count == arr->capacity)
  {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);

  // Increment count by 1
  arr->count = arr->count + 1;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{
  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int search_index = 0;
  int found = 0;
  while (search_index < arr->count && !found)
  {
    if (!strcmp(arr->elements[search_index], element))
    {
      free(arr->elements[search_index]);
      found = 1;
    }
    else
    {
      search_index = search_index + 1;
    }
  }
  if (!found)
  {
    fprintf(stderr, "Index not found");
  }
  else
  {
    // Shift over every element after the removed element to the left one position
    while (search_index < arr->count - 1)
    {
      arr->elements[search_index] = arr->elements[search_index + 1];
      search_index = search_index + 1;
    }

    // Decrement count by 1
    arr->count = arr->count - 1;
  }
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);
  printf("%d\n", arr->count);

  // arr_insert(arr, "STRING1", 0);
  arr_append(arr, "string 1");
  arr_append(arr, "string 2");
  arr_append(arr, "string 3");
  // arr_insert(arr, "STRING2", 0);
  // arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  // arr_remove(arr, "STRING3");
  // arr_print(arr);
  printf("%s\n", arr_read(arr, 0));
  printf("%s\n", arr_read(arr, 1));
  printf("%s\n", arr_read(arr, 2));
  printf("%d\n", arr->count);

  destroy_array(arr);

  return 0;
}
#endif
