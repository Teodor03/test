#include<cstdio>
#pragma GCC optimise("unroll-loops",03)
using namespace std;

const int Max_N=1001,Max_M=1001;

int n,m,b;

FILE* in;
FILE* out;

int table_sums [Max_N][Max_M];

int memo_table [Max_N][Max_N];

int memo_table_path [Max_N][Max_N][2];

int find_up(int start,int _end){
int current_obh;
int result=0;
for(int counter=0;counter<m;counter++){
    current_obh=table_sums[_end][counter];
    if(start!=0){
        current_obh=current_obh-table_sums[start-1][counter];
        if(current_obh<0){
            current_obh=current_obh+b;
        }
    }
    result=result+current_obh*current_obh;
}
    return result;
}

int main(){
in = fopen("subsetselection.in", "rt");
out = fopen("subsetselection.out", "wt");
fscanf(in,"%d%d%d",&n,&m,&b);
int current_scanning;
for(int counter=0;counter<n;counter++){
    for(int counter_1 =0;counter_1<m;counter_1++){
        fscanf(in,"%d",&current_scanning);
        table_sums[counter][counter_1]=table_sums[counter-1][counter_1]+current_scanning;
        if(table_sums[counter][counter_1]>=b){
            table_sums[counter][counter_1]=table_sums[counter][counter_1]-b;
        }
    }
}
int adding;
for(int counter=0;counter<n;counter++){
    for(int second_counter=0;second_counter<m;second_counter++){
        adding=table_sums[counter][second_counter];
        if(counter!=0){
            adding-=table_sums[counter-1][second_counter];
        }
        if(adding<0){
        adding+=b;
        }
        memo_table[counter][counter]+=adding*adding;
    }
    memo_table_path[counter][counter][0]=counter;
    memo_table_path[counter][counter][1]=counter;
}
int first_al;
int second_al;
int third_al;
for(int _end=1;_end<n;_end++){
    for(int start=_end-1;start>-1;start--){
        first_al=find_up(start,_end);
        second_al=memo_table[_end][start+1];
        third_al=memo_table[_end-1][start];
        if(first_al>=second_al and first_al>=third_al){
            memo_table[_end][start]=first_al;
            memo_table_path[_end][start][0]=start;
            memo_table_path[_end][start][1]=_end;
        }
        if(second_al>=first_al and second_al>=third_al){
            memo_table[_end][start]=second_al;
            memo_table_path[_end][start][0]=memo_table_path[_end][start+1][0];
            memo_table_path[_end][start][1]=memo_table_path[_end][start+1][1];
        }
        if(third_al>=first_al and third_al>=second_al){
            memo_table[_end][start]=third_al;
            memo_table_path[_end][start][0]=memo_table_path[_end-1][start][0];
            memo_table_path[_end][start][1]=memo_table_path[_end-1][start][1];
        }
    }
}
int start=memo_table_path[n-1][0][0]+1;
int finish=memo_table_path[n-1][0][1]+1;
int size_place=finish-start+1;
fprintf(out,"%d",size_place);
for(int counter=start;counter<=finish;counter++){
fprintf(out,"\n%d",counter);
}
return 0;
}
