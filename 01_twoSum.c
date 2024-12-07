/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
   *returnSize = 2; 
   int* returnArray = (int*) malloc(*returnSize * sizeof(int)); 
   
   for (int i = 0; i < numsSize - 1; i++) {
	   for (int j = i + 1; i < numsSize; j++) {
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
	int arr[] = {7, 2, 8, 6};
	int target = 9;
	int size = sizeof(arr) / sizeof(arr[0]);
	int returnsize;	
	int *ans = twoSum(arr, size, target, &returnsize); 
	if (ans != NULL) {
		printf("%d , %d ", ans[0], ans[1]);
		free(ans);
	} else {
		printf("Solution Not found.");
	}

	return 0;
}
