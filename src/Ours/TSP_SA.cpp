struct node{
    int x, y, w;
}a[10005];
 
int n, sx=0, sy=0;
double ansx, ansy;
double ans=1e18, t;
const double p=0.9935; // 温度下降率
 
double f(double x, double y)
{
    double rt=0;
    for(int i=1; i<=n; i++)
    {
        double sx=x-a[i].x, sy=y-a[i].y;
        rt+=sqrt(sx*sx+sy*sy)*a[i].w;
    }
    return rt;
}
 
void dfs()
{
    double x=ansx, y=ansy;
    t=2000; // 初始温度, 越大越能接受差异值
    while(t>1e-14)
    {
        double X=x+((rand()<<1)-RAND_MAX)*t;
        double Y=y+((rand()<<1)-RAND_MAX)*t;
        double now=f(X, Y);
        double T=now-ans;
        if(T<0)
        {
            x=X, y=Y;
            ansx=x, ansy=y, ans=now;
        }
        else if(exp(-T/t)*RAND_MAX>rand())
        {
            x=X, y=Y;
        }
        t*=p;
    }
 
}
 
void solve()
{
    ansx=1.0*sx/n, ansy=1.0*sy/n;
    dfs();
    dfs();
    dfs();
}
 
int main()
{
    srand(1000000007);srand(rand());srand(rand());
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
        sx+=a[i].x, sy+=a[i].y;
    }
    solve();
    printf("%.3f %.3f", ansx, ansy);
 
    return 0;
}