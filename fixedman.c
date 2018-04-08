#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>    
struct haffNode{  
    int weight; 
    int data;   
    struct haffNode *leftChild;
    struct haffNode *rightChild;   
};
typedef struct haffNode hn;   
char code[260][50]={{}};
int code2[260];
char code3[260][50]={{}};
hn left[260]; 
hn right[260];  
void compress_file(char* in,FILE* fout,int count);

void fixedcode(int ascii,int length,int sum){
    char fcode[9]={'\0'};
    int i,r;
    for(i=length-1;i>=0;i--){
        if(sum%2)
            fcode[i]='1';
        else
            fcode[i]='0';
        sum /=2;
    }
    strcpy(code[ascii],fcode);
}
int main(){  
    int ascii[260]={0};
    char temp[3000];   
    char c,sign='#'; 
    int filesize=0;   
    int zsize=0,i;    
    int count=0;   
    hn node[260];
    char in[20];
    char out[20];
    printf("Please enter your input filename.\n");
    scanf("%s",in);
    printf("Please enter your output filename.\n");
    scanf("%s",out);   
    FILE *fin = fopen(in,"rb"); 
    FILE *fout = fopen(out,"wb");  
  
    fseek(fin, 0, SEEK_END);
    filesize = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    int a,len=1;
    while((a=fgetc(fin))!=EOF){   
        ascii[a]++;  
        if(ascii[a] == 1)
            count++;
    }   
    for(i=1;i<=8;i++){
        if(len >= count)
            break;
        else
            len *=2;
    }
    len = i-1;
    int l = 0, result = 0;
     for(i=0; i<256; i++){  
         if(ascii[i]!=0){  
             fixedcode(i,len,l);
             l++;
         }  
     }  
    fclose(fin);
    l=0;
    for(i=0;i<256;i++){
        
        if(code[i][0]=='0' || code[i][0]=='1' ){   
            fprintf(fout,"%s %c ",code[i],i);    
            result+=ascii[i] * strlen(code[i]);
            code2[l] = i;
            strcpy(code3[l],code[i]);
            l++;
        }
    }
        
    fprintf(fout,"%c",sign);
    fprintf(fout,"%d",count);
    fprintf(fout,"%c",sign);
    fprintf(fout,"%c",sign);
    fprintf(fout,"%d",result);
    fprintf(fout,"%c",sign);

    compress_file(in,fout,count);     

    return 0;  
    }   
void compress_file(char* in,FILE* fout,int count)
{
    FILE* fo = fopen(in,"rb"); 
    int i,sum = 0,flag = 0,j,k = 0;
    int bits[1000];
    memset(bits,0,1000*sizeof(int));
    
    int bytes = 0;
    // int sum_bytes = getSumBytes();
    while(!feof(fo))
    {
        sum = 0;
        int a = fgetc(fo);
        for(i=0;i<=count;i++)
        {
            if(code2[i] == a)
            {
                
                flag+=strlen(code3[i]);
                int len = strlen(code3[i]);
                if(flag<8)
                {
                    for(j=0;j<len;j++)
                        bits[k++] = code3[i][j]-'0';
                }
                else if(flag>=8)
                {
                    for(j=0;k<8;j++)
                      bits[k++] = code3[i][j]-'0';
                    for(;j<len;j++)
                      bits[k++] = code3[i][j]-'0';
                    sum+=bits[0]*128+bits[1]*64+bits[2]*32+bits[3]*16+bits[4]*8+bits[5]*4+bits[6]*2+bits[7]*1;
                    for(j=0;j<8;j++)
                      bits[j] = 0;
                    for(j=8;j<k;j++)
                      bits[j-8] = bits[j];
                    k = flag = j-8;
                    char c = sum;
                    fputc(c,fout);bytes++;
                    fflush(fout);
                    i = count+1;
                }
            }
        }
    }
    if(flag)
    {
        sum+=bits[0]*128+bits[1]*64+bits[2]*32+bits[3]*16+bits[4]*8+bits[5]*4+bits[6]*2+bits[7]*1;
        char c = sum;
        fputc(c,fout);
        bytes++;
        // sum_bit +=flag;
        fflush(fout);
    }
    fclose(fout);
    fclose(fo);
    printf("壓縮完成\n");  
}