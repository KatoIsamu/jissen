#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 0  /* 1:通常版，  0:番兵版   */
#define LOOP   1  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */ 

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
    int max;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
    /* dataの一番最後に番兵を追加する */
    if(data[N-1]==target){
		return N-1;
	}else{
		data[N-1]=target;
	}
    i=0;
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    while(data[i]!=target){
        i++;
    }
    if(i==N-1){
        return -1;
    }else{
        return i;
    }
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
#endif
}

/* クイックソート */
void quick(int data[], int a, int b)
{
    if(a>=b)return;
    int pivot,box;
    int fa,fb;
    int count=0;
    //要素がひとつなら何もせずにreturn
    pivot=data[a];
    fa=a;
    fb=b;
    //pivotをd[a]とする
	while(1){
		while(a<b&&data[a]<=pivot){
			a++;
		}
		//d[a]がpivotより小さい限りa++;
		while(a<b&&data[b]>pivot){
			b--;
		}
		//d[b]がpivotより大きい限りb--;
		if(a>=b)break;
		//d[a]とd[b]とを交換
		box=data[a];
		data[a]=data[b];
		data[b]=box;
	}
	//aとbが同じ可能性があるのでほとんどのプログラムに「＝」をいれた
	a--;
	box=data[a];
	data[a]=data[fa];
	data[fa]=box;
	quick(data,a+1,fb);
	quick(data,fa,a);    
    /* 前期で作成したquick関数を再利用する(再利用にあたって修正が必要なら、修正後に再利用する) */
    /* クイックソートがまだ完成していない場合は既にできているもので最も速いソートを用いてよい */
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
    int mid,i;
#if LOOP 
    /* ループバージョン */
    /* 実装せよ */
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
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
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
		x=b_search(data,low,high,target);//xはmidにしないと課題的にはダメかもしれない
		return x;
	}
	if(data[mid]<target){
		low=mid;
		x=b_search(data,low,high,target);
		return x;
	}
	return -1;
    /* 再帰バージョン */
    /* 実装せよ */
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */
#endif
}

/* メイン */
int main(void)
{
    int a[N], i,j, target, work[N], index;
	clock_t start,end;
	int count=0;
	double watch=0;
	start=clock();
	for(j=0;j<10;j++){
    	for( i = 0; i < N; i++ ) work[i] = rand() % N;
#if LINEAR		/* 1:線形探索，0:二分探索 */
#else
    	quick(work,0,N-1);
#endif
    	for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR		/* 1:線形探索，0:二分探索 */
        	index = l_search(work,target);
#else
        	index = b_search(work,0,N-1,target);
#endif
        	printf("TARGET=%d: ", target);
		//printf("%d\n",index);
        	if ( index != -1 ){
				printf("○\n");
			}else{
				printf("×\n");
			}
		}
    }
	end=clock();
	watch=(double)(end-start)/(double)CLOCKS_PER_SEC;
	printf("10回の探索の平均 %lf\n",(double)watch/10);
    return 0;
}