#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct connection
{
  int a;
  int b;
};
struct graph
{
    int* elements;
    int elements_count;
    struct connection* connections;
    int connections_count;
};

int main()
{
	int i, j;
    struct graph g;
    
    g.connections_count = 0;
    g.elements_count = 0;
    g.elements = NULL;
    g.connections = NULL;
    int finished = 0;
    
    while(!finished)
    {
        printf("1.Add element\n2.Add connection\n3.Generate graphviz code\n4.Delete element\n5.Print sorted elements\n6.Finish\n");
        int in;
        scanf("%d", &in);
        switch(in)
        {
            case 1:
            {
                g.elements_count++;
                g.elements = (int*)realloc(g.elements, sizeof(int) * g.elements_count);
                printf("Type element number: ");
                int a;
                scanf("%d", &a);
                g.elements[g.elements_count - 1] = a;
                break;
            }
            case 2:
            {
                g.connections_count++;
                g.connections = (struct connection*)realloc(g.connections, sizeof(struct connection) * g.connections_count);
                printf("Type 2 values: ");
                int a, b;
                scanf("%d %d", &a, &b);
                g.connections[g.connections_count - 1].a = a;
                g.connections[g.connections_count - 1].b = b;
                
                break;
            }
            case 3:
            {
                char* filename = "out.txt";
                FILE* f = fopen(filename, "w");
                fprintf(f, "graph g {\n");
                for(i = 0; i != g.elements_count; ++i)
                    fprintf(f, "%d;\n", i);
                for(i = 0; i != g.connections_count; ++i)
                {
                    fprintf(f, "%d -- %d;\n", g.connections[i].a, g.connections[i].b);
                }
                fprintf(f, "}");
                fclose(f);
                printf("Code is written to out.txt!\n");
                break;
            }
            case 4:
            {
            	printf("Enter the element number:");
            	int in;
            	scanf("%d", &in);
            
				for(i = 0; i < g.elements_count; ++i)
				{
					if(g.elements[i] == in)
					{
						g.elements_count--;
						for(j = i; j < g.elements_count; ++j)
						{
							g.elements[j] = g.elements[j + 1];
						}
						g.elements = (int*)realloc(g.elements, sizeof(int) * g.elements_count);
						i--;
					}
				}
                for(i = 0; i < g.connections_count; ++i)
				{
					if((g.connections[i].a == in) || (g.connections[i].b == in))
					{
						g.connections_count--;
						for(j = i; j < g.connections_count; ++j)
						{
							g.connections[j] = g.connections[j + 1];
						}
						g.connections = (struct connection*)realloc(g.connections, sizeof(struct connection) * g.connections_count);
						i--;
					}
				}
				if(g.elements_count == 0)
                    g.elements = NULL;
                if(g.connections_count == 0)
                    g.connections = NULL;
				break;
            }
            case 5:
            {
            	int* adj_connections_count = (int*)malloc(sizeof(int) * g.elements_count);
            	int* printed = (int*)malloc(sizeof(int) * g.elements_count);
            	for(i = 0; i != g.elements_count; ++i)
            	{
            		adj_connections_count[i] = 0;
					printed[i] = 0;	
				}
            		
            	for(i = 0; i != g.connections_count; ++i)
            	{
					int a_index, b_index;
					for(j = 0; j != g.elements_count; ++j)
					{
						if(g.elements[j] == g.connections[i].a)
							a_index = j;
						if(g.elements[j] == g.connections[i].b)
							b_index = j;
					}
            		adj_connections_count[a_index]++;
            		adj_connections_count[b_index]++;
				}
				int max;
            	int maxi = 0;
            	for(i = 0; i != g.elements_count; ++i)
            	{
            		max = 0;
            		for(j = 0; j != g.elements_count; ++j)
            		{
            			if((adj_connections_count[j] >= max) && (!printed[j]))
						{
							max = adj_connections_count[j]; 
							maxi = j;	
						} 	
					}
					printed[maxi] = 1;
					printf("Element %d: %d connections\n", g.elements[maxi], max);

				}
				free(printed);
				free(adj_connections_count);
				break;
			}
            case 6:
            {
                finished = 1;
                break;
            }
            default:
            {
                printf("incorrect input\n");
                break;
            }
            
        };
    }    

    return 0;
}  
