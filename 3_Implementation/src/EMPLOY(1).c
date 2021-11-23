#include<stdio.h>
#include<conio.h>

void insert_record();
void display_record();
void search_record();
void del_record();
void update_record();
void sort_record();

struct employee
{
    int emp_id;
    char name[40];
    int age;
    char designation[30];
    int salary;
};
    struct employee e;
int main()
{
    int ch;
    while(ch!=7)
    {
    printf("\t***********************************************\n");
    printf("\t\tWELCOME TO EMPLOYEE MANAGEMENT PROGRAM\n");
    printf("\t***********************************************\n\n\n");

	printf("\t**** AVAILABLE FUNCTIONALITIES ****\n\n\n");
	printf("\t\t1: Insert employee record\n");
	printf("\t\t2: Display employee record\n");
	printf("\t\t3: Search employee record\n");
	printf("\t\t4: Delete employee record\n");
	printf("\t\t5: Update employee record\n");
	printf("\t\t6: Sort employee record\n");
        printf("\t\t7: Exit\n\n");
        printf("\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                insert_record();
                break;
            case 2:
            display_record();
                break;

            case 3:
            search_record();
                break;

            case 4:
            del_record();
                break;
            case 5:
            update_record();
                break;
            case 6:
            sort_record();
                break;
	    case 7:
            default:
                printf("\n\t\tWrong choice Entered");
        }
        printf("\n\t\tPress any key to continue ");
        getch();
       }
}

void insert_record()
{
    FILE *fp;

    fp=fopen("emp.txt","ab+");

    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\t **** Previous Stored Data ****");
    display_record();

    printf("\n\n\t**** ENTER NEW EMPLOYEE DATA ****\n\n");
    printf("\n\t\tEnter Employee ID: ");
    scanf("%d",&e.emp_id);
    fflush(stdin);
    printf("\n\t\tEnter Employee Name: ");
    gets(e.name);
    printf("\n\t\tEnter Employee Age: ");
    scanf("%d",&e.age);
     fflush(stdin);
    printf("\n\t\tEnter Employee Designation: ");
    gets(e.designation);
    printf("\n\t\tEnter Employee Salary: ");
    scanf("%d",&e.salary);
    fwrite(&e,sizeof(e),1,fp);

    {
	printf("\n\n\t !!! Employee Record Inserted Sucessfully\n");
    }
    fclose(fp);
    printf("\n\t\t Updated Record !!\n");
    display_record();

}

void display_record()
{
    FILE *fp;
    fp=fopen("emp.txt","rb");

    if(fp==NULL)
    {
	printf("\n\t\tError : Cannot open the File !!!");
	return;
    }

    printf("\n\n\t **** Employee Details Are As Follows ****\n");
    printf("\nEmployee ID\tName of Employee\tAge\t\tDEsignation\tSalary\n\n");

    while(fread(&e,sizeof(e),1,fp)==1)
    {
	printf("%d\t%s\t%d  \t\t%s\t\t%d\n",e.emp_id,e.name,e.age,e.designation,e.salary);
    }
    fclose(fp);
}

void search_record()
{
    int id,flag=0;
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\tError: Cannot Open the File!!!");
        return;
    }
    printf("\n\n\tEnter Employee ID Which You Want To Search: ");
    scanf("%d",&id);
    while(fread(&e,sizeof(e),1,fp)>0 && flag==0)
    {
	if(e.emp_id==id)
	{
	flag=1;
	printf("\n\n\tSearch Sucessfull And Employee Records Is as Follows: \n\n");
	printf("\nEmployee ID\tName of Employee\tAge\t\tDEsignation\t\tSalary\n\n");
	printf("%d\t%s\t%d  \t\t%s\t\t%d\n",e.emp_id,e.name,e.age,e.designation,e.salary);
	}
    }
    if(flag==0)
    {
    printf("\n\n\t\tNo Such Record Found !!!!!\n");
    }
fclose(fp);
}

void del_record()
{
    int id,flag=0;
    FILE *fp,*ft;
    fp=fopen("emp.txt","rb");
    ft=fopen("emp1.txt","ab+");
    if(fp==NULL)
    {
	 printf("\n\t\tError: Cannot Open the File!!!");
	return;
    }
    printf("\n\t **** Previous Stored Data ****");
    display_record();
    printf("\n\n\tEnter Employee Id Which You Want to Delete ");
    scanf("%d",&id);
    while(fread(&e,sizeof(e),1,fp)>0 && flag==0)
    {
	if(e.emp_id==id)
	{
	flag=1;
	printf("\n\t\tRecord Deleted Sucessfully \n");

	}
	else
	{
	fwrite(&e,sizeof(e),1,ft);
	}
    }
    if(flag==0)
    {
    printf("\n\n\t\tNo Such Record Found !!!");
    }
    fclose(fp);
    fclose(ft);
    remove("emp.txt");
    rename("emp1.txt","emp.txt");
    printf("\n\t\t Updated Record !!\n");
    display_record();
}

void update_record()
{
    int id,flag=0;
    FILE *fp;
    fp=fopen("emp.txt","rb+");
    if(fp==NULL)
    {
	printf("\n\t\tError: Cannot Open the File!!!");
	return;
    }
    printf("\n\n\tEnter Employee ID Whose Record You Want To Update: ");
    scanf("%d",&id);
    printf("\n\t\t*** Previously Stored Record Of Given Employee ID ***");

    while(fread(&e,sizeof(e),1,fp)>0 && flag==0)
    {
	if(e.emp_id==id)
	{
	flag=1;

	printf("\n\t\t*** Now Enter the New Record ***\n\n");

	printf("\n\t\tUpdated Employee ID: ");
	scanf("%d",&e.emp_id);
	fflush(stdin);
	printf("\n\t\tUpdated Employee Name: ");
	gets(e.name);
	printf("\n\t\tUpdated Employee Age: ");
	scanf("%d",&e.age);
	printf("\n\t\tUpdated Employee Designation: ");
	gets(e.designation);
	printf("\n\t\tUpdated Employee Salary: ");
	scanf("%d",&e.salary);
	fseek(fp,-(long)sizeof(e),1);
	fwrite(&e,sizeof(e),1,fp);
	printf("\n\n\t\tRecord Updated Successfully Check The Display Section!!\n\t\t");
	}
    }
    if(flag==0)
    {
	printf("\n\t\tError : Something went wrong!!!");
    }
fclose(fp);
}
void sort_record()
{
    struct employee temp;
    struct employee arr[50];

    int i,j,k=0;
    FILE *fp;
    fp=fopen("stu.txt","rb");
    if(fp==NULL)
    {
	printf("\n\t\tError: Cannot Open File !!!\n");
    }
    i=0;

    while(fread(&arr[i],sizeof(arr[i]),1,fp)==1)
    {
	 i++;k++;
    }

    for(i=0;i<k;i++)
	{
	for(j=0;j<k-i-1;j++)
	 {
	    if(arr[j].emp_id>arr[j+1].emp_id)
	     {
	       temp=arr[j];
	       arr[j]=arr[j+1];
	       arr[j+1]=temp;
	     }
	  }
	}
	printf("\n\t\tAfter Sorting Employee Details !!\n\n");
	for(i=0;i<k;i++)
	{
	   printf("%d\t\t%s\t\t%d\t\t%s\t\t%d\n",arr[i].emp_id,arr[i].name,arr[i].age,
	   arr[i].designation,arr[i].salary);
	}
    fclose(fp);
}