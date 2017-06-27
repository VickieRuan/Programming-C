#include <stdio.h>
#include <string.h>
 
struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};


/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
 
#define MAX_QTY 		999
#define SKU_MAX 		999
#define SKU_MIN 		100

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

int yes(void);  // ms2
void GrocInvSys(void);  // ms2
int menu(void);  // ms2

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
const double TAX = 0.13;

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);



/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/


#define MAX_ITEM_NO 500   
#define DATAFILE "items.txt" 

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
	 TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR                                                      
		 TT       EE         SS             TT       EE          RR     RR          
		 TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
		 TT       EE               SS       TT       EE          RR  RR
		 TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:
void prnFile() {
	FILE* tp = fopen("test.txt", "r");
	char ch;
	if (tp) {
		for (; fscanf(tp,"%c", &ch) == 1; putchar(ch));
		fclose(tp);
	}
	else {
		printf("text.txt not found\n");
	}
} 
int main(void) {
	int i, n;
	struct Item GI[3] = {
		{ 4.4,275,0,10,2,"Royal Gala Apples" },
		{ 5.99,386,0,20,4,"Honeydew Melon" },
		{ 3.99,240,0,30,5,"Blueberries" },
	};
 
	struct Item I;
	struct Item IN[3];
	printf("***********Testing saveItem:\n");
	printf("Your saveItem saved the following in test.txt: \n");
	FILE* tp = fopen("test.txt", "w");
	if (tp) {
		for (i = 0; i < 3; i++) saveItem(GI[i], tp);
		fclose(tp);
		prnFile();
	}
	printf("*******************************\nThey have to match the following:\n");
	printf("275,10,2,4.40,0,Royal Gala Apples\n");
	printf("386,20,4,5.99,0,Honeydew Melon\n");
	printf("240,30,5,3.99,0,Blueberries\n");
	printf("***********END Testing saveItem!\n\n\n");
	pause();
	printf("***********Testing loadItem:\n");
	printf("Your loadItem loaded the following from test.txt: \n");
	tp = fopen("test.txt", "r");
	if (tp) {
		for (i = 0; i < 3; i++) {
			loadItem(&I, tp);
			dspItem(I, LINEAR);
		}
		fclose(tp);
		tp = fopen("test.txt", "w");
		fclose(tp);
	}
	printf("*******************************\nThey have to match the following:\n");
	printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
	printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
	printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
	printf("***********END Testing loadItem!\n\n\n");
	pause();
	printf("***********Testing saveItems:\n");
	printf("Your saveItems saved the following in test.txt: \n");
	saveItems(GI, "test.txt", 3);
	prnFile();
	printf("*******************************\nThey have to match the following:\n");
	printf("275,10,2,4.40,0,Royal Gala Apples\n");
	printf("386,20,4,5.99,0,Honeydew Melon\n");
	printf("240,30,5,3.99,0,Blueberries\n");
	printf("***********END Testing saveItems!\n\n\n");
	pause();
	printf("***********Testing loadItems:\n");
	printf("Your loadItems loaded the following from test.txt: \n");
	loadItems(IN, "test.txt", &n);
	for (i = 0; i < n; i++) {
		dspItem(IN[i], LINEAR);
	}
	printf("*******************************\nThey have to match the following:\n");
	printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
	printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
	printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
	printf("***********END Testing loadItems!\n\n\n");
	pause();
	printf("Done!\n"); 
	return 0;
} 
/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here:*/
int main(void) {
    GrocInvSys();
    return 0;
}
/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/
void saveItem(struct Item item, FILE* dataFile){
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n",item.sku,item.quantity,item.minQuantity,item.price,item.isTaxed,item.name);
}
int loadItem(struct Item* item, FILE* dataFile){
	int result = 0;
	fscanf(dataFile, "%d,%d,%d,%lf,%d,%[^\n]\n", &item->sku,&item->quantity,&item->minQuantity,&item->price,&item->isTaxed,item->name);
    result = 1;
	return result;
}
int saveItems(struct Item* item, char fileName[], int NoOfRecs){
	int i = 0;
	int result = 0;
	FILE *fp;
	fp = fopen(fileName, "w");
	if(fp){
		for(i=0;i<NoOfRecs;i++){
		    saveItem(item[i], fp);
	    }
	    fclose(fp);
	    result = 1;
	}else{
		printf("Cannot open file\n");

	}
	
	return result;
}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){
	int i = 0;
	int result = 0;
	char ch;
	FILE *fp;
	fp = fopen(fileName, "r");
	*NoOfRecsPtr = 0;
    while((ch = fgetc(fp))!= EOF ){
	    if(ch == '\n'){
	        *NoOfRecsPtr += 1;
	    }
    }
    rewind(fp);
   
	if(fp){
		for(i=0;i<*NoOfRecsPtr;i++){
			loadItem(&item[i], fp);
		}
		fclose(fp);
		result = 1;
	}else{
		printf("Cannot open file\n");
	}
	return result;
}

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/
void welcome(void){
		printf("---=== Grocery Inventory System ===---\n\n");
	}
void prnTitle(void){
		printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
		printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
	}
void prnFooter(double gTotal){
		printf("--------------------------------------------------------+----------------\n");
		if (gTotal > 0){
			
			printf("                                           Grand Total: |%12.2lf\n", gTotal);
		}
	}
void clrKyb(void){
    while(getchar() != '\n');
    
	/*getchar is a function that reads a single character form the stdin,and returns it to the program.*/
    }

void pause(void){
	 
		printf("Press <ENTER> to continue...");
		clrKyb();
	}

int getInt(void){
		char NL = 'x';
		int Value = 0;
		while( NL != '\n'){
			scanf("%d%c", &Value,&NL);
		    if(NL != '\n'){
			    clrKyb(); 
			    printf("Invalid integer, please try again: ");
		    }
		}
		return Value; 
	}

int getIntLimited(int lowerLimit, int upperLimit){
		int Value = -1;
		while(Value < lowerLimit || Value > upperLimit){
		    Value = getInt();
		    if(Value < lowerLimit || Value > upperLimit){
			    printf("Invalid value, %d <= value <= %d: ", lowerLimit, upperLimit);
			}
		}
	    return Value;
	}
double getDbl(void){
		char NL = 'x';
	    double Value = 0;
		while( NL != '\n'){
			scanf("%lf%c", &Value,&NL);
			if(NL != '\n'){
			    clrKyb(); 
				printf("Invalid number, please try again: ");
			}
		}
	    return Value; 
	}

double getDblLimited(double lowerLimit, double upperLimit){
		double Value = 0;
		while(Value < lowerLimit || Value > upperLimit){
			Value = getDbl();
			if(Value < lowerLimit || Value > upperLimit){
				printf("Invalid value, %lf <= value <= %lf: ", lowerLimit, upperLimit);
			}
		}
		return Value;	
}
void search(const struct Item item[], int NoOfRecs) {
	    int temp_sku;
		int searchIndex=0;
		int itemFound;
	 
	 
		printf("Please enter the SKU: ");
		scanf("%d", &temp_sku);
	 
		itemFound = locateItem(item, NoOfRecs, temp_sku, &searchIndex);
		if(itemFound == 0){                  
			printf("Item not found!\n");
		}else if(itemFound == 1){
			dspItem(item[searchIndex], FORM);
		}	
	}

void updateItem(struct Item* itemptr) {
		struct Item temp;
		int result = 0;
		
		printf("Enter new data:\n");
		temp = itemEntry(itemptr->sku);
		printf("Overwrite old data? (Y)es/(N)o: ");
		result = yes(); 
		if(result == 1){
			*itemptr = temp;
			 
			printf("--== Updated! ==--\n");
		}else{
			printf("--== Aborted! ==--\n");
		}
	}

void addItem(struct Item item[], int *NoOfRecs, int sku) {
	    struct Item temp;
	    int flag = 0;
		int result = 0;
	 	if(*NoOfRecs == MAX_ITEM_NO){
			printf("Can not add new item; Storage Full!\n");
		
		}
 
	    while(*NoOfRecs < MAX_ITEM_NO && flag == 0){
				  
			    temp = itemEntry(sku);
				
				printf("Add Item? (Y)es/(N)o: ");
			    result = yes();
			    if(result == 1){
				    printf("--== Added! ==--\n");
	 
					item[*NoOfRecs] = temp;
				    *NoOfRecs += 1;
				    flag = 1;
			    
				}else{
				    printf("--== Aborted! ==--\n");
				    flag = 1;
				}
			}
		}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
		int temp_sku;
		int sku_index=0;
		int ifFound = 0;
		int ifYes = 0;
		struct Item temp;
		printf("Please enter the SKU: ");
		temp_sku = getIntLimited(SKU_MIN,SKU_MAX);
		ifFound = locateItem(item, *NoOfRecs, temp_sku, &sku_index);
		temp = item[sku_index];
	  
		if(ifFound == 1){
			dspItem(temp, FORM);
			printf("Item already exists, Update? (Y)es/(N)o: ");
			ifYes = yes();
			if(ifYes == 1){
				updateItem(&item[sku_index]);
				 
			}else{
				printf("--== Aborted! ==--\n");
			}
		}else if(ifFound == 0){
			addItem(&item[sku_index], NoOfRecs, temp_sku);
	 
		}
	}
	 
void adjustQty(struct Item item[], int NoOfRecs, int stock) {
		int temp_sku;
		int index = 0;
	    int	ifFound = 0;
	    int stock_qty=0;
	    int checkout_qty=0;
	    int ifLow = 0;
		printf("Please enter the SKU: ");
		scanf("%d", &temp_sku);
		ifFound = locateItem(item, NoOfRecs, temp_sku, &index);
		if(ifFound == 1){
			dspItem(item[index], FORM);
			if(stock == STOCK){
				printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ","to stock", MAX_QTY-item[index].quantity);
				stock_qty = getIntLimited(0, MAX_QTY-item[index].quantity);
				if (stock_qty == 0){
					printf("--== Aborted! ==--\n");
				}else{
					item[index].quantity += stock_qty;
					printf("--== Stocked! ==--\n");
					
				}
			}else if(stock == CHECKOUT){
				printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ","to checkout",item[index].quantity);
				checkout_qty = getIntLimited(0, item[index].quantity);
				if (checkout_qty == 0){
					printf("--== Aborted! ==--\n");
				}else{
					item[index].quantity -= checkout_qty;
					printf("--== Checked out! ==--\n");
				}
            }
		}else if(ifFound == 0){
			printf("SKU not found in storage!\n");
			clrKyb();
		}
		ifLow = isLowQty(item[index]);
		if(ifLow==1){
			printf("Quantity is low, please reorder ASAP!!!\n");
		}
		 
}
	/*End of Milestone 4 functions
	******************************************************************/

	/*****************************************************************
	Milestone 3 function implementations:
	Please copy your milestone 3 functions here: */

double totalAfterTax(struct Item item){
		double total = 0;
		if(item.isTaxed == 1){
			total = (item.price * item.quantity) * (1+TAX);		
		}else if(item.isTaxed == 0){
			total = item.price * item.quantity;
		}
		return total;	
	}
int isLowQty(struct Item item){
		int result = 0;
		if(item.quantity <= item.minQuantity){
			result = 1;
		}
		return result;
	}
struct Item itemEntry(int sku){
		struct Item I;
		 
		I.sku = sku;
		printf("        SKU: %d\n",sku);
	    printf("       Name: ");
	    scanf("%20[^\n]" , I.name);
	    printf("      Price: ");
	    I.price = getDblLimited(0.01, 1000.00);
	    printf("   Quantity: ");
	    I.quantity = getIntLimited(1, MAX_QTY);
	    printf("Minimum Qty: ");
	    I.minQuantity = getIntLimited(0, 100);
	    printf("   Is Taxed: ");
	    I.isTaxed = yes();
	    return I;
	    
	}
void dspItem(struct Item item,int linear){
		char result[4];
		char lowquantity[4];
		if(item.isTaxed == 1){
			strcpy(result,"Yes");
			if(isLowQty(item) == 1){
				strcpy(lowquantity,"***");
			}else{
				strcpy(lowquantity,"");
			}
		}else if(item.isTaxed == 0){
			strcpy(result, "No");
			if(isLowQty(item) == 1){
				strcpy(lowquantity,"***");
			}else{
				strcpy(lowquantity,"");
			}
		}
		 
		if(linear == 1){
			        
			printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|%s\n",item.sku,item.name,item.price,result,item.quantity,item.minQuantity,totalAfterTax(item),lowquantity);
		}else if(linear==0 && isLowQty(item) == 1){
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
		    printf("      Price: %.2lf\n", item.price);
		    printf("   Quantity: %d\n", item.quantity);
		    printf("Minimum Qty: %d\n", item.minQuantity);
		    printf("   Is Taxed: %s\n", result);
		    printf("WARNING: Quantity low, please order ASAP!!!\n");
		
		}else if(linear == 0){
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2lf\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: %s\n", result);
		} 	     	    
	}
void listItems(const struct Item item[], int NoOfItems){
		int i = 0;
		double total_aftertax = 0;
		double grand_total = 0;
		prnTitle();
		for(i = 0; i<NoOfItems;i++){
			printf("%-4d",i+1);
			dspItem(item[i], 1);
			total_aftertax = totalAfterTax(item[i]);
			grand_total += total_aftertax;
		}
		  
		prnFooter(grand_total);
	}
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index){
		int i = 0;  //true value
		int flag = 0;
		int result = 0;
		for(i=0;i < NoOfRecs;i++){
			if (item[i].sku == sku){
			    flag = 1;
			    *index = i;
			    i = NoOfRecs;
			}
		}
		if(flag == 1){
			result = 1;
		}else if(flag == 0){
			result = 0;
		}
		return result;
	}
	
int yes(void){
		    char CH;
			int RET = 0;
		    do{
		
		        CH = getchar();
				clrKyb();
				if ((CH != 'Y' && CH != 'y') && (CH != 'N' && CH != 'n')){
			        printf("Only (Y)es or (N)o are acceptable: ");
				}else if(CH == 'y' || CH == 'Y'){
				    RET = 1;
				}else if(CH == 'n' || CH == 'N'){
					RET = 0;
				}
				
				}while ((CH != 'Y' && CH != 'y') && (CH != 'N' && CH != 'n'));
				
			return RET;
		}
int menu(void){
			int select = 0;
			printf("1- List all items\n");
			printf("2- Search by SKU\n");
			printf("3- Checkout an item\n");
			printf("4- Stock an item\n");
			printf("5- Add new item or update item\n");
			printf("0- Exit program\n");
			printf("> ");
			select = getIntLimited(0,5);
			return select;
		}
void GrocInvSys(void){
			int DONE = 0;
			int SEL = 0;
			struct Item array[MAX_ITEM_NO];
			int i = 0;
			int flag = 0;
 
			welcome();
			
			flag = loadItems(array, DATAFILE, &i);
      
			if(flag == 0){
				printf("Could not read from %s.\n",DATAFILE);
			}else{
				while(DONE == 0){

				    SEL = menu();
				    switch(SEL){
					    case 1:
						    listItems(array, i);
						    pause();
						    break;
					    case 2:
					    	 
					        search(array, i);
					        clrKyb();
					        pause();
						    break;
					    case 3:
     
					        adjustQty(array, i, CHECKOUT);
					        flag = saveItems(array, DATAFILE, i);
					        if(flag == 0){
						        printf("Could not update data file %s\n",DATAFILE);
					        }
					    
						    pause();
						    break;
					    case 4:
						 
						    adjustQty(array, i, STOCK);
						    flag = saveItems(array, DATAFILE, i);
						    if(flag == 0){
							    printf("Could not update data file %s\n",DATAFILE);
						    }
						   
						    pause();
						    break;
					    case 5:
						    addOrUpdateItem(array, &i);
		                  
						    flag = saveItems(array, DATAFILE, i);
						    if(flag == 0){
							    printf("Could not update data file %s\n",DATAFILE);
						    }
						    
						    pause();
						    break;
					    case 6:
						    printf("Delete Item!\n");
						    printf("Not implemented!\n"); 
						    pause();
						    break;
					    case 7:
					    	printf("Search by name!\n");
					        printf("Not implemented!\n");
						    pause();
						    break;
					    default:
						    printf("Exit the program? (Y)es/(N)o): ");
						    DONE = yes();
			    }
			}	
		}
}
			

 




/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output
***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!
Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!
Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!
Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!
Press <ENTER> to continue...
Done!
*/
