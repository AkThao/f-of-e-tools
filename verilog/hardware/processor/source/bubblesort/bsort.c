#include "sf-types.h"
//#include "sh7708.h"
//#include "devscc.h"
//#include "print.h"
#include "bsort-input.h"

#define BSORT_INPUT_LIST { \
        0x53, 0x69, 0x6e, 0x67, 0x20, 0x74, 0x6f, 0x20, 0x6d, 0x65, 0x20,\
        0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6d, 0x61, 0x6e,\
        0x2c, 0x20, 0x4d, 0x75, 0x73, 0x65, 0x2c, 0x20, 0x74, 0x68,\
        0x65, 0x20, 0x6d, 0x61, 0x6e, 0x20, 0x6f, 0x66, 0x20, 0x74,\
        0x77, 0x69, 0x73, 0x74, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20,\
        0x74, 0x75, 0x72, 0x6e, 0x73, 0x2e, 0x2e, 0x2e,\
}


int
main(void)
{
	// magic address to write to the processor's output pins
	volatile unsigned char* output_reg = (unsigned char*) 0x2000;
	// pull the output pins low before the work starts
	*output_reg = 0x00;

	// pull the output pins high while working
        *output_reg = 0xFF;
	for (int j=0; j<10; j++) {
		int i;
		int maxindex = bsort_input_len - 1;
		uchar bsort_input[] = BSORT_INPUT_LIST;
		while (maxindex > 0)
		{
			for (i = 0; i < maxindex; i++)
			{
				if (bsort_input[i] > bsort_input[i+1])
				{
					/*		swap		*/
					bsort_input[i] ^= bsort_input[i+1];
					bsort_input[i+1] ^= bsort_input[i];
					bsort_input[i] ^= bsort_input[i+1];
				}
			}

			maxindex--;
		}
	}
	// work done, pull the outputs low again
	*output_reg = 0x00;

	return 0;
}
