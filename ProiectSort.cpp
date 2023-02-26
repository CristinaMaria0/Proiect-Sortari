#include<iostream>
#include<fstream>
#include<time.h>
#include<vector>
#include<chrono>
#include<algorithm>
using namespace std::chrono;
using namespace std;
///RadixSort
vector<long>v;

long Maxim(long n)
{
    long max=0;
    for(long i=1;i<n;i++)
        if(v[i]>max)
            max=v[i];
    return max;
}
void CountSort(long n, long div)
{
    vector<long> output(n);
    long i,frecv[10];
    for(i=0;i<10;i++)
        frecv[i]=0;
    for(i=0;i<n;i++)
        frecv[(v[i]/div)%10]++;
    for(i=1;i<10;i++)
        frecv[i]+=frecv[i-1];
    for(i=n-1;i>=0;i--)
    {
        output[frecv[(v[i]/div)%10]-1]=v[i];
        frecv[(v[i]/div)%10]--;
    }
    for(i=0;i<n;i++)
        v[i]=output[i];
}
void RadixSort(long n)
{
    long m=Maxim(n);
    for(long div=1;m/div>0;div*=10)
        CountSort(n,div);

}

///MergeSort
void Merge(long st, long dr, long mid)
{
    long i,j,k;
    long left[mid-st+1];
    long right[dr-mid];
    for(i=0;i<mid-st+1;i++)
        left[i]=v[st+i];
    for(j=0;j<dr-mid;j++)
        right[j]=v[mid+j+1];
    i=0; j=0;
    k=st;
    for(k=st;i<mid-st+1&&j<dr-mid;k++)
        if(left[i]<=right[j])
            v[k]=left[i++];
        else
            v[k]=right[j++];
    while(i<mid-st+1)
        v[k++]=left[i++];
    while(j<dr-mid)
        v[k++]=right[j++];
}
void MergeSort(long st,long dr)
{
    long mid;
    if(st<dr)
    {
        mid=(st+dr)/2;
        MergeSort(st,mid);
        MergeSort(mid+1,dr);
        Merge(st,dr,mid);
    }
}
///ShellSort
void ShellSort(long n)
{
    long i,j,k;
    for(i=n/2;i>0;i=i/2)
        for(j=i;j<n;j++)
        {
            long t=v[i];
            long k;
            for(k=j; k>=i&&v[k-i]>t;k-=i)
                v[k]=v[k-i];
            v[k]=t;
        }
}
///CountingSort

void CountingSort(long n)
{
    long max=*max_element(v.begin(),v.end());
    long min=*min_element(v.begin(),v.end());
    long range=max-min+1;
    vector<long> count(range), output(n);
    for (int i = 0; i < n; i++)
        count[v[i] - min]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[v[i] - min] - 1] = v[i];
        count[v[i] - min]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = output[i];
}

///InsertionSort
void InsertionSort(long n)
{
    long k,j;
    for(long i=1;i<n;i++)
    {
        k=v[i];
        j=i;
        while(j>0&&v[j-1]>k)
        {
            v[j]=v[j-1];
            j--;
        }
        v[j]=k;
    }
}
void generate_random(long r, long n)
{
    long i;
    for(i=0;i<n;i++)
    {
        long nr=(rand()%(r+1))+1;
        v.push_back(nr);
    }
}

int main()
{
    ifstream f("teste.in");
    ofstream g("teste.out");
    long NrTeste;
    f>>NrTeste;
    long i;
    vector<long>copie;
    for(i=1;i<=NrTeste;i++)
    {
        g<<"Testul numarul "<<i<<":"<<endl;
        long n;
        long NrMax;
        v.clear();
        f>>n>>NrMax;
        //generare elemente
        generate_random(NrMax,n);
        copie=v;

        auto start2 = high_resolution_clock::now();
        InsertionSort(n);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        g <<"InsertionSort:"<< duration2.count() << " microsecunde"<<endl;

        v=copie;
        auto start = high_resolution_clock::now();
        CountingSort(n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        g <<"CountingSort:"<< duration.count() << " microsecunde"<<endl;

        v=copie;
        auto start1 = high_resolution_clock::now();
        RadixSort(n);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        g <<"RadixSort:"<< duration1.count() << " microsecunde"<<endl;


        v=copie;
        auto start3 = high_resolution_clock::now();
        ShellSort(n);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        g <<"ShellSort:"<< duration3.count() << " microsecunde"<<endl;

        if(n>=1000000)
        g<<"MergeSort: Can't sort"<<endl;
        else
        {
            v=copie;
        auto start4 = high_resolution_clock::now();
        MergeSort(0, n-1);
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop4 - start4);
        g <<"MergeSort:"<< duration4.count() << " microsecunde"<<endl;
        }

        v=copie;
        auto start5 = high_resolution_clock::now();
        sort(v.begin(),v.end());
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast<microseconds>(stop5 - start5);
        g <<"Sort:"<< duration5.count() << " microsecunde"<<endl;
        g<<endl;

    }
    return 0;
}
