//
//     MINOTAUR -- It's only 1/2 bull
//
//     (C)opyright 2008 - 2014 The MINOTAUR Team.
//

/**
 * \file KnapCovHandler.h
 * \brief Declare the KnapCovHandler class for handling knapsack cover 
 * constraints. It generates the cuts whenever they are needed. 
 * \author Serdar Yildiz, Argonne National Laboratory
 */

#ifndef MINOTAURKNAPCOVHANDLER_H
#define MINOTAURKNAPCOVHANDLER_H

#include "Handler.h"
#include "Types.h"
#include "Solution.h"
#include "Variable.h"
#include "Relaxation.h"
#include "CoverCutGenerator.h"

namespace Minotaur {

// Pointers for knapsack cover cut handler are defined.
class KnapCovHandler;
typedef boost::shared_ptr<KnapCovHandler> KnapCovHandlerPtr;
typedef boost::shared_ptr<const KnapCovHandler> ConstKnapCovHandler;

class Logger;
typedef boost::shared_ptr<Logger> LoggerPtr;


struct KCStats
{
  UInt knaps; /// Number of knapsacks solved.  
  UInt cuts; /// Number of cover cuts generated.
  UInt extended; /// Number of extended cover cuts generated.
  UInt simple; /// Number of simple lifted cuts generated.
  UInt gns; /// Number of Gu, Nemhauser, Savelsbergh lifted cover cuts
            /// generated.
  UInt singlectwo; /// Number of general lifted cover cuts generated by using
                   /// a single element for C2 (downlifting).
  Double time; /// Total time used to generate cuts.
  UInt cutdel; /// Number of cuts marked for deletion.
};

/** 
 * KnapCovHandler class considers knapsack cover cuts in the problem. It
 * generates the cuts and manages them.
 */
class KnapCovHandler : public Handler {
public:

  /// Default constructor.
  KnapCovHandler();

  /// Constructor.
  KnapCovHandler(EnvPtr env, ProblemPtr problem);

  /// Destroy 
  ~KnapCovHandler();

  /// Does nothing. 
  void relaxInitFull(RelaxationPtr , Bool * ) {};

  /// Does nothing.
  void relaxInitInc(RelaxationPtr , Bool * ) {};

  /// Does nothing.
  void relaxNodeFull(NodePtr , RelaxationPtr , Bool * ) {};

  /// Does nothing.
  void relaxNodeInc(NodePtr , RelaxationPtr , Bool * ) {};

  /// Check if solution is feasible.
  /// Checks all the constraints if they are satisfied by the given solution.
  Bool isFeasible(ConstSolutionPtr sol, RelaxationPtr relaxation,
                  Bool & isInfeasible);

  
  /**
   * We need separation for this handler to generate the knapsack cover
   * cuts.
   * A set of knapsack cover cuts will be generated.
   */
  void separate(ConstSolutionPtr, NodePtr, RelaxationPtr, CutManager *cutman,
                SolutionPoolPtr, Bool *, SeparationStatus * status);

  /// Does nothing. 
  virtual void getBranchingCandidates(RelaxationPtr ,
                                      const std::vector< Double > & ,
                                      ModVector & , BrCandSet & ,
                                      Bool & ) {};

  /// Does nothing.
  virtual ModificationPtr getBrMod(BrCandPtr , DoubleVector & ,
                                   RelaxationPtr , BranchDirection )
    {return ModificationPtr();};

  /// Does nothing.
  virtual Branches getBranches(BrCandPtr , DoubleVector & ,
                               RelaxationPtr , SolutionPoolPtr )
    {return Branches();};

  /// Does nothing.
  SolveStatus presolve(PreModQ *, Bool *) {return Finished;};

  /// Does nothing.
  //void postsolveGetX(const Double *, UInt, DoubleVector *) {};

  // Does nothing.
  virtual Bool presolveNode(RelaxationPtr , NodePtr ,
                            SolutionPoolPtr , ModVector &,
                            ModVector &) {return false;};

  // Write name.
  std::string getName() const;

  /// Show statistics.
  void writeStats(std::ostream &) const;

  /// Updates the handler statistics by using returned information form
  /// cover cut generator.
  // void updateStats(ConsCovCutGenStatsPtr covstats);

  // Return specific statistics.
  UInt KC_knaps(){return stats_->knaps;}
  UInt KC_cuts() {return stats_->cuts;}
  UInt KC_extended() {return stats_->extended;}
  UInt KC_simple()   {return stats_->simple;}
  UInt KC_gns()      {return stats_->gns;}
  UInt KC_singlectwo() {return stats_->singlectwo;} 
  Double KC_time()       {return stats_->time;}

private:
  /// Environment.
  EnvPtr env_;

  /// The problem for which the handler is created.
  ProblemPtr minlp_;

  /// Log.
  LoggerPtr logger_;

  /// Statistics.
  KCStats * stats_;

  /**
   * This is false if the current solution violates one of the knapsack
   * cover cuts.
   * We generate the cuts only if we checked the feasibility and it is false.
   */
  Bool isFeas_;

  /// Tolerance for accepting a new a solution value: absolute threshold.
  const Double solAbsTol_;

  // Number of variables in the MINLP.
  UInt numvars_;

  /// Tolerance for checking integrality.
  Double intTol_;

  /// For log:
  static const std::string me_;
};
}


#endif // MINOTAURKNAPCOVHANDLER_H


// Local Variables: 
// mode: c++ 
// eval: (c-set-style "k&r") 
// eval: (c-set-offset 'innamespace 0) 
// eval: (setq c-basic-offset 2) 
// eval: (setq fill-column 78) 
// eval: (auto-fill-mode 1) 
// eval: (setq column-number-mode 1) 
// eval: (setq indent-tabs-mode nil) 
// End:

