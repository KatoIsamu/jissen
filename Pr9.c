#include<stdio.h>
#include<string.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE]; /* 隣接行列 */
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* キュー */

char *graph_data[] = {
      "BEF",      /* A is B E F */
      "ACF",      /* B is A C F */
      "BDG",      /* C is B D G */
      "C",        /* D is C */
      "AFH",      /* E is A F H */
      "ABEGIJ",   /* F is A B E G I J */
      "CFJ",      /* G is C F J */
      "EI",       /* H is E I*/
      "FHJ",      /* I is F H J */
      "FGIK",     /* J is F G I K */
      "J"         /* K is J */
};


/* グラフの初期化 */
void init_graph(void)
{
        /* 実装せよ */
	int i,j;
	for(i=0; i<MAX_SIZE; i++) visited[i]=-1;
	for(i=0; i<MAX_SIZE; i++) for(j=0; j<MAX_SIZE; j++) adjacent[i][j]=0;
	for(i=0; i<MAX_SIZE; i++) for(j=0; j<MAX_SIZE; j++) if(strchr(graph_data[i],'A'+j)!=NULL)  adjacent[i][j]=1;
}

/* キューの初期化 */
void init_queue(int *q)
{
        int i;
        for( i = 0; i < MAX_SIZE; i++ ){
                q[i] = -1;
        }
}

/*隣接行列の表示*/
void dispgragh()
{
  int i,j;
  for(i=0; i<MAX_SIZE; i++)
  {
    for(j=0; j<MAX_SIZE; j++)
    {
      printf("%d ",adjacent[i][j]);
    }
    printf("\n");
  }
  return;
}

/* キューの表示 */
void print_queue(int *q)
{
        int i;
        printf("{");
        for( i = 0; i < MAX_SIZE; i++ )
                if( q[i] != -1 )
                        printf("%c",q[i]+'A');
        printf("}\n");
}

/* キューの中にデータdが存在しているかどうかをチェック */
int check_queue(int *q,int d)
{
        int i;
        for( i = 0; i < MAX_SIZE;i++ )
                if( q[i] == d ) return TRUE;
        return FALSE;
}

/*キューに中身があるか*/
int check_empty(int *q){
	int i,cnt=0;
	for(i=0; i<MAX_SIZE; i++) if(q[i]==-1) cnt++;
	if(cnt==MAX_SIZE) return TRUE;
	else return FALSE;
}

/* キューにデータを入れる */
void enqueue(int *q, int d)
{
        /* 実装せよ */
	int i=0;
	while(q[i]!=-1) i++;
	q[i]=d;
	return;
}

/*キューの中身を表示*/
void dispqueque(int *q)
{
  int i;
  printf("queque contents (");
  for(i=0; i<MAX_SIZE; i++) printf("%d,",q[i]);
  printf(")\n");
  return;
}

/* キューからデータを取り出す */
int dequeue(int *q)
{
        /* 実装せよ */
	int out=q[0],i;
	for(i=0; i<MAX_SIZE-1; i++) q[i]=q[i+1];
	q[MAX_SIZE]=-1;
	return out;
}

/* 経路の探索（幅優先探索） */
void search(int now, int end)
{
        /* 実装せよ */
	int i=0,j;

	init_queue(open_list);
	enqueue(open_list,now);
	visited[now]=TRUE;

	while(check_empty(open_list)==FALSE){
    i=0;
    now=dequeue(open_list);
    printf("searching ... %c\n",'A'+now);
    print_queue(open_list);
		visited[now]=TRUE;
		if(now==end){
      printf("Found.\n");
      return;
    }
		else{
      for(i=0; i<MAX_SIZE; i++){
        if(adjacent[now][i]==1&&visited[i]!=TRUE&&check_queue(open_list,i)==FALSE){
            enqueue(open_list,i);
        }
      }
		}
	}
  return;
}

/* メイン関数 */
int main(void)
{
  init_graph();
  dispgragh();
        search(0, 10 );         /* A から K の経路 */
        return 0;
}
