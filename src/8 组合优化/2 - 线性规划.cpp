// Simplex for linear programming
// min. A(0, 0:n-1)
// s.t. A(1:m, 0:n-1) x <= A(1:m, n)

#define lp for(;;)
#define repf(i,a,b)
#define ft(i,a,b) for (int i=(a);i<=(b);++i)
#define rep(i,n) for (int i=0;i<(n);++i)
#define rtn return
#define pb push_back
#define mp make_pair
#define sz(x) (int((x).size()))
typedef double db;
typedef vector<int> vi;
db inf=1e+10;
db eps=1e-10;
inline int sgn(const db& x){rtn (x>+eps)-(x<-eps);}

const int MAXN=500;
const int MAXM=501;
int n,m;
db A[MAXM+1][MAXN+1],X[MAXN];
int basis[MAXM+1],out[MAXN+1];

void pivot(int a,int b) {
  ft(i,0,m) if (i!=a&&sgn(A[i][b])) ft(j,0,n)
    if (j!=b) A[i][j]-=A[a][j]*A[i][b]/A[a][b];
  ft(j,0,n) if (j!=b) A[a][j]/=A[a][b];
  ft(i,0,m) if (i!=a) A[i][b]/=-A[a][b];
  A[a][b]=1/A[a][b];
  swap(basis[a],out[b]);
}
db simplex() {
  rep(j,n) A[0][j]=-A[0][j];
  ft(i,0,m) basis[i]=-i;
  ft(j,0,n) out[j]=j;
  lp {
    int ii=1,jj=0;
    ft(i,1,m) if (mp(A[i][n],basis[i])<mp(A[ii][n],basis[ii])) ii=i;
    if (A[ii][n]>=0) break;
    rep(j,n) if (A[ii][j]<A[ii][jj]) jj=j;
    if (A[ii][jj]>=0) rtn -inf;
    pivot(ii,jj);
  }
  lp {
    int ii=1,jj=0;
    rep(j,n) if (mp(A[0][j],out[j])<mp(A[0][jj],out[jj])) jj=j;
    if (A[0][jj]>=0) break;
    ft(i,1,m)
      if (A[i][jj]>0&&(A[ii][jj]<=0||mp(A[i][n]/A[i][jj],basis[i])
        <mp(A[ii][n]/A[ii][jj],basis[ii])))
        ii=i;
    if (A[ii][jj]<=0) rtn +inf;
    pivot(ii,jj);
  }
  rep(j,n) X[j]=0;
  ft(i,1,m) if (basis[i]>=0) X[basis[i]]=A[i][n];
  rtn A[0][n];
}
