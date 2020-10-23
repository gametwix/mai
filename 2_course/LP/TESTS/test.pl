factor(X,[X]).
factor(X,[Head|Tail]):- Z is X div Head,Z*Head == X,factor(Z,Tail).