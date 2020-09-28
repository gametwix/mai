father(rhaegar,jon_snow).
father(rickard,benjen).
father(rickard,eddard).
father(rickard,brandon).
father(rickard,lyanna).
father(aerys_ii,rhaegar).
father(aerys_ii,viserys).
father(aerys_ii,daenerys).
father(jahaerys_ii,aerys_ii).
father(aegon_v,jahaerys_ii).
father(aegon_v,rhaelle).
father(maekar_i,aegon_v).
father(aegon_i,maekar_i).
father(ormud,steffon).
father(steffon,robert).
father(steffon,stannis).
father(steffon,renly).
father(eddard,robb).
father(eddard,sansa).
father(eddard,arya).
father(eddard,brandon).
father(eddard,rickon).
father(hoster,lysa).
father(hoster,edmure).
father(hoster,catelyn).
father(jon,robin).
father(stannis,shireen).
father(robert,joffrey).
father(robert,myrcella).
father(robert,tommen).
father(tywin,cersei).
father(tywin,jaime).
father(tywin,tyrion).
mother(lyanna,jon_snow).
mother(rhaelle,steffon).
mother(catelyn,robb).
mother(catelyn,sansa).
mother(catelyn,arya).
mother(catelyn,brandon).
mother(catelyn,rickon).
mother(lysa,robin).
mother(cersei,joffrey).
mother(cersei,myrcella).
mother(cersei,tommen).
mother(joanna,cersei).
mother(joanna,jaime).
mother(joanna,tyrion).

parent(X,Y):-mother(X,Y).
parent(X,Y):-father(X,Y).

third(X,Y):-parent(Z1,X),parent(Z2,Z1),parent(Z2,Z3),parent(Z3,Y).