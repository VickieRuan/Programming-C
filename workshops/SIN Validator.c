#include <stdio.h>

int main() {
	long long SIN_number = -1;
	int d1,d2,d3,d4,d5,d6,d7,d8,d9;
	int sum1,sum2,sum3,sum4;
	int digits_sum, digits_sum2, total, next_highest,diff;

	
	printf("SIN Validator\n");
	printf("==============\n");
    
	
	
	while (SIN_number == -1 || SIN_number != 0){
		printf("SIN (0 to quit): ");
		scanf("%lld", &SIN_number);
	    d1 = SIN_number / 100000000;
	    d2 = (SIN_number % 100000000) / 10000000;
	    d3 = (SIN_number % 10000000) / 1000000 ;
	    d4 = (SIN_number % 1000000) / 100000;
	    d5 = (SIN_number % 100000) / 10000;
	    d6 = (SIN_number % 10000) / 1000;
	    d7 = (SIN_number % 1000) / 100;
	    d8 = (SIN_number % 100) / 10;
	    d9 = (SIN_number % 10);
			    
	    sum1 = d2 + d2;
	    sum2 = d4 + d4;
		sum3 = d6 + d6;
	    sum4 = d8 + d8;
		digits_sum = (sum1/10) + (sum1%10) + (sum2/10) + (sum2%10) + (sum3/10) + (sum3%10) + (sum4/10) + (sum4%10);
	    digits_sum2 = d1 + d3 + d5 + d7;
		total = digits_sum + digits_sum2;
		next_highest = (total/10) * 10 + 10;
		diff = next_highest -  total;
		
		
		if (SIN_number == 0){
			printf("Have a Nice Day!\n");
		
		}else if (diff == d9){
		    printf("This is a valid SIN.\n");
		    
	    }else if (diff != d9){
		    printf("This is not a valid SIN.\n");
		 

		}
    }
	
    return 0;

}
