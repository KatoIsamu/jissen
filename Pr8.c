#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE      1
#define FALSE     0
#define MAX_SIZE 11

typedef struct character{
        int  no;                        /* キー */
        char name;                      /* 名前 */
        struct character *next_addr;    /* 次のデータのアドレス */
}CELL;

char *graph_data[] = {
        "CI",           /* A : C I */
        "DGH",          /* B : D G H */
        "ADG",          /* C : A D G */
        "BCHIJ",        /* D : B C H I J */
        "FHJ",          /* E : F H J */
        "EGK",          /* F : E G K */
        "BCF",          /* G : B C F */
        "BDEJ",         /* H : B D E J */
        "AD",           /* I : A D */
        "DEHK",         /* J : D E H K */
        "FJ"            /* K : F J */
};

CELL *adjacent[MAX_SIZE]; /* 隣接リスト */
int visited[MAX_SIZE];
int path[MAX_SIZE];
int stacks=0;


int stack(int num){
	if(stacks>=MAX_SIZE) return -1;
	visited[stacks]=num;
	stacks++;
	return 1;
}

//numがvisited[]にあったら1、なかったら0
int check(int num){
	int i;
	for(i=0; i<MAX_SIZE; i++) if(visited[i]==num) return 1;
	return 0;
}

/* リスト構造で並んでいる様子を表示する */
void disp(void) {
        int i = 0;
        CELL *current_addr;
        printf("隣接リスト:\n");
        for( i = 0; i < MAX_SIZE; i++ ){
                if( adjacent[i] != NULL ){
                        current_addr = adjacent[i];
                        do{
                                printf("-|%c|-",current_addr->name);
                                current_addr = current_addr->next_addr;
                        }while( current_addr != NULL );
                }
                printf("\n");
        }
}

/* データの追加 */
void add(int parent, int child) {
        CELL *p;
        CELL *q;
         p = (CELL *)malloc(sizeof(CELL));
        p->no = child;
        p->name = 'A' + child;
        p->next_addr = NULL;
         q = adjacent[parent];
        while ( q->next_addr != NULL ) {
                q = q->next_addr;
        }
        q->next_addr = p;
}

/* グラフの初期化 */
void init_graph(void) {
/* 実装せよ */

	int i,j;
	CELL *p,*q,*current;

  for(i=0; i<MAX_SIZE; i++){
    visited[i]=FALSE;
  }

	for(i=0; i<11; i++){
		p=(CELL *)malloc(sizeof(CELL));
		current=p;
		p->no=i;
		p->name='A'+i;

			for(j=0; j<11; j++){
				if(strchr(graph_data[i],'A'+j)!=NULL){
					q=(CELL *)malloc(sizeof(CELL));
					q->no=j;
					q->name='A'+j;
					current->next_addr=q;
					current=q;
				}
			}
		current->next_addr=NULL;
		adjacent[i]=p;
	}
}

/* 経路の表示 */
void print_path(int num) {
        int i;
        for( i = 0; i <= num; i++ ){
                 printf("%c ", path[i] + 'A' );
        }
        printf("\n");
}

/* 経路の探索（深さ優先探索） */
void search(int num, int now, int end) {
/* 実装せよ */
  int i,j;
//printf("%d,%d",now,end);
  visited[now]=TRUE;
  path[num]=now;
  if(now==end){
    print_path(num);
    visited[now]=FALSE;
    return;
  }
  else{
    CELL *p;
    p=adjacent[now];
    while(p->next_addr!=NULL){
      p=p->next_addr;
      //printf("%d\n",visited[p->no] );
      if(visited[p->no]==0)  search(num+1,p->no,end);
    }

    visited[now]=FALSE;
  }
}


/* メイン関数 */
int main(void) {
        init_graph();
	      disp();


        search( 0, 0, 10 );             /* A(0) から K(10) の経路 */
        return 0;
}
