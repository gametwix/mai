text-->append([]).
p([_]).
p([_,_|X]):-p(X).

last(L,Last):-append(_,[Last],L).

fib(1,1).
fib(2,1).
fib(N,R):-fib(N,R,3,1,1).
fib(N,N3,H,N1,N2):-N = H,N3 is N1 + N2,!.
fib(N,R,H,N1,N2):-N>H,N3 is N1 + N2,H1 is H + 1,fib(N,R,H1,N2,N3).

fact(0,1).
fact(X,R):-fact(X,1,1,R).
fact(X,N,H,R):-X>N,H1 is H*N,N1 is N + 1,fact(X,N1,H1,R).
fact(X,N,H,H1):-X=N,H1 is H*N,!.

v([_|T],N):-v(T,N1),N1 = N -1.
v([],0).