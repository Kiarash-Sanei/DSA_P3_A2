#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int *neighbors;
    int neighborsCount;
    int distance;
} Node;

void freeTree(Node *tree, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(tree[i].neighbors);
    }
    free(tree);
}

void setDistance(Node *tree, int root, int parent, int curr_distance)
{
    tree[root].distance = curr_distance;

    for (int i = 0; i < tree[root].neighborsCount; i++)
    {
        int neighbor = tree[root].neighbors[i];
        if (neighbor != parent)
        {
            setDistance(tree, neighbor, root, curr_distance + 1);
        }
    }
}

int checkCondition(Node *tree, int n)
{
    int max_distance = 0;

    for (int i = 0; i < n; i++)
    {
        if (tree[i].distance > max_distance)
        {
            max_distance = tree[i].distance;
        }
    }

    int *level_degrees = calloc(max_distance + 1, sizeof(int));
    int *level_counts = calloc(max_distance + 1, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int dist = tree[i].distance;
        if (level_counts[dist] == 0)
        {
            level_degrees[dist] = tree[i].neighborsCount;
        }
        else if (level_degrees[dist] != tree[i].neighborsCount)
        {
            free(level_degrees);
            free(level_counts);
            return 0;
        }
        level_counts[dist]++;
    }

    free(level_degrees);
    free(level_counts);
    return 1;
}

int main()
{
    int n;
    scanf("%d", &n);

    Node *tree = malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++)
    {
        tree[i].neighbors = malloc(n * sizeof(int));
        tree[i].neighborsCount = 0;
    }

    int u, v;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &u, &v);
        u--;
        v--;

        tree[u].neighbors[tree[u].neighborsCount++] = v;
        tree[v].neighbors[tree[v].neighborsCount++] = u;
    }

    int ans = -1;
    for (int i = 0; i < n && ans == -1; i++)
    {
        setDistance(tree, i, -1, 0);
        if (checkCondition(tree, n))
        {
            ans = i + 1;
        }
    }

    printf("%d\n", ans);
    freeTree(tree, n);
    return 0;
}