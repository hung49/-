#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 10 // 最大字串長度
typedef struct {//將City Sex Age 結構化 
    int city;
    int sex;
    int age;
} Entry;
void addArray(Entry entry, int cityCount[], int sexCount[], int ageCount[]) {
    cityCount[entry.city - 1]++; //陣列統計  cityCount[1,5,6]  C01有出現1次,C02有出現5次, C03有出現6次 索引值代表城市編號,內容為統計次數 
    sexCount[entry.sex - 1]++;
    ageCount[entry.age - 1]++;
}
int main() {
	//---------------------------------------------------宣告區--------------------------------------------------- 
    char filename[20];				//將開啟的檔案
	char output_filename[20];		//將輸出檔案 
	int fileN;						//檔案編號 
    int line_totalCount = 0;		//行數總統計 
    int line_count = 0;				//行數統計 
    int  min_supportCount = 0;		//最小支持個數 
    int g=0,i=0,j=0,k=0,l=0,u=0,x=0,y=0,z=0;	//迴圈、數量計算用變數 
    int cityCount[91] = {0};		//City統計陣列 
    int sexCount[2] = {0};          //Sex統計陣列     
    int ageCount[26] = {0};			//Age統計陣列 
    int L1[3][50][2] ={0};			//L1陣列,[3]區分CSA, [50]存放資料最大長度 ,[2]存放標簽與累積數EX:L1[0][0][0]:3 代表C03 , L1[0][0][1]:130 出現130次 
	int CS[50][3]={0};				//C2中的CS[50]代表  最大 CS 組合量 [3]代表 [0]C, [1]S, [2]計數 
	int CA[572][3]={0};				//C2中的CA[572]代表 最大 CA 組合量 [3]代表 [0]C, [1]A, [2]計數
	int SA[50][3]={0};				//C2中的CA[50]代表  最大 AS 組合量 [3]代表 [0]S, [1]A, [2]計數	
	int L3[1144][4]={0};			//L3陣列 [1144] 代表最多的CSA組合量 [4]代表 [0]C, [1]S, [2]A, [3]計數  
	float supportCity;				//支持度 
	float supportSex;				//支持度 
	float supportAge; 				//支持度 
    float min_support = 0.001;		//最小支持度 
    
	//---------------------------------------------------檔案讀取寫入--------------------------------------------------- 
	FILE *fp; 						// 讀檔位置 
	FILE *ofp;						// 寫檔位置 
	for(fileN = 5101; fileN <= 5142; fileN++) {
		sprintf(filename, "S%d.txt", fileN); // 格式化輸入文件名
		sprintf(output_filename, "L1%d.txt", fileN);// 格式化輸出文件名
		fp = fopen(filename, "r");
    	ofp = fopen(output_filename, "w");
      	if (fp == NULL) {
     	    printf("無法開啟檔案：%s\n", filename);
		    continue;
       	}
		printf("當前處理檔案：%s\n", filename);		
		line_count = 0;
    	//---------------------------------------------------C1---------------------------------------------------
    	char line[50];//存放每次讀取時1行的資料 
		fgets(line, sizeof(line), fp);// 讀取第一行 (header)，但不做處理		
		while (fgets(line, sizeof(line), fp) != NULL) {//---------------------------------------------------讀檔 
			char city_str[MAX_STRING_LENGTH];
        	char sex_str[MAX_STRING_LENGTH];
        	char age_str[MAX_STRING_LENGTH];
        	sscanf(line, "%[^,],%[^,],%[^,]", city_str, sex_str, age_str);	//將Line 讀取一行時資料用逗號切割,分別存放進 city_str, sex_str, age_str 
			Entry entry;
        	entry.city = atoi(city_str + 1); // 從第2個字元開始轉換為整數
        	entry.sex = atoi(sex_str + 1);
        	entry.age = atoi(age_str + 1);
   			line_totalCount++;//行數統計 
      		line_count++;					
        	addArray(entry, cityCount, sexCount, ageCount);//呼叫陣列統計函數 
    	}
   		if (ftell(fp) > 0) {
   			line_totalCount++;
      		line_count++;
    	}
    	line_count= line_count-1;
    	fclose(fp);//---------------------------------------------------關檔 
    	//---------------------------------------------------L1---------------------------------------------------
		min_supportCount =  min_support * line_count; //最小支持個數 = 最小支持度 *資料量 
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
	    fprintf(ofp,"最小支持度 %0.4f\n",min_support);
	    fprintf(ofp,"最小支持個數 %d\n",min_supportCount);
	    for (i = 0; i < 91; i++) {//---------------------------------------------------C
	        if (cityCount[i] > 0 && cityCount[i] >= min_supportCount) {    //滿足存在且大於等於最小支持個數顯示出來並輸出成txt 
				if(L1[0][x][0] == 0){
					L1[0][x][0] = i+1;
	        		L1[0][x][1] = cityCount[i];
	        		x++;
	        	}
	        	float supportCity = (float)cityCount[i] / line_count;
	        	fprintf(ofp,"[C%02d] 支持個數:%d 支持度:%.4f\n",L1[0][x-1][0],L1[0][x-1][1], supportCity);
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
	        	fprintf(ofp,"[S%d] 支持個數:%d 支持度:%.4f\n",L1[1][x-1][0],L1[1][x-1][1], supportSex);
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
	        	fprintf(ofp,"[A%02d] 支持個數:%d 支持度:%.4f\n",L1[2][x-1][0],L1[2][x-1][1], supportAge);
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
		//fgets(line, sizeof(line), fp);// 讀取第一行 (header)，但不做處理
    	while (fgets(line, sizeof(line), fp) != NULL){//---------------------------------------------------讀檔 
    		char city_str[MAX_STRING_LENGTH];
        	char sex_str[MAX_STRING_LENGTH];
        	char age_str[MAX_STRING_LENGTH];
        	sscanf(line, "%[^,],%[^,],%[^,]", city_str, sex_str, age_str);

    		for(i=0;i<x;i++){ //跑CS一圈 如果沒有就算了 
	    		if(atoi(city_str+1)==CS[i][0] && atoi(sex_str+1)==CS[i][1]){ //如果相同 
	    			CS[i][2]++;
				}
			}
			for(i=0;i<y;i++){ //跑CA一圈 如果沒有就算了 
	    		if(atoi(city_str+1)==CA[i][0] && atoi(age_str+1)==CA[i][1]){ //如果相同 
	    			CA[i][2]++;
				}
			}
			for(i=0;i<z;i++){ //跑SA一圈 如果沒有就算了 
	    		if(atoi(sex_str+1)==SA[i][0] && atoi(age_str+1)==SA[i][1]){ //如果相同 
	    			SA[i][2]++;
				}
			}
		}
		fclose(fp);//---------------------------------------------------關檔 
		//---------------------------------------------------L2---------------------------------------------------
		for(i=0;i<x;i++){
			if(CS[i][2]>= min_supportCount){
				float min_su = (float) CS[i][2]/ line_count;
				fprintf(ofp,"[C%02d,S%d] 支持個數:%d 支持度:%.4f\n",CS[i][0],CS[i][1],CS[i][2], min_su);
			}
		} 
		for(i=0;i<y;i++){
			if(CA[i][2]>= min_supportCount){
				float min_su = (float) CA[i][2]/ line_count;
				fprintf(ofp,"[C%02d,A%02d] 支持個數:%d 支持度:%.4f\n",CA[i][0],CA[i][1],CA[i][2], min_su);
			}
		}
		for(i=0;i<z;i++){
			if(SA[i][2]>= min_supportCount){
				float min_su = (float) SA[i][2]/ line_count;
				fprintf(ofp,"[S%d,A%02d] 支持個數:%d 支持度:%.4f\n",SA[i][0],SA[i][1],SA[i][2], min_su);
			}
		}
		//---------------------------------------------------C3---------------------------------------------------
		g=0,k=0,l=0,u=0;
    	for(i=0;i<x;i++){//-------------------------------CS
        	for(l=0;l<y;l++){//-------------------------------CA
	            if(CS[i][2] >= (min_supportCount) && CA[l][2] >= (min_supportCount)){//組合的元素是否大於最小支持度 
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
	            if(CS[i][2] >= (min_supportCount) && SA[l][2] >= (min_supportCount)){//組合的元素是否大於最小支持度 
					if(CS[i][1] == SA[l][0]){
						for(u=0;u<k;u++){
							if(L3[u][0] == CS[i][0] && L3[u][1] == CS[i][1] && L3[u][2] == SA[l][1]){//檢查C3中是否已經存在這個組合 		
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
	            if(CA[i][2] >= (min_supportCount) && SA[l][2] >= (min_supportCount)){//組合的元素是否大於最小支持度 
					if(CA[i][1] == SA[l][1]){
						for(u=0;u<k;u++){
							if(L3[u][0] == CA[i][0] && L3[u][1] == SA[l][0] && L3[u][2] == SA[l][1]){//檢查C3中是否已經存在這個組合 
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
		fgets(line, sizeof(line), fp);// 讀取第一行 (header)，但不做處理
		while (fgets(line, sizeof(line), fp) != NULL){//---------------------------------------------------讀檔 
		    char city_str[3];
		    char sex_str[2];
		    char age_str[3];
		    sscanf(line, "%3[^,],%2[^,],%3[^,]", city_str, sex_str, age_str);	//將Line 讀取一行時資料用逗號切割,分別存放進 city_str, sex_str, age_str
			for(i=0; i<k; i++){
    			if(L3[i][0] == atoi(city_str+1) && L3[i][1] == atoi(sex_str+1) && L3[i][2] == atoi(age_str+1) ){
					L3[i][3] += 1;
					break;
				}
			}
		}
		fclose(fp);//---------------------------------------------------關檔 
		//---------------------------------------------------L3---------------------------------------------------
		for(i=0;i< k;i++){
			if(L3[i][3] >= min_supportCount){
				float min_su = 0.00;
				min_su = (float) L3[i][3] / line_count;
				fprintf(ofp,"[C%02d, S%d, A%02d], 支持個數為%d 支持度:%.4f\n", L3[i][0],L3[i][1],L3[i][2],L3[i][3], min_su);
			}
		}
		printf("%d\n", line_count);
	    //---------------------------------------------------初始化區塊 
	    memset(L1, 0 ,300 * sizeof(L1[0][0][0]));
		memset(CS, 0 ,150 * sizeof(CS[0][0]));
		memset(CA, 0 ,1716* sizeof(CA[0][0]));
		memset(SA, 0 ,150 * sizeof(SA[0][0]));
		memset(L3, 0 ,4576* sizeof(L3[0][0]));				
	    memset(cityCount, 0 ,91*sizeof(cityCount[0]));		
	    memset(sexCount, 0 ,2*sizeof(sexCount[0]));
	    memset(ageCount, 0 ,26*sizeof(ageCount[0]));
	    g=0,i=0,j=0,k=0,l=0,u=0,x=0,y=0,z=0;
	    //---------------------------------------------------初始化區塊 
	    fclose(ofp);//---------------------------------------------------關檔 
    }
	return 0;
}
