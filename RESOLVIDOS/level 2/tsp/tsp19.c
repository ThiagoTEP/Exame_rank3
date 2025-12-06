#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define MAX 11

typedef struct
{
    float x, y;
} City;

City cities[MAX];

int n;
float dist[MAX][MAX];
int used[MAX];
int route[MAX];
float best = 1e9;

float distance(City a, City b)
{
    return (sqrtf((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
}

void solve(int k, int lenght)
{
    if(k == n)
    {
        lenght += dist[route[n -1]][route[0]];
        if(lenght < best)
            best = lenght;
        return;
    }
    int i = 0;
    while(i < n)
    {
        if(!used[i])
        {
            used[i] = 1;
            route[k] = i;
            float new_lenght = lenght;
            if(k > 0)
                new_lenght += dist[route[k - 1]][i];
            solve(k + 1, new_lenght);
            used[i] = 0;
        }
        i++;
    }
}

int main(void)
{
    n = 0;

    while(fscanf(stdin, " %f, %f", &cities[n].x, &cities[n].y) == 2)
        n++;

    int i = 0;
    while(i < n)
    {
        int j = 0;
        while(j < n)
        {
            dist[i][j] = distance(cities[i], cities[j]);
            j++;
        }
        i++;
    }
    solve(0 , 0.0);
    fprintf(stdout, "%.2f\n", best);
    return 0;
}