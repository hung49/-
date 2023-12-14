#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 10 // �̤j�r�����
typedef struct {//�NCity Sex Age ���c�� 
    int city;
    int sex;
    int age;
} Entry;
void addArray(Entry entry, int cityCount[], int sexCount[], int ageCount[]) {
    cityCount[entry.city - 1]++; //�}�C�έp  cityCount[1,5,6]  C01���X�{1��,C02���X�{5��, C03���X�{6�� ���ޭȥN�����s��,���e���έp���� 
    sexCount[entry.sex - 1]++;
    ageCount[entry.age - 1]++;
}
int main() {
	//---------------------------------------------------�ŧi��--------------------------------------------------- 
    char filename[20];				//�N�}�Ҫ��ɮ�
	char output_filename[20];		//�N��X�ɮ� 
	int fileN;						//�ɮ׽s�� 
    int line_totalCount = 0;		//����`�έp 
    int line_count = 0;				//��Ʋέp 
    int  min_supportCount = 0;		//�̤p����Ӽ� 
    int g=0,i=0,j=0,k=0,l=0,u=0,x=0,y=0,z=0;	//�j��B�ƶq�p����ܼ� 
    int cityCount[91] = {0};		//City�έp�}�C 
    int sexCount[2] = {0};          //Sex�έp�}�C     
    int ageCount[26] = {0};			//Age�έp�}�C 
    int L1[3][50][2] ={0};			//L1�}�C,[3]�Ϥ�CSA, [50]�s���Ƴ̤j���� ,[2]�s���ñ�P�ֿn��EX:L1[0][0][0]:3 �N��C03 , L1[0][0][1]:130 �X�{130�� 
	int CS[50][3]={0};				//C2����CS[50]�N��  �̤j CS �զX�q [3]�N�� [0]C, [1]S, [2]�p�� 
	int CA[572][3]={0};				//C2����CA[572]�N�� �̤j CA �զX�q [3]�N�� [0]C, [1]A, [2]�p��
	int SA[50][3]={0};				//C2����CA[50]�N��  �̤j AS �զX�q [3]�N�� [0]S, [1]A, [2]�p��	
	int L3[1144][4]={0};			//L3�}�C [1144] �N��̦h��CSA�զX�q [4]�N�� [0]C, [1]S, [2]A, [3]�p��  
	float supportCity;				//����� 
	float supportSex;				//����� 
	float supportAge; 				//����� 
    float min_support = 0.001;		//�̤p����� 
    
	//---------------------------------------------------�ɮ�Ū���g�J--------------------------------------------------- 
	FILE *fp; 						// Ū�ɦ�m 
	FILE *ofp;						// �g�ɦ�m 
	for(fileN = 5101; fileN <= 5142; fileN++) {
		sprintf(filename, "S%d.txt", fileN); // �榡�ƿ�J���W
		sprintf(output_filename, "L1%d.txt", fileN);// �榡�ƿ�X���W
		fp = fopen(filename, "r");
    	ofp = fopen(output_filename, "w");
      	if (fp == NULL) {
     	    printf("�L�k�}���ɮסG%s\n", filename);
		    continue;
       	}
		printf("��e�B�z�ɮסG%s\n", filename);		
		line_count = 0;
    	//---------------------------------------------------C1---------------------------------------------------
    	char line[50];//�s��C��Ū����1�檺��� 
		fgets(line, sizeof(line), fp);// Ū���Ĥ@�� (header)�A�������B�z		
		while (fgets(line, sizeof(line), fp) != NULL) {//---------------------------------------------------Ū�� 
			char city_str[MAX_STRING_LENGTH];
        	char sex_str[MAX_STRING_LENGTH];
        	char age_str[MAX_STRING_LENGTH];
        	sscanf(line, "%[^,],%[^,],%[^,]", city_str, sex_str, age_str);	//�NLine Ū���@��ɸ�ƥγr������,���O�s��i city_str, sex_str, age_str 
			Entry entry;
        	entry.city = atoi(city_str + 1); // �q��2�Ӧr���}�l�ഫ�����
        	entry.sex = atoi(sex_str + 1);
        	entry.age = atoi(age_str + 1);
   			line_totalCount++;//��Ʋέp 
      		line_count++;					
        	addArray(entry, cityCount, sexCount, ageCount);//�I�s�}�C�έp��� 
    	}
   		if (ftell(fp) > 0) {
   			line_totalCount++;
      		line_count++;
    	}
    	line_count= line_count-1;
    	fclose(fp);//---------------------------------------------------���� 
    	//---------------------------------------------------L1---------------------------------------------------
		min_supportCount =  min_support * line_count; //�̤p����Ӽ� = �̤p����� *��ƶq 
	    for (i = 0; i < 91; i++) {
	        if (cityCount[i] > 0) {
	        	supportCity = (float)cityCount[i] / line_count;
	        }
	    }
	    for (i = 0; i < 2; i++) {
	        if (sexCount[i] > 0) {
	        	float supportSex = (float)sexCount[i] / line_count;
	        }
	    }
	    for (i = 0; i < 26; i++) {
	        if (ageCount[i] > 0) {
	        	float supportAge = (float)ageCount[i] / line_count;
	        }
	    }
	    fprintf(ofp,"�̤p����� %0.4f\n",min_support);
	    fprintf(ofp,"�̤p����Ӽ� %d\n",min_supportCount);
	    for (i = 0; i < 91; i++) {//---------------------------------------------------C
	        if (cityCount[i] > 0 && cityCount[i] >= min_supportCount) {    //�����s�b�B�j�󵥩�̤p����Ӽ���ܥX�Өÿ�X��txt 
				if(L1[0][x][0] == 0){
					L1[0][x][0] = i+1;
	        		L1[0][x][1] = cityCount[i];
	        		x++;
	        	}
	        	float supportCity = (float)cityCount[i] / line_count;
	        	fprintf(ofp,"[C%02d] ����Ӽ�:%d �����:%.4f\n",L1[0][x-1][0],L1[0][x-1][1], supportCity);
			}
	    }
	    x=0;
	    for (i = 0; i < 2; i++) {//---------------------------------------------------S
	        if (sexCount[i] > 0 && sexCount[i] >= min_supportCount ) {
	        	if(L1[1][x][0] == 0){
					L1[1][x][0] = i+1;
	        		L1[1][x][1] = sexCount[i];
	        		x++;
	        	}
	        	float supportSex = (float)sexCount[i] / line_count;
	        	fprintf(ofp,"[S%d] ����Ӽ�:%d �����:%.4f\n",L1[1][x-1][0],L1[1][x-1][1], supportSex);
	        }
	    }
	    x=0;
	    for (i = 0; i < 26; i++) {//---------------------------------------------------A
	        if (ageCount[i] > 0 && ageCount[i] >= min_supportCount) {
	        	if(L1[2][x][0] == 0){
					L1[2][x][0] = i+1;
	        		L1[2][x][1] = ageCount[i];
	        		x++;
	        	}
	        	float supportAge = (float)ageCount[i] / line_count;
	        	fprintf(ofp,"[A%02d] ����Ӽ�:%d �����:%.4f\n",L1[2][x-1][0],L1[2][x-1][1], supportAge);
	        }
	    }
		//---------------------------------------------------C2---------------------------------------------------
	    i=0,j=0,k=0,x=0,y=0,z=0;
	    while(i<50){
	    	if(L1[0][i][0]!=0){//---------------------------------------------------C
	    		while(j<50){
	    			if(L1[1][j][0]!=0){//---------------------------------------------------S
	    				CS[x][0]=L1[0][i][0];
	    				CS[x][1]=L1[1][j][0];
	    				x++;
					}
					if(L1[2][j][0]!=0){//---------------------------------------------------A
	    					CA[y][0]=L1[0][i][0];
	    					CA[y][1]=L1[2][j][0];
	    					y++;
					}
					j++;
				}
				j=0;
			}
			i++;
		}
		while(j<50){
			if(L1[1][j][0]!=0){//---------------------------------------------------S
	    		while(k<50){
	    			if(L1[2][k][0]!=0){//---------------------------------------------------A
	    				SA[z][0]=L1[1][j][0];
	    				SA[z][1]=L1[2][k][0];
	    				z++;
					}
					k++;
				}
				k=0;
			}
			j++;
		}
		fp = fopen(filename, "r");
		//fgets(line, sizeof(line), fp);// Ū���Ĥ@�� (header)�A�������B�z
    	while (fgets(line, sizeof(line), fp) != NULL){//---------------------------------------------------Ū�� 
    		char city_str[MAX_STRING_LENGTH];
        	char sex_str[MAX_STRING_LENGTH];
        	char age_str[MAX_STRING_LENGTH];
        	sscanf(line, "%[^,],%[^,],%[^,]", city_str, sex_str, age_str);

    		for(i=0;i<x;i++){ //�]CS�@�� �p�G�S���N��F 
	    		if(atoi(city_str+1)==CS[i][0] && atoi(sex_str+1)==CS[i][1]){ //�p�G�ۦP 
	    			CS[i][2]++;
				}
			}
			for(i=0;i<y;i++){ //�]CA�@�� �p�G�S���N��F 
	    		if(atoi(city_str+1)==CA[i][0] && atoi(age_str+1)==CA[i][1]){ //�p�G�ۦP 
	    			CA[i][2]++;
				}
			}
			for(i=0;i<z;i++){ //�]SA�@�� �p�G�S���N��F 
	    		if(atoi(sex_str+1)==SA[i][0] && atoi(age_str+1)==SA[i][1]){ //�p�G�ۦP 
	    			SA[i][2]++;
				}
			}
		}
		fclose(fp);//---------------------------------------------------���� 
		//---------------------------------------------------L2---------------------------------------------------
		for(i=0;i<x;i++){
			if(CS[i][2]>= min_supportCount){
				float min_su = (float) CS[i][2]/ line_count;
				fprintf(ofp,"[C%02d,S%d] ����Ӽ�:%d �����:%.4f\n",CS[i][0],CS[i][1],CS[i][2], min_su);
			}
		} 
		for(i=0;i<y;i++){
			if(CA[i][2]>= min_supportCount){
				float min_su = (float) CA[i][2]/ line_count;
				fprintf(ofp,"[C%02d,A%02d] ����Ӽ�:%d �����:%.4f\n",CA[i][0],CA[i][1],CA[i][2], min_su);
			}
		}
		for(i=0;i<z;i++){
			if(SA[i][2]>= min_supportCount){
				float min_su = (float) SA[i][2]/ line_count;
				fprintf(ofp,"[S%d,A%02d] ����Ӽ�:%d �����:%.4f\n",SA[i][0],SA[i][1],SA[i][2], min_su);
			}
		}
		//---------------------------------------------------C3---------------------------------------------------
		g=0,k=0,l=0,u=0;
    	for(i=0;i<x;i++){//-------------------------------CS
        	for(l=0;l<y;l++){//-------------------------------CA
	            if(CS[i][2] >= (min_supportCount) && CA[l][2] >= (min_supportCount)){//�զX�������O�_�j��̤p����� 
					if(CS[i][0] == CA[l][0]){
	                    L3[k][0] = CS[i][0];
	                    L3[k][1] = CS[i][1];
	                    L3[k][2] = CA[l][1];
	                    k++;
                	}
            	}
        	}
    	}
		for(i=0;i<x;i++){//-------------------------------CS
        	for(l=0;l<z;l++){//-------------------------------SA
	            if(CS[i][2] >= (min_supportCount) && SA[l][2] >= (min_supportCount)){//�զX�������O�_�j��̤p����� 
					if(CS[i][1] == SA[l][0]){
						for(u=0;u<k;u++){
							if(L3[u][0] == CS[i][0] && L3[u][1] == CS[i][1] && L3[u][2] == SA[l][1]){//�ˬdC3���O�_�w�g�s�b�o�ӲզX 		
								g = 1;
								break;
							}
						}
						if(g != 1){
							L3[k][0] = CS[i][0];
		                    L3[k][1] = CS[i][1];
		                    L3[k][2] = SA[l][1];
		                    k++;
		                }
						else{
							g = 0;
		                    continue; 
		    			}
					}
				}
            }
        }
		for(i=0;i<y;i++){//-------------------------------CA
        	for(l=0;l<z;l++){//-------------------------------SA
	            if(CA[i][2] >= (min_supportCount) && SA[l][2] >= (min_supportCount)){//�զX�������O�_�j��̤p����� 
					if(CA[i][1] == SA[l][1]){
						for(u=0;u<k;u++){
							if(L3[u][0] == CA[i][0] && L3[u][1] == SA[l][0] && L3[u][2] == SA[l][1]){//�ˬdC3���O�_�w�g�s�b�o�ӲզX 
								g = 1;
								break;
							}
						}
						if(g != 1){
							L3[k][0] = CA[i][0];
		                    L3[k][1] = SA[l][0];
		                    L3[k][2] = SA[l][1];
		                    k++;
						}
						else{
							g = 0;
		                    continue;  
		    			}
					}
				}
            }
        }
		fp = fopen(filename, "r");
		fgets(line, sizeof(line), fp);// Ū���Ĥ@�� (header)�A�������B�z
		while (fgets(line, sizeof(line), fp) != NULL){//---------------------------------------------------Ū�� 
		    char city_str[3];
		    char sex_str[2];
		    char age_str[3];
		    sscanf(line, "%3[^,],%2[^,],%3[^,]", city_str, sex_str, age_str);	//�NLine Ū���@��ɸ�ƥγr������,���O�s��i city_str, sex_str, age_str
			for(i=0; i<k; i++){
    			if(L3[i][0] == atoi(city_str+1) && L3[i][1] == atoi(sex_str+1) && L3[i][2] == atoi(age_str+1) ){
					L3[i][3] += 1;
					break;
				}
			}
		}
		fclose(fp);//---------------------------------------------------���� 
		//---------------------------------------------------L3---------------------------------------------------
		for(i=0;i< k;i++){
			if(L3[i][3] >= min_supportCount){
				float min_su = 0.00;
				min_su = (float) L3[i][3] / line_count;
				fprintf(ofp,"[C%02d, S%d, A%02d], ����ӼƬ�%d �����:%.4f\n", L3[i][0],L3[i][1],L3[i][2],L3[i][3], min_su);
			}
		}
		printf("%d\n", line_count);
	    //---------------------------------------------------��l�ư϶� 
	    memset(L1, 0 ,300 * sizeof(L1[0][0][0]));
		memset(CS, 0 ,150 * sizeof(CS[0][0]));
		memset(CA, 0 ,1716* sizeof(CA[0][0]));
		memset(SA, 0 ,150 * sizeof(SA[0][0]));
		memset(L3, 0 ,4576* sizeof(L3[0][0]));				
	    memset(cityCount, 0 ,91*sizeof(cityCount[0]));		
	    memset(sexCount, 0 ,2*sizeof(sexCount[0]));
	    memset(ageCount, 0 ,26*sizeof(ageCount[0]));
	    g=0,i=0,j=0,k=0,l=0,u=0,x=0,y=0,z=0;
	    //---------------------------------------------------��l�ư϶� 
	    fclose(ofp);//---------------------------------------------------���� 
    }
	return 0;
}
