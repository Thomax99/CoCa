
#include "EdgeConReduction.h"
#include "Z3Tools.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Z3_ast getVariableIsIthTranslator(Z3_context ctx, int node1, int node2, int number)
{
    char name[40];
    if (node1 < node2)
        snprintf(name, 40, "[(%d,%d),%d]", node1, node2, number);
    else
        snprintf(name, 40, "[(%d,%d),%d]", node2, node1, number);
    return mk_bool_var(ctx, name);
}

Z3_ast getVariableParent(Z3_context ctx, int child, int parent)
{
    char name[40];
    snprintf(name, 40, "p_[%d,%d]", child, parent);
    return mk_bool_var(ctx, name);
}

Z3_ast getVariableLevelInSpanningTree(Z3_context ctx, int level, int component)
{
    char name[40];
    snprintf(name, 40, "l_[%d,%d]", component, level);
    return mk_bool_var(ctx, name);
}

/**
 * @brief Get a formula which ensure that a given translator is associated to at most on edge
 * 
 * @param ctx The solver context
 * @param edgeSet The associated edgeSet, of type edgeSet[i] = (j,k) ; when j, k is a set of edge.
 * @param nbEdges The number of edges on the edgeSet
 * @param translatorNumber the number of the given translator
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaOneTranslatorAtMostOneEdge(Z3_context ctx, int ** edgeSet, int nbEdges, int translatorNumber) {
    fprintf(stderr, "nTrans is %d\n", translatorNumber) ;
    Z3_ast * formulasEachEdge = malloc(sizeof(Z3_ast)*(nbEdges*(nbEdges - 1) / 2)) ; // formulasEachEdge[i] contains a formula not x_e,i or not x_e',i*
    fprintf(stderr, "nTrans is %d\n", translatorNumber) ;
    int curFormulaNb = 0 ;
    for (int e = 0 ; e < nbEdges ; e++) {
        for (int e_p = e + 1 ; e_p < nbEdges ; e_p++) {
            Z3_ast form_Or[] = {Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSet[e][0], edgeSet[e][1], translatorNumber)),
                    Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSet[e_p][0], edgeSet[e_p][1], translatorNumber))} ;
            formulasEachEdge[curFormulaNb] = Z3_mk_or(ctx, 2, form_Or) ;
            curFormulaNb ++ ;
        }
    }
    return Z3_mk_and(ctx, curFormulaNb, formulasEachEdge) ;
}

/**
 * @brief Get a formula which ensure that any translator is associated to at most on edge
 * 
 * @param ctx The solver context
 * @param edgeSet The associated edgeSet, of type edgeSet[i] = (j,k) ; when j, k is a set of edge.
 * @param nbEdges The number of edges on the edgeSet
 * @param nTranslators The number of translators
 * @return Z3_ast The corresponding formula
 * @pre graph must be an initialized EdgeConGraph with computed connected components.
 */
Z3_ast getFormulaForeachOneTranslatorAtMostOneEdge(Z3_context ctx, int ** edgeSet, int nbEdges, int nTranslators) {
    Z3_ast * formulasEachTranslator = malloc(sizeof(Z3_ast)*nTranslators) ;
    for (int i = 0 ; i < nTranslators ; i++) {
         fprintf(stderr, "i is %d\n", i) ;
        formulasEachTranslator[i] = getFormulaOneTranslatorAtMostOneEdge(ctx, edgeSet, nbEdges, i) ;
    }
    return Z3_mk_and(ctx, nTranslators, formulasEachTranslator) ;
}

/**
 * @brief Get a formula which ensure that any translator on the graph is associated to at most on edge, and
 * any edge is associated to at most one translator
 * @param ctx The solver context.
 * @param edgeSet The associated edgeSet, of type edgeSet[i] = (j,k) ; when j, k is a set of edge.
 * @param nbEdges The number of edges on the edgeSet
 * @param nTranslators The number of translators
 * @return Z3_ast The corresponding formula.
 * @pre graph must be an initialized EdgeConGraph with computed connected components.
 */
Z3_ast getFormulaForEachOneTranslatorOneEdge(Z3_context ctx, int ** edgeSet, int nbEdges, int nTranslators) {
    return getFormulaForeachOneTranslatorAtMostOneEdge(ctx, edgeSet, nbEdges, nTranslators) ;
}

Z3_ast EdgeConReduction(Z3_context ctx, EdgeConGraph edgeGraph, int cost)
{
    // Z3_mk_or --> return an or between all the given variables on the given array on parameters
    // Z3_mk_and --> return an and between all the given variables on the given array on parameters
    // Z3_mk_not --> return the negation of the given variable
    // TODO
    Graph g = getGraph(edgeGraph) ;
    int nbEdges = sizeG(g) ;
    int ** edgeSet = malloc(nbEdges * sizeof(int*)) ;
    int curNb = 0 ;
    for (int i = 0 ; i < g.numNodes; i++) {
        for (int j = i+1 ; j < g.numNodes ; j++) {
            if (isEdge(g, i, j)) {
                edgeSet[curNb] = malloc(2*sizeof(int)) ;
                edgeSet[curNb][0] = i ;
                edgeSet[curNb][1] = j ;
                curNb ++ ;
            }
        }
    }
    return getFormulaForEachOneTranslatorOneEdge(ctx, edgeSet, nbEdges, getNumComponents(edgeGraph) - 1);
}

void getTranslatorSetFromModel(Z3_context ctx, Z3_model model, EdgeConGraph graph)
{
    return;
}
