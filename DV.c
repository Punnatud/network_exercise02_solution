#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define INFINITY 9999

typedef struct {
  int id;
  int distance[MAX_NODES];
  int nextHop[MAX_NODES];
} Node;

Node nodes[MAX_NODES];
int costMatrix[MAX_NODES][MAX_NODES];
int numNodes;

void initializeNodes() {
  for (int i = 0; i < numNodes; i++) {
    for (int j = 0; j < numNodes; j++) {
      if (i == j) {
        nodes[i].distance[j] = 0;
        nodes[i].nextHop[j] = i;
      } else if (costMatrix[i][j] != 0) {
        nodes[i].distance[j] = costMatrix[i][j];
        nodes[i].nextHop[j] = j;
      } else {
        nodes[i].distance[j] = INFINITY;
        nodes[i].nextHop[j] = -1;
      }
    }
  }
}

void updateDistanceVector(int node) {
  for (int i = 0; i < numNodes; i++) {
    if (i != node) {
      for (int j = 0; j < numNodes; j++) {
        if (nodes[node].distance[j] >
            costMatrix[node][i] + nodes[i].distance[j]) {
          nodes[node].distance[j] = costMatrix[node][i] + nodes[i].distance[j];
          nodes[node].nextHop[j] = i;
        }
      }
    }
  }
}

void printRoutingTable() {
  for (int i = 0; i < numNodes; i++) {
printf("Routing table for node %c:\n", i+'A'== 'E' ? 'S' : i+'A');
printf("Destination\tDistance\tNext Hop\n");
for (int j = 0; j < numNodes; j++) {
  if (nodes[i].distance[j] == INFINITY) {
    printf("% d\t\tINFINITY\t -\n", j);
  } else {
    printf("%c\t\t % d\t\t %c\n", j + 'A' == 'E' ? 'S' : j+'A', nodes[i].distance[j],
           nodes[i].nextHop[j] + 'A' == 'E' ? 'S' : nodes[i].nextHop[j] + 'A');
  }
}
printf("\n");
  }
}

int main() {
  printf("Enter the number of nodes : ");
  scanf("%d", &numNodes);

  printf("Enter the cost matrix :\n");
  for (int i = 0; i < numNodes; i++) {
    for (int j = 0; j < numNodes; j++) {
      scanf("%d", &costMatrix[i][j]);
    }
  }

  initializeNodes();

  int converged = 0;
  int count = 0;
  printf("Initial Tables\n");
  printRoutingTable();
  while (!converged) {
    count++;
    printf("====================================================\n");
    printf("Iteration %d Time = %d\n", count, count*100);
    converged = 1;
    for (int i = 0; i < numNodes; i++) {
      int oldDistance[MAX_NODES];
      for (int j = 0; j < numNodes; j++) {
        oldDistance[j] = nodes[i].distance[j];
      }
      updateDistanceVector(i);
      for (int j = 0; j < numNodes; j++) {
        if (nodes[i].distance[j] != oldDistance[j]) {
          converged = 0;
        }
      }
    }
    printRoutingTable();

    if(converged){
      printf("ends in %d iterations and using Time = %d\n", count, count*100);
    }

  }


  return 0;
}
