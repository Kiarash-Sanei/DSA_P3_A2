#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node **neighbors;
    int neighborsCount;
    int distance;
} Node;

void freeTree(Node **tree, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(tree[i]->neighbors);
        free(tree[i]);
    }
}

void setDistance(Node *root, int rootOfRoot)
{
    int distance = root->distance + 1;
    for (int i = 0; i < root->neighborsCount; i++)
    {
        if (root->neighbors[i]->value != rootOfRoot)
        {
            root->neighbors[i]->distance = distance;
            setDistance(root->neighbors[i], root->value);
        }
    }
}

int checkCondition(Node **tree, int n)
{
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tree[i]->distance == tree[j]->distance && tree[i]->neighborsCount != tree[j]->neighborsCount)
            {
                flag = 0;
                break;
            }
        }
        if (!flag)
        {
            break;
        }
    }
    return flag;
}

int main()
{
    int n;
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("-1\n");
        return 0;
    }

    Node *tree[n];
    for (int i = 0; i < n; i++)
    {
        tree[i] = (Node *)malloc(sizeof(Node));
        tree[i]->value = i + 1;
        tree[i]->neighbors = (Node **)malloc(sizeof(Node *) * n);
        tree[i]->neighborsCount = 0;
    }

    int u, v;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &u, &v);
        u--;
        v--;

        tree[u]->neighbors[tree[u]->neighborsCount++] = tree[v];
        tree[v]->neighbors[tree[v]->neighborsCount++] = tree[u];
    }

    Node *root;
    int ans = -1;
    for (int i = 0; i < n; i++)
    {
        root = tree[i];
        root->distance = 0;
        setDistance(root, 0);
        if (checkCondition(tree, n))
        {
            ans = root->value;
            break;
        }
    }

    printf("%d\n", ans);

    freeTree(tree, n);

    return 0;
}