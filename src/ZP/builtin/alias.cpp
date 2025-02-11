class alias{
    private:
        char* key;
        char* value;
        typedef struct DNode{
            char* key;
            char* value;
            DNode *next;
        }DNode, *AliasLink;

    public:
        alias(){

        }
        ~alias(){

        }
        int addAlias(){

        }
        int rmAlias(){

        }

};

int alias(void){

    return 0;
}