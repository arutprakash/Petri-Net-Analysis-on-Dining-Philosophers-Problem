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
#include <Net/NetState.h>
#include <Exploration/SimpleProperty.h>
#include <Exploration/Firelist.h>

class DFSExploration;
class StatePredicate;

/*!
\brief the verification task

This class wraps the stateless reachability check

*/

class ReachabilityFindpathTask : public Task
{
public:
	ternary_t result;
    ReachabilityFindpathTask();
    ~ReachabilityFindpathTask();

    /// run the actual verification algorithm
    virtual ternary_t getResult();
	
    /// interprete and display the result
    virtual void interpreteResult(ternary_t result); 

    /// return the witness path
    virtual Path getWitnessPath();
    /// return the target marking
    virtual capacity_t *getMarking();

    /// return the number of stored markings
    virtual void getStatistics(); 
    static Task * buildTask();
    NetState * ns;
    SimpleProperty * p;
    EmptyStore<void> * store;
    Firelist * fl;
    StatePredicate * spFormula;
    DFSExploration * exploration;
    char * getStatus(uint64_t);
    char * early_abortion(){return NULL;}
};
