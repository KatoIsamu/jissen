#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 1  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 1  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   1  /* 1:���[�v�ŁC0:�ċA��   */

#define N  30000  /* �T�����郌�R�[�h�� (���ӁF���̒l"����"��ς��Ă��A���ۂ̌������R�[�h���͑����Ȃ��j */ 

/* ���`�T�� */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* �ԕ��� */
    /* �������� */
    data[N+1]=target;
    for(i=0; i<N+1; i++){
		if(data[i]==target){
			break;
		}
    }
	if(i==N+1){
		return -1;
	}else{
		return i;
	}

    /* data�̈�ԍŌ�ɔԕ���ǉ����� */
    /* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
    /* �݂������烋�[�v�𔲂��� */
    /* �ԕ������݂���Ȃ�������-1��Ԃ� */
    /* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int d[], int a, int b)
{
    
    /* �O���ō쐬����quick�֐����ė��p����(�ė��p�ɂ������ďC�����K�v�Ȃ�A�C����ɍė��p����) */
    int tmp;
	int a0=a,b0=b;
	if(b-a>1)
	{
		int pivot=d[a0];
		while(1)
		{
			a++;
			while(d[a]<pivot)
			{
				a++;
			}
			b--;
			while(d[b]>pivot)
			{
				b--;
			}
			if(a>=b) break;
			tmp=d[a];
			d[a]=d[b];
			d[b]=tmp;
		}
		
		tmp=d[a-1];
		d[a-1]=d[a0];
		d[a0]=tmp;
		
		quick(d,a0,a-1);
		quick(d,a,b0);
	}


    /* �N�C�b�N�\�[�g���܂��������Ă��Ȃ��ꍇ�͊��ɂł��Ă�����̂ōł������\�[�g��p���Ă悢 */
}

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
    int mid,i;
#if LOOP 
    /* ���[�v�o�[�W���� */
    /* �������� */

	for(i=low; i<=high; i++){
		mid=(high+low)/2;
		if(data[mid]>target) high=mid-1;
		else if(data[mid]<target) low=mid+1;
		else if(data[mid]==target) return mid;
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
    /* �ċA�o�[�W���� */
    /* �������� */

	if(high-low==1){
	    if(data[high]==target) return high;
	    else if(data[low]==target) return low;
	    else return -1;
	}else{
		if(low>high) return -1;
		mid=(high+low)/2;
		if(data[mid]>target) b_search(data,low,mid,target);
		else if(data[mid]<target) b_search(data,mid,high,target);
		else if(data[mid]==target) return mid;
	}

#endif
}

/* ���C�� */
int main(void)
{

    int a[N], i, target, work[N], index,start,end;
    for( i = 0; i < N; i++ ) work[i] = rand( ) % N;
	
	start=clock();
	for(i=0; i<10; i++){
		#if LINEAR
		#else
	    quick(work,0,N-1);	
	#endif
	    for( target = N/2-500; target < N/2+500; target++ ) {  // �������R�[�h����ς���ɂ́A���̕ӂ���C������K�v������
	#if LINEAR
	    index = l_search(work,target);
	#else
	    index = b_search(work,0,N-1,target);
	#endif
    	printf("TARGET=%d: ", target);
	    if ( index != -1 )
    	    printf("��\n");
	    else
    	    printf("�~\n");
    	}
	}

	end=clock();
	double time=end-start;
	printf("�X�^�[�g%d �G���h%d ���s���ԂP�O��̕��ώ��� %lfs",start,end,time/10000);
    return 0;
}