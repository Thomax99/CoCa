
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
 * @brief Get a formula which ensure that a given edge is associated to at most one translator
 * 
 * @param ctx The solver context
 * @param edgeSource the source of the dge.
 * @param edgeTarget the target of the edge
 * @param nTranslators the number of translators
 * @return Z3_ast The corresponding formula
 */

Z3_ast getFormulaOneEdgeAtMostOneTranslator(Z3_context ctx, int edgeSource, int edgeTarget, int nTranslators) {
    Z3_ast * formulasEachTranslator = malloc(sizeof(Z3_ast)*(nTranslators*(nTranslators - 1) / 2)) ; // formulasEachEdge[i] contains a formula not x_e,i or not x_e,j
    int curFormulaNb = 0 ;
    for (int i = 0 ; i < nTranslators ; i++) {
        for (int j = i + 1 ; j < nTranslators ; j++) {
            Z3_ast form_Or[] = {Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSource, edgeTarget, i)),
                    Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSource, edgeTarget, j))} ;
            formulasEachTranslator[curFormulaNb] = Z3_mk_or(ctx, 2, form_Or) ;
            curFormulaNb ++ ;
        }
    }
    Z3_ast outputAst = Z3_mk_and(ctx, curFormulaNb, formulasEachTranslator) ;
    free(formulasEachTranslator) ;
    return outputAst ;
}

/**
 * @brief Get a formula which ensure that any edge is associated to at most on translator : this part of formula corresponds to \phi_{1,2}
 * 
 * @param ctx The solver context
 * @param edgeSet The associated edgeSet, of type edgeSet[i] = (j,k) ; when j, k is a set of edge.
 * @param nbEdges The number of edges on the edgeSet
 * @param nTranslators The number of translators
 * @return Z3_ast The corresponding formula
 * @pre graph must be an initialized EdgeConGraph with computed connected components.
 */
Z3_ast getFormulaForeachOneEdgeAtMostOneTranslator(Z3_context ctx, int ** edgeSet, int nbEdges, int nTranslators) {
    Z3_ast * formulasEachEdge = malloc(sizeof(Z3_ast)*nbEdges) ;
    for (int e = 0 ; e < nbEdges ; e++) {
        formulasEachEdge[e] = getFormulaOneEdgeAtMostOneTranslator(ctx, edgeSet[e][0], edgeSet[e][1], nTranslators) ;
    }
    Z3_ast output =  Z3_mk_and(ctx, nbEdges, formulasEachEdge) ;
    free(formulasEachEdge) ;
    return output ;
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
    Z3_ast * formulasEachEdge = malloc(sizeof(Z3_ast)*(nbEdges*(nbEdges - 1) / 2)) ; // formulasEachEdge[i] contains a formula not x_e,i or not x_e',i*
    int curFormulaNb = 0 ;
    for (int e = 0 ; e < nbEdges ; e++) {
        for (int e_p = e + 1 ; e_p < nbEdges ; e_p++) {
            Z3_ast form_Or[] = {Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSet[e][0], edgeSet[e][1], translatorNumber)),
                    Z3_mk_not(ctx, getVariableIsIthTranslator(ctx, edgeSet[e_p][0], edgeSet[e_p][1], translatorNumber))} ;
            formulasEachEdge[curFormulaNb] = Z3_mk_or(ctx, 2, form_Or) ;
            curFormulaNb ++ ;
        }
    }
    Z3_ast output = Z3_mk_and(ctx, curFormulaNb, formulasEachEdge) ;
    free(formulasEachEdge) ;
    return output ;
}

/**
 * @brief Get a formula which ensure that any translator is associated to at most on edge : this part of formula corresponds to \phi_{1,1}
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
        formulasEachTranslator[i] = getFormulaOneTranslatorAtMostOneEdge(ctx, edgeSet, nbEdges, i) ;
    }
    Z3_ast output =  Z3_mk_and(ctx, nTranslators, formulasEachTranslator) ;
    free(formulasEachTranslator) ;
    return output ;
}

/**
 * @brief Get a formula which ensure that any translator on the graph is associated to at most on edge, and
 * any edge is associated to at most one translator : this part of formula corresponds to \phi_{1} on the report
 * @param ctx The solver context.
 * @param edgeSet The associated edgeSet, of type edgeSet[i] = (j,k) ; when j, k is a set of edge.
 * @param nbEdges The number of edges on the edgeSet
 * @param nTranslators The number of translators
 * @return Z3_ast The corresponding formula.
 * @pre graph must be an initialized EdgeConGraph with computed connected components.
 */
Z3_ast getFormulaForEachOneTranslatorOneEdge(Z3_context ctx, int ** edgeSet, int nbEdges, int nTranslators) {
    Z3_ast contraints [2] ;
    contraints[0] = getFormulaForeachOneTranslatorAtMostOneEdge(ctx, edgeSet, nbEdges, nTranslators) ;
    contraints[1] =  getFormulaForeachOneEdgeAtMostOneTranslator(ctx, edgeSet, nbEdges, nTranslators) ;
    return Z3_mk_and(ctx, 2, contraints) ;
}

/**
 * @brief Get a formula which ensure that one given pear of homogeneous components are not parents of the same vertice. Used by \phi_{2,1}
 * (getFormulaForeachPearHomogeneousComponentNotSameChild)
 * 
 * @param ctx The solver context
 * @param homComp1 The first homogeneous component of the pear
 * @param homComp2 The second homogeneous component of the pear
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast 
 */
Z3_ast getFormulaOnePearHomogeneousComponentNotSameChild(Z3_context ctx, int homComp1, int homComp2, int nbHomogeneousComponents) {
    Z3_ast formulaForeachVertice[nbHomogeneousComponents - 2] ; // - 2 because we don't put the formula for homComp1 and homComp2. See below
    int curNb = 0 ;
    for (int homCur = 0 ; homCur < nbHomogeneousComponents ; homCur ++) {
        if (homCur != homComp1 && homCur != homComp2) {
            // because p_{i,i} is always false, if we put a formula of type
            //  not p_{i,i} or not p_{j,i}, it is always true so useless
            Z3_ast contraints[2] = { Z3_mk_not(ctx, getVariableParent(ctx, homCur, homComp1)),
                                    Z3_mk_not(ctx, getVariableParent(ctx, homCur, homComp2))
                                    } ;
            formulaForeachVertice[curNb] = Z3_mk_or(ctx, 2, contraints) ;
            curNb ++ ;
        }
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents - 2, formulaForeachVertice) ;
}

/**
 * @brief Get a formula which ensure that foreach pear of differents homogeneous components, they are not the parent of the same vertice :
 * corresponds to \phi_{2,1}
 * 
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast 
 */
Z3_ast getFormulaForeachPearHomogeneousComponentNotSameChild(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachPear[nbHomogeneousComponents*(nbHomogeneousComponents-1)/2] ;
    int curNb = 0 ;
    for (int homComp1 = 0 ; homComp1 < nbHomogeneousComponents ; homComp1 ++) {
        for (int homComp2 = homComp1 + 1 ; homComp2 < nbHomogeneousComponents ; homComp2 ++) {
            formulaForeachPear[curNb++] = getFormulaOnePearHomogeneousComponentNotSameChild(ctx, homComp1, homComp2, nbHomogeneousComponents) ;
        }
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents*(nbHomogeneousComponents-1)/2, formulaForeachPear) ;
}

/**
 * @brief Get a formula which ensure that, for a given homogeneous component, if it depth is 0, then it doesn't have any parent :
 * this formula is used by \phi_{2,2} (getFormulaForeachHomogeneousComponentIfDepth0NoParents)
 * 
 * @param ctx The solver context
 * @param currentHomogeneousComponent the given homogeneous component
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 * @warning this formula is not in CNF
 */
Z3_ast getFormulaOneHomogeneousComponentIfDepth0NoParents(Z3_context ctx, int currentHomogeneousComponent, int nbHomogeneousComponents) {
    Z3_ast formulaNoParents[nbHomogeneousComponents-1] ;
    int nbCur = 0 ;
    for(int hom = 0 ; hom < nbHomogeneousComponents ; hom ++) {
        if (hom != currentHomogeneousComponent) {
            // we don't put not p_{i,i} because it is already false
            formulaNoParents[nbCur] = Z3_mk_not(ctx, getVariableParent(ctx, currentHomogeneousComponent, hom)) ;
            nbCur ++ ;
        }
    }
    return Z3_mk_implies(ctx, getVariableLevelInSpanningTree(ctx, 0, currentHomogeneousComponent), Z3_mk_and(ctx, nbHomogeneousComponents - 1, formulaNoParents)) ;
}


/**
 * @brief Get a formula which ensure that, foreach homogeneous component, if it depth is 0, then it doesn't have any parent :
 * this formula corresponds to \phi_{2,2}
 * 
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachHomogeneousComponentIfDepth0NoParents(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachComp[nbHomogeneousComponents] ;
    for(int curHom = 0 ; curHom < nbHomogeneousComponents ; curHom ++) {
        formulaForeachComp[curHom] = getFormulaOneHomogeneousComponentIfDepth0NoParents(ctx, curHom, nbHomogeneousComponents) ;
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents, formulaForeachComp) ;
}

/**
 * @brief Get a formula which ensure that, for a given homogeneous component, if it depth is not 0, then it has at least one parent :
 * this formula is used by \phi_{2,3} (getFormulaForeachHomogeneousComponentIfNotDepth0HasParent)
 *
 * @param ctx The solver context
 * @param currentHomogeneousComponent the given homogeneous component
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 * @warning this formula is not in CNF
 */
Z3_ast getFormulaOneHomogeneousComponentIfNotDepth0HasParents(Z3_context ctx, int currentHomogeneousComponent, int nbHomogeneousComponents) {
    Z3_ast formulaHasParents[nbHomogeneousComponents-1] ;
    int nbCur = 0 ;
    for(int hom = 0 ; hom < nbHomogeneousComponents ; hom ++) {
        if (hom != currentHomogeneousComponent) {
            // we don't put not p_{i,i} because it is already false
            formulaHasParents[nbCur] = getVariableParent(ctx, currentHomogeneousComponent, hom) ;
            nbCur ++ ;
        }
    }
    return Z3_mk_implies(ctx, Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, 0, currentHomogeneousComponent)), Z3_mk_or(ctx, nbHomogeneousComponents - 1, formulaHasParents)) ;
}

/**
 * @brief Get a formula which ensure that, foreach homogeneous component, if it depth is not 0, then it has at least one parent :
 * this formula corresponds to \phi_{2,3}
 * 
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachHomogeneousComponentIfNotDepth0HasParent(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachComp[nbHomogeneousComponents] ;
    for(int curHom = 0 ; curHom < nbHomogeneousComponents ; curHom ++) {
        formulaForeachComp[curHom] = getFormulaOneHomogeneousComponentIfNotDepth0HasParents(ctx, curHom, nbHomogeneousComponents) ;
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents, formulaForeachComp) ;
}


/**
 * @brief Get a formula which ensure that at most one homogeneous component has a depth of 0.
 * It is equivalent to, foreach pear of homogeneous component, at least one of the pear is not at depth 0 :
 * this formula corresponds to phi_{2,4}
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaJustOneHomogeneousComponentIsRoot(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachPear[nbHomogeneousComponents*(nbHomogeneousComponents-1)/2] ;
    int nbCur = 0 ;
    for (int homComp1 = 0 ; homComp1 < nbHomogeneousComponents ; homComp1 ++) {
        for (int homComp2 = homComp1 + 1 ; homComp2 < nbHomogeneousComponents ; homComp2 ++) {
            Z3_ast contraints[2] = { Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, 0, homComp1)),
                                        Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, 0, homComp2))
                                    } ;
            formulaForeachPear[nbCur++] = Z3_mk_or(ctx, 2, contraints) ;
        }
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents*(nbHomogeneousComponents-1)/2, formulaForeachPear) ;
}
/**
 * @brief Get a formula which ensure that foreach homogeneous component, it parent is never itself :
 * This formula corresponds to phi_{2,5}
 * 
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachHomogeneousComponentNotItParent(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachHomogeneousComponent[nbHomogeneousComponents] ;
    for(int homComp = 0 ; homComp < nbHomogeneousComponents ; homComp ++) {
        formulaForeachHomogeneousComponent[homComp] = Z3_mk_not(ctx, getVariableParent(ctx, homComp, homComp)) ;
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents, formulaForeachHomogeneousComponent) ;
}

/**
 * @brief Get a formula which ensure that any homogeneous component as one and only parent, except the root which has not any parent :
 * this formula corresponds to \phi_{2}
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachHomogeneousComponentOneParentExceptRoot(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast contraints[5] = {getFormulaForeachPearHomogeneousComponentNotSameChild(ctx, nbHomogeneousComponents),
                            getFormulaForeachHomogeneousComponentIfDepth0NoParents(ctx, nbHomogeneousComponents),
                            getFormulaForeachHomogeneousComponentIfNotDepth0HasParent(ctx, nbHomogeneousComponents),
                            getFormulaJustOneHomogeneousComponentIsRoot(ctx, nbHomogeneousComponents),
                            getFormulaForeachHomogeneousComponentNotItParent(ctx, nbHomogeneousComponents)
                            } ;
    return Z3_mk_and(ctx, 5, contraints);
}

/**
 * @brief Get a formule which ensure that for a given homogeneous component, this component has at least one level,
 * used by phi_{3, 1}
 * @param ctx The solver context
 * @param int currentHomogeneousComponent the given homogeneous component
 * @param levelMax The maximum level of a component on the tree
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaOneComponentAtLeastOneLevel(Z3_context ctx, int currentHomogeneousComponent, int levelMax) {
    Z3_ast formulaForeachLevel[levelMax+1] ;
    for (int l = 0 ; l <= levelMax ; l++) {
        formulaForeachLevel[l] = getVariableLevelInSpanningTree(ctx, l, currentHomogeneousComponent) ;
    }
    return Z3_mk_or(ctx, levelMax+1, formulaForeachLevel) ;
}

/**
 * @brief Get a formule which ensure that foreach homogeneous component, this compoonent has at least one level,
 * corresponds to phi_{3, 1}
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachComponentAtLeastOneLevel(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachComponent[nbHomogeneousComponents] ;
    for (int comp = 0 ; comp < nbHomogeneousComponents ; comp++) {
        formulaForeachComponent[comp] = getFormulaOneComponentAtLeastOneLevel(ctx, comp, nbHomogeneousComponents - 1) ;
        // the maximum depth of a tree with n nodes is n-1, in case of filiform tree
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents, formulaForeachComponent) ;
}

/**
 * @brief Get a formule which ensure that for a given homogeneous component, this component has at most one level,
 * used by phi_{3, 2}
 * @param ctx The solver context
 * @param int currentHomogeneousComponent the given homogeneous component
 * @param levelMax The maximum level of a component on the tree
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaOneComponentAtMostOneLevel(Z3_context ctx, int currentHomogeneousComponent, int levelMax) {
    Z3_ast formulaForeachPearLevel[(levelMax+1)*levelMax/2] ;
    int curNb = 0 ;
    for (int l1 = 0 ; l1 <= levelMax ; l1++) {
        for (int l2 = l1+1 ; l2 <= levelMax ; l2 ++) {
            Z3_ast contraints[2] = {Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, l1, currentHomogeneousComponent)),
                                    Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, l2, currentHomogeneousComponent))
                                    } ;
                    formulaForeachPearLevel[curNb++] = Z3_mk_or(ctx, 2, contraints) ;
        }
    }
    return Z3_mk_and(ctx, (levelMax+1)*levelMax/2, formulaForeachPearLevel) ;
}

/**
 * @brief Get a formule which ensure that foreach homogeneous component, this component has at most one level,
 * corresponds to phi_{3, 2}
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachComponentAtMostOneLevel(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast formulaForeachComponent[nbHomogeneousComponents] ;
    for (int comp = 0 ; comp < nbHomogeneousComponents ; comp++) {
        formulaForeachComponent[comp] = getFormulaOneComponentAtMostOneLevel(ctx, comp, nbHomogeneousComponents - 1) ;
        // the maximum depth of a tree with n nodes is n-1, in case of filiform tree
    }
    return Z3_mk_and(ctx, nbHomogeneousComponents, formulaForeachComponent) ;
}


/**
 * @brief Get a formule which ensure that foreach homogeneous component, this compoonent has exactly one level,
 * corresponds to phi_{3}
 * @param ctx The solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachComponentOneAndOnlyOneLevel(Z3_context ctx, int nbHomogeneousComponents) {
    Z3_ast contraints[2] = {getFormulaForeachComponentAtLeastOneLevel(ctx, nbHomogeneousComponents),
                            getFormulaForeachComponentAtMostOneLevel(ctx, nbHomogeneousComponents)
                            } ;
    return Z3_mk_and(ctx, 2, contraints) ;
}


/**
 * @brief Get a formula which ensure that there is at least one component which has a depth strictly bigger than k
 * corresponds to phi_{4}
 * @param ctx the solver context
 * @param nbHomogeneousComponents The number of homogeneous components
 * @param k the given k (corresponds to the maximum cost)
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaAtLeastOneComponentDepthKPlus1(Z3_context ctx, int nbHomogeneousComponents, int k) {
    Z3_ast formulaForeachComponent[nbHomogeneousComponents] ;
    for (int comp = 0 ; comp < nbHomogeneousComponents ; comp ++) {
        formulaForeachComponent[comp] = getVariableLevelInSpanningTree(ctx, k+1, comp) ;
    }
    return Z3_mk_or(ctx, nbHomogeneousComponents, formulaForeachComponent) ;
}

/**
 * @brief Get a formula which ensure there is at least one translator between a given edge
 * Used by phi_{5} (getFormulaGivenComponentPearEdgeBetweenComponentWithTranslator)
 * 
 * @param ctx the solver context
 * @param sourceEdge the source of the given edge
 * @param targetEdge the targetEdge of the given edge
 * @param nTranslators the number of translators
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaGivenEdgeAtLeastOneTranslator(Z3_context ctx, int sourceEdge, int targetEdge, int nTranslators) {
    Z3_ast formulaForeachTranslator[nTranslators] ;
    for (int trans = 0 ; trans < nTranslators ; trans++) {
        formulaForeachTranslator[trans] = getVariableIsIthTranslator(ctx, sourceEdge, targetEdge, trans) ;
    }
    return Z3_mk_or(ctx, nTranslators, formulaForeachTranslator) ;
}

/**
 * @brief Get the number of edges between two given components
 * 
 * @param edgeGraph a edgeCon problem
 * @param homComp1 the first given homogeneous component
 * @param homComp2 the second given homogeneous component
 * @return int the number of edges
 */
int getNumberEdgesBetweenTwoHomogeneousComponents(EdgeConGraph edgeGraph, int homComp1, int homComp2) {
    int backNb = 0 ;
    Graph g = getGraph(edgeGraph) ;
    for (int node1 = 0 ; node1 < g.numNodes ; node1++) {
        if (isNodeInComponent(edgeGraph, node1, homComp1)) {
            for (int node2 = 0 ; node2 < g.numNodes ; node2++) {
                if (isNodeInComponent(edgeGraph, node2, homComp2) && isEdge(g, node1, node2)) {
                    backNb++ ;
                }
            }
        }
    }
    return backNb ;
}

/**
 * @brief Get a formula which ensure that, for two given homogeneous component, there is an edge betwen those two components
 * with a translator. This formula corresponds to phi_{5}
 * 
 * @param ctx the solver context
 * @param edgeGraph a edgeCon problem
 * @param homogeneousComponent1 The first given homogeneous component
 * @param homogeneousComponent2 The second given homogeneous  component
 * @param nTranslators the number of translators
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaGivenComponentPearEdgeBetweenComponentWithTranslator(Z3_context ctx, EdgeConGraph edgeGraph, int homogeneousComponent1,
                                                                    int homogeneousComponent2, int nTranslators) {
    // this is a slighty modified version of the formula given in the report :
    // if there is no edge between the components, we just return a formula toto and not toto which is unsatisfiable
    // else we just return the so called part "fact"
    int nbEdges = getNumberEdgesBetweenTwoHomogeneousComponents(edgeGraph, homogeneousComponent1, homogeneousComponent2) ;
    if (nbEdges == 0) {
        Z3_ast var = mk_bool_var(ctx, "toto") ;
        Z3_ast contraints_not_any_edge[2] = { var,
                                                Z3_mk_not(ctx, var)
                                            } ;
        return Z3_mk_and(ctx, 2, contraints_not_any_edge) ;
    }
    Z3_ast formulaForeachEdge[nbEdges] ;
    int curNb = 0 ;
    Graph g = getGraph(edgeGraph) ;
    for (int node1 = 0 ; node1 < g.numNodes ; node1++) {
        if (isNodeInComponent(edgeGraph, node1, homogeneousComponent1)) {
            for (int node2 = 0 ; node2 < g.numNodes ; node2++) {
                if (isNodeInComponent(edgeGraph, node2, homogeneousComponent2) && isEdge(g, node1, node2)) {
                    // node1, node2 is an edge between comp1 and comp2
                    formulaForeachEdge[curNb++] = getFormulaGivenEdgeAtLeastOneTranslator(ctx, node1, node2, nTranslators) ;
                }
            }
        }
    }
    return Z3_mk_or(ctx, curNb, formulaForeachEdge) ;
}

/**
 * @brief Get a formula which ensure that, for a given pear j, j' of differents homogeneous components, the level of j' is the level of j minus 1 :
 * corresponds to phi_{6}
 * 
 * @param ctx the solver context
 * @param homComp1 the first given homogeneous component (with level l)
 * @param homComp2 the second given homogeneous component (with level l-1)
 * @param levelMax the maximul level of an homogeneous component
 * @return Z3_ast the corresponding formula
 */
Z3_ast getFormulaGivenComponentPearLevelIsMinus1(Z3_context ctx, int homComp1, int homComp2, int levelMax) {
    Z3_ast formulaForeachlevel[levelMax] ;
    for (int l = 1 ; l <= levelMax ; l++) {
        Z3_ast contraints[2] = { Z3_mk_not(ctx, getVariableLevelInSpanningTree(ctx, l, homComp1)),
                                    getVariableLevelInSpanningTree(ctx, l-1, homComp2)
                                } ;
        formulaForeachlevel[l-1] = Z3_mk_or(ctx, 2, contraints) ;
    }
    return Z3_mk_and(ctx, levelMax, formulaForeachlevel) ;
}
/**
 * @brief get a formula which ensure that, for a given pear j, j' of differents homogeneous components, if j' is parent of j, then
 * there is an edge between j and j' which is a translator, and the level of j' is equals to the levels of j minus 1 :
 * used by phi_{7} (getFormulaForeachPearHomCompIfParentExistEdgeTransAndLevelMinus1)
 * @param ctx the solver context
 * @param edgeGraph a edgeCon problem
 * @param homComp1 the first given homogeneous component, which is child of the second
 * @param homComp2 the second given homogeneous component, which is parent of the first
 * @param maxLevel the maximul level of a component
 * @param nTranslators the number of translators
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaOnePearHomCompIfParentExistEdgeTransAndLevelMinus1(Z3_context ctx, EdgeConGraph edgeGraph, int homComp1, int homComp2, int maxLevel, int nTranslators) {
    Z3_ast andContraint[2] = {getFormulaGivenComponentPearEdgeBetweenComponentWithTranslator(ctx, edgeGraph, homComp1, homComp2, nTranslators),
                                getFormulaGivenComponentPearLevelIsMinus1(ctx, homComp1, homComp2, maxLevel)
                            } ;
    return Z3_mk_implies(ctx, getVariableParent(ctx, homComp1, homComp2),
                        Z3_mk_and(ctx, 2, andContraint)) ;
}

/**
 * @brief get a formula which ensure that, for any pear j, j' of differents homogeneous components, if j' is parent of j, then
 * there is an edge between j and j' which is a translator, and the level of j' is equals to the levels of j minus 1 :
 * corresponds to phi_{7}
 * @param ctx the solver context
 * @param edgeGraph a edgeCon problem
 * @return Z3_ast The corresponding formula
 */
Z3_ast getFormulaForeachPearHomCompIfParentExistEdgeTransAndLevelMinus1(Z3_context ctx, EdgeConGraph edgeGraph) {
    int nComponents = getNumComponents(edgeGraph) ;
    Z3_ast formulasForeachPear[nComponents * (nComponents - 1) / 2] ;
    int curNb = 0 ;
    for (int homComp1 = 0 ; homComp1 < nComponents ; homComp1 ++) {
        for (int homComp2 = homComp1+1 ; homComp2 < nComponents ; homComp2 ++) {
            formulasForeachPear[curNb++] = getFormulaOnePearHomCompIfParentExistEdgeTransAndLevelMinus1(ctx, edgeGraph,
                                                                homComp1, homComp2, nComponents-1, nComponents-1) ;
        }
    }
    return Z3_mk_and(ctx, curNb, formulasForeachPear) ;
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
    Z3_ast formula_complete[5] = {getFormulaForEachOneTranslatorOneEdge(ctx, edgeSet, nbEdges, getNumComponents(edgeGraph) - 1),
                                    getFormulaForeachHomogeneousComponentOneParentExceptRoot(ctx, getNumComponents(edgeGraph)),
                                    getFormulaForeachComponentOneAndOnlyOneLevel(ctx, getNumComponents(edgeGraph)),
                                    getFormulaAtLeastOneComponentDepthKPlus1(ctx, getNumComponents(edgeGraph), cost),
                                    getFormulaForeachPearHomCompIfParentExistEdgeTransAndLevelMinus1(ctx, edgeGraph)
                                } ;
    for(int i = 0 ; i < curNb ; i++) {
        free (edgeSet[i]) ;
    }
    free(edgeSet) ;
    return Z3_mk_and(ctx, 5, formula_complete) ;
}

void getTranslatorSetFromModel(Z3_context ctx, Z3_model model, EdgeConGraph graph)
{
    return;
}
