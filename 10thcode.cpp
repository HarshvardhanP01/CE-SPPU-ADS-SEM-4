#include<iostream>
#include<vector>
using namespace std;
class Heap
{
    public:
    void print(vector<int>& arr){
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    void heapify(vector<int>& arr,int n,int i){
        int largest = i;
        while(true){
            int left=2*i+1 , right=2*i+2;
            if(left<n && arr[left]>arr[largest]) largest=left;
            if(right<n && arr[right]>arr[largest]) largest=right;
            if(largest==i) break;
            swap(arr[largest],arr[i]);
            i=largest;
        } 
    }
    void heapsort(vector<int>& arr){
        int n = arr.size();
        for(int i=n/2;i>=0;i--){
            heapify(arr,n,i);
        }
        for(int i=n-1;i>0;i--){
            swap(arr[0],arr[i]);
            heapify(arr,i,0);
        }
    }
};
int main(){
    int n;
    Heap h;
    cout<<"\nEnter the size of array : ";
    cin>>n;
    cout<<"\nEnter the elements : ";
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"\nBefore sorting : ";
    h.print(arr);
    h.heapsort(arr);
    cout<<"\nAfter sorting : ";
    h.print(arr);
}