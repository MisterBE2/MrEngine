#include "obj.h"

typedef struct matrix
{
    int rows;
    int columns;
    float** body;
} matrix;

matrix createMatrix(int, int);
matrix createMatrixFromVectorHorizontal(vec3*);
matrix createMatrixFromVectorsHorizontal(vec3*, int);

matrix mulMatrix(matrix, matrix);
void dotProduct(float*, int, float*, int, float*);

void freeMatrix(matrix*);
void displayMatrix(matrix*);

matrix getOrtoProj();
matrix getPersProj(float, float);
matrix getRotX(float);
matrix getRotY(float);
matrix getRotZ(float);

