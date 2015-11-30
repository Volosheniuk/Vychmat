#include <iostream>
#define M  4
#define N  3
#define NRHS 1

extern "C" {
     void dgesv_(int *n, int *nrhs,  double *a,  int  *lda,  
           int *ipivot, double *b, int *ldb, int *info) ;
     void sgelsd_(int *m,int*n,int *nrhs,double *a, int *lda,
			double *b,int *ldb,double *s,double *rcond,int *rank,
			double *work,int *lwork,int *iwork,int *info);//http://www.netlib.org/lapack/explore-html/da/db8/sgelsd_8f.html
}


int main(){
   int n;
   int nrhs = 1;
   double a[MAX][MAX];
   double b[1][MAX];
   int lda = MAX;
   int ldb = MAX;
   int ipiv[MAX];
   int info;
   // Other values
   int i,j;

   // Read the values of the matrix
   std::cout << "Enter n \n";
   std::cin >> n;
   std::cout << "On each line type a row of the matrix A followed by one element of b:\n";
   for(i = 0; i < n; i++){
     std::cout << "row " << i << " ";
     for(j = 0; j < n; j++)std::cin >> a[j][i];
     std::cin >> b[0][i];
   }

   // Solve the linear system
   dgesv_(&n, &nrhs, &a[0][0], &lda, ipiv, &b[0][0], &ldb, &info);

   // Check for success
   if(info == 0){
      std::cout << "The answer is\n";
      for(i = 0; i < n; i++)
        std::cout << "b[" << i << "]\t" << b[0][i] << "\n";
   }
   else
   {
      // Write an error message
      std::cerr << "dgesv returned error " << info << "\n";
   }
   return info;
}
