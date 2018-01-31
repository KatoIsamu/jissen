#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     INT_MAX

/* �f�[�^�i�אڍs��j */
int adjacent[MAX_SIZE][MAX_SIZE] = {
        {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // A: ����
        {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // B: ���
        {IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      // C: �Q�n
        {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // D: ��t
        {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // E: ���
        {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // F: �Ȗ�
        {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     // G: ����
        {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     // H: �V��
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     // I: �R�`
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     // J: �{��
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // K: �H�c
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // L: ���
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // M: �X
};

char *graph_data[] = {  // ��L�אڍs���0?12�Ԗڂ̊e�v�f�ɑΉ�
        "Tokyo",
        "Saitama",
        "Gunma",
        "Chiba",
        "Ibaraki",
        "Tochigi",
        "Fukushima",
        "Niigata",
        "Yamagata",
        "Miyagi",
        "Akita",
        "Iwate",
        "Aomori"
};


int visited[MAX_SIZE];  /* ���ׂ����_���L�� */
int cost[MAX_SIZE];             /* �R�X�g */
int prev[MAX_SIZE];             /* ���O�̒��_ */

void print_path(void)
{
        /* �������� */
	int i,p;
	for(i=0; i<MAX_SIZE; i++){
		p=prev[i];
		printf("���_:%10s ���O�̒��_:%10s �R�X�g:%d\n",graph_data[i],graph_data[p],cost[i]);
	}
}

void print_visited(){
  int i;
  for(i=0; i<MAX_SIZE; i++){
    printf("visited[%d]=%d\n",i,visited[i]);
  }
}

void search(int start)
{
        /* �������� */
	int i,min,next;

	cost[start]=0;

	do{
		min=IMAX;
		next=-1;
		visited[start]=TRUE;
		for(i=0; i<MAX_SIZE; i++){
			if(visited[i]==FALSE){
				if(adjacent[start][i]<IMAX){
					if(cost[i]>(cost[start]+adjacent[start][i])){
						cost[i]=cost[start]+adjacent[start][i];
						prev[i]=start;
					}
				}
        if(cost[i]<min){
          min=cost[i];
          next=i;
        }
			}
		}
		start=next;
	}while(start!=-1);
}

int main(void)
{
        int i,j,
                departure,
                arrival;
        int path[MAX_SIZE]; // �ȉ��̃v���O�����ł͏������ȍ~�Apath[]���g�p���Ă��Ȃ����A
                        // �ŒZ�o�H�ۑ��p�Ƃ��Ďg�p�ł���i�������A�g�p���Ȃ��Ă��ǂ��j
        /* ������ */
        for( i = 0; i < MAX_SIZE; i++ ){
                visited[i] = FALSE;
                cost[i] = IMAX;
                /* �ŒZ�o�H�ۑ��p�̔z�񏉊��� */
                path[i] = -1;
        }

        /* �s�����̕\���ƁA�o���A�����n�_�̓��� */
	for(i=0; i<MAX_SIZE; i++){
		printf("%2d:%10s\n",i,graph_data[i]);
	}
	printf("�o���n�_����͂��Ă�������->");
	scanf("%d",&departure);
	printf("�����n�_����͂��Ă�������->");
	scanf("%d",&arrival);

        /* �T�� */
        search( departure );

        /* �\�� */
        print_path();

	i=0;
	j=arrival;
        /* �ŒZ�o�H�̕\�� */
	while(departure!=j){
		path[i]=j;
		j=prev[j];
		i++;
	}
	path[i]=departure;
	for(; i!=0; i--){
		j=path[i];
		printf("[%s]->",graph_data[j]);
	}
	printf("[%s] : cost=%d",graph_data[arrival],cost[arrival]);
        return 0;
}
