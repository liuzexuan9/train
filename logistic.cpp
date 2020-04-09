double sigmoid(vector<double>&x,vector<double>&w)
{
    double sum=0;
    int n=x.size();
    for(int i=0;i<n;i++)
    {
        sum+=(x[i]*w[i]);
    }
    
    return 1.0/(1+exp(sum*-1));
}
