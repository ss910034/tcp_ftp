#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>   
#include<math.h>
char code[260][30];
char code2[260];
char code3[30];
int num2[8];

void uncompress_file(FILE* fo,FILE* fw,int sum_bit,int count);
int  swap(int data);
int main(){   
    char c; 
    int num=0,j=0,i=0;
    int k=0,m=0,count2=0;
    int innum[10];
    int sum_bit=0,z=0;
    char in[20];
    char out[20];
    char cd[20];
    printf("Please enter your input filename.\n");
    scanf("%s",in);
    printf("Please enter your output filename.\n");
    scanf("%s",out);   
    FILE *fin= fopen(in,"rb");;   
    FILE *fout = fopen(out,"wb");   
    c = fgetc(fin);
    while(!feof(fin)){
        if( c == '#' )
            break;
        j=0;
        while( c!=' ' ){
            cd[j++] = c;
            c = fgetc(fin);
        }
        cd[j] = '\0';
        c = fgetc(fin);
        strcpy(code[z],cd);
        code2[z]=c;
        z++;
        c = fgetc(fin);
        c = fgetc(fin);
    }
    c = fgetc(fin);
    while(c!='#')
    {
        innum[k++] = c-'0';
        c = fgetc(fin);
    }
    for(k=k-1;k>=0;k--)
    {
        count2+=innum[k]*pow(10,m);
        m++;
    }
    k=0,m=0;
    for(i=0;i<10;innum[i++]=0);
    c = fgetc(fin);
    c = fgetc(fin);
    while(c!='#')
    {
        innum[k++] = c-'0';
        c = fgetc(fin);
    }

    for(k=k-1;k>=0;k--)
    {
        sum_bit+=innum[k]*pow(10,m);
        m++;
    }  
    uncompress_file(fin,fout,sum_bit,count2);
   
    return 0;  
} 

int  swap(int data)
{
    int i = 0;
    while(data)
    {
        num2[i++] = data%2;
        data = data/2;
    }
    return i;
}
void uncompress_file(FILE* fo,FILE* fw,int sum_bit,int count)
{
    char str[1000];
    int i,j,k,temp = 0;
    int index;
    int sum_bit2 = sum_bit;
    while(!feof(fo))
    {
      if(sum_bit2<0) break;
      sum_bit2 -=8;
      int data = fgetc(fo);
      if(data == -1) break;
      if(sum_bit2<0)
            index = 0-sum_bit2;
      else
          index = 0;
      if(data == -1) break;
      memset(num2,0,sizeof(num2));
      swap(data);
      i = temp;
      for(k=7;k>=index;i++,k--)
      {
          if(num2[k])
              str[i] = '1';
            else
              str[i] = '0';

          str[i+1] ='\0';
          for(j=0;j<count;j++)
          {
              if(strcmp(str,code[j])==0)
              {
                    
                    fputc(code2[j],fw);
                    fflush(fw);
                    j = count+1;
                    i = -1;
              }
          }
      }
      if(i)
            temp = i;
      else
            temp = 0;
    }
    sum_bit2 = 0;
    printf("解壓縮成功!\n");
    fclose(fw);
    fclose(fo);
}