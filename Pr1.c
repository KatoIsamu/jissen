#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 0  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   1  /* 1:���[�v�ŁC0:�ċA��   */

#define N  30000  /* �T�����郌�R�[�h�� (���ӁF���̒l"����"��ς��Ă��A���ۂ̌������R�[�h���͑����Ȃ��j */ 

/* ���`�T�� */
int l_search(int data[], int target)
{
    int i, count = 0;
    int max;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* �ԕ��� */
    /* �������� */
    /* data�̈�ԍŌ�ɔԕ���ǉ����� */
    if(data[N-1]==target){
		return N-1;
	}else{
		data[N-1]=target;
	}
    i=0;
    /* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
    /* �݂������烋�[�v�𔲂��� */
    while(data[i]!=target){
        i++;
    }
    if(i==N-1){
        return -1;
    }else{
        return i;
    }
    /* �ԕ������݂���Ȃ�������-1��Ԃ� */
    /* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int data[], int a, int b)
{
    if(a>=b)return;
    int pivot,box;
    int fa,fb;
    int count=0;
    //�v�f���ЂƂȂ牽��������return
    pivot=data[a];
    fa=a;
    fb=b;
    //pivot��d[a]�Ƃ���
	while(1){
		while(a<b&&data[a]<=pivot){
			a++;
		}
		//d[a]��pivot��菬��������a++;
		while(a<b&&data[b]>pivot){
			b--;
		}
		//d[b]��pivot���傫������b--;
		if(a>=b)break;
		//d[a]��d[b]�Ƃ�����
		box=data[a];
		data[a]=data[b];
		data[b]=box;
	}
	//a��b�������\��������̂łقƂ�ǂ̃v���O�����Ɂu���v�����ꂽ
	a--;
	box=data[a];
	data[a]=data[fa];
	data[fa]=box;
	quick(data,a+1,fb);
	quick(data,fa,a);    
    /* �O���ō쐬����quick�֐����ė��p����(�ė��p�ɂ������ďC�����K�v�Ȃ�A�C����ɍė��p����) */
    /* �N�C�b�N�\�[�g���܂��������Ă��Ȃ��ꍇ�͊��ɂł��Ă�����̂ōł������\�[�g��p���Ă悢 */
}

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
    int mid,i;
#if LOOP 
    /* ���[�v�o�[�W���� */
    /* �������� */
	for(i=low;i<=high;i++){
		mid=(low+high)/2;
		if(data[mid]==target){
			return mid;
		}else if(data[mid]>target){
			high=mid-1;
		}else{
			low=mid+1;
		}
	}
	return -1;
    /* low <= high �̊Ԃ̓��[�v�ilow > high�Ȃ猩����Ȃ������j */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������� high �� mid-1 �� */
    /* data[mid] ��� target ���傫����� low �� mid+1 �� */
    /* data[mid] == target �������烋�[�v�𔲂��� */
    /* ���������Ȃ� mid ��Ԃ� */
    /* ������Ȃ������Ȃ� -1 ��Ԃ� */
#else
	int x;
	if(high-low==1){
		if(data[high]==target){
			return high;
		}
		if(data[low]==target){
			return low;
		}else{
			return -1;
		}
	}
	mid=(low+high)/2;
	if(data[mid]==target)return mid;
	if(data[mid]>target){
		high=mid;
		x=b_search(data,low,high,target);//x��mid�ɂ��Ȃ��Ɖۑ�I�ɂ̓_����������Ȃ�
		return x;
	}
	if(data[mid]<target){
		low=mid;
		x=b_search(data,low,high,target);
		return x;
	}
	return -1;
    /* �ċA�o�[�W���� */
    /* �������� */
    /* low > high �Ȃ猩����Ȃ������Ƃ������Ƃ� -1 ��Ԃ� */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������ΑO�������ōċA */
    /* data[mid] ��� target ���傫����Ό㔼�����ōċA */
    /* data[mid] == target �������猩�������Ƃ������Ƃ� mid ��Ԃ� */
#endif
}

/* ���C�� */
int main(void)
{
    int a[N], i,j, target, work[N], index;
	clock_t start,end;
	int count=0;
	double watch=0;
	start=clock();
	for(j=0;j<10;j++){
    	for( i = 0; i < N; i++ ) work[i] = rand() % N;
#if LINEAR		/* 1:���`�T���C0:�񕪒T�� */
#else
    	quick(work,0,N-1);
#endif
    	for( target = N/2-500; target < N/2+500; target++ ) {  // �������R�[�h����ς���ɂ́A���̕ӂ���C������K�v������
#if LINEAR		/* 1:���`�T���C0:�񕪒T�� */
        	index = l_search(work,target);
#else
        	index = b_search(work,0,N-1,target);
#endif
        	printf("TARGET=%d: ", target);
		//printf("%d\n",index);
        	if ( index != -1 ){
				printf("��\n");
			}else{
				printf("�~\n");
			}
		}
    }
	end=clock();
	watch=(double)(end-start)/(double)CLOCKS_PER_SEC;
	printf("10��̒T���̕��� %lf\n",(double)watch/10);
    return 0;
}