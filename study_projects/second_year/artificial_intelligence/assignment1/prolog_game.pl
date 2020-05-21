:-dynamic([minCounter/1, minPath/1, pass/1]).

:- use_module(library(lists)).
:- use_module(library(random)).
:- use_module(library(aggregate)).

%:-["./Input_Maps/CornerCase1.pl"].
%:-["./Input_Maps/CornerCase2.pl"].
%:-["./Input_Maps/CornerCase3.pl"].
%:-["./Input_Maps/CornerCase4.pl"].


%:-["./Input_Maps/Example_AssignmentDescription.pl"].

%:-["./Input_Maps/Map1_5x5.pl"].
%:-["./Input_Maps/Map2_5x5.pl"].
%:-["./Input_Maps/Map3_5x5.pl"].
%:-["./Input_Maps/Map4_5x5.pl"].
%:-["./Input_Maps/Map5_5x5.pl"].
%:-["./Input_Maps/Map6_5x5.pl"].

:-["./Input_Maps/Map1_10x10.pl"].


%----Facts----
right(1).
left(2).
up(3).
down(4).


%----Initialization----
initGame:-

    retractall(minCounter(_)),
    assert(minCounter(1000)),

    retractall(minPath(_)),
    assert(minPath([])),

    retractall(pass(_)),
    assert(pass(1)).


%----Start----
writeResultAndTime(Algorithm):-
    statistics(walltime, [_ | _]),
    startMatch(Algorithm),
    statistics(walltime, [_| [ExecutionTime]]),
    nl,write('Execution took '), write(ExecutionTime), writeln(' ms.').


startMatch(Algorithm):-
    initGame,
    (
        (not(startOnOrc),not(startOnTouchdown),launchAgent(Algorithm));
        (startOnOrc, writeln("Impossible to move: orc at [0,0]."));
        (startOnTouchdown, writeln("Win. Touchdown on [0,0]"))
    ).



%----Algorithms----
launchAgent(Algorithm):-
    (Algorithm = 1, executeRandomSearch);
    (Algorithm = 2, startBacktrackingSearch);
    (Algorithm = 3, startOptimizedSearch).



%----Random----
executeRandomSearch:-
    (initGame,
    executeRandomNTimes(100));
    printResults.

executeRandomNTimes(Count) :-
    Count > 0,
    (
	(
        format('---------------~n'),

        retractall(pass(_)),
        assert(pass(1)),

        (startOnPlayer, MoveCounter is -1; MoveCounter is 0),

        startRandomSearch([0,0], [[0,0]], MoveCounter,_)
        );

        (NewCount is Count - 1,
        executeRandomNTimes(NewCount))
    ).


startRandomSearch(AgentLocation,Path,MoveCounter,EndCounter):-
    (theEnd(AgentLocation,Path,MoveCounter,EndCounter),writeln("Win."),!,true);

    (orcDetected(AgentLocation),writeln("Death. Game Over."),!,fail);

    (movesLimit(MoveCounter),writeln("No more moves. Game Over."),!,fail);

    (wallDetected(AgentLocation), write(AgentLocation), writeln("Bumping. Game Over."), !,fail);

    (
        not(wallDetected(AgentLocation)),

        (determineRandomAction(AgentLocation,Path,MoveCounter,NewLocation,NewPath,NewMoveCounter),

        startRandomSearch(NewLocation,NewPath,NewMoveCounter,EndCounter)
        )
    ).



movesLimit(MoveCounter):-
    MoveCounter =:= 100.


determineRandomAction(Location,Path,MoveCounter,NewLocation,NewPath,NewMoveCounter):-
    chooseActionRandomly(Action),
    (
        (Action = 0,
         changeDirectionRandomly(NewDirection),
         lookAt(Location,NewDirection,Path,NextCellState),
         updateMoveCounter(MoveCounter,NextCellState,NewMoveCounter),
         updateParameters(Location,NewDirection,Path,NewLocation,NewPath));

        (Action = 1,
         makeRandomPass(Location,MoveCounter,NewLocation,NewMoveCounter),
         updatePathForPass(Path,NewPath)
        )
    ).


% 0 move; 1 pass
chooseActionRandomly(Action):-
    pass(Permission),
    (
        (Permission = 1, random_between(0,1,Action));
        (Permission = 0,Action is 0)
    ).

updatePass:-
    retractall(pass(_)),
    assert(pass(0)).


updatePathForPass(Path,NewPath):-
    append(["pass"],Path,NewPath).


chooseRandomPassDirection(PassDirection):-
    random_between(1,8,PassDirection),!.


makeRandomPass(Location,MoveCounter,NewLocation,NewMoveCounter):-
    updatePass,

    chooseRandomPassDirection(PassDirection),
    checkSuccessOfPass(Location,PassDirection,Success,NewLocation),
    (
        (Success = 1,NewMoveCounter is MoveCounter+1);
        (Success = 0,writeln("Wasted Pass. Game Over."),fail)
    ).



%----Implementation of pass----
makePass(Location,Success,PossibleLocation):-
    getXYofLocation(Location,X,Y),
    (
    (NewX is X+1,
     checkRTrajectory(NewX,Y,Success,PossibleLocation));
    (NewX is X-1,
     checkLTrajectory(NewX,Y,Success,PossibleLocation));
    (NewY is Y+1,
     checkUTrajectory(X,NewY,Success,PossibleLocation));
    (NewY is Y-1,
     checkDTrajectory(X,NewY,Success,PossibleLocation));
    (NewX is X+1, NewY is Y+1,
     checkRUTrajectory(NewX,NewY,Success,PossibleLocation));
    (NewX is X+1, NewY is Y-1,
     checkRDTrajectory(NewX,NewY,Success,PossibleLocation));
    (NewX is X-1, NewY is Y+1,
     checkLUTrajectory(NewX,NewY,Success,PossibleLocation));
    (NewX is X-1, NewY is Y-1,
     checkLDTrajectory(NewX,NewY,Success,PossibleLocation));
     Success is 0, fail
    ).



checkSuccessOfPass(Location,Direction,Success,PossibleLocation):-
    getXYofLocation(Location,X,Y),
    (
    (Direction = 1, NewX is X+1,
     checkRTrajectory(NewX,Y,Success,PossibleLocation));
    (Direction = 2, NewX is X-1,
     checkLTrajectory(NewX,Y,Success,PossibleLocation));
    (Direction = 3, NewY is Y+1,
     checkUTrajectory(X,NewY,Success,PossibleLocation));
    (Direction = 4, NewY is Y-1,
     checkDTrajectory(X,NewY,Success,PossibleLocation));
    (Direction = 5, NewX is X+1, NewY is Y+1,
     checkRUTrajectory(NewX,NewY,Success,PossibleLocation));
    (Direction = 6, NewX is X+1, NewY is Y-1,
     checkRDTrajectory(NewX,NewY,Success,PossibleLocation));
    (Direction = 7, NewX is X-1, NewY is Y+1,
     checkLUTrajectory(NewX,NewY,Success,PossibleLocation));
    (Direction = 8, NewX is X-1, NewY is Y-1,
     checkLDTrajectory(NewX,NewY,Success,PossibleLocation));
     Success is 0,fail
    ).


%----RightPass----
checkRTrajectory(X,Y,Success,PossibleLocation):-
    maxX(MaxX),
    (
        X =< MaxX,
        (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X+1,checkRTrajectory(NewX,Y,Success,PossibleLocation))
        )
    ).


%----LeftPass----
checkLTrajectory(X,Y,Success,PossibleLocation):-
    minX(MinX),
    (
        X >= MinX,
        (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X-1,checkLTrajectory(NewX,Y,Success,PossibleLocation))
         )
    ).


%----UpPass----
checkUTrajectory(X,Y,Success,PossibleLocation):-
    maxY(MaxY),
    Y =< MaxY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
          (NewY is Y+1,checkUTrajectory(X,NewY,Success,PossibleLocation))
    ).


%----DownPass----
checkDTrajectory(X,Y,Success,PossibleLocation):-
    minY(MinY),
    Y >= MinY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewY is Y-1,checkDTrajectory(X,NewY,Success,PossibleLocation))
    ).


%----RightUpPass----
checkRUTrajectory(X,Y,Success,PossibleLocation):-
    maxX(MaxX), maxY(MaxY),
    X =< MaxX, Y =< MaxY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X+1, NewY is Y+1,checkRUTrajectory(NewX,NewY,Success,PossibleLocation))
    ).


%----RightDownPass----
checkRDTrajectory(X,Y,Success,PossibleLocation):-
    maxX(MaxX), minY(MinY),
    X =< MaxX, Y >= MinY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X+1, NewY is Y-1,checkRDTrajectory(NewX,NewY,Success,PossibleLocation))
    ).


%----LeftUpPass----
checkLUTrajectory(X,Y,Success,PossibleLocation):-
    minX(MinX), maxY(MaxY),
    X >= MinX, Y =< MaxY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X-1, NewY is Y+1,checkLUTrajectory(NewX,NewY,Success,PossibleLocation))
    ).


%----LeftDownPass----
checkLDTrajectory(X,Y,Success,PossibleLocation):-
    minX(MinX), minY(MinY),
    X >= MinX, Y >= MinY,
    (
         (orcDetected([X,Y]), Success is 0,!);
         (playerDetected([X,Y]), Success is 1, PossibleLocation=[X,Y],!);
         (NewX is X-1, NewY is Y-1,checkLDTrajectory(NewX,NewY,Success,PossibleLocation))
    ).


changeDirectionRandomly(NewDirection):- random_between(1, 4, NewDirection),!.



%----Backtacking----
startBacktrackingSearch:-
    (startOnPlayer, MoveCounter is -1; MoveCounter is 0),
    aggregate_all(min(EndCounter),startBacktracking([0,0],[[0,0]],1,MoveCounter,EndCounter),EndCounter),
    printResults,!,true.


startBacktracking(AgentLocation,Path,PassStatus,MoveCounter,EndCounter):-
    (theEnd(AgentLocation,Path,MoveCounter,EndCounter),!,true);

    (
        not(wallDetected(AgentLocation)),

        (
            (
               determineAction(AgentLocation,Path,MoveCounter,NewLocation,NewPath,NewMoveCounter),
               startBacktracking(NewLocation,NewPath,PassStatus,NewMoveCounter,EndCounter)
            );

            (
             PassStatus = 1, NewPassStatus is 0,
             makePass(AgentLocation,Success,PossibleLocation),
             Success = 1,
              NewMoveCounter is MoveCounter+1,
             updatePathForPass(Path,NewPath),
             startBacktracking(PossibleLocation,NewPath,NewPassStatus,NewMoveCounter,EndCounter)
            )

        )
    );

    (minPath(MP), MP = [], EndCounter is 0).


theEnd(Location,Path,MoveCounter,EndCounter):-
    touchdownDetected(Location),
    (
        isSmaller(MoveCounter),updateMinPath(Path),updateMinCounter(MoveCounter), EndCounter is MoveCounter
    ).

updateMinCounter(MoveCounter):-
    retractall(minCounter(_)),
    assert(minCounter(MoveCounter)).

updateMinPath(Path):-
    retractall(minPath(_)),assert(minPath(Path)).

isSmaller(MoveCounter):-
    minCounter(Min), MoveCounter < Min.



%----OptimizedBacktracking----
startOptimizedSearch:-
    (startOnPlayer, MoveCounter is -1; MoveCounter is 0),
    aggregate_all(min(EndCounter),startOptimized([0,0],[[0,0]],1,MoveCounter,EndCounter),EndCounter),
    printResults,!,true.


startOptimized(AgentLocation,Path,PassStatus,MoveCounter,EndCounter):-
    (theEnd(AgentLocation,Path,MoveCounter,EndCounter),!,true);

    (
        not(wallDetected(AgentLocation)),
        continueSearch(MoveCounter),

        (
            (
               determineAction(AgentLocation,Path,MoveCounter,NewLocation,NewPath,NewMoveCounter),
               startOptimized(NewLocation,NewPath,PassStatus,NewMoveCounter,EndCounter)
               );

            (
             PassStatus = 1, NewPassStatus is 0,
             makePass(AgentLocation,Success,PossibleLocation),
             Success = 1,
             NewMoveCounter is MoveCounter+1,
             updatePathForPass(Path,NewPath),
             startOptimized(PossibleLocation,NewPath,NewPassStatus,NewMoveCounter,EndCounter)
             )

        )
    );

    (minPath(MP), MP = [], EndCounter is 0).


continueSearch(MoveCounter):-
    minCounter(Min), MoveCounter < Min.



%----DetermineAction----
determineAction(Location,Path,MoveCounter,NewLocation,NewPath,NewMoveCounter):-
    (
        %writeln("try move right"),
        lookAt(Location,1,Path,NextCellState),
        isSafe(NextCellState),
        updateMoveCounter(MoveCounter,NextCellState,NewMoveCounter),
        updateParameters(Location,1,Path,NewLocation,NewPath)
    );
    (
        %writeln("try move left"),
        lookAt(Location,2,Path,NextCellState),
        isSafe(NextCellState),
        updateMoveCounter(MoveCounter,NextCellState,NewMoveCounter),
        updateParameters(Location,2,Path,NewLocation,NewPath)

    );
    (
        %writeln("try move up"),
        lookAt(Location,3,Path,NextCellState),
        isSafe(NextCellState),
        updateMoveCounter(MoveCounter,NextCellState,NewMoveCounter),
        updateParameters(Location,3,Path,NewLocation,NewPath)

    );
    (
        %writeln("try move down"),
        lookAt(Location,4,Path,NextCellState),
        isSafe(NextCellState),
        updateMoveCounter(MoveCounter,NextCellState,NewMoveCounter),
        updateParameters(Location,4,Path,NewLocation,NewPath)

    ).





%----Detection/Checking----
lookAt(Location,Direction,Path,NextCellState):-
    (
        (Direction = 1, getRightCell(Location,NewLocation),!);
        (Direction = 2, getLeftCell(Location,NewLocation),!);
        (Direction = 3, getUpCell(Location,NewLocation),!);
        (Direction = 4, getDownCell(Location,NewLocation),!)
    ),
    detectObject(NewLocation,Path,NextCellState).


detectObject(Location,Path,CellState):-
    (orcDetected(Location), CellState is 1,!);
    (playerDetected(Location), CellState is 2,!);
    (touchdownDetected(Location), CellState is 3,!);
    (visitedLocation(Location,Path), CellState is 5,!);
    CellState is 0.


orcDetected(Location):- o(OrcLocation), isEqual(Location, OrcLocation).
playerDetected(Location):- h(PlayerLocation), isEqual(Location, PlayerLocation).
touchdownDetected(Location):- t(TouchdownLocation), isEqual(Location, TouchdownLocation).
wallDetected(Location):- bumpingX(Location); bumpingY(Location).
visitedLocation(Location,Path):- member(Location,Path).

%----checkBumping----
bumpingX(Location):-
    getXYofLocation(Location,X,_),
    maxX(MaxX), minX(MinX),
    (X > MaxX; X < MinX).
bumpingY(Location):-
    getXYofLocation(Location,_,Y),
    maxY(MaxY), minY(MinY),
    (Y > MaxY; Y < MinY).


isSafe(State):-
    (State = 2; State = 3; State = 0);
    fail.


%----CornerCases----
startOnOrc:-
    o(OrcLocation),
    isEqual([0,0],OrcLocation).

startOnPlayer:-
    h(PlayerLocation),
    isEqual([0,0],PlayerLocation).

startOnTouchdown:-
    t(TouchdownLocation),
    isEqual([0,0],TouchdownLocation).



%----UpdateParameters----
updateMoveCounter(MoveCounter,CellState,NewMoveCounter):-
    (CellState = 2, FreeMove is -1; FreeMove is 0),
    Value is 1,
    NewMoveCounter is (FreeMove+Value+MoveCounter).


updateParameters(Location,Direction,Path,NewLocation,NewPath):-
    updateLocation(Location,Direction,NewLocation),
    updatePath(NewLocation,Path,NewPath).


updateLocation(Location,Direction,NewLocation):-
    (
    (Direction = 1, getRightCell(Location,NewLocation));
    (Direction = 2, getLeftCell(Location,NewLocation));
    (Direction = 3, getUpCell(Location,NewLocation));
    (Direction = 4, getDownCell(Location,NewLocation))
    ).


updatePath(NewLocation,Path,NewPath):-
    append([NewLocation],Path,NewPath).



%----getLocation----
getXYofLocation(Location, X, Y):-
    Location = [H1|T],
    X is H1,
    T = [H2|_],
    Y is H2.


getRightCell(Location,NewLocation):-
     getXYofLocation(Location,X,Y),
     NewX is X+1, NewLocation = [NewX,Y].
getLeftCell(Location,NewLocation):-
     getXYofLocation(Location,X,Y),
     NewX is X-1, NewLocation = [NewX,Y].
getUpCell(Location,NewLocation):-
     getXYofLocation(Location,X,Y),
     NewY is Y+1, NewLocation = [X,NewY].
getDownCell(Location,NewLocation):-
     getXYofLocation(Location,X,Y),
     NewY is Y-1, NewLocation = [X,NewY].



%----compareLocations----
isEqual(Location1, Location2):-
    getXYofLocation(Location1, X1, Y1), getXYofLocation(Location2, X2, Y2),
    X1 = X2, Y1 = Y2.

isNotEqual(Location1, Location2):-
    getXYofLocation(Location1, X1, Y1), getXYofLocation(Location2, X2, Y2),
    (X1 =\= X2; Y1 =\= Y2).



%----PrintResults----
printResults:-
    (
    minPath(Path),Path \== [],
    write("Min counter "),
    minCounter(Min),writeln(Min),
    writeln("Min path "),
    printReversedPath(Path)
    );
    (writeln("Game Over. No path. Or no correct random path.")).


printReversedPath(Path):- reverse(Path,_,ReversedPath),printPath(ReversedPath).

printPath([]):- !.
printPath([H|T]):-
    writeln(H), printPath(T).

reverse([],Buffer,Buffer).
reverse([H|T],Buffer,ReversedList):-
    reverse(T,[H|Buffer],ReversedList).




