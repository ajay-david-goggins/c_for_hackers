/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

// bruteforce logic
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

   *returnSize = 2; 
   int* returnArray = (int*) malloc(*returnSize * sizeof(int)); 
   
   for (int i = 0; i < numsSize - 1; i++) {
	   for (int j = i + 1; j < numsSize; j++) {
		   if (target == nums[i] + nums[j]) {
			   returnArray[0] = i;
			   returnArray[1] = j;
			   return returnArray;
		   }
	   }
   }
	
   free(returnArray);
   return NULL;
}

int main() {
	int n;
	printf("Enter the number : ");
	scanf("%d", &n);
	int arr[n];
	int returnsize;
	int target;
	int size = sizeof(arr) / sizeof(arr[0]);
	
	for (int i = 0; i < n; i++) {
		printf("Enter the value of a[%d]  : ", i );
		scanf("%d",&arr[i]);
	}

	printf("Enter the target number. it must be sum of two value in the array : ");
	scanf("%d", &target);

	int *ans = twoSum(arr, size, target, &returnsize); 

	if (ans != NULL) {
		printf("%d , %d ", ans[0], ans[1]);
		free(ans);
	} else {
		printf("Solution Not found.");
	}

	return 0;
}
