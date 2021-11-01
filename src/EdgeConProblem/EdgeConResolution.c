#include "EdgeConResolution.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

void getCostMatrix(EdgeConGraph graph, int ** costMatrix) {
    int i, j ;
    Graph g = getGraph(graph) ;
    for (i = 0 ; i < g.numNodes; i++) {
        for (j = 0 ; j < g.numNodes; j++) {
            if (i == j || isEdgeHomogeneous(graph, i, j)) {
                costMatrix[i][j] = 0 ;
            } else if (isTranslator(graph, i, j)){
                costMatrix[i][j] = 1 ;
            } else {
                // we have an heterogeneous edge which is not a translator : this edge does not exists
                // or we doesn't have any edge
                costMatrix[i][j] = -1 ;
            }
        }
    }
}

void floydWarshallFromCostMatrix(int nbNodes, int ** costMatrix) {
    int i, j, k ;
    for (k = 0 ; k < nbNodes ; k++) {
        for (i = 0 ; i < nbNodes ; i++) {
            for (j = 0 ; j < nbNodes ; j++) {
                if (costMatrix[i][k] >= 0 && costMatrix[k][j] >= 0) {
                    // there is a path from i to k and a path from k to j
                    if (costMatrix[i][k] + costMatrix[k][j] < costMatrix[i][j] || costMatrix[i][j] < 0) {
                        costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j] ;
                    }
                }
            }
        }
    }
}

int mostHeavyPath(EdgeConGraph graph, int ** costMatrix) {
    getCostMatrix(graph, costMatrix) ;
    int nbNodes = getGraph(graph).numNodes ;
    /*fprintf(stderr, "la cost matrix est : \n") ;
    for (int i = 0 ; i < nbNodes ; i++) {
        for (int j = 0 ; j < nbNodes ; j++) {
            fprintf(stderr,"%d ", adjMatrix[i][j]) ;
        }
        fprintf(stderr,"\n") ;
    }*/
    floydWarshallFromCostMatrix(nbNodes, costMatrix) ;
    int max = -1 ;
    /*fprintf(stderr, "Acfter FW, la cost matrix est : \n") ;
    for (int i = 0 ; i < nbNodes ; i++) {
        for (int j = 0 ; j < nbNodes ; j++) {
            fprintf(stderr,"%d ", adjMatrix[i][j]) ;
        }
        fprintf(stderr,"\n") ;
    }*/

    for (int i = 0 ; i < nbNodes ; i++) {
        for (int j = 0 ; j < nbNodes ; j++) {
            if (costMatrix[i][j] == -1) {
                return 0 ;
            }
            if (costMatrix[i][j] > max) {
                max = costMatrix[i][j] ;
            }
        }
    }
    return max ;
}

void getFirstSet(int size, int k, int * set) {
    for (int i = 0; i < k ; i++) {
        set[i] = 1 ;
    }
    for (int i = k ; i < size ; i++) {
        set[i] = 0 ;
    }
}

int getNextSet(int size, int k, int * set) {
    // we search for the first element which could be moved
    // it is the first i with set[i] = 1 and set[i+1] = 0
    int firstMovableElement = -1 ;
    for (int i = 0 ; i < size - 1 ; i++) {
        if (set[i+1] == 0 && set[i] == 1) {
            firstMovableElement = i ;
            break ;
        }
    }
    if (firstMovableElement == -1) {
        // there is no next set
        return 0 ;
    }
    // else the idea is this :
    // set[i] for i from size - 1 to firstMovableElement+2 don't change
    // set[firstMovableElement + 1] = 1
    // set[firstMovableElement] = 0
    set[firstMovableElement + 1] = 1 ;
    set[firstMovableElement] = 0 ;
    // after, we call nbOne the number of element which are from size - 1 to firstMovableElement now
    int nbOne = 0 ;
    for (int i = size - 1 ; i > firstMovableElement ; i--) {
        if (set[i] == 1)
            nbOne ++ ;
    }
    // the k - nbOne first bits are at 1 ; the other are at 0
    for (int i = 0; i < k - nbOne ; i++) {
        set[i] = 1 ;
    }
    for (int i = k - nbOne ; i <= firstMovableElement ; i++) {
        set[i] = 0 ;
    }
    return 1 ;
}

int ** getHeterogeneousEdgeSet(EdgeConGraph graph, int * size) {
    (*size) = getNumHeteregeneousEdges(graph) ;
    Graph g = getGraph(graph) ;
    int curNb = 0 ;
    int ** hetEdgeSet = (int **) malloc((*size)* sizeof(int*)) ;
    for (int i = 0 ; i < g.numNodes ; i++) {
        for (int j = 0 ; j <= i ; j++) { // because the graph is unoriented, i,j is the same edge than j,i
            if (isEdgeHeterogeneous(graph, i, j)) {
                hetEdgeSet[curNb] = (int *) malloc(2*sizeof(int)) ;
                hetEdgeSet[curNb][0] = i ;
                hetEdgeSet[curNb][1] = j ;
                curNb ++ ;
            }
        }
    }
    return hetEdgeSet ;
}

void putTranslatorCorrespondingToSubset(EdgeConGraph graph, int * subset, int ** heterogeneousEdgeSet, int size) {
    resetTranslator(graph) ;
    for (int i = 0 ; i < size ; i++) {
        if (subset[i]) {
            addTranslator(graph, heterogeneousEdgeSet[i][0], heterogeneousEdgeSet[i][1]) ;
        }
    }
}

#include <stdio.h>

int BruteForceEdgeCon(EdgeConGraph graph)
{
    int N = getNumComponents(graph) - 1 ;
    int existConnex = 0 ;
    if (N  <= 0) {
        // only one homogeneous component : we don't have to add any translator : return 0
        return 0 ;
    }
    //fprintf(stderr, "here\n") ;
    // here, there is N >= 1 translators to add
    Graph g = getGraph(graph) ;
    int size = 0;
    int mostHeavy = -1 ;
    int ** costMatrix = malloc(g.numNodes *sizeof(int*)) ;
    for (int i = 0; i < g.numNodes; i++) {
        costMatrix[i] = malloc(g.numNodes * sizeof(int)) ;
    }
    costMatrix[0][0] = 1 ;
    int ** hetereogeneousEdgeSet = getHeterogeneousEdgeSet(graph, &size) ;
    /*for (int i = 0 ; i < size ; i++) {
        fprintf(stderr, "l'het est (%d, %d)\n", hetereogeneousEdgeSet[i][0], hetereogeneousEdgeSet[i][1]) ;
    }*/
    fprintf(stderr, "la size est %d ; N = %d\n", size, N) ;
    int * correspondingSet = malloc(sizeof(int)*size) ;
    getFirstSet(size, N, correspondingSet) ;
    do {
        putTranslatorCorrespondingToSubset(graph, correspondingSet, hetereogeneousEdgeSet, size) ;
        int currentMostHeavy = mostHeavyPath(graph, costMatrix) ;
        //fprintf(stderr, "le most heavy est %d\n", currentMostHeavy) ;
        if (currentMostHeavy > mostHeavy) {
            mostHeavy = currentMostHeavy ;
        }
        if (currentMostHeavy > 0) {
            existConnex = 1 ;
        }
    } while(getNextSet(size, N, correspondingSet)) ;
    for (int i = 0; i < g.numNodes; i++) {
        free(costMatrix[i]) ;
    }
    free(costMatrix) ;
    for (int i = 0 ; i < size ; i ++) {
        free(hetereogeneousEdgeSet[i]) ;
    }
    free(hetereogeneousEdgeSet) ;
    free(correspondingSet) ;
    return existConnex ? mostHeavy : -1 ;
}
