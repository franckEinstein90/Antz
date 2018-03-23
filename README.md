# Antz


Evolves Cooperative Behavior

C++, OpenGL, Genetic Programming, Cooperation, Distributed Systems, Emergence

Overview
A family is a group of organisms that behave in a similar manner. Each individual in a family is equipped with sensors, actuators and a mechanism for leaving markers that can be detected by the other individuals in its family. Families are evaluated in a 2-dimensional environment E, for a duration of t time units. At the beginning of each evaluation run, the environment contains n particles of some collectible resource that needs to be gathered and carried back a specific place (the drop). In the screenshot below, the system is in its initial state. Each line in the list is a program that specifies the behaviour of a single family of ant. None of these have been evaluated in the environment yet.

The goal is to evolve cooperative behavior that brings back a maximum amount of collectible to the drop site, starting from any randomly created environment. The behavior of each individual in a family is specified by a typed program.

For example (from an individual organism's perspective):

(1) If I'm carrying a resource particule, and I'm at the drop off point, then I should drop the resource. However, if I'm carrying and I'm not at the drop, then I should head towards the drop, and on the way, I should drop flags that communicate to the other individuals of my family informations about the location of the remaining resource particles.

(2) If I'm not carrying, then I should check to see if there is any collectables where I am. If there are, I should pick up one item. If there aren't, check and see if there are collectibles within sensory perception field. If affirmative, go to location, otherwise check for markers from other individuals, and follow the trail. If there are no markers in sensory field, none move randomly. ```

Every ant in a given family behaves the same way, but every family will code a different behavior. The best behaviors (see below for more on the objective function) will then be rewarded by having a higher chance of reappearing in the next round of evaluation. The example algorithm above is simple algorithm and seems to make sense. But is it really the best one? Does the manner by which ants use their capacity to produce and sense pheromones in that algorithm fully optimize the total gathering of food (team work). Might it not be more efficient if instead of carrying the food straight home, the ants dropped it on the way for other ants to pick up ? Or used a strategy that was more complicated ?

Crossover

The purpose of crossover is the production of a genetically diverse population of behaviors. Because each behavior is coded as a tree, it is imperative that the crossover operator that is used forces the production of syntactically valid offspring.

There are two ways of induring syntactic validity: either by reparing faulty trees that are produced by random crossover or setting rules of formation that prohibit the formation of faulty trees.

It is the second approach that was chosen for this task. The specification of the typed language called Antze that was used can be downloaded here is because during the evolution process In order to evolve behavior that were complicated, ....evolving valid program trees using type theory

The Language $PICKUP: (ENV\xx ENVOBJECT)\xx ANT\rarr ENV\xx (ANT\xx ENVOBJECT)$ $DROP: ENV\xx (ANT\xx ENVOBJECT)->(ENV\xx ENVOBJECT)\xx ANT$ $MOVELEFT : (ENV\xx ANT)\rarr (ENV\xx ANT)$ $MOVEFRONT : (ENV\xx ANT)\rarr (ENV\xx ANT)$ $MOVERIGHT : (ENV\xx ANT)\rarr (ENV\xx ANT)$ $TURNRIGHT : ANT\rarr ANT$ $TURNLEFT : ANT\rarr ANT$ $PRODUCEPHEROMONE : ANT\rarr (ANT\xx ENVOBJECT)$ $SENSEPHEROMONE : (ENV\xx ANT)\rarr bool$ $SENSEFOOD : (ENV\xx ANT)\rarr bool$ Each ant can only move forward, to the left or to the right. Likewise, an ant can only sense for food to its right, left or front. The environment is toroidal (north wraps to south and east wraps to west). The environment can do the following: $GIVEOBJECT : ENV \rarr (ENV\xx ENVOBJECT)$ $ADDOBJECT: (ENV\xx ENVOBJECT)\rarr ENV$ In order to avoid behavior evolution that overfits a specific environment, every time a new environment is created, the food distribution and quantity is different. There is no most efficient algorithm that applies to all the environments.

The Evaluation function

Each family is evaluated in E by the objective function Fg within tg time units. At the beginning of the run, E contains f0E units of food and ft-1E at the end. For each families, Fg returns a real value proportional to (ft-1E-f0E)/ nF where nF is the number of ants in the family. The population size (the number of families being evaluated) is \lambda

The Software:

The ants behavior is coded in a tree like structure called a CDNAStatement. These are program tree, but they also happen to represent the genotype of the ants. AntEvolver evolves CDNAStatements. It then evaluates each CDNAStatements using an objective function whose primary input is the amount of food a family of ants whose genotype is a particular CDNAStatement gathers. A fitness based non-deterministic selection process is then applied, a bit of mutation is shaked up in the mix and vodka. I mean voila. Using the software

There are three modes:

Ant Simulation mode

In this mode a CDNAStatement (program tree) can be seen in action in the environment. In this mode, the settings for the size of the environment grid and the number of ants can be set by choosing View -> Setting in the main menu. There is also a slider rule that allows the setting of the pheromonal strength. The file->open/file->save features allows the opening and the saving of DNAStatement files (.ant extension). The Play button on the right toolbar will start the simulation, while the Pause button will pause it. When the simulation is paused, the indicator in the toolbar giving the amount of food left in the environment is updated (not while it is running). Make sure that the simulation is paused before changing any settings while a simulation is running.

The I button on the left toolbar (simulation should be paused) will reset the environment The Grid button on the left toolbar will toggle grid view The Pheromone View Button on the first Resizable bar will toggle pheromone Viewing · The G button on the left toolbar (simulation should be paused) will open DNAStatement in the Tree mode

Tree mode

In Tree mode, the CDNAStatement is displayed in a Tree View control. It can be edited by selecting the new statement and right clicking on the tree item that is to be replaced. Hitting the refresh tree button will then validate the new tree. Make sure the tree is refreshed after a compound else statement is introduced in the tree.

Evolve Mode

Creating a new GP is done by selecting File->New->Evolver on the main menu. To start the evolution of the GP, simply enter the generation number to which it should evolve in the EvolveTo edit box on the second top toolbar and press the play button. Each GP is represented as an entry in the main view, and double clicking on its ID number will open it in Tree Mode. When a GP is selected it can be either:

Saved as an ant file: File->save, Ant Simulated directly by pressing the Play Individual button (top toolbar) Viewed as a tree by double clicking on it.
