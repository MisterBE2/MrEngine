#include "matrix.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

matrix createMatrix(int row, int col)
{
    matrix temp;

    temp.rows = row;
    temp.columns = col;
    temp.body = (float**)malloc(sizeof(temp.body)*row);

    int i, j;
    for(i=0; i<row; i++)
    {
        temp.body[i] = (float*)malloc(sizeof(temp.body[i])*col);
        for(j=0; j<col; j++)
        {
            temp.body[i][j] = 0;
        }
    }

    return temp;
}

matrix createMatrixFromVectorHorizontal(vec3* source)
{
    matrix temp = createMatrix(1, 3);

    temp.body[0][0] = source->x;
    temp.body[0][1] = source->y;
    temp.body[0][2] = source->z;

    return temp;
}

matrix createMatrixFromVectorsHorizontal(vec3* sources, int count)
{
    matrix temp = createMatrix(count, 3);

    int i;
    for(i=0; i<count; i++)
    {
        temp.body[i][0] = sources[i].x;
        temp.body[i][1] = sources[i].y;
        temp.body[i][2] = sources[i].z;
    }

    return temp;
}

matrix mulMatrix(matrix matA, matrix matB)
{
    matrix temp;
    if(matA.columns == matB.rows)
    {
        temp = createMatrix(matA.rows, matB.columns);

        float* colA;
        float* rowB;
        int i, j, k;

       colA = (float*)malloc(sizeof(colA)*matA.columns);
       rowB = (float*)malloc(sizeof(rowB)*matB.rows);

        for(i =0; i<temp.rows; i++)
        {
            for(j=0; j<matA.columns; j++)
            {
                colA[j] = matA.body[i][j];
            }

            for(k =0; k<matB.columns; k++)
            {
                for(j=0; j<matB.rows; j++)
                {
                    rowB[j] = matB.body[j][k];
                }

                dotProduct(colA, matA.columns, rowB, matB.rows, &temp.body[i][k]);
            }
        }

        free(colA);
        free(rowB);
    }

    return temp;
}

void dotProduct(float* arrA, int arrASize, float* arrB, int arrBSize, float* target)
{
    if(arrASize == arrBSize)
    {
        int i;
        float res = 0;
        for(i = 0; i< arrASize; i++)
        {
            res+= (arrA[i])*(arrB[i]);
        }

        (*target) = res;
    }
    else
        (*target) = 0;
}

void freeMatrix(matrix* target)
{
	int i;
	for (i = 0; i < target->rows; i++)
    {
		free(target->body[i]);
	}

	free(target->body);
}

void displayMatrix(matrix* target)
{
    int i, j;
    for(i=0; i<target->rows; i++)
    {
        printf("[");
        for(j=0; j<target->columns; j++)
        {
            printf("%g", target->body[i][j]);
            if(j != target->columns-1)
                printf(", ");
        }
        printf("]\n");
    }

}

matrix getOrtoProj()
{
    vec3 p[] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 0}
    };

    return createMatrixFromVectorsHorizontal(p, 3);
}

matrix getPersProj(float z, float dist)
{
    float newZ = z/(dist-z);

    vec3 p[] = {
    {newZ, 0, 0},
    {0, newZ, 0},
    {0, 0, 0}
    };

    return createMatrixFromVectorsHorizontal(p, 3);
}

matrix getRotX(float angle)
{

    vec3 p[] = {
    {1, 0, 0},
    {0, cos(angle), -sin(angle)},
    {0, sin(angle), cos(angle)}
    };

    return createMatrixFromVectorsHorizontal(p, 3);
}

matrix getRotY(float angle)
{
    vec3 p[] = {
    {cos(angle), 0, sin(angle)},
    {0, 1, 0},
    {-sin(angle), 0, cos(angle)}
    };

    return createMatrixFromVectorsHorizontal(p, 3);
};


matrix getRotZ(float angle)
{
    vec3 p[] =
    {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {0, 0, 1}
    };

    return createMatrixFromVectorsHorizontal(p, 3);
}


