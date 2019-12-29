#include<stdio.h>
#include<string.h>
#define MAX 10000

 
 int validate(char num[]){
    int i=0;
 
    while(num[i]){
         if(num[i] < 48 || num[i]> 57)
		 {
             printf("Invalid positive integer: %s",num);
             return 1;
         }
         i++;
    }
 
    return 0;
}
 
char * division(char dividend[],long divisor, long int *remainder)
{
   
    static char quotient[MAX];
    long temp=0;
    int i=0,j=0;
 
    while(dividend[i]){
        
         temp = temp*10 + (dividend[i] - 48);
         if(temp<divisor){
            
             quotient[j++] = 48;
            
         }
         else{
             quotient[j++] = (temp / divisor) + 48;;
             temp = temp % divisor;
 
         }
         i++;
    }
 
    quotient[j] = '\0';
    *remainder = temp;
    return quotient;
}
 
int main(){
 
    char dividend[MAX],*quotient;
    long int divisor;
	long int remainder;
	setbuf(stdout, NULL);
    printf("Enter dividend: ");
    scanf("%s",dividend);
    if(validate(dividend))
         return 0;
 
    printf("Enter divisor: ");
    scanf("%ld",&divisor);
 
    quotient = division(dividend,divisor, &remainder);
 
    while(*quotient)
         if(*quotient ==48)
             quotient++;
         else
             break;
 
    printf("Quotient: %s / %ld  =  %s",dividend,divisor,quotient);
    printf ("\nRemainder: %ld",remainder);
    return 0;
}
 
