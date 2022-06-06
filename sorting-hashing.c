#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

    printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);  //call by reference 
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)  //초기화 및 srand를 통해 배열에 임의의 값 지정
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;  //temp에 배열의 주소 저장해 활용

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;   

	return 0;
}

int freeArray(int *a)  //배열의 포인터
{
	if(a != NULL) //배열이 null이 아니라면
		free(a);  //메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {  //프리컨디션 조사
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) 
		printf("a[%02d] ", i);  //배열 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);  //배열 값 출력
	printf("\n");
}


int selectionSort(int *a)  //선택정렬 시간복잡도 O(n^2)
{
	int min;
	int minindex;  
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];  
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])  //기준점보다 값이 작으면
			{
				min = a[j];  // 기준위치에 저장
				minindex = j;  //인덱스 변경
			}
		}
		a[minindex] = a[i];  //새로운 기준위치 설정
		a[i] = min;  
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)  //삽입정렬 시간복잡도 O(n)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //삽입정렬의 특징, 두 번째 요소부터 접근
	{
		t = a[i];  
		j = i;
		while (a[j-1] > t && j > 0)  // 오른쪽 요소가 더 작으면
		{
			a[j] = a[j-1];  //왼쪽 요소와 교환한다.
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)  //버블정렬의 시간복잡도 O(n^2)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  //인접노드와 비교 및 변경 과정의 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])  //왼쪽 인덱스의 값이 더 크면 인접한 배열과 자리 교환  
			{
				t = a[j-1];  
				a[j-1] = a[j];  
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)  //삽입 정렬의 보완된 정렬, 시간 복잡도 O(n^1.25)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전의 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //두개의 배열로 나눔
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  //어느정도 정렬된 상태에서 삽입정렬 실시
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 이후 배열 출력

	return 0;
}

int quickSort(int *a, int n) //퀵 정렬 O(n^2) 
{//recursive하게 구현
	int v, t;
	int i, j;

	if (n > 1) //maxarraysize가 1보다 클 때, 배열에 데이터가 있을 때 
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1) //무한루프
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break; //탈출 조건, 
			t = a[i];
			a[i] = a[j];
			a[j] = t;  //값 교환
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;  //값 교환

		quickSort(a, i);  //교환된 매개로 재귀 호출
		quickSort(a+i+1, n-i-1);  //재귀 호출
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; 
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;  //해시테이블 포인터 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);  //메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  
		hashtable[i] = -1;  //해시함수 초기화


	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);  //테이블 출력


	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);

		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);  //내부값 출력

		if (hashtable[hashcode] == -1)  //내부 값이 없을 때
		{
			hashtable[hashcode] = key;  //해시테이블에 키값 대입
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)  // -1이 아닐 동안 반복문 동작
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //제산 함수 이용?

				printf("index = %d\n", index);

			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)  //서치 함수
{
	int index = hashCode(key);  //인덱스 = key % MAX_HASH_TABLE_SIZE

	if(ht[index] == key)  //if key % MAX_HASH_TABLE_SIZE == key
		return index;  //인덱스 반환

	while(ht[++index] != key) 
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; 
}



