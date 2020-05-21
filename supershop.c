#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

int bill_calc();

typedef struct{
    char name[20];
    int id;
    int price;
}product;

product pro[100];
int Total_product;

void print_product(product pro){
    printf("Product details:\n");
    printf("name: %s\n",pro.name);
    printf("id: %d\n",pro.id);
    printf("price: %d\n",pro.price);

}

void setproduct(char *str,int x){
    int i,j,k;
    char demo[3][20];
    for(i=0,j=0,k=0;i<strlen(str);i++,k++)
    {
        if(str[i]==','){
            demo[j][k]='\0';
            j++;
            k=-1;
            continue;
        }
        demo[j][k]=str[i];
    }
    demo[2][k]='\0';

    strcpy(pro[x].name,demo[0]);
    int id = atoi(demo[1]);
    pro[x].id = id;
    int p = atoi(demo[2]);
    pro[x].price = p;

}

int main()
{
    char userid[]="user";
    char pass[] = "123";

    FILE* fp;
    fp = fopen("product.txt","r");
    char str[100][1000],ch;
    int i=0,j=0;

    while(1){
        if((ch = fgetc(fp)) == EOF)
            break;
        if(ch=='\n'){
            i=0;
            j++;
            continue;
        }

        str[j][i++]=ch;
    }
    Total_product = j;

// make each product as a object of product struct..
    for(i=0;i<Total_product;i++)
        setproduct(str[i],i);

    int choice;

// ---- User login ----
    char user[10];
    char password[10];
    printf("Enter User id: ");
    scanf("%s",&user);
    printf("Enter password: ");
    int p = 0;
    do{
		password[p]=getch();
		if(password[p]!='\r'){
			printf("*");
		}
		p++;
	}while(password[p-1]!='\r');
	password[p-1]='\0';


    if(strcmp(user,userid)==0 && strcmp(pass,password)==0){
        printf("\n\t---Welcome to Pizza Hut---\n\n");
    }
    else{
        printf("\nuser login isn't correct!!\n");
        return 0;
    }

    printf("Enter 1 for add product:\n");
    printf("Enter 2 for for Cash Memo:\n");
    printf("Enter 3 for for Close the Program:\n\n");

    int products[20],amounts[20];
    int proid,amount,co=0;
    while(1){
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Product id: ");
                scanf("%d",&proid);
                printf("amount: ");
                scanf("%d",&amount);
                products[co]=proid;
                amounts[co]=amount;
                co++;
                break;
            case 2:
                if(co==0){
                    printf("No items sold yet!\n\n");
                    break;
                }
                bill_calc(products,amounts,co);
                co=0;
                printf("Enter 1 for add product:\n");
                printf("Enter 2 for for Cash Memo:\n");
                printf("Enter 3 for for Close the Program:\n\n");
                break;
            case 3:
                printf("\nClosing Pizza Hut......\n");
                exit(0);
            default:
                printf("Invalid choice..\n");
        }
    }

    return 0;
}

int bill_calc(int *products, int *amounts,int co){
    int Total_bill = 0,i,j,cash=0;
    float discounted = 0, discount=0;

    printf("\n-----------Cash Memo------------\n\n");
    printf("ID\tName\tCost\tQuantity\n");
    for(i=0;i<co;i++){
        int flag=0;
        for(j=0;j<Total_product;j++){
            if(products[i]==pro[j].id)
            {
                flag=1;
                //printf("%d\t%s\t%d\t%d\n",pro[j].id,pro[j].name,pro[j].price,amounts[i]);
                printf("%d",pro[j].id);
                printf("\t%s",pro[j].name);
                printf("\t%d",pro[j].price);
                printf("\t%d\n",amounts[i]);

                Total_bill+=pro[j].price*amounts[i];
            }
        }
        if(flag==0)
            printf("No such Product found for #product_id: %d\n",products[i]);
    }
    printf("\n");


    if(Total_bill>=10000){
        discounted = (double) Total_bill - .05*Total_bill;
        discount = .05*Total_bill;
    }
    else{
        discounted = (double) Total_bill;
    }

    printf("\tTotal Bill: %dtk\n",Total_bill);
    printf("\tDiscount: %.2ftk\n",discount);
    printf("\tPayment Bill: %.2ftk\n\n",discounted);

    while(1){
    printf("Cash received from customer: ");
    scanf("%d",&cash);
    float returnbill = 0;
    returnbill = cash - discounted;
    if(returnbill>=0){
        printf("Cash returned: %.2ftk\n\n", cash - discounted);
        printf("------------Thanks--------------\n\n\n");
        return 0;
    }
    else{
        printf("Insufficient Cash received.. Please Enter valid Cash:\n");
    }

    }





    //memset(amounts,0,20);
    //memset(products,0,20);

}
