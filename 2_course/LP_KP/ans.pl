:- discontiguous father/2.
:- discontiguous mother/2.
father(zeus,hermes).
mother(maia,hermes).
father(atlas,maia).
mother(playona,maia).
father(cronos,zeus).
mother(reyha,zeus).




parent(X,Y) :- father(X,Y).
parent(X,Y) :- mother(X,Y).