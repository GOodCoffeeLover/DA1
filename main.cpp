#include<iostream>
#include<stdlib.h>
#include<chrono>
const int SIZE_OF_STRING=65;
const int STARTING_SIZE=100;
const int MAX_VALUE=200;
const double SHIFT=100.0;
struct Data{
    double key;
    char str[SIZE_OF_STRING];
};

class TVector{
    public:
        Data * Arr;
        int Size;
        int MaxSize;
        TVector(){
            Size=0;
            MaxSize=1;
            Arr = ( Data * ) malloc( sizeof( Data ) );
        }
        TVector(int n){
            Size=0;
            MaxSize=n;
            Arr = ( Data * ) malloc( sizeof( Data ) * n );
        }
        ~TVector(){
            free(Arr);
        }
        void Assing(int n){
            MaxSize=n;
            Arr = ( Data* ) realloc(Arr, sizeof( Data ) * n );
        }
        Data& operator [] (int indx){
            return Arr[indx];
        }
};

void BucketSort(TVector& arr) {
    TVector* buckets=new TVector[arr.Size+1];
    for (int i=0; i<arr.Size; ++i) {
        if (buckets[ (int) ( (arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ].Size == buckets[ (int) ( ( arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ].MaxSize) {
            buckets[ (int) ( (arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ].Assing( buckets[ (int) ( (arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ].Size * 2 );
        }
        buckets[ (int) ( (arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ][ buckets[ (int) ( (arr[i].key+SHIFT) / MAX_VALUE * arr.Size ) ].Size++ ]=arr[i];
    }    
    int k;
    for (int i=0; i<arr.Size+1; ++i) {
        if (buckets[i].Size==0 || buckets[i].Size==1) {
            continue;
        }
        for (int j=0; j<buckets[i].Size; ++j) {
            Data q=buckets[i][j];
            k=j-1;
            while (k>=0 && q.key<buckets[i][k].key) {
                buckets[i][k+1]=buckets[i][k];
                k-=1;
            }
            buckets[i][k+1]=q;
        }
    }
    k=0;
    for (int i=0; i<arr.Size+1; ++i) {
        for (int j=0; j<buckets[i].Size; ++j) { 
            arr[k++]=buckets[i][j];
        } 
    }
    delete [] buckets;
    return;
}

int main() {
    std::ios::sync_with_stdio(false);
    TVector arr(STARTING_SIZE);
    while (std::cin) {
        std::cin >> arr[ arr.Size ].key;
        if (!std::cin) {
            break;
        }
        std::cin>>arr[ arr.Size ].str; 
        arr.Size+=1;
        if (arr.Size==arr.MaxSize) {
            arr.Assing( arr.Size * 2 );
        }
    }
    std::cout<<"star sorting"<<std::endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    BucketSort(arr);
    end = std::chrono::system_clock::now();
    
  /*  for(int i=0; i<arr.Size; ++i){
        std::cout<<std::fixed<<arr[i].key<<"\t"<<arr[i].str<<std::endl;
    }*/
    double diff=std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout<<"sorting time = "<<std::fixed<<diff/1000<<"s"<<std::endl;
    return 0;
}
