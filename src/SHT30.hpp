/*
 * Header file for reading SHT30 values
 */
 
#ifndef SHT30_hpp
#define SHT30_hpp

class SHT {
    int SHTaddr;
    public:
        SHT(int SHTaddr);
        void collect();
};

#endif
