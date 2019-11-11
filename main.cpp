#include<iostream>
#include<stdlib.h>
struct data{
	double key;
	char str[64];
};

class vector{
	public:	
		data * arr;
		int size;
		int max_size;
		vector(){
			size=0;
			max_size=1;
			arr = (data*) malloc(sizeof(data));
		}
		vector(int n){
			size=0;
			max_size=n;
			arr = (data*) malloc(sizeof(data)*n);
		}
		~vector(){
			free(arr);
		}
		void assing(int n){
			max_size=n;
			arr = (data*) realloc(arr, sizeof(data)*n);
		}
		data& operator [] (int indx){
			return arr[indx];
		}
};

void bucket_sort(vector& arr, int size){
	vector* buckets=new vector[20];
	for(int i=0; i<20; ++i) buckets[i].assing(size);
	for(int i=0; i<size; ++i){
		buckets[(int)(arr[i].key)/10+10][buckets[(int)(arr[i].key)/10+10].size++]=arr[i];
	}	
	int k;
	for(int i=0; i<20; ++i){
		if(buckets[i].size==0) continue;
		for(int j=0; j<buckets[i].size; ++j){
			data q=buckets[i][j];	
			k=j;
			for(k=j; k>0; --k){
				if(q.key<buckets[i][k-1].key) buckets[i][k]=buckets[i][k-1]; else break;
			}
			buckets[i][k]=q;
		}
	}
	k=0;
	for(int i=0; i<20; ++i){
		for(int j=0; j<buckets[i].size; ++j){ 
			arr[k++]=buckets[i][j];
		} 
	}
	return;
}

int main(){
	vector arr(20);
	int n=0;
	while(std::cin){
		std::cin>>arr[n].key>>arr[n].str; n++;
	}
	n-=1;
	bucket_sort(arr, n);
	for(int i=0; i<n; ++i){
		std::cout<<arr[i].key<<"\t"<<arr[i].str<<std::endl;
	}
}
