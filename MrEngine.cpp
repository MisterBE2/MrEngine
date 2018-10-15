#include "MrEngine.h"
#include "graphics.h"
#include "obj.h"
#include "matrix.h"
#include "stdio.h"

#define objsCount 1

win window; // Stores quick informations about the window
obj* objs; // List with all 3D objects
obj oBuf; // Single obj on which calculations are performed
int highestVertexes = 0; // Variable needed to initialize objBuffer
matrix vBuf; // Buffer for vector to matrix conversions
matrix vBufTemp;
vec2* vBuf2D; // 2D vertex to draw

// Opens drawing window and initializes global variables
void initialize()
{
    window.width = 540;
    window.height =480;
    window.c_x = 540/2;
    window.c_y = 480/2;
    initwindow(540, 480,"MrEngine V0.1",0,0,true, true);

    objs = (obj*)malloc(objsCount * sizeof(obj*));
    objs[0] = getCube();
    objs[0].scale = createVector(100, 100, 100);
    objs[0].rotation = createVector(0,0,0);
    objs[0].displacement = createVector(0,0,0);

    int i;
    for(i = 0; i<objsCount; i++)
    {
        if(objs[i].count > highestVertexes)
            highestVertexes = objs[i].count;
    }

    oBuf.count = highestVertexes;
    oBuf.ver = (vertex*)malloc(sizeof(vertex)*highestVertexes);

    vBuf2D = (vec2*)malloc(sizeof(vec2*)*3);

    vec2 v = {0,0};
    vBuf2D[0] = v;
    vBuf2D[1] = v;
    vBuf2D[2] = v;

}

void update()
{
    clearviewport();

    // Filling buffer with objects
    int i;
    for(i = 0; i<objsCount; i++)
    {
        oBuf.count = objs[i].count;
        oBuf.displacement = objs[i].displacement;
        oBuf.rotation = objs[i].rotation;
        oBuf.scale = objs[i].scale;

        int z;
        for(z = 0; z<objs[i].count; z++)
        {
            // Operations on buffer
            oBuf.ver[z] = objs[i].ver[z];
            scaleObjVec(&oBuf, &oBuf.scale);

            int j;
            for(j = 0; j<3; j++)
            {

                vBuf = createMatrixFromVectorHorizontal(&oBuf.ver[z].vector[j]);

                vBuf = mulMatrix(vBuf, getRotX(oBuf.rotation.x));
                vBuf = mulMatrix(vBuf, getRotY(oBuf.rotation.y));
                vBuf = mulMatrix(vBuf, getRotZ(oBuf.rotation.z));

                vBuf = mulMatrix(vBuf, getOrtoProj());

                //displayMatrix(&vBuf);

                vBuf2D[j].x = vBuf.body[0][0];
                vBuf2D[j].y = vBuf.body[0][1];

                freeMatrix(&vBuf);

            }

            // Drawing vertex
            line((int)(vBuf2D[0].x + window.c_x),
                 (int)(vBuf2D[0].y + window.c_y),
                 (int)(vBuf2D[1].x + window.c_x),
                 (int)(vBuf2D[1].y + window.c_y));

            line((int)(vBuf2D[1].x + window.c_x),
                 (int)(vBuf2D[1].y + window.c_y),
                 (int)(vBuf2D[2].x + window.c_x),
                 (int)(vBuf2D[2].y + window.c_y));

            line((int)(vBuf2D[2].x + window.c_x),
                 (int)(vBuf2D[2].y + window.c_y),
                 (int)(vBuf2D[0].x + window.c_x),
                 (int)(vBuf2D[0].y + window.c_y));
        }

        objs[0].rotation.x += 0.00001f;
        objs[0].rotation.y += 0.001f;
        objs[0].rotation.z -= 0.00001f;
    }

    swapbuffers();
}
