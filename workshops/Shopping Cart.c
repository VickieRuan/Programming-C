#include <stdio.h>
#define MAX_ITEMS 10

// function prototypes
struct Item{
	  int sku_;
	  float price_;
	  int quantity_;
		};
void menu(void);
int validate(const int low, const int high);
void clear(void);
void displayInventory(const struct Item item[],const int size);
int searchInventory(const struct Item item[],const int sku_item, const int size);
void addItem(struct Item item[], int *size);
void checkPrice(const struct Item items[], const int size);

int main(){

		struct Item item[MAX_ITEMS]; //An array of Item representing the inventory
		int size = 0; //Number of items in the inventory. The inventory is initially empty.
		int select = -1;

        clear();
		printf("Welcome to the Shop\n");
		printf("====================\n");
	
        while(size <= MAX_ITEMS && select != 0){
	        menu();
	        select = validate(0, 4);
	        if(select == 0){
		        printf("Good bye!\n");
	        }else if(select == 1){
		        displayInventory(item, size);
	        }else if(select == 2){
		        addItem(item, &size); //this is the only function that may make change to the size
		    }else if(select == 3){
			    checkPrice(item, size);
		    }else if(select == 4){
			    clear();
		    }
	    }
        return 0;
}

        
// function definitions		
void menu(void){
	 printf("Please select from the following options:\n");
 	 printf("1) Display the inventory.\n");
 	 printf("2) Add to the inventory.\n");
     printf("3) Check price.\n");
	 printf("4) Clear Screen.\n");
     printf("0) Exit.\n");
}
int validate(const int low, const int high){
	int select = 0;
	printf("Please select from the following options: \n");
	printf("Select: ");
	scanf("%d", &select);
	while(select < low || select > high){
		printf("Invalid input, try again:");
		scanf("%d", &select);
	}
	return select;
}
void clear(){
	int i = 0;
	for (i = 0; i < 40 ; i++){
		printf("\n");
	}
}
void displayInventory(const struct Item item[],const int size){
	int i = 0;
	printf("Inventory\n");
	printf("==============================\n");
    printf("Sku      Price   Quantity\n");
	for (i = 0; i < size; i ++){
        printf("%d%10.2f%5d\n", item[i].sku_, item[i].price_,item[i].quantity_);
	}
    printf("==============================\n");
	
}
int searchInventory(const struct Item item[],const int sku_item, const int size){
       int flag = 0; 
       int i = 0;
       int j = 0;
 
	   for(i=0;i<size;i++){
	       if (item[i].sku_ == sku_item){
		              j = i;
		              i = size;
		           flag = 1;
	       }
	   }
	   if(flag == 0){
		   j = -1;
	   }
	   
    return j;
}
void addItem(struct Item item[], int *size){
	int temp_sku = 0;
	int temp_qty = 0;
	int j = 0;
	
	printf("Please input a SKU number: ");
	scanf("%d", &temp_sku);
	printf("Quantity: ");
	scanf("%d", &temp_qty);
	 
	j = searchInventory(item,temp_sku, *size);
	 
	if(j == -1){
		if(*size == MAX_ITEMS){
			printf("The inventory is full.\n");
		}else{
			
			printf("Price: ");
			scanf("%f", &item[*size].price_);
			item[*size].sku_ = temp_sku;
			item[*size].quantity_ = temp_qty;
			*size += 1;
			printf("The item is successfully added to the inventory.\n");
		}
	
	}else{
		item[j].quantity_ += temp_qty;
		printf("The item exists in the repository, quantity is updated\n");
	}
	
}
void checkPrice(const struct Item items[], const int size){
	int i = 0;
	int j = 0;
	int flag = 0;
	int temp_sku;
	printf("Please input the sku number of the item: ");
	scanf("%d", &temp_sku);
	for (i=0; i<size; i++){
		if(items[i].sku_ == temp_sku){
		    j = i;
			i = size;
		  flag=1;
		}
	}
	if(flag == 1){
		printf("Item %d costs $%.2f\n", items[j].sku_, items[j].price_); 
	}else{
		printf("Item does not exist in the shop! Please try again.\n");
	}
}



	                                                                                    