#include"slrtable.hpp"

SLRTable::SLRTable() {
    init_action();
    init_go();
}

void SLRTable::init_action() {
    //规约项目，使用规约的产生式编号加100表示，用来与规约编号区分
    action[1][Over] = 0 + 100;           //接收项目
    for(int i = 0;i < 31;++i) {
        action[1][i] = 0 + 100;     //{S -> S'.} = I1
        action[4][i] = 2 + 100;     //I4 = {A -> B.}
        action[5][i] = 4 + 100;     //{B -> C.} = I5
        action[6][i] = 5 + 100;     //{B -> E.} = I6
        action[9][i] = 6 + 100;     //{C -> integer D.} = I9
        action[10][i] = 7 + 100;    //{D -> a.} = I10
        action[13][i] = 3 + 100;    //{A -> A;B.} = I13
        action[14][i] = 11 + 100;   //{H -> I.} = I14
        action[15][i] = 13 + 100;   //{I -> J.} = I15
        action[16][i] = 14 + 100;   //{I -> K.} = I16
        action[17][i] = 15 + 100;   //{I -> L.} = I17
        action[18][i] = 16 + 100;   //{I -> M.} = I18
        action[24][i] = 1 + 100;    //{S' -> begin A;H end.} = I24
        action[31][i] = 21 + 100;   //{N -> O.,O -> O.*P} = I31
        action[32][i] = 23 + 100;   //{O -> P.} = I32
        action[33][i] = 24 + 100;   //{P -> D.} = I33
        action[34][i] = 25 + 100;   //{P -> int.} = I34
        action[35][i] = 26 + 100;   //{P -> T.} = I35
        action[36][i] = 7 + 100;    //{D -> id.,T -> id.(N)} = I36
        action[38][i] = 12 + 100;   //{H -> H;I.} = I38
        action[41][i] = 19 + 100;   //{L -> D := N.,N -> N.-O} = I41
        action[45][i] = 29 + 100;   //{R -> <.} = I45
        action[46][i] = 30 + 100;   //{R -> <=.} = I46
        action[47][i] = 31 + 100;   //{R -> >.} = I47
        action[48][i] = 32 + 100;   //{R -> >=.} = I48
        action[49][i] = 33 + 100;   //{R -> =.} = I49
        action[50][i] = 34 + 100;   //{R -> <>.} = I50
        action[54][i] = 9 + 100;    //{F -> D.} = I54
        action[55][i] = 17 + 100;   //{J -> read(D).} = I55
        action[56][i] = 18 + 100;   //{K -> write(D).} = I56
        action[58][i] = 28 + 100;   //{Q -> NRN.,N -> N.-O} = I58
        action[59][i] = 20 + 100;   //{N -> N-O.,O -> O.*P,} = I59
        action[60][i] = 22 + 100;   //{O -> O*P.} = I60
        action[64][i] = 35 + 100;   //{T -> id(N).} = I64
        action[66][i] = 27 + 100;   //{M -> if Q then I else I.} = I66
        action[67][i] = 8 + 100;    //{E -> integer function id(F);G.} = I67
        action[72][i] = 10 + 100;   //{G -> begin A;H end.} = I72

    }
    //产生异常的项目
    for(int i = 0;i < 31;++i) {
        action[19][i] = 1 + 150;    //read m)
        action[20][i] = 2 + 150;    //write m) 
        action[3][i] = 3 + 150;
    }
    //移进项目，直接使用移进到的状态编号表示，编号值均小于100
    action[0][BEGIN] = 2;
    action[2][INTEGER] = 7;
    action[3][SEM] = 8;
    action[7][ID] = 10;
    action[7][FUNCTION] = 11;
    action[8][READ] = 19;
    action[8][WRITE] = 20;
    action[8][IF] = 22;
    action[8][ID] = 10;
    action[8][INTEGER] = 7;
    action[11][ID] = 23;
    action[12][END] = 24;
    action[12][SEM] = 25;
    action[19][LPAR] = 26;
    action[20][LPAR] = 27;
    action[21][ASSIGN] = 28;
    action[22][INT] = 34;
    action[22][ID] = 36;
    action[23][LPAR] = 37;
    action[25][READ] = 19;
    action[25][WRITE] = 20;
    action[25][IF] = 22;
    action[25][ID] = 10;
    action[26][ID] = 10;
    action[27][ID] = 10;
    action[28][INT] = 34;
    action[28][ID] = 36;
    action[29][THEN] = 42;
    action[30][SUB] = 44;
    action[30][LT] = 45;
    action[30][LE] = 46;
    action[30][GT] = 47;
    action[30][GE] = 48;
    action[30][EQ] = 49;
    action[30][NE] = 50;
    action[31][MUL] = 51;
    action[36][LPAR] = 52;
    action[37][ID] =  10;
    action[39][RPAR] = 55;
    action[40][RPAR] = 56;
    action[41][SUB] = 44;
    action[42][READ] = 19;
    action[42][WRITE] = 20;
    action[42][IF] = 22;
    action[42][ID] = 10;
    action[43][INT] = 34;
    action[43][ID] = 36;
    action[44][INT] = 34;
    action[44][ID] = 36;
    action[51][INT] = 34;
    action[51][ID] = 36;
    action[52][INT] = 34;
    action[52][ID] = 36;
    action[53][RPAR] = 62;
    action[57][ELSE] = 63;
    action[58][SUB] = 44;
    action[59][MUL] = 51;
    action[61][RPAR] = 64;
    action[61][SUB] = 44;
    action[62][SEM] = 65;
    action[63][READ] = 19;
    action[63][WRITE] = 20;
    action[63][IF] = 22;
    action[63][ID] = 10;
    action[65][BEGIN] = 68;
    action[68][INTEGER] = 7;
    action[69][SEM] = 70;
    action[70][READ] = 19;
    action[70][WRITE] = 20;
    action[70][IF] = 22;
    action[70][ID] = 10;
    action[70][INTEGER] = 7;
    action[71][END] = 72;
    action[71][SEM] = 25;
    
}

void SLRTable::init_go() {
    //规约项目
    for(int i = 0;i < 20;++i) {
        go[1][i] = 0 + 100;     //{S -> S'.} = I1
        go[4][i] = 2 + 100;     //I4 = {A -> B.}
        go[5][i] = 4 + 100;     //{B -> C.} = I5
        go[6][i] = 5 + 100;     //{B -> E.} = I6
        go[9][i] = 6 + 100;     //{C -> integer D.} = I9
        go[10][i] = 7 + 100;    //{D -> a.} = I10
        go[13][i] = 3 + 100;    //{A -> A;B.} = I13
        go[14][i] = 11 + 100;   //{H -> I.} = I14
        go[15][i] = 13 + 100;   //{I -> J.} = I15
        go[16][i] = 14 + 100;   //{I -> K.} = I16
        go[17][i] = 15 + 100;   //{I -> L.} = I17
        go[18][i] = 16 + 100;   //{I -> M.} = I18
        go[24][i] = 1 + 100;    //{S' -> begin A;H end.} = I24
        go[31][i] = 21 + 100;   //{N -> O.,O -> O.*P} = I31
        go[32][i] = 23 + 100;   //{O -> P.} = I32
        go[33][i] = 24 + 100;   //{P -> D.} = I33
        go[34][i] = 25 + 100;   //{P -> int.} = I34
        go[35][i] = 26 + 100;   //{P -> T.} = I35
        go[36][i] = 7 + 100;    //{D -> id.,T -> id.(N)} = I36
        go[38][i] = 12 + 100;   //{H -> H;I.} = I38
        go[41][i] = 19 + 100;   //{L -> D := N.,N -> N.-O} = I41
        go[45][i] = 29 + 100;   //{R -> <.} = I45
        go[46][i] = 30 + 100;   //{R -> <=.} = I46
        go[47][i] = 31 + 100;   //{R -> >.} = I47
        go[48][i] = 32 + 100;   //{R -> >=.} = I48
        go[49][i] = 33 + 100;   //{R -> =.} = I49
        go[50][i] = 34 + 100;   //{R -> <>.} = I50
        go[54][i] = 9 + 100;    //{F -> D.} = I54
        go[55][i] = 17 + 100;   //{J -> read(D).} = I55
        go[56][i] = 18 + 100;   //{K -> write(D).} = I56
        go[58][i] = 28 + 100;   //{Q -> NRN.,N -> N.-O} = I58
        go[59][i] = 20 + 100;   //{N -> N-O.,O -> O.*P,} = I59
        go[60][i] = 22 + 100;   //{O -> O*P.} = I60
        go[64][i] = 35 + 100;   //{T -> id(N).} = I64
        go[66][i] = 27 + 100;   //{M -> if Q then I else I.} = I66
        go[67][i] = 8 + 100;    //{E -> integer function id(F);G.} = I67
        go[72][i] = 10 + 100;   //{G -> begin A;H end.} = I72
    }
    //产生异常的项目
    for(int i = 0;i < 31;++i) {
        go[19][i] = 1 + 150;    //read m)
        go[20][i] = 2 + 150;    //write m) 
        go[3][i] = 3 + 150;
    }
    //移进项目
    go[0][S_] = 1;
    go[2][A] = 3;
    go[2][B] = 4;
    go[2][C] = 5;
    go[2][E] = 6;
    go[7][D] = 9;
    go[8][H] = 12;
    go[8][B] = 13;
    go[8][I] = 14;
    go[8][J] = 15;
    go[8][K] = 16;
    go[8][L] = 17;
    go[8][M] = 18;
    go[8][D] = 21;
    go[8][C] = 5;
    go[8][E] = 6;
    go[22][Q] = 29;
    go[22][N] = 30;
    go[22][O] = 31;
    go[22][P] = 32;
    go[22][D] = 33;
    go[22][T] = 35;
    go[25][I] = 38;
    go[25][J] = 15;
    go[25][K] = 16;
    go[25][L] = 17;
    go[25][M] = 18;
    go[25][D] = 21;
    go[26][D] = 39;
    go[27][D] = 40;
    go[28][N] = 41;
    go[28][O] = 31;
    go[28][P] = 32;
    go[28][D] = 33;
    go[28][T] = 35;
    go[30][R] = 43;
    go[37][F] = 53;
    go[37][D] = 54;
    go[42][I] = 57;
    go[42][J] = 15;
    go[42][K] = 16;
    go[42][L] = 17;
    go[42][M] = 18;
    go[42][D] = 21;
    go[43][N] = 58;
    go[43][O] = 31;
    go[43][P] = 32;
    go[43][D] = 33;
    go[43][T] = 35;
    go[44][O] = 59;
    go[44][P] = 32;
    go[44][D] = 33;
    go[44][T] = 35;
    go[51][P] = 60;
    go[51][D] = 33;
    go[51][T] = 35;
    go[52][N] = 61;
    go[52][O] = 31;
    go[52][P] = 32;
    go[52][D] = 33;
    go[52][T] = 35;
    go[63][I] = 66;
    go[63][J] = 15;
    go[63][K] = 16;
    go[63][L] = 17;
    go[63][M] = 18;
    go[63][D] = 21;
    go[65][G] = 67;
    go[68][A] = 69;
    go[68][B] = 4;
    go[68][C] = 5;
    go[68][E] = 6;
    go[70][H] = 71;
    go[70][B] = 13;
    go[70][I] = 14;
    go[70][J] = 15;
    go[70][K] = 16;
    go[70][L] = 17;
    go[70][M] = 18;
    go[70][D] = 21;
    go[70][C] = 5;
    go[70][E] = 6;

}


