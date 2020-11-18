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