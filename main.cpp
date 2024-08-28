#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std;

#define MAX       2000
#define blockSize 125

double A[MAX][MAX], x[MAX][MAX], y[MAX][MAX];

void fillMatrix(){
  srand((unsigned)time(nullptr));
  for(int i=0; i<MAX; i++){
    for(int j=0; j<MAX; j++){
      A[i][j] = rand()%10;
      x[i][j] = rand()%10;
      y[i][j] = 0;
    }
  }
}

void reset_Y(){
  for(int i=0; i<MAX; i++){
    for(int j=0; j<MAX; j++){
      y[i][j]=0;
    }
  }
}

void printMatrix(double const M[MAX][MAX], string matrixName){
  cout<<matrixName<<": "<<endl;
  for(int i=0; i<MAX; i++){
    for(int j=0; j<MAX; j++){
      cout<<M[i][j]<<" ";
    }
    cout<<endl;
  }
}

void bucles(){
  cout<<"Bucles Anidados"<<endl;
  cout<<"Recorrido por filas"<<endl;
  reset_Y();
  // printMatrix(y,"Y");
  for(int i=0; i<MAX; i++){
    for(int j=0; j<MAX; j++){
      y[i][j] += A[i][j]*x[i][j];
    }
  }
  printMatrix(y,"Y");

  cout<<"Recorrido por columnas"<<endl;
  reset_Y();
  // printMatrix(y,"Y");

  for(int j=0; j<MAX; j++){
    for(int i=0; i<MAX; i++){
      y[i][j] += A[i][j]*x[i][j];
    }
  }
  printMatrix(y,"Y");
}

void classicMultiplication(){
  // Recorre las filas de las matrices
  for(int i=0; i<MAX; i++){
    // Recorre las columnas de las matrices
    for(int j=0; j<MAX; j++){
      // Producto punto
      for(int k=0; k<MAX; k++){
        y[i][j] += A[i][k] * x[k][j];
      }
    }
  }
}

void blockedMultiplication(){
  // Recorrer bloque por bloque
  for(int i=0; i<MAX; i+=blockSize){
    for(int j=0; j<MAX; j+=blockSize){
      for(int k=0; k<MAX; k+=blockSize){
        // Recorrer el interior de cada bloque
        for(int ii=i; ii<min(i+blockSize,MAX); ii++){
          for(int jj=j; jj<min(j+blockSize,MAX); jj++){
            // Producto punto
            for(int kk=k; kk<min(k+blockSize,MAX); kk++){
              y[ii][jj] += A[ii][kk] * x[kk][jj];
            }
          }
        }
      }
    } 
  }
}

int main(){
  fillMatrix();
  // printMatrix(A,"A");
  // printMatrix(x,"X");
  // printMatrix(y,"Y");
  // bucles();

  reset_Y();

  // auto start = chrono::high_resolution_clock::now();
  classicMultiplication();
  // auto end = chrono::high_resolution_clock::now();
  // chrono::duration<double,milli> duration = end - start;
  // cout<<"Clasico: "<<duration.count()<<endl;
  // printMatrix(y,"Y");

  reset_Y();

  // start = chrono::high_resolution_clock::now();
  blockedMultiplication();
  // end = chrono::high_resolution_clock::now();
  // duration = end - start;
  // cout<<"Bloques: "<<duration.count()<<endl;
  // printMatrix(y,"Y");

  return 0;
}
