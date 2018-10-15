/*
    Jakub Wójcik 2018
*/

#if !defined(objLo)
#define objLo 1
// Structure describing point in 3D and 2D space
typedef struct vec3
{
    float x, y, z;
} vec3;

typedef struct vec2
{
    float x,y;
} vec2;

// Structure describing one triangle, called vertex. Points are stored in clockwise order
typedef struct vertex
{
    struct vec3 vector[3];
} vertex;

// Structure describing 3D object
typedef struct obj
{
    struct vertex* ver;
    int count;
    vec3 scale;
    vec3 rotation;
    vec3 displacement;
} obj;

typedef struct objBuffer
{
    struct vertex* ver;
    int maxCount;
    int curCount;
    vec3 scale;
    vec3 rotation;
    vec3 displacement;
} objBuffer;

#endif

//-------------------------
// Functions declarations
//-------------------------

//-------------------------
// Vector
//-------------------------

void displayVector(vec3*);
vec3 createVector(float, float, float);
void mulVectorConst(vec3*, float);
void mulVectorVec(vec3*, vec3*);

//-------------------------
// Vertex constructor and destructor
//-------------------------

vertex createVertex(vec3, vec3, vec3);
void displayVertex(vertex*);
void scaleVertexConst(vertex*, float);
void scaleVertexVec(vertex*, vec3*);
void freeVertex(vertex*);
void freeVertexes(vertex*, int);
//-------------------------
// Obj constructor and destructor
//-------------------------

obj createObj(int);
obj createObjFromVertexes(vertex*, int);
void freeObjs(obj*, int);
void freeObj(obj*);
void displayObj(obj*);
void scaleObjConst(obj*, float);
void scaleObjVec(obj*, vec3*);

//-------------------------
// Obj cube
//-------------------------

obj getCube();

