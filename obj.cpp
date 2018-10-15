/*
    Jakub Wójcik 2018
*/

//-------------------------
// Includes
//-------------------------

#include <stdlib.h>
#include <stdio.h>
#include "obj.h"
//-------------------------
// Functions definitions
//-------------------------

//-------------------------
// Vector
//-------------------------

void displayVector(vec3* target)
{
    printf("Vec3 - X:%g Y:%g Z:%g\n", target->x, target->y, target->z);
}

vec3 createVector(float x, float y, float z)
{
    vec3 temp = {x, y, z};
    return temp;
};

void mulVectorConst(vec3* v, float factor)
{
    v->x*=factor;
    v->y*=factor;
    v->z*=factor;
};

void mulVectorVec(vec3* v, vec3* factor)
{
    v->x*=factor->x;
    v->y*=factor->y;
    v->z*=factor->z;
};

//-------------------------
// Vertex constructor and destructor
//-------------------------

vertex createVertex(vec3 v1, vec3 v2, vec3 v3)
{
    vertex temp;
    temp.vector[0] = v1;
    temp.vector[1] = v2;
    temp.vector[2] = v3;

    return temp;
}

void displayVertex(vertex* ver)
{
    printf("Vertex\n");
    int i;
    for(i=0; i<3; i++)
    {
        printf("\t");
        displayVector(&ver->vector[i]);
    }
}

void scaleVertexConst(vertex* target, float factor)
{
    mulVectorConst(&(target->vector[0]), factor);
    mulVectorConst(&(target->vector[1]), factor);
    mulVectorConst(&(target->vector[2]), factor);
};

void scaleVertexVec(vertex* target, vec3* factor)
{
    mulVectorVec(&(target->vector[0]), factor);
    mulVectorVec(&(target->vector[1]), factor);
    mulVectorVec(&(target->vector[2]), factor);
};

void freeVertex(vertex* target)
{
    free(target->vector);
}

void freeVertexes(vertex* targets, int count)
{
    int i;
    for(i=0; i<count; i++)
        free(targets->vector);
}

//-------------------------
// Obj constructor and destructor
//-------------------------

obj createObj(int count)
{
    obj temp;
    temp.count = count;
    temp.ver = (vertex*)malloc(count* sizeof(vertex));
    return temp;
}

obj createObjFromVertexes(vertex* ver, int count)
{
    obj temp = createObj(count);

    int i;
    for(i=0; i<count; i++)
        temp.ver[i] = ver[i];

    return temp;
}

void freeObjs(obj* targets, int count)
{
    int i;
    for(i=0; i<count; i++)
        freeVertexes(targets[i].ver, targets[i].count);
}

void freeObj(obj* target)
{
    freeVertexes(target->ver, target->count);
}

void displayObj(obj* target)
{
    printf("OBJ, count: %d\n", target->count);
    int i;
    for(i=0; i<target->count; i++)
    {
        printf("\t");
        displayVertex(&target->ver[i]);
    }
}

void scaleObjConst(obj* target, float factor)
{
    int i;
    for(i=0; i<target->count; i++)
    {
        scaleVertexConst(&target->ver[i], factor);
    }
};

void scaleObjVec(obj* target, vec3* factor)
{
    int i;
    for(i=0; i<target->count; i++)
    {
        scaleVertexVec(&target->ver[i], factor);
    }
};

//-------------------------
// Obj cube
//-------------------------

obj getCube()
{
    vec3 p[] =
    {
        {0, 0, 0},
        {-1, -1, 1},
        {1, -1, 1},
        {1, 1, 1},
        {-1, 1, 1},
        {-1, -1, -1},
        {1, -1, -1},
        {1, 1, -1},
        {-1, 1, -1}
    };

    vertex ver[] =
    {
        {p[1], p[4], p[2]},
        {p[4], p[3], p[2]},
        {p[2], p[3], p[6]},
        {p[3], p[7], p[6]},
        {p[6], p[7], p[5]},
        {p[7], p[8], p[5]},
        {p[5], p[8], p[1]},
        {p[8], p[4], p[1]},
        {p[1], p[5], p[2]},
        {p[5], p[6], p[2]},
        {p[4], p[8], p[3]},
        {p[8], p[7], p[6]}
    };

    return createObjFromVertexes(ver, 12);
}
