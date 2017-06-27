#include <stdio.h>

struct account{
	int acctNumber;
	double balance;
	
};

double balanceUp(double balance, double amount); 
double interestCalc(double balance, double rate);
double balanceDown(double balance, double amount);


int main() {
  
	int select = 0;
   int i = 0;
   int j = 0;
   int temp = 0;
   int flag = 0;
   double rate = 0;            //use for case 3
   double calcInterest = 0;    // use for case 3
   double service_charge = 0;  // use for case 4
   // initialize 5 savings accounts
	struct account acct[5] = {     {11111111, 123.45},
                                  {22222222, 12365.50},
                                  {33333333, 0},
                                  {44444444, 1475},
                                  {55555555, 25000.65}
                            };
                           
	printf("***** Welcome to Savings Account Banking*****\n\n");
	
   do {
	      printf("1.) Deposit\n");
         printf("2.) Withdraw\n");
         printf("3.) Apply monthly interest earnings to all accounts\n");
         printf("4.) Apply service charges to all accounts\n");
         printf("5.) Account Summary\n");
         printf("0.) Log out\n\n");
         printf("Please enter an option to continue: ");
         scanf("%d", &select);
         printf("\n");
         switch (select){
	          case 1:
		            printf("-- Make a deposit --\n\n");
		            printf("Enter account number: ");
		            scanf("%d", &temp); 
		
		            for(i=0;i<5;i++){
                      flag = 0;
			             if(acct[i].acctNumber == temp){
			                 flag = 1;
                          j = i;
			                 i = 4;
			             } 
			         }
			         if (flag == 0){
				          printf("ERROR: Account number does not exist.\n\n");
				      }else if(flag == 1){
					       double amount = 0;
					       printf("Enter amount to deposit (CAD): ");
					       scanf("%lf", &amount);
					       acct[j].balance = balanceUp(acct[j].balance, amount);
					       printf("The current balance is %.2lf\n\n", acct[j].balance);
				      }
				      break;
				
             case 2:
	              printf("-- Withdraw funds --\n\n");
	              printf("Enter account number: ");
	              scanf("%d", &temp); 
	              for(i=0;i<5;i++){
                     flag = 0;
		               if(acct[i].acctNumber == temp){
		                   flag = 1;
                         j = i;
		                   i = 4;
		               }
		           }
		           if(flag == 0){
			             printf("ERROR: Account number does not exist.\n\n");
			        }else if(flag == 1){
				         double withdraw = 0;
				         printf("Enter amount to withdraw (CAD): ");
				         scanf("%lf", &withdraw);
				         if(withdraw > acct[j].balance){
					          printf("Withdrawal failed. You only have %.2lf in your account\n\n", acct[j].balance);
				         }else{
					          acct[j].balance = balanceDown(acct[j].balance,withdraw);
				             printf("Current balance is: %.2lf\n\n", acct[j].balance);
			            }
			        }
			        break;
			         
	         case 3:
		         printf("-- Add monthly interest earnings to all accounts --\n\n");
		         printf("Account#  New Balance  Interest Earnings (M)\n");
		         printf("-------   -----------  ---------------------\n");
		         for(i = 0; i< 5; i++){
			      
			          if(acct[i].balance <= 500){
				           rate = 0.99;
				       }else if(acct[i].balance > 500 && acct[i].balance <= 1500){
					        rate = 1.66;
					    }else{
						     rate = 2.49;
				       }
				       calcInterest = interestCalc(acct[i].balance,rate);
				       acct[i].balance = balanceUp(acct[i].balance, calcInterest);
				       printf("%8d%11.2lf%21.2lf\n", acct[i].acctNumber,acct[i].balance,calcInterest);
		         }
		         printf("\n");
		         break;
              
             case 4:
	                printf("-- Apply service charges to all accounts --\n\n");
	                printf("Account#  New Balance  Service charges (M)\n");
	                printf("--------  -----------  -------------------\n");
	                for(i=0; i<5;i++){
		                 if(acct[i].balance <= 1500){
			                  service_charge = 7.5;
			              }else{
				               service_charge = 2.50;
				           }
				           acct[i].balance = balanceDown(acct[i].balance, service_charge);
				           printf("%8d%11.2lf%19.2lf\n", acct[i].acctNumber,acct[i].balance,service_charge);
		             }
		             printf("\n");
		             break;
	                
	         case 5:
		            printf("-- Account information --\n\n");
		            printf("Account#  Balance\n");
		            printf("--------  ----------\n");
		            for (i=0;i<5;i++){
			            printf("%8d%10.2lf\n", acct[i].acctNumber, acct[i].balance);
			        }
			        printf("\n");
			        break;

	         default:
		             if(select != 0){
			             printf("Error, this is not a valid option.\n\n");
		             }
   
         }
	
    }while(select != 0);
    
    return 0;    	
}

/* function definitions */
double balanceUp(double balance, double amount){
   double result = 0;
	if(amount > 0){
		result = balance + amount;
	}else{
		result = balance;
	}		
   return result;
}
	
double interestCalc(double balance, double rate){
	return balance * (rate/100);
}

double balanceDown(double balance, double amount){
   double result = 0;
	if (amount > 0){
		result = balance - amount;
	}else{
		result = balance;
	}
   return result;
}

