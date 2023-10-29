#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char CS[50][20]={0};
char CA[100][20]={0};
char SA[50][20]={0};
int CSi=0;
int CAi=0;
int SAi=0;
void C2(char L1[][15],int S_start,int S_end){
	int C_start=0;
	int S_current=S_start;
	int i=0;
	while(C_start!=S_start){
		while(S_current!=S_end+1){
			strcpy(CS[i], L1[C_start]);
            strcat(CS[i], ",");
            strcat(CS[i], L1[S_current]);
			S_current++;
			i++;
		}
		S_current=S_start;
		C_start++;
	}
	CSi=i;
}
void C3(char L1[][15],int S_start,int A_start,int A_end){
	int C_start=0;
	int A_current=A_start;
	int i=0;
	while(C_start!=S_start){
		while(A_current!=A_end+1){
			strcpy(CA[i], L1[C_start]);
            strcat(CA[i], ",");
            strcat(CA[i], L1[A_current]);
            //printf("%s\n",CA[i]);
			A_current++;
			i++;
		}
		A_current=A_start;
		C_start++;
	}
	CAi=i;
}
void C4(char L1[][15],int S_start,int A_start,int A_end){
	int A_current=A_start;
	int i=0;
	while(S_start!=A_start){
		while(A_current!=A_end+1){
			strcpy(SA[i], L1[S_start]);
            strcat(SA[i], ",");
            strcat(SA[i], L1[A_current]);
			A_current++;
			i++;
		}
		A_current=A_start;
		S_start++;
	}
	SAi=i;
}
int main(){
    char L1[50][15];
    FILE *fp = fopen("C:\\Users\\User\\Desktop\\專題\\L1\\L15101.txt", "r");
    FILE *ofp = fopen("C:\\Users\\User\\Desktop\\專題\\C251\\C2.txt", "w");
    int i = 0;
    int S_start = 0;
    int S_end = 0;
    int A_start= 0;
    int A_end=0;
    char line[15];
    char *line2;
    fgets(line, sizeof(line),fp);
    fgets(line, sizeof(line),fp);
    while (fgets(line, sizeof(line), fp) != NULL)
    {
    	line2 = strtok(line,":");
    	if(line2[0] == 'C' || line2[0] == 'S' || line2[0] == 'A'){
    		strcpy(L1[i],line2);
        	i++;
		}
    }
    
    int j;
    for(j=0;j<i;j++){
    	if(L1[j][0]=='S'){
    		S_start = j;
    		break;
		}
	}
	for(j=S_start;j<i;j++){
		if(L1[j][0]=='A'){
			A_start = j;
			S_end=A_start-1;
			break;
		}
	}
	A_end = i-1;
	C2(L1,S_start,S_end);
	C3(L1,S_start,A_start,A_end);
	C4(L1,S_start,A_start,A_end);
	for(i=0;i<CSi;i++){
		fprintf(ofp,"%s\n",CS[i]);
	}
	for(i=0;i<CAi;i++){
		fprintf(ofp,"%s\n",CA[i]);
	}
	for(i=0;i<SAi;i++){
		fprintf(ofp,"%s\n",SA[i]);
	}

    fclose(ofp);
    return 0;
}
