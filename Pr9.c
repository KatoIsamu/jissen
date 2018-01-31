#include<stdio.h>
#include<string.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE]; /* �אڍs�� */
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* �L���[ */

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


/* �O���t�̏����� */
void init_graph(void)
{
        /* �������� */
	int i,j;
	for(i=0; i<MAX_SIZE; i++) visited[i]=-1;
	for(i=0; i<MAX_SIZE; i++) for(j=0; j<MAX_SIZE; j++) adjacent[i][j]=0;
	for(i=0; i<MAX_SIZE; i++) for(j=0; j<MAX_SIZE; j++) if(strchr(graph_data[i],'A'+j)!=NULL)  adjacent[i][j]=1;
}

/* �L���[�̏����� */
void init_queue(int *q)
{
        int i;
        for( i = 0; i < MAX_SIZE; i++ ){
                q[i] = -1;
        }
}

/*�אڍs��̕\��*/
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

/* �L���[�̕\�� */
void print_queue(int *q)
{
        int i;
        printf("{");
        for( i = 0; i < MAX_SIZE; i++ )
                if( q[i] != -1 )
                        printf("%c",q[i]+'A');
        printf("}\n");
}

/* �L���[�̒��Ƀf�[�^d�����݂��Ă��邩�ǂ������`�F�b�N */
int check_queue(int *q,int d)
{
        int i;
        for( i = 0; i < MAX_SIZE;i++ )
                if( q[i] == d ) return TRUE;
        return FALSE;
}

/*�L���[�ɒ��g�����邩*/
int check_empty(int *q){
	int i,cnt=0;
	for(i=0; i<MAX_SIZE; i++) if(q[i]==-1) cnt++;
	if(cnt==MAX_SIZE) return TRUE;
	else return FALSE;
}

/* �L���[�Ƀf�[�^������ */
void enqueue(int *q, int d)
{
        /* �������� */
	int i=0;
	while(q[i]!=-1) i++;
	q[i]=d;
	return;
}

/*�L���[�̒��g��\��*/
void dispqueque(int *q)
{
  int i;
  printf("queque contents (");
  for(i=0; i<MAX_SIZE; i++) printf("%d,",q[i]);
  printf(")\n");
  return;
}

/* �L���[����f�[�^�����o�� */
int dequeue(int *q)
{
        /* �������� */
	int out=q[0],i;
	for(i=0; i<MAX_SIZE-1; i++) q[i]=q[i+1];
	q[MAX_SIZE]=-1;
	return out;
}

/* �o�H�̒T���i���D��T���j */
void search(int now, int end)
{
        /* �������� */
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

/* ���C���֐� */
int main(void)
{
  init_graph();
  dispgragh();
        search(0, 10 );         /* A ���� K �̌o�H */
        return 0;
}
