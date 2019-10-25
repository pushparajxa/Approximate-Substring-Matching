#include<stdio.h>
void main(){
    char str[20],str2[20];
    int i,l=0,c=0,j,f=0,k;
printf("enter string:");
scanf("%s",str);
printf("enter substring:");
scanf("%s",str2);
for(i=0;str2[i]!='\0';i++){
    l++;
}
for(i=0;str[i]!='\0';i++){
    c++;
}
for(i=0;i<c;i++){
    if(str2[0]==str[i]){
            f=0;
        for(j=i,k=0;j<l+i,k<l;j++,k++){
            if(str2[k]==str[j]){
                f++;}}}
         if(f==l){
                printf("starting pos:%d",i+1);
                    break;
                }

}}
