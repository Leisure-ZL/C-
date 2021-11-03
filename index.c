  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>
  
  #define TEANUM 20		//��ʦ���� 
  #define STUNUM 5		//�༶���� 
  #define ROOMNUM 5		//���Ҹ��� 
  
  /////////////////////�������/////////////////
  
  //��ʦ��Ϣ�洢 
  struct teacher_data{
  	int ID;						//��ʦID 
  	char name[10];				//��ʦ���� 
  	struct{ 		
  		int stuID;				//�οΰ༶ID 
  		char Class[10];			//�γ����� 
  		char ClassGrade[10];	//�ν̰༶���� 
	  }classArr[15];			//�ν̿γ��� 
	struct{
		int spare;
	}timeArr[12][5];			//��¼��ʱ����Ƿ���� 
  }tea[TEANUM]; 
  
  
  //ѧ����Ϣ�洢 
  struct student_data{
  	int ID;
  	char ClassGrade[10];			//�༶���� 
  	struct{
  		int spare;					//�������(1/0) 
  		char Class[10];				//�γ����� 
  		int teaID;					//��ʦID 
  		int time;					//�γ��ܿ�ʱ 
  		int weekClaNum[2];			//ÿ�ܿγ̶�    �洢int 
	  }classArr[15];				//����15�ſ� 
  }stu[STUNUM]; 
  
  
   //������Ϣ�洢 
  struct classroom_data{
   	int ID;						//���ұ�� 
	struct{
		int spare;				//���������1/0��
		char Class[10];			//�γ����� 
		int teaID;				//��ʦID 
		char ClassGrade[10];	//�༶����		
	}timeArr[12][5];			//�γ�ʱ���
   }cla[ROOMNUM]; 
   
  
  //�༶�α�洢
  struct classList{
  	int ID;
  	char ClassGrade[10];		//�༶���� 
  	struct{
  		char Class[10];			//�γ����� 
	  }timeArr[12][5];
  }claList[STUNUM]; 
  

  //��ʦ�α�洢
  struct teacherList{
  	int ID;
  	char name[10];
  	struct{
  		int spare;
  		char Class[10];			//�γ����� 
  		char ClassGrade[10];	//�ν̰༶���� 
	  }timeArr[12][5];
  }teaList[TEANUM]; 
  
  
  ///////////////////�������//////////////////// 
  
  ///////////��ʦ�ˣ� 
  
//��ʦ��Ϣ¼�� 
  void teacher_input(int teaNum,char path[20]){
  	int i=0;
	int flag = 1;
	FILE *fp;
	fp = fopen(path,"w");
	if (NULL == fp){				 
    	printf ("Failed to open the file !\n");
	}
  	printf("������ID,name:\n");
  	scanf("%d%s",&tea[teaNum].ID,&tea[teaNum].name);
  	fprintf(fp,"%d\t%s\n",tea[teaNum].ID,tea[teaNum].name);
  	while(flag){
  		printf("������γ���༶����ID:\n");
  		scanf("%s%s%d",&tea[teaNum].classArr[i].Class,&tea[teaNum].classArr[i].ClassGrade,&tea[teaNum].classArr[i].stuID);
  		fprintf(fp,"%s %s %d\n",tea[teaNum].classArr[i].Class,tea[teaNum].classArr[i].ClassGrade,tea[teaNum].classArr[i].stuID);
  		printf("�Ƿ����¼�루1/0����");
		scanf("%d",&flag); 
		i++;
	  }
	  fclose(fp);
  } 
  
//��ʦ��Ϣ��� 
  void teacher_output(int teaNum,char path[20]){
  	int i=0;
  	FILE *fp;
  	fp = fopen(path,"r");
  	if (NULL==fp) {
    	printf ("Failed to open the file !\n");
    	exit(0);
	}
  	printf("��ʦ���ã�\n"); 
  	fscanf(fp,"%d\t%s\n",&tea[teaNum].ID,&tea[teaNum].name);
  	printf("ID:%d\nname:%s\n",tea[teaNum].ID,tea[teaNum].name);
  	while(tea[teaNum].classArr[i].Class[0] != '\0' || !feof(fp)){
  		fscanf(fp,"%s %s %d",&tea[teaNum].classArr[i].Class,&tea[teaNum].classArr[i].ClassGrade,&tea[teaNum].classArr[i].stuID);
  		printf("sub:%8s class:%8s stuID:%d\n",tea[teaNum].classArr[i].Class,tea[teaNum].classArr[i].ClassGrade,tea[teaNum].classArr[i].stuID);
  		i++;
  	}
  	fclose(fp);
  	printf("------------------------------------\n");
  }
   
//��ʦ��ʼ�� 
  void teacher_init(){
  	int i,j,m,n;
  	for(i=0;i<TEANUM;i++){
  		  	for(m=0;m<12;m++){
  		  		for(n=0;n<5;n++){
  		  			tea[i].timeArr[m][n].spare = 1;	
			}
		}	
	  }
  }
  
//��ʦ����
  
  	//����ʱ����� 
void teacherSet(int ID,int day,int time){
	tea[ID].timeArr[time-1][day-1].spare = 0;
} 

	//ʱ��ε��� 
void teacherSetPeriod(int ID,int x){//x=0:����   x=1:����   x=2:���� 
	int i,j;
	if(!x){//���� 
		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}	
	}
	if(x){//���� 
		for(i=0;i<5;i++){
			for(j=5;j<9;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}
	}
	if(x == 2){//���� 
		for(i=0;i<5;i++){
			for(j=9;j<12;j++){
				tea[ID].timeArr[j][i].spare = 0;			
			}
		}
	}
}

//��ʦ����for user(����ʽ)
void teacherSetForUser(){
	int id,day,time;
	printf("����������ID:\n");
	scanf("%d",&id);
	printf("%s��ʦ���ã�����������Ҫ���ݵ�ʱ��(1-5 & 1-12)\n",tea[id].name);
	scanf("%d %d",&day,&time);
	tea[id].timeArr[time-1][day-1].spare = 0;
	printf("succeed!\n");
} 



//��ʦ�α����
void teacherList_output(int teaNum,char path[20]){
	int i,j,k;
	FILE *fp;
	fp = fopen(path,"w");
	printf("ID:%d\t��ʦ:%s\n",tea[teaNum].ID,tea[teaNum].name);
	fprintf(fp,"ID:%d\t��ʦ:%s\n",tea[teaNum].ID,tea[teaNum].name);
	for(i=0;i<12;i++){
		for(j=0;j<5;j++){
			printf("class:%8s course:%8s | ",teaList[teaNum].timeArr[i][j].Class,teaList[teaNum].timeArr[i][j].ClassGrade);
			fprintf(fp,"class:%10s course:%10s | ",teaList[teaNum].timeArr[i][j].Class,teaList[teaNum].timeArr[i][j].ClassGrade);
		}
		printf("\n");
		fprintf(fp,"\n");
		if(i==4 || i==8){
			printf("\n");
			fprintf(fp,"\n");				
		}
	} 
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
} 
  
  
  
  //////////////ѧ���ˣ�
  
//ѧ����Ϣ¼��(д���ļ�student_data.txt)
  void student_input(int stuNum,char path[20]){
  	int i=0;
  	int flag=1;
  	FILE *fp1;
  	fp1=fopen(path,"w");
  	if (NULL == fp1){				 //�Է���ֵfpl�ж��Ƿ���� 
    	printf ("Failed to open the file !\n");
	}
  	printf("������ID���༶:\n");
  	scanf("%d%s",&stu[stuNum].ID,&stu[stuNum].ClassGrade);
  	fprintf(fp1,"%d\t%s\n",stu[stuNum].ID,stu[stuNum].ClassGrade);//���ļ����� 
  	while(flag){
  		printf("������γ�,�ν̽�ʦID��ѧʱ:\n");
  		scanf("%s%d%d",&stu[stuNum].classArr[i].Class,&stu[stuNum].classArr[i].teaID,&stu[stuNum].classArr[i].time);
  		if(stu[stuNum].classArr[i].time > 54){//�������54��ʱ��ÿ�ܿδ���3�ڣ��ֳ������Ͽ� 
  			stu[stuNum].classArr[i].weekClaNum[0] = stu[stuNum].classArr[i].time / 18 / 2;
 			stu[stuNum].classArr[i].weekClaNum[1] = stu[stuNum].classArr[i].time / 18 - stu[stuNum].classArr[i].weekClaNum[0];
		  }else{
		  	stu[stuNum].classArr[i].weekClaNum[0] = stu[stuNum].classArr[i].time / 18;
		  	stu[stuNum].classArr[i].weekClaNum[1] = 0;
		  }
  		fprintf(fp1,"%s %d %d %d %d\n",stu[stuNum].classArr[i].Class,stu[stuNum].classArr[i].teaID,stu[stuNum].classArr[i].time,stu[stuNum].classArr[i].weekClaNum[0],
		stu[stuNum].classArr[i].weekClaNum[1]);
  		printf("�Ƿ����¼�루1/0����");
		scanf("%d",&flag);
		i++;
	  }
	  fclose(fp1);
  } 
  
  
//ѧ����Ϣ���(���ļ��ж�ȡ���洢)
  void student_output(int stuNum,char path[30]){
  	int i=0;
  	FILE *fp;
  	fp=fopen(path,"r");
  	if (NULL==fp) {
    	printf ("Failed to open the file !\n");
    	exit(0);
	}
  	fscanf(fp,"%d	%s\n",&stu[stuNum].ID,&stu[stuNum].ClassGrade);
  	printf("ID:%d\nclass:%s\n",stu[stuNum].ID,stu[stuNum].ClassGrade);
  	while(stu[stuNum].classArr[i].Class[0] != '\0' || !feof(fp)){//feof�ж��Ƿ��ȡ���� 
		fscanf(fp,"%s %d %d %d %d ",&stu[stuNum].classArr[i].Class,&stu[stuNum].classArr[i].teaID,&stu[stuNum].classArr[i].time,&stu[stuNum].classArr[i].weekClaNum[0],
			&stu[stuNum].classArr[i].weekClaNum[1]);
		printf("sub:%8s teaID:%d spare:%d time:%d weektime:%d\n",stu[stuNum].classArr[i].Class,stu[stuNum].classArr[i].teaID,stu[stuNum].classArr[i].spare,
		  stu[stuNum].classArr[i].time,stu[stuNum].classArr[i].weekClaNum[1]);
  		i++;
  } 
  fclose(fp);
  printf("------------------------------------------------\n");
}

//�༶��ʼ��
  void class_init(int stuNum){
  	int i;
  	for(i=0;i<15;i++){
  		stu[stuNum].classArr[i].spare = 1;
	  }
	}
	
	
//�༶�α����
void class_output(int stuNum,char path[20]){
	int i,j,k;
	FILE *fp;
	fp = fopen(path,"w");
	printf("�༶:%s\n",stu[stuNum].ClassGrade);
	fprintf(fp,"�༶:%s\n",stu[stuNum].ClassGrade);
	for(i=0;i<12;i++){
		for(j=0;j<5;j++){
			printf("class:%8s course:%8s | ",claList[stuNum].ClassGrade,claList[stuNum].timeArr[i][j].Class);
			fprintf(fp,"class:%10s course:%10s | ",claList[stuNum].ClassGrade,claList[stuNum].timeArr[i][j].Class);
		}
		printf("\n");
		fprintf(fp,"\n");
		if(i==4 || i==8){
			printf("\n");
			fprintf(fp,"\n");				
		}
	}
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
} 


////////////����

//���ҳ�ʼ��
  void classroom_init(){//������ʱ��ν���spare��Ϊ1 
  	int i,k,j;
  	for(i=0;i<ROOMNUM;i++){
  		cla[i].ID = i + 1;
  		for(j=0;j<12;j++)
  			for(k=0;k<5;k++){
  				cla[i].timeArr[j][k].spare=1;
			  }
	  }
  } 
  
//������Ϣ���
void classroom_output(){
	int i,j,k,x;
	FILE *fp;
	fp=fopen("classroom_data.txt","w");
	if (NULL==fp) 
	{
    	printf ("Failed to open the file !\n");
    	exit (0) ; 
		}
	for(i=0;i<ROOMNUM;i++){
		printf("����:%d\n",cla[i].ID);
		fprintf(fp,"����:%d\n",cla[i].ID);
		for(j=0;j<12;j++){
			for(k=0;k<5;k++){
				printf("class:%8s coures:%8s | ",cla[i].timeArr[j][k].ClassGrade,cla[i].timeArr[j][k].Class);
				fprintf(fp,"class:%8s coures:%8s | ",cla[i].timeArr[j][k].ClassGrade,cla[i].timeArr[j][k].Class);
			}
			printf("\n");
			fprintf(fp,"\n");
			if(j==4 || j==8){
				printf("\n");
				fprintf(fp,"\n");				
			}

		}
		printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(fp,"\n*******************************************************************************\n");
	}
	fclose(fp);
} 


  ////////////�ſ� 
 
//�ſ�
 void arrange(){
 	int i,j,k,x,y,z,t,m,n=0;
 	int teaID;
 	for(x=0;x<STUNUM;x++){					//�༶ 	
 		for(t=0;t<2;t++){					//ÿ�����ογ� 
 			class_init(x);					//��ʼ���γ�spare=1; 
		 	for(y=0;y<15;y++){				//�γ� 
		  		for(i=0;i<ROOMNUM;i++){		//������ 
		 			for(j=0;j<5;j++){		//���� 
		 				for(k=0;k<12;k++){	//ÿ��ʱ��� 
		 					teaID = stu[x].classArr[y].teaID;	//��¼�ÿγ̽�ʦID	 					
			 				if(k <= 4){				//����5�� 	1~5
			 					if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 5-k >= stu[x].classArr[y].weekClaNum[t] ){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							teaList[teaID].timeArr[z][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);	//�γ����ƴ��������Ϣ 
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);		//�༶���ƴ��������Ϣ
										strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);//��Ϣ����༶�α� 
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;								//��Ϣ�����ʦ�α� 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							 }
							if(k>4 && k<9){		//����4�� 	6~9
								if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 9-k-stu[x].classArr[y].weekClaNum[t] >= 0){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							teaList[teaID].timeArr[z][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
			 							strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;		//�����ʦ�α� 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							}
							if(k>8){				//����4�� 	10~12
								if(cla[i].timeArr[k][j].spare && stu[x].classArr[y].spare && tea[teaID].timeArr[k][j].spare && 12-k-stu[x].classArr[y].weekClaNum[t] >= 0){
			 						for(z=k;z<stu[x].classArr[y].weekClaNum[t]+k;z++){
			 							cla[i].timeArr[z][j].spare = 0;
			 							tea[teaID].timeArr[k][j].spare = 0;
			 							strcpy(cla[i].timeArr[z][j].Class,stu[x].classArr[y].Class);
			 							strcpy(cla[i].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
			 							strcpy(claList[x].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(claList[x].ClassGrade,cla[i].timeArr[z][j].ClassGrade);
										teaList[teaID].ID = tea[teaID].ID;//�����ʦ�α� 
										strcpy(teaList[teaID].name,tea[teaID].name);
										strcpy(teaList[teaID].timeArr[z][j].Class,cla[i].timeArr[z][j].Class);
										strcpy(teaList[teaID].timeArr[z][j].ClassGrade,stu[x].ClassGrade);
										teaList[teaID].timeArr[z][j].spare = 0;
									 }
			 						stu[x].classArr[y].spare = 0;
							 	}
							}
						 }
					}
			 	}		
			 }
		}
	 }
 } 
 
 
   
   ///////////�������///////////////// 
   void teacher_input(int teaNum,char path[20]); 		//��ʦ��Ϣ¼��(����̨���룬�洢��д���ļ�) 
   void teacher_output(int teaNum,char path[20]);		//��ʦ��Ϣ���(��ȡ�ļ������ڴ�) 
   void teacher_init();									//��ʦ��ʼ��
   void teacherSet(int ID,int day,int time);			//����ʱ�����  day:����  time:ʱ��� 
   void teacherSetPeriod(int ID,int x);					//ʱ��ε���    x=0:����   x=1:����   x=2:���� 
   void teacherSetForUser();							//����ʽ���ε���
   void teacherList_output(int teaNum,char path[20]);	//��ʦ�α����
   void student_input(int stuNum,char path[20]);		//ѧ����Ϣ¼��
   void student_output(int stuNum,char path[30]);		//ѧ����Ϣ���
   void class_init(int stuNum);							//�༶��ʼ��
   void class_output(int stuNum,char path[20]);			//�༶�α����
   void classroom_init();								//���ҳ�ʼ��
   void classroom_output();								//������Ϣ���
   void arrange();										//�ſ����㷨 
    
    
   					
  //////////////////���������///////////////// 
  int main(){

//	student_input(5,"./student/student_data_5.txt");
//	teacher_input(14,"./teacher/teacher_data_14.txt");
   	student_output(0,"./student/student_data_0.txt");
  	student_output(1,"./student/student_data_1.txt");
   	student_output(2,"./student/student_data_2.txt");
   	student_output(3,"./student/student_data_3.txt");
   	student_output(4,"./student/student_data_4.txt");
  	teacher_output(0,"./teacher/teacher_data_0.txt");
	teacher_output(1,"./teacher/teacher_data_1.txt");
	teacher_output(2,"./teacher/teacher_data_2.txt");
	teacher_output(3,"./teacher/teacher_data_3.txt");
	teacher_output(4,"./teacher/teacher_data_4.txt");
	teacher_output(5,"./teacher/teacher_data_5.txt");
	teacher_output(6,"./teacher/teacher_data_6.txt");
	teacher_output(7,"./teacher/teacher_data_7.txt");
	teacher_output(8,"./teacher/teacher_data_8.txt");
	teacher_output(9,"./teacher/teacher_data_9.txt");
	teacher_output(10,"./teacher/teacher_data_10.txt");
	teacher_output(11,"./teacher/teacher_data_11.txt");
	teacher_output(12,"./teacher/teacher_data_12.txt");
	teacher_output(13,"./teacher/teacher_data_13.txt");
	teacher_output(14,"./teacher/teacher_data_14.txt");
   	
   	teacher_init();
  	classroom_init();
//	teacherSet(0,1,1);
//	teacherSet(0,1,2);
//  teacherSet(0,1,3);
//	teacherSetPeriod(0,1);
//	teacherSetForUser();
  	arrange();
  	
	classroom_output();
  	class_output(0,"./class/class_data_0.txt");
  	class_output(1,"./class/class_data_1.txt");
  	class_output(2,"./class/class_data_2.txt");
  	class_output(3,"./class/class_data_3.txt");
  	class_output(4,"./class/class_data_4.txt");

  	teacherList_output(0,"./teacher/teacherList_0.txt");
  	teacherList_output(1,"./teacher/teacherList_1.txt");
  	teacherList_output(2,"./teacher/teacherList_2.txt");
  	teacherList_output(3,"./teacher/teacherList_3.txt");

  	return 0;
  }
  
  
  
  
  
