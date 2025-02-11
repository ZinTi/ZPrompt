#ifndef SLLS_EXT_INC
#define SLLS_EXT_INC

namespace run{
    namespace slls{
        // SLLS_Ext类
        class SLLS_Ext{
        private:
            SLLS slls;
        public:
            SLLS_Ext();
            ~SLLS_Ext();
            void addDNode(const char* str, int at = 0);
            void deleteDNode(const char* str);
            void updateDNode(const char* oldStr, const char* newStr);
            void print(void);
            void writeToFile(const char* filename, const char* mode);
            int getLen(void);
            char* getElem(int position);
        }; // class: run::slls::SLLS_Ext
    } // namespace: run::slls
} // namespace: run

#endif