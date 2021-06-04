_Pragma("once");

class SLRTable {

    public:
        SLRTable();
        enum {        //终结符的集合
            ID = 1,   //ID
            INT = 3,  //integer value
            EQ = 5,   //=
            LE = 7,   //<=
            NE = 9,   //<>
            LT = 11,  //<
            GT,       //>     12
            GE,       //>=    13
            SUB,      //-     14
            MUL,      //*     15
            ASSIGN,   //:=    16
            LPAR,     //(     17
            RPAR,     //)     18
            SEM,      //;     19
            BEGIN,    //begin 20
            END,      //end   21
            INTEGER,  //integer22
            IF,       //if     23
            THEN,     //then   24
            ELSE,     //else   25
            FUNCTION, //function26
            READ,     //read    27
            WRITE,    //write   28
            EOLN,     //end of line 29
            Over
        };
        enum {        //非终结符的集合
            S_,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            T      
        };

        unsigned char Go(int state,int symbol) const {
            return go[state][symbol];
        }

        unsigned char Action(int state,int terminal) const {
            return action[state][terminal];
        }
        
    private:
        void init_action();
        void init_go();
        unsigned char action[100][31];
        unsigned char go[100][20];
};