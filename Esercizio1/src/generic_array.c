#include "../include/generic_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Initial capacity for the array
#define INITIAL_CAPACITY 10

// It represents the internal structure of this implementation of Generic Array
struct _GenericArray {
	void** array;
	int capacity;
	int size;
	GenericArrayCmp compare;
};

GenericArray* GenericArray_create(GenericArrayCmp compare) {
	GenericArray* generic_array = (GenericArray* ) malloc(sizeof(GenericArray));
	if(generic_array == NULL) {
		fprintf(stderr, "GenericArray_create: unable to allocate memory for the ordered array");
		exit(EXIT_FAILURE);
	}
	
	generic_array -> array = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));
	if(generic_array -> array == NULL) {
		fprintf(stderr, "GenericArray_create: unable to allocate memory for the internal array");
		exit(EXIT_FAILURE);
	}
	
	generic_array -> size = 0;
	generic_array -> capacity = INITIAL_CAPACITY;
	generic_array -> compare = compare;
	
	return generic_array;
	
}

int GenericArray_empty(GenericArray* generic_array) {
	if (generic_array == NULL) {
		fprintf(stderr, "GenericArray_empty: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return generic_array -> size == 0;
}

int GenericArray_capacity(GenericArray* generic_array) {
	if (generic_array == NULL) {
		fprintf(stderr, "GenericArray_capacity: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return generic_array -> capacity;
}

unsigned long GenericArray_size(GenericArray* generic_array) {
	if (generic_array == NULL) {
		fprintf(stderr, "GenericArray_size: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	return generic_array -> size;
}

void GenericArray_free(GenericArray* generic_array) {
	if (generic_array == NULL) {
		fprintf(stderr, "GenericArray_free: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	free(generic_array -> array);
	free(generic_array);
}

void* GenericArray_get(GenericArray* generic_array, int i) {
	if (generic_array == NULL) {
		fprintf(stderr, "GenericArray_get: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	
	if (i >= generic_array -> size) {
		fprintf(stderr, "GenericArray_get: Index %d is out of the array bounds", i);
		exit(EXIT_FAILURE);
	}
	return generic_array -> array[i];
}

void GenericArray_check_and_realloc(GenericArray* generic_array) {
	if(generic_array -> size >= generic_array -> capacity) {
		generic_array -> array = (void**)realloc (generic_array -> array, 2* (generic_array -> capacity) * sizeof(void*));
		generic_array -> capacity *= 2;
	}
}


void GenericArray_insert(GenericArray* generic_array, void* element) {
	if(generic_array == NULL) {
		fprintf(stderr, "GenericArray_insert: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	
	if (element == NULL) {
		fprintf(stderr, "GenericArray_insert: element parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	
	GenericArray_check_and_realloc(generic_array);
	generic_array -> array[generic_array -> size] = element;
	generic_array -> size += 1;
	
	return;
}

void GenericArray_reverse(GenericArray* generic_array) {
	if (generic_array -> size == 0)
        return;
	
    int i;
    int j;
    for (i = 0, j = generic_array -> size - 1; i < (generic_array -> size - 1) / 2; i++, j--) {
        void* tmp = generic_array -> array[i];
        generic_array -> array[i] = generic_array -> array[j];
        generic_array -> array[j] = tmp;
    }
}


// SORTING FUNCTIONS

void Merge(GenericArray* generic_array, int l, int c, int r) {
	int i,j = 0;
	int k;
	int ll = (c-l)+1;
	int rr = r-c;
	
	void **left = malloc(ll *sizeof(void *));
	void **right = malloc(rr *sizeof(void *));

	if(generic_array == NULL) {
		fprintf(stderr, "Merge: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}	
	
	for (i = 0; i < ll; i++) {
		left[i] = (generic_array->array)[l + i];
	}
    	
  	for (j = 0; j < rr; j++) {
		right[j] = (generic_array->array)[c + 1 + j];
	  }
   		
    
    i = 0;
	j = 0;
  	k = l;
  	
  	while (i < ll && j < rr) {
    	if ((generic_array->compare)(left[i], right[j])) {
      	   (generic_array->array)[k] = left[i];
      	   i++;
    }
    else { (generic_array->array)[k] = right[j]; j++; }
    		k++;
 	 }

  	while (i < ll) {
    	(generic_array->array)[k] = left[i];
    	k++;
    	i++;
  	}

  	while (j < rr) {
   	 	(generic_array->array)[k] = right[j];
   	 	k++;
    	j++;
  	}

  	free(left);
  	free(right);
	
}

void MergeSort(GenericArray* generic_array, int low, int high)
{
	int m, size;

	if (low < high) {
		size = (high - low) + 1;
		if (size <= K) {
			InsertionSort(generic_array, low, high);
		}
		else {
		m = low + (high - low) / 2;

			MergeSort(generic_array, low, m);
			MergeSort(generic_array, m + 1, high);

			Merge(generic_array, low, m, high);
		}
  }
}

void InsertionSort(GenericArray* generic_array, int low, int high)  {
	int i = 0;
	int elem= 0;
	
	void* tmp;

	if(generic_array == NULL) {
		fprintf(stderr, "InsertionSort: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}	
	

  	for (i = low + 1; i <= high; i++) {
    	tmp = (generic_array->array)[i];
    	elem = BinarySearch(generic_array, low, i, tmp);

    	if (elem > high) {
      		fprintf(stderr, "InsertionSort: elem out of bounds of the array");
      	exit(EXIT_FAILURE);
    	}

    	if (elem < i) {
      		memmove((generic_array->array) + elem + 1, (generic_array->array) + elem, 
			  	sizeof(void *) * (i - elem));
			(generic_array->array)[elem] = tmp;
    }
  }
}

int BinarySearch(GenericArray* generic_array, int low, int high, void* element) {

	if(generic_array == NULL) {
		fprintf(stderr, "BinarySearch: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}	

	int m = low + ((high - low) / 2);
        
  	if (low == high)
    	return low;

 	if ((generic_array->compare)((generic_array->array)[m], element)) {
		 return BinarySearch(generic_array, m + 1, high, element);
	 }

    return BinarySearch(generic_array, low, m, element);

}

// HYBRID ALGORITHM
void Merge_Binary_InsertionSort(GenericArray* generic_array) {
	
	if(generic_array == NULL) {
		fprintf(stderr, "Merge_Binary_InsertionSort: generic_array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}	
	
	  if ((generic_array->size) <= K)
    	InsertionSort(generic_array, 0, (generic_array->size) - 1);
 	 else
    	MergeSort(generic_array, 0, (generic_array->size) - 1);
	
}

// COMPARATORS

int compare_string(void* elem1, void* elem2) {
  return strcmp(((char*)elem1),((char*) elem2));
}

int compare_int(void* elem1, void* elem2) {

  if (*((int*) elem1) == *((int*) elem2)) {
    return 0;
  }

  if (*((int*) elem1) < *((int*) elem2)) {
    return -1;
  }
  return 1;
}

int compare_float(void* elem1, void* elem2) {

  if (*((double*) elem1) == *((double*) elem2)) {
    return 0;
  }

  if (*((double*) elem1) < *((double*) elem2)) {
    return -1;
  }
  return 1;
}