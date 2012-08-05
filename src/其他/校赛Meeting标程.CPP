#include <stdio.h>
#include <math.h>

int u1, v1, u2, v2, u3, v3;
double x, y, d;

double f(double u, double v)
{
   double r=0;
   r+=sqrt((u-u1)*(u-u1)+(v-v1)*(v-v1));
   r+=sqrt((u-u2)*(u-u2)+(v-v2)*(v-v2));
   r+=sqrt((u-u3)*(u-u3)+(v-v3)*(v-v3));
   if(r<d)
   {
      d=r;
      x=u;
      y=v;
   }
   return r;
}

double f(double u)
{
   double L, R, M1, M2;
   for(L=-1001, R=1001; R-L>1e-6; )
   {
      M1=(L*2+R)/3;
      M2=(L+R*2)/3;
      f(u, M1)<f(u, M2)?(R=M2):(L=M1);
   }
   return f(u, (L+R)/2);
}

int main()
{
   int T;
   double L, R, M1, M2;
   
   for(scanf("%d", &T); T--; )
   {
      scanf("%d %d %d %d %d %d", &u1, &v1, &u2, &v2, &u3, &v3);
      for(d=1e100, L=-1001, R=1001; R-L>1e-6; )
      {
         M1=(L*2+R)/3;
         M2=(L+R*2)/3;
         f(M1)<f(M2)?(R=M2):(L=M1);
      }
      printf("(%.3lf,%.3lf)\n", x, y);
   }
   
   return 0;
}
