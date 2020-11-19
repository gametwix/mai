true(you).
true(name).
true(kek).
true(lol).
true(true).


check("~",X,true):-not(true(X)).
check("~",X,false):-true(X).

check("V", X, Y,true):- true(X), true(Y).
check("V", X, Y,true):- not(true(X)), true(Y).
check("V", X, Y,true):- true(X), not(true(Y)).
check("V", X, Y,false):- not(true(X)), not(true(Y)).

check("^", X, Y,true):-  true(X), true(Y).
check("^", X, Y,false):-  not(true(X)), true(Y).
check("^", X, Y,false):-  not(true(Y)), true(X).
check("^", X, Y,false):-  not(true(X)), not(true(Y)).

check("=>",X,Y,true):-true(X),true(Y).
check("=>",X,Y,true):-not(true(X)),true(Y).
check("=>",X,Y,true):-not(true(X)),not(true(Y)).
check("=>",X,Y,false):-true(X),not(true(Y)).


calculate(Expr,Val):-reverse(Expr,Expr1),a_term(Expr1,Val).
a_term([X],X).
a_term(T,V):-append([X],["V"|Y],T),a_term(Y,Vy),check("V",X,Vy,V).
a_term(T,V):-append([X],["~"|_],T),check("~",X,V).
a_term(T,V):-append([X],["^"|Y],T),a_term(Y,Vy),check("^",X,Vy,V).
a_term(T,V):-append([X],["=>"|Y],T),a_term(Y,Vy),check("=>",Vy,X,V).

no_skobok([H|T],S,X):-S >0,no_skobok(T,S,X1),append([H],X1,X).
no_skobok([H|T],S,X):-H = "(",S1 is S + 1,no_skobok(T,S1,X),!.
no_skobok([H|T],S,X):-H = ")",S1 is S - 1,no_skobok(T,S1,X),!.
no_skobok([_|T],0,X):-no_skobok(T,0,X).
no_skobok([],0,[]).

no_skobok([H|T],X):-no_skobok([H|T],0,X).

razb(L):-length(L, I),I>0,no_skobok(L,R1),write(R1),razb(R1).


