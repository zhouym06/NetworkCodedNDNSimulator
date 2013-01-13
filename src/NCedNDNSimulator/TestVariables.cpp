
#include "Tests.h"



		
	int len				= 10;
	int	level			= 5;
	int	tree_degree		= 2;
/**/
	//for all k
	int request_num				= 10000;
	int content_num_s[3]		= {10, 100, 1000};
	int content_num_l			= 3;
	int slice_per_content_s[1]	= {10};
	int slice_per_content_l		= 1;

	int k_s[10]					= {1,2,3,5,6,7,8,9,10};
	int k_l						= 10;

	

	/*

	//for little cache
	int request_num				= 10000;
	int content_num_s[1]		= {100};
	int content_num_l			= 1;
	int slice_per_content_s[1]	= {10};
	int slice_per_content_l		= 1;

	int k_s[1]					= {1000};
	int k_l						= 1;

*/
/*

	//for fig1
	int request_num				= 1000;
	int content_num_s[3]		= {10, 100, 1000};
	//int content_num_s[3]		= {100};
	int content_num_l			= 3;

	int slice_per_content_s[1]	= {10};
	int slice_per_content_l		= 1;

	int k_s[1]					= {10000};
	int k_l						= 1;

	*/