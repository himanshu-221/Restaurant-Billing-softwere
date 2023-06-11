#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void BillHeader(char CustomerName[50],char date[20]);
void BillBody(char itemName[],int Qty,float Price);
void BillFooter(float total);

struct item{
    char item[20];
    int qty;
    float price;
};

struct order{
    char customer[50];
    char date[20];
    int NoOfItem;
    struct item itm[];
};

int main()
{
    FILE *fp;
    float total=0;
    struct order ord;
    int itemNo,opt,invoicefound=0;
    char ch,name[50];
    printf("Choose operation you want to perform\n");
    printf("1. Genearte New Bill\n");
    printf("2. Show all invoice\n");
    printf("3. Search invoice\n");
    printf("4. Exit\n");
    printf("\nChoose your option:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch (opt)
    {
        case 1:
            printf("Enter customer name\t");
            fgets(ord.customer,50,stdin);
            ord.customer[strlen(ord.customer)-1]=0;
            strcpy(ord.date,__DATE__);
            printf("Enter number of item\t");
            scanf("%d",&itemNo);
            ord.NoOfItem=itemNo;
            for(int i=1;i<=itemNo;i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Enter item name %d:\t",i);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("Enter Quantity\t");
                scanf("%d",&ord.itm[i].qty);
                printf("Enter price\t");
                scanf("%f",&ord.itm[i].price);
                total+=ord.itm[i].qty*ord.itm[i].price;
            }
            BillHeader(ord.customer,ord.date);
            for(int i=1;i<=ord.NoOfItem;i++)
            {
                BillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);

            }
            BillFooter(total);
            printf("Do you want to save the bill [y/n]\n");
            scanf("%s",&ch);

            if(ch == 'y')
            {
            fp = fopen("RestaurantBill.text","a+");
            fwrite(&ord,sizeof(struct order),1,fp);
            if(fwrite != 0)
            {
                printf("\nSuccessfully saved");
            }
            else{
                printf("\nError saving");
            }
            fclose(fp);
            }
            break;
        case 2:
            fp=fopen("RestaurantBill.text","r");
            while(fread(&ord,sizeof(struct order),1,fp))
            {
                BillHeader(ord.customer,ord.date);
                for(int i=1;i<=ord.NoOfItem;i++)
                {
                    BillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                    total += (ord.itm[i].qty*ord.itm[i].price);
                }
                BillFooter(total);
            }
            fclose(fp);
            break;
        case 3:
             printf("\nEnter name of the customer: ");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            //system("clear");
            fp = fopen("RestaurantBill.text","r");
            while(fread(&ord,sizeof(struct order),1,fp))
            {
                if(!strcmp(ord.customer,name))
                {
                    BillHeader(ord.customer,ord.date);
                    for(int i=1;i<=ord.NoOfItem;i++)
                    {
                        BillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                        total += (ord.itm[i].qty*ord.itm[i].price);
                    }
                    BillFooter(total);
                    invoicefound=1;
                }
            }
            if(!invoicefound)
            {
                printf("Sorry invoice is not found for %s name",name);
            }
            fclose(fp);
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("invalid operation");
    }
    return 0;
}

void BillHeader(char CustomerName[50],char date[20])
{
    printf("\n\t\tABC Restaurant\n");
    printf("-------------------------------------------\n");
    printf("Date:- %s\n",date);
    printf("Invoice to:- %s\n",CustomerName);
    printf("-------------------------------------------");
    printf("\nItem \t\tQty.\t\tPrice\n");
    printf("___________________________________________\n");
}

void BillBody(char itemName[],int Qty,float Price)
{
    printf("%s\t\t%d\t\t%.2f\n",itemName,Qty,Qty*Price);
    
    
}

void BillFooter(float total)
{
    float dis = 0.1*total;
    float netTotal = total - dis;
    float CGST = total * 9/100, grandTotal = netTotal + 2*CGST;
    printf("-------------------------------------------\n");
    printf("Sub Toatal\t\t\t%.2f\n",total);
    printf("Discount @10%s\t\t\t%.2f","%",dis);
    printf("\n-----------------------------------------\n");
    printf("Net Total\t\t\t%.2f\n",netTotal);
    printf("CGST @9%s\t\t\t%.2f\n","%",CGST);
    printf("SGST @9%s\t\t\t%.2f","%",CGST);
    printf("\n-----------------------------------------\n");
    printf("Grand Toatal\t\t\t%.2f",grandTotal);
    printf("\n-----------------------------------------\n");
}
