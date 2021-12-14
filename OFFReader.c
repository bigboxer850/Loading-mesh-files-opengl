#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct Vt {
	float x, y, z;
}Vertex;

typedef struct Pgn {
	int noSides;
	int* v;
}Polygo;

typedef struct offmodel {
	Vertex* vertices;
	Polygo* polygons;
	int numberOfVertices;
	int numberOfPolygons;
}OffModel;

OffModel* readOffFile(char* OffFile) {
	FILE* input;
	char typ[10];
	int noEdges;
	int i, j;
	float x, y, z;
	int n, v;
	int nv, np;
	OffModel* model;
	input = fopen(OffFile, "r");
	fscanf(input, "%s", typ);
	// First line should be OFF
	if(strcmp(typ,"OFF")) {
		printf("Not a OFF file");
		exit(1);
	}
	/* Read the no. of vertices, faces and edges */
	fscanf(input, "%d", &nv);
	fscanf(input, "%d", &np);
	fscanf(input, "%d", &noEdges);

	model = (OffModel*)malloc(sizeof(OffModel));
	model->numberOfVertices = nv;
	model->numberOfPolygons = np;


	/* allocate required data */
	model->vertices = (Vertex*)malloc(nv * sizeof(Vertex));
	model->polygons = (Polygo*)malloc(np * sizeof(Polygo));


	/* Read the vertices' location*/
	for (i = 0; i < nv; i++) {
		fscanf(input, "%f %f %f", &x, &y, &z);
		(model->vertices[i]).x = x;
		(model->vertices[i]).y = y;
		(model->vertices[i]).z = z;
	}

	/* Read the Polygons */
	for (i = 0; i < np; i++) {
		/* No. of sides of the polygon (Eg. 3 => a triangle) */
		fscanf(input, "%d", &n);

		(model->polygons[i]).noSides = n;
		(model->polygons[i]).v = (int*)malloc(n * sizeof(int));
		/* read the vertices that make up the polygon */
		for (j = 0; j < n; j++) {
			fscanf(input, "%d", &v);
			(model->polygons[i]).v[j] = v;
		}
	}

	fclose(input);
	return model;
}

int FreeOffModel(OffModel* model)
{
	int i, j;
	if (model == NULL)
		return 0;
	free(model->vertices);
	for (i = 0; i < model->numberOfPolygons; ++i)
	{
		if ((model->polygons[i]).v)
		{
			free((model->polygons[i]).v);
		}
	}
	free(model->polygons);
	free(model);
	return 1;
}

/*int main(int argc, char ** argv) {
	// testing code
	Polygon * p;
	Vertex * v;
	int noVerts, noPolys;
	int i, j;
	OffModel *model = readOffFile("1duk.off");

	printf("OFF\n");
	printf("%d %d 0 \n", model->numberOfVertices, model->numberOfPolygons );
	for(i = 0;i < model->numberOfVertices;i ++) {
		printf("%f %f %f \n", (model->vertices[i]).x, (model->vertices[i]).y, (model->vertices[i]).z);
	}
	for(i = 0;i < model->numberOfPolygons;i ++) {
		printf("%d ", (model->polygons[i]).noSides);
		for(j = 0;j < (model->polygons[i]).noSides;j ++) {
			printf("%d ", (model->polygons[i]).v[j]);
		}
		printf("\n");
	}

	FreeOffModel(model);
	return 0;
}*/


