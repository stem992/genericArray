#include "../include/generic_array.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define BUFFSIZE 1024
#define COMPARESTRING compare_record_string
#define COMPAREINT compare_record_int
#define COMPAREFLOAT compare_record_float

typedef struct _GenericArray GenericArray;

typedef struct Record
{
  int id;
  char *field1;
  int field2;
  float field3;
} Record;

int compare_record_string(void* elem1, void* elem2) {
  if(elem1 == NULL) {
	fprintf(stderr, "compare_record_string: the first parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
  
  if(elem2 == NULL) {
	fprintf(stderr, "compare_record_string: the second parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
	
  Record *r1 = (struct Record *)elem1;
  Record *r2 = (struct Record *)elem2;
  return (strcmp(r1->field1, r2->field1) < 0);
 
}

int compare_record_int(void* elem1, void* elem2) {
  if(elem1 == NULL) {
	fprintf(stderr, "compare_record_string: the first parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
  
  if(elem2 == NULL) {
	fprintf(stderr, "compare_record_string: the second parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
  
  Record *r1 = (struct Record *)elem1;
  Record *r2 = (struct Record *)elem2;
  return (r1->field2 < r2->field2);

}

int compare_record_float(void* elem1, void* elem2) {
  if(elem1 == NULL) {
	fprintf(stderr, "compare_record_string: the first parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
  
  if(elem2 == NULL) {
	fprintf(stderr, "compare_record_string: the second parameter is a null pointer");
	exit(EXIT_FAILURE);
  }
  
  Record *r1 = (struct Record *)elem1;
  Record *r2 = (struct Record *)elem2;
  return (r1->field3 < r2->field3);

}

static void free_array(GenericArray* generic_array)
{
  int num_elements = GenericArray_size(generic_array), i;
  for (i = 0; i < num_elements; i++)
  {
    struct Record *array = (struct Record *)GenericArray_get(generic_array, i);
    free(array->field1);
    free(array);
  }
  GenericArray_free(generic_array);
}

static void print_array(GenericArray* generic_array)
{
  int num_elements = GenericArray_size(generic_array), i;
  for (i = 0; i < num_elements; i++)
  {
    struct Record *array = (struct Record *)GenericArray_get(generic_array, i);
    printf("%d, %s, %d, %f\n",array->id, array->field1, array->field2, array->field3);
  }
  
}

static void load_array(const char *filename, GenericArray* generic_array)
{
  char *read_line;
  char buffer[BUFFSIZE];
  FILE *fp;

  printf("READING FILE...\n");
  fp = fopen(filename, "r");
  
  if(fp == NULL) {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
   }
    
  while (fgets(buffer, BUFFSIZE, fp) != NULL) {
    read_line = malloc((strlen(buffer) + 1) * sizeof(char));
    
  if(read_line == NULL){
         printf("\nUnable to to allocate memory\n");
         printf("Please check if file exists and you have read privilege.\n");
         exit(EXIT_FAILURE);
    }
    strcpy(read_line, buffer);
    char *id_read_line = strtok(read_line, ",");
    char *string_read_line = strtok(NULL, ",");
    char *int_read_line = strtok(NULL, ",");
    char *float_read_line = strtok(NULL, ",");
    char *string_field = malloc((strlen(string_read_line) + 1) * sizeof(char));
    
    if (string_field == NULL){
         printf("\nUnable to to allocate memory\n");
         printf("Please check if file exists and you have read privilege.\n");
         exit(EXIT_FAILURE);
    }

    int read_id = atoi(id_read_line);
    strcpy(string_field, string_read_line);
    int read_field2 = atoi(int_read_line);
    float read_field3 = (float)atof(float_read_line);
    struct Record *record_p = malloc(sizeof(struct Record));
    
    if (record_p == NULL){
         printf("\nUnable to to allocate memory\n");
         printf("Please check if file exists and you have read privilege.\n");
         exit(EXIT_FAILURE);
    }

    record_p->id = read_id;
    record_p->field1 = string_field;
    record_p->field2 = read_field2;
    record_p->field3 = read_field3;

    GenericArray_insert(generic_array, (void *)record_p);
    free(read_line);
  }
  fclose(fp);
}

static void loadfunction(const char *filename, GenericArrayCmp compare)
{
  GenericArray* generic_array = GenericArray_create(compare);
  struct timeval start, stop;
  double secs = 0;

  gettimeofday(&start, NULL); //Start Timer
  load_array(filename, generic_array);
  gettimeofday(&stop, NULL); //End Timer
  secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  printf("\nFile loaded in : %0.2fs\n", secs);

  secs = 0;
  
  printf("\nPlease Wait.. Hybrid sort will be loaded soon..\n");
  gettimeofday(&start, NULL); //Start Timer
  Merge_Binary_InsertionSort(generic_array);
  gettimeofday(&stop, NULL); //End Timer
  secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
  print_array(generic_array);
  printf("\nOK, your array was ordered to: %0.2fs\n", secs);

  free_array(generic_array);
}


int main(int argc, char const *argv[])
{
  if (argc < 2) {
    printf("\nIncorrect number of arguments\n");
    exit(EXIT_FAILURE);
  }
  
	int algorithm;
	printf("\n");
	printf("How would you like to order your algorithm ?\n\n");
	printf("Type 1 to order by string \n");
	printf("Type 2 to order by int \n");
	printf("Type 3 to order by float \n");
	printf("Type 4 to order by string, by int and by float \n");
	printf("\nChoose a number : ");
	
	scanf("%d", &algorithm);
	    switch(algorithm) {
        case 1:
  		    loadfunction(argv[1], COMPARESTRING);	
  		    printf("Array ordered by string\n");
        break;

        case 2:
  		    loadfunction(argv[1], COMPAREINT);
  	    	printf("Array ordered by int\n");
        break;

        case 3:
  	    	loadfunction(argv[1], COMPAREFLOAT);
  	    	printf("Array ordered by float\n");
        break;
        
        case 4:
          loadfunction(argv[1], COMPARESTRING);	
          printf("Array ordered by string\n\n");

          loadfunction(argv[1], COMPAREINT);
          printf("Array ordered by int\n\n");

  		    loadfunction(argv[1], COMPAREFLOAT);
  	    	printf("Array ordered by float\n\n");
          
  	      printf("\nArray ordered by string, by int and by float\n");
        break;

        default:
            printf("YOU TYPED AN INCORRECT NUMBER\n");
            exit(-1);
        break;
    }

  return (EXIT_SUCCESS);
}