/**
 * @file EdgeConResolution.h
 * @author Vincent Penelle (vincent.penelle@u-bordeaux.fr)
 * @brief  Algorithms to solve directly the EdgeCon problem
 * @version 1
 * @date 2021-10-18
 * 
 * @copyright Creative Commons.
 * 
 */

#ifndef COCA_EDGECONRESOLUTION_H
#define COCA_EDGECONRESOLUTION_H

#include "EdgeConGraph.h"

/**
 * @brief Applies the Floyd-Warshall algorithm to the given cost matrix
 * 
 * @param nbNodes the number of vertices of the graph
 * @param costMatrix the cost matrix of the graph
 * 
 * @pre costMatrix is a matrix of int of size nbNodes * nbNodes ; costMatrix[i][j] >= 0 if there is an edge between i and j ; else it is negative
 */
void floydWarshallFromCostMatrix(int nbNodes, int ** costMatrix) ;

/**
 * @brief get the cost matrix corresponding to the edgeCon Graph
 * @brief the cost of the (i,j) is 0 if there is an homogeneous edge between i and j ; 1 if the edge is a translator ; -1 else (if there is no edge or the edge is heterogeneous but not a translator)
 * @brief be carefull this DO NOT CREATE the matrix of shortest ways
 * @param graph the given problem
 * @param adjMatrix the adjacency matrix according to the graph ; the cost matrix is put on it
 */
void getCostMatrix(EdgeConGraph graph, int ** adjMatrix) ;

/**
 * @brief Calculate the most heavy path of the given graph
 * 
 * @param graph the graph we would like the most heavy path
 * @return int the weight of the most heavy path
 * @pre graph has already the translators sets
 */
int mostHeavyPath(EdgeConGraph graph, int ** adjMatrix) ;

/**
 * @brief Brute Force Algorithm. If there is a result, the solution will be stored in @param graph, and its homogeneous components updated. If no solution, graph won't be modified. Returns the maximal cost of communication for any choice of translators.
 * 
 * @param graph An instance of the problem.
 * @return the maximal cost that two nodes communicate with for any possible set of transducers of minimal size. Returns -1 if there is no solution (i.e., the graph is not connex).
 * 
 * @pre graph must be valid.
 */
int BruteForceEdgeCon(EdgeConGraph graph);

/**
 * @brief Get the First subset by lexical order, of size size and with k elements. Typically, it is 0,...,0,1,...,1 ; with k 1 and size - k 0
 * if set[i] = 1 then i is on the set ; else it is not
 * @param size the size of the set
 * @param k the number of element of the subset
 * @param set the set we put the elements
 */
void getFirstSet(int size, int k, int * set) ;

/**
 * @brief Get the subset of the set of size size with k element which is the next subset by lexical order
 * 
 * @param size the size of the set
 * @param k the number of element of the subset
 * @param set the current subset
 * @return 1 if there is a next set ; 0 else (ie there is no next set)
 */
int getNextSet(int size, int k, int * set) ;

/**
 * @brief Get the Heterogeneous Edge Set corresponding to the given graph ; back[i] correspond to an heterogeneous edge ; and it is an int tab of type j, k ; when the heterogeneous edge is (j,k)
 * 
 * @param graph the graph we would like the edge set
 * @return int** the edge set ; put on size the size of this edge set
 */
int ** getHeterogeneousEdgeSet(EdgeConGraph graph, int * size) ;

/**
 * @brief Reinitialize the translators of graph, and put each edge on subset (according to heterogeneousEdgeSet) on the graph
 * 
 * @param graph the graph we put the translator
 * @param subset the subset of the translator we have to put
 * @param heterogeneousEdgeSet the corresponding heterogeneous edge : if subset[i] == 1, then we put the edge heterogeneousEdgeSet[i]
 * @param size the size of heterogeneousEdgeSet
 */
void putTranslatorCorrespondingToSubset(EdgeConGraph graph, int * subset, int ** heterogeneousEdgeSet, int size) ;
#endif