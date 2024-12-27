#pragma once
class Indexes
{
public:
    uint16_t index = 0;
    uint16_t uniformIndex = 0;
    
    static Indexes * IndexCounter(){
        static Indexes indexes;
        return &indexes;
    }
};