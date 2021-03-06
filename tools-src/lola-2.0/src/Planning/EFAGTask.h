/****************************************************************************
  This file is part of LoLA.

  LoLA is free software: you can redistribute it and/or modify it under the
  terms of the GNU Affero General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  LoLA is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
  more details.

  You should have received a copy of the GNU Affero General Public License
  along with LoLA. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once

#include <Core/Dimensions.h>
#include <Witness/Path.h>
#include <Planning/Task.h>
#include <Planning/AGEFTask.h>


/*!
\brief the verification task

This class delegates the EFAG problem to the AGEF problem.
It adjusts the return value and the result interpretation.

*/

class EFAGTask : public Task
{
public:
     Task * D; // the corresponding AGEF task
    ~EFAGTask(){}

    /// run the actual verification algorithm
    ternary_t getResult() {
	ternary_t result = D -> getResult(); // run the AGEF task
	switch(result)   // toggle result
	{
	case TERNARY_TRUE: return TERNARY_FALSE;
	case TERNARY_FALSE: return TERNARY_TRUE;
	case TERNARY_UNKNOWN: return TERNARY_UNKNOWN;
	default: assert(false);
	}
	return result;
   }

    /// interprete and display the result
    void interpreteResult(ternary_t result) {
	switch(result)
	{
	case TERNARY_TRUE: RT::rep->status("The predicate is possibly invariant"); return;
	case TERNARY_FALSE: RT::rep->status("The predicate is not possibly invariant"); return;
	case TERNARY_UNKNOWN: RT::rep->status("The predicate may or may not be possibly invariant"); return;
	default: assert(false);
	}
   }

    /// return the witness path
    Path getWitnessPath() { return D -> getWitnessPath();}
    /// return the target marking
    capacity_t *getMarking() { return D -> getMarking();}

    /// return the number of stored markings
    void getStatistics() {D -> getStatistics();}
    static Task * buildTask() {
	EFAGTask * N = new EFAGTask();
	N -> D = AGEFTask::buildTask();
	return N;
    }
   char * getStatus(uint64_t elapsed){ return D -> getStatus(elapsed);}
    char * early_abortion(){return D->early_abortion();}
    StatePredicate * spFormula;
};
