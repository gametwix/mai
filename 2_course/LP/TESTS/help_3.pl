swap_bl([b,X|T],[X,b|T]).
swap_bl([X,b|T],[b,X|T]).
swap_bl([X|T],[X|R]):- swap_bl(T,R).

swap_wh([w,X|T],[X,w|T]).
swap_wh([X,w|T],[w,X|T]).
swap_wh([X|T],[X|R]):- swap_wh(T,R).

move(S,F):-swap_wh(S,F).
move(S,F):-swap_bl(S,F).

path(Start,Finish):-path(Start,Finish,[Start],Path),reverse(Path,R),write_path(R).
path(Start,Start,Path,Path).
path(Start,Finish,List,Path):-move(Start,Z),not(member(Z, List)),path(Z,Finish,[Z|List],Path).

write_path([]):-write("-------------\n").
write_path([X|L]):-write(X),write("\n"),write_path(L).
prolong([H|T],[X,H|T]):-move(H,X),not(member(X,[H|T])).
path_min(X,Y):-bdth([[X]],Y,P),reverse(P,R),write_path(R).
bdth([[X|T]|_],X,[X|T]).
bdth([P|QI],X,R):-findall(Z,prolong(P,Z),T),append(QI,T,QO),!,bdth(QO,X,R).
