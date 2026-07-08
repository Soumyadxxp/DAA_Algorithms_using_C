#include<stdio.h>
int input(int p[],int w[],int W,int n)
{
    int i;
    printf("\nEnter the Total Capacity of Knapsack : ");
    scanf("%d",&W);
    for(i=0;i<n;i++)
    {
        printf("\nEnter the weight of item %d : ",i+1);
        scanf("%d",&w[i]);
        printf("\nEnter the Profit of weight %d : ",w[i]);
        scanf("%d",&p[i]);
    }
    return W;
}
int max(int a,int b,int x[],int n)
{
    if(a>b)
    {
        x[n]=1;
        return a;
    }
    else
    {
        x[n]=0;
        return b;
    }
}
int ks(int W,int w[],int p[],int n,int x[])
{
    if(n==0||W==0) return 0;
    else if(w[n]>W) return ks(W,w,p,n-1,x);

    int included = p[n]+ks(W-w[n],w,p,n-1,x);
    int excluded = ks(W,w,p,n-1,x);

    return max(included,excluded,x,n);
}
int main()
{
    int p[100],w[100],W,n,result;
    printf("\nEnter the Number of Elements : ");
    scanf("%d",&n);
    W=input(p,w,W,n);
    int x[n];
    for (int i = 0; i < n; i++) x[i] = 0;
    result=ks(W,w,p,n-1,x);
    printf("Value: %d\n{",result);
    for(int i=0;i<n;i++)printf("%2d",x[i]);
    printf("}");
}
