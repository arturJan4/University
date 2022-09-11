# random notes
## 1st idea (-> wood1)
- select a card to focus on (lowest current debt)
- calculate received debt for each application created
- go to places which have cards we lack -> (only that much we lack or more, potential to create not need cards)
- when we focus on one app then we focus -> else we randomize

### how to improve
- more greedy (we can disregard more debt as game goes on)
- include where we can move to calculations
- predict opponent's next move (beam search)
- somehow include your discard and draw pile into calculations 
- write heuristics

## wood 1 changes
- GIVE (don't move next to (picking correct card when have to give))
- SKILLS:
    - Training -> draw 2, play 1
    - Architecture - draw one more until end release of application
        - may be useful for last one or big apps
    - Code review - 2 bonus skill from the boards (WTF) to the discard pile
    - refactoring - remove technical debt and put in on the board (WTF)
- discard permanent skills on release

### ideas
- calculate probabilities and usefulness of skills
- watch games and analyze!
- when to focus on big app and when on smaller ones?
- draw pile gets smaller meaning increasing probabilities
- when have to give, give useless (no such app, or opponent has a lot of them already) skills
- give bonus when possible
- video 10:26
- don't use training when needed for release this turn or don't have interesting cards at hand
- include that if i move for card when i need it may backfire because i have to give card to opp
- collect architecture and review when can
- keep debt relatively low <= 10 (based on turns)
- draw a nice state machine to understand code better
- how to transform heuristics into heuristic evaluation (some probabilities??)
- State + state changing -> random games?
- estimates on cards left etc. -> on paper 
- can you calculate opponents cards based on what he played?
- machine learning -> not enough time i think
- pick a set of cards at start and track
- changing parameters by running A LOT of game locally
- low depth MCTS/Beam Search/Minmax ??? -> check time
- final version of search -> rewrite to c++
reach bronze fast for full rules testing

### wood 1 TODO
- calculating debt per app given current hand
- focusing on one app (lowest debt + random + not including architecture and refactoring)
- trying not to move next to opponent
- predict next move + release action
- predict your draw pile (small draw pile -> bigger chance (< 4 in draw (discard -> draw))
- architecture study till (6 ?), code_review (when possible), refactoring (when possible)
- release the focused app
- if no release (then maybe there is not enough cards), then change focus app after few turns

separate debt from hand for calculating now-turn and cost given current draw!

## bronze ideas
- optimize Move to force less administrative tasks (heuristics + randomness)
- use daily routine (when)
- use coding (when)
- use task_prior (when)
- use CI (when)
- introduce 2nd focus
- if we collect some from next to each other and they are needed for same app!
- changing focus based on heuristic (cards in draw pile, total debt, total cost, if they are next to each other)
- add permament cards

*final league: gold*
