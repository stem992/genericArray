#include "../Resources/unity.h"
#include "../include/generic_array.h"

#include <stdlib.h>
#include <malloc.h>

typedef struct _GenericArray GenericArray;

static void test_generic_array_create_zero_sized() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	
	TEST_ASSERT_EQUAL(0, GenericArray_size(generic_array));
	
	GenericArray_free(generic_array);
}

static void test_generic_array_not_null() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);	
	
	TEST_ASSERT_NOT_NULL(generic_array);
	
	GenericArray_free(generic_array);
}

static void test_generic_array_empty() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	
	TEST_ASSERT_EQUAL(1, GenericArray_empty(generic_array));
	
	GenericArray_free(generic_array);
}

static void test_generic_array_one_element() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	GenericArray_insert(generic_array, (int*) 1);
	
	TEST_ASSERT_EQUAL_INT(1, GenericArray_size(generic_array));
	
	GenericArray_size(generic_array);
}

static void test_generic_array_two_elements() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	GenericArray_insert(generic_array, (int*) 1);
	GenericArray_insert(generic_array, (int*) 5);
	
	TEST_ASSERT_EQUAL_INT(2, GenericArray_size(generic_array));
	
	GenericArray_size(generic_array);
}

static void test_generic_array_three_elements() {
	GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	GenericArray_insert(generic_array, (int*) 1);
	GenericArray_insert(generic_array, (int*) 5);
	GenericArray_insert(generic_array, (int*) 8);
	
	TEST_ASSERT_EQUAL_INT(3, GenericArray_size(generic_array));
	
	GenericArray_size(generic_array);
}

static void test_generic_array_ordered() {
	 GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	 GenericArray_insert(generic_array,(int*) 4);
	 GenericArray_insert(generic_array,(int*) 7);
	 GenericArray_insert(generic_array,(int*) 3);
	 GenericArray_insert(generic_array,(int*) 1);
	 GenericArray_insert(generic_array,(int*) 9);
	  
	 TEST_ASSERT_EQUAL(4, GenericArray_get(generic_array, 0));
     TEST_ASSERT_EQUAL(7, GenericArray_get(generic_array, 1));
     TEST_ASSERT_EQUAL(3, GenericArray_get(generic_array, 2));
     TEST_ASSERT_EQUAL(1, GenericArray_get(generic_array, 3));
     TEST_ASSERT_EQUAL(9, GenericArray_get(generic_array, 4));
     
	 GenericArray_free(generic_array);
	
}

static void test_generic_array_reverse() {
	 GenericArray* generic_array = GenericArray_create((GenericArrayCmp) compare_int);
	 GenericArray_insert(generic_array,(int*) 4);
	 GenericArray_insert(generic_array,(int*) 7);
	 GenericArray_insert(generic_array,(int*) 3);
	 GenericArray_insert(generic_array,(int*) 1);
	 GenericArray_insert(generic_array,(int*) 9);
	 
	 GenericArray_reverse(generic_array);
	  
     TEST_ASSERT_EQUAL(9, GenericArray_get(generic_array, 0));
     TEST_ASSERT_EQUAL(1, GenericArray_get(generic_array, 1));
     TEST_ASSERT_EQUAL(3, GenericArray_get(generic_array, 2));
     TEST_ASSERT_EQUAL(7, GenericArray_get(generic_array, 3));
     TEST_ASSERT_EQUAL(4, GenericArray_get(generic_array, 4));
     
	 GenericArray_free(generic_array);
	
}


int main() {
	UNITY_BEGIN();
	
	RUN_TEST(test_generic_array_create_zero_sized);
	RUN_TEST(test_generic_array_not_null);
	RUN_TEST(test_generic_array_empty);
	RUN_TEST(test_generic_array_one_element);
	RUN_TEST(test_generic_array_two_elements);
	RUN_TEST(test_generic_array_three_elements);
	RUN_TEST(test_generic_array_ordered);
	RUN_TEST(test_generic_array_reverse);
	
	UNITY_END();
	
	return 0;
}