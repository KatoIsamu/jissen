#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 1  /* 1:線形探索，0:二分探索 */
#define NORMAL 1  /* 1:通常版，  0:番兵版   */
#define LOOP   1  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */ 

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
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

    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
#endif
}

/* クイックソート */
void quick(int d[], int a, int b)
{
    
    /* 前期で作成したquick関数を再利用する(再利用にあたって修正が必要なら、修正後に再利用する) */
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


    /* クイックソートがまだ完成していない場合は既にできているもので最も速いソートを用いてよい */
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
    int mid,i;
#if LOOP 
    /* ループバージョン */
    /* 実装せよ */

	for(i=low; i<=high; i++){
		mid=(high+low)/2;
		if(data[mid]>target) high=mid-1;
		else if(data[mid]<target) low=mid+1;
		else if(data[mid]==target) return mid;
	}
	return -1;

    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
#else
    /* 再帰バージョン */
    /* 実装せよ */

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

/* メイン */
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
	    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
	#if LINEAR
	    index = l_search(work,target);
	#else
	    index = b_search(work,0,N-1,target);
	#endif
    	printf("TARGET=%d: ", target);
	    if ( index != -1 )
    	    printf("○\n");
	    else
    	    printf("×\n");
    	}
	}

	end=clock();
	double time=end-start;
	printf("スタート%d エンド%d 実行時間１０回の平均時間 %lfs",start,end,time/10000);
    return 0;
}
