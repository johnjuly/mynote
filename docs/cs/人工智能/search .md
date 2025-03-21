#

search for solutions

* refelx agents:

try to get an apple from a tree
choose action based on current percept(and memory maybe)
may have memory or a model of the world's current 
do not consider the future consequences of their actions
consider how the world is
**does not think ahead at all**


吃豆人游戏中看到一颗豆子就吃，有看不到的情况


* planning agents:

ask what if
decision based on(hypothesized)consequence of actions
must have a model of how the world evolves in response to actions 
must formulate a goal(test)
consider how the world would be
吃豆人

* a search problem consists of:
* a state space
* a successor function(with actions,costs)后继 状态
* start state and a goal test
* a solution is a sequence if actions (a plan)which transforms the state to a goal state


**search problems are models**,some details about the world are irelevant
abstraction of the world 

!!! example "travelling in romania"

  state space:cities
  successor function: roads:go to adjacent city with cost =distance

  start state:arad
  goal test:is state==bucharest?

!!! note
  the **world state**includes every last detail of the environment

!!! note
  a **search state**keeps only the details needed fot planning (abstraction)
    * problem:pathing
      * states:(x,y)locations


