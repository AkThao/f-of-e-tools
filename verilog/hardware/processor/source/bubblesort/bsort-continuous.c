#include "sf-types.h"
//#include "sh7708.h"
//#include "devscc.h"
//#include "print.h"
#include "bsort-input.h"


int
main(void)
{
while (1) {
	int i;
	int maxindex = bsort_input_len - 1;

	// copy the input to a new array
	uchar bsort_output[bsort_input_len];
	for (i=0; i<bsort_input_len; i++) {
		bsort_output[i] = bsort_input[i];
	}

	//print("\n\n[%s]\n", bsort_input);
	while (maxindex > 0)
	{
		for (i = 0; i < maxindex; i++)
		{
			if (bsort_output[i] > bsort_output[i+1])
			{
				/*		swap		*/
				bsort_output[i] ^= bsort_output[i+1];
				bsort_output[i+1] ^= bsort_output[i];
				bsort_output[i] ^= bsort_output[i+1];
			}
		}

		maxindex--;
	}
	//print("[%s]\n", bsort_input);
}
}
