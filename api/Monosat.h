/*
 * MonoSAT.h
 *
 *  Created on: May 21, 2015
 *      Author: sam
 */

#ifndef MONOSAT_H_
#define MONOSAT_H_
//Monosat library interface
extern "C"
{

  int varToLit(int var, bool negated){
	  return toInt(mkLit(var,negated));
  }

  int litToVar(int lit){
	  return lit/2;
  }

  void * newSolver(int argc, char**argv);


  void deleteSolver (Monosat::SimpSolver * S);

  void readGNF(Monosat::SimpSolver * S, const char  * filename);

  bool solve(Monosat::SimpSolver * S);
  bool solveAssumptions(Monosat::SimpSolver * S,int * assumptions, int n_assumptions);
  //Solve under assumptions, and also minimize a set of BVs (in order of precedence)
  bool solveAssumptions_MinBVs(Monosat::SimpSolver * S,int * assumptions, int n_assumptions, int * minimize_bvs, int n_minimize_bvs);

  //Returns 1 for proved false, 2 for proved true, 0 for failed to find a solution within the conflict limit
  int solveLimited(Monosat::SimpSolver * S,int conflict_limit);
  int solveAssumptionsLimited(Monosat::SimpSolver * S,int conflict_limit,int * assumptions, int n_assumptions);
  //Solve under assumptions, and also minimize a set of BVs (in order of precedence)
  int solveAssumptionsLimited_MinBVs(Monosat::SimpSolver * S,int conflict_limit,int * assumptions, int n_assumptions, int * minimize_bvs, int n_minimize_bvs);


  void backtrack(Monosat::SimpSolver * S);
  int newVar(Monosat::SimpSolver * S);
  void setDecisionVar(Monosat::SimpSolver * S,int var,bool decidable);
  bool isDecisionVar(Monosat::SimpSolver * S,int var);

  //Static, lexicographic heuristic. Larger values are higher priority (decided first); default priority is 0
  void setDecisionPriority(Monosat::SimpSolver * S,int var, int priority);
  int getDecisionPriority(Monosat::SimpSolver * S,int var);
  // Which polarity the decision heuristic should use for a variable (by default).
  void setDecisionPolarity(Monosat::SimpSolver * S,Var v, bool b);
  bool getDecisionPolarity(Monosat::SimpSolver * S,Var v);

  //The solver will (sometimes) instantiate an arbitrary true literal for use as a constant.
  //Call this method to a) force that literal to be instantiate, and b) get that literal.
  int true_lit(Monosat::SimpSolver * S);

  //Prevents this literal from being simplified by the preprocessor
  bool disallowLiteralSimplification(Monosat::SimpSolver * S, int lit);

  int nVars(Monosat::SimpSolver * S);
  int nClauses(Monosat::SimpSolver * S);
  int nBitvectors(Monosat::SimpSolver * S,Monosat::BVTheorySolver<long> * bv);

  bool addClause(Monosat::SimpSolver * S,int * assumptions, int n_assumptions);
  bool addUnitClause(Monosat::SimpSolver * S,int lit);
  bool addBinaryClause(Monosat::SimpSolver * S,int lit1, int lit2);
  bool addTertiaryClause(Monosat::SimpSolver * S,int lit1, int lit2, int lit3);
  //theory interface for bitvectors
  void * initBVTheory(Monosat::SimpSolver * S);
  int newBitvector_const(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvWidth, long constval);
  int newBitvector(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int * bits, int n_bits);
  int newBVComparison_const_lt(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, long weight);
  int newBVComparison_bv_lt(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, int compareID);
  int newBVComparison_const_leq(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, long weight);
  int newBVComparison_bv_leq(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, int compareID);
  int newBVComparison_const_gt(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, long weight);
  int newBVComparison_bv_gt(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, int compareID);
  int newBVComparison_const_geq(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, long weight);
  int newBVComparison_bv_geq(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, int compareID);


  void bv_concat( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int aID, int bID, int resultID);
  void bv_slice( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int aID, int lower, int upper, int resultID);
  void bv_not( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvResultID);
  void bv_and( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);
  void bv_nand( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);
  void bv_or( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);
  void bv_nor( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);
  void bv_xor( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);
  void bv_xnor( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv,int bvaID, int bvbID, int bvResultID);

  void bv_ite( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int condition_lit,int bvThenID, int bvElseID, int bvResultID);

  void bv_addition( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID1, int bvID2, int resultID);
  void bv_subtraction( Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID1, int bvID2, int resultID);
  void bv_min(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int n_args, int* args,int resultID);
  void bv_max(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int n_args, int* args, int resultID);
  void bv_popcount(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int n_args, int* args, int resultID);

  //simple at-most-one constraint: asserts that at most one of the set of variables (NOT LITERALS) may be true.
  //for small numbers of variables, consider using a direct CNF encoding instead
  void at_most_one(Monosat::SimpSolver * S, int * vars, int n_vars);

  //theory interface for graphs

  void * newGraph(Monosat::SimpSolver * S);

  int newNode(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G);
  int newEdge(Monosat::SimpSolver * S, Monosat::GraphTheorySolver<long> *G,int from,int  to,  long weight);
  int newEdge_double(Monosat::SimpSolver * S, Monosat::GraphTheorySolver<double> *G,int from,int  to,  double weight);
  int newEdge_bv(Monosat::SimpSolver * S, Monosat::GraphTheorySolver<long> *G,int from,int  to, int bvID);
  int reaches(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to);
  int shortestPathUnweighted_lt_const(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, int steps);
  int shortestPathUnweighted_leq_const(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, int steps);
  int shortestPath_lt_const(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, long dist);
  int shortestPath_leq_const(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, long dist);
  int shortestPath_lt_bv(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, int bvID);
  int shortestPath_leq_bv(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int from, int to, int bvID);
  int maximumFlow_geq(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int source, int sink, long weight);
  int maximumFlow_gt(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int source, int sink, long weight);
  int maximumFlow_geq_bv(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int source, int sink, int bvID);
  int maximumFlow_gt_bv(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int source, int sink, int bvID);
  int minimumSpanningTree_leq(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G, long weight);
  int minimumSpanningTree_lt(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int source, int sink, long weight);
  int acyclic_undirected(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G);
  int acyclic_directed(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G);
  //model query
  //For a given literal (not variable!), returns 0 for true, 1 for false, 2 for unassigned.
  int getModel_Literal(Monosat::SimpSolver * S,int lit);
  //Get an assignment to a bitvector in the model. The model may find a range of satisfying assignments to the bitvector;
  //If getMaximumValue is true, this function returns the maximum satisfying assignment to the bitvector in the model; else it returns the smallest.
  long getModel_BV(Monosat::SimpSolver * S, Monosat::BVTheorySolver<long> * bv, int bvID, bool getMaximumValue);
  //graph queries:
  //maxflow_literal is the literal (not variable!) that is the atom for the maximum flow query
  long getModel_MaxFlow(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int maxflow_literal);
  //maxflow_literal is the literal (not variable!) that is the atom for the maximum flow query
  long getModel_EdgeFlow(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int maxflow_literal, int edgeLit);
  long getModel_AcyclicEdgeFlow(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int maxflow_literal, int edgeLit);

  long getModel_MinimumSpanningTreeWeight(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int spanning_tree_literal);
/*
  //Returns the number of nodes in the path length for this reachability or shortest path literal (1+number of edges)
  int getModel_PathLength(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int reach_or_shortest_path_lit);
  void getModel_Path(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int reach_or_shortest_path_lit, int * store_path);
  void getModel_PathByEdgeLit(Monosat::SimpSolver * S,Monosat::GraphTheorySolver<long> *G,int reach_or_shortest_path_lit, int * store_path);
*/


}
#endif /* MONOSAT_H_ */