#ifndef Thirteen_hpp
#define Thirteen_hpp

#include <iostream>
#include <string>

class Thirteen {

    private :

        size_t size;
        unsigned char* array;

    public : 


        Thirteen();
        Thirteen(const size_t& n, unsigned char t);
        Thirteen(const std::initializer_list< unsigned char> &t);
        Thirteen(const std::string &t);                          
        Thirteen(const Thirteen& other); 
        Thirteen(Thirteen&& other) noexcept;                      

        bool operator== (const Thirteen &other) const;
        bool operator!= (const Thirteen &other) const; 
        bool operator< (const Thirteen &otbher) const; 
        bool operator> (const Thirteen &other) const; 

        Thirteen& operator= (const Thirteen &other); 
        Thirteen& operator+= (const Thirteen &other); 
        Thirteen& operator-= (const Thirteen &other);

        std::ostream& print(std::ostream& os) const;

        virtual ~Thirteen();
};

#endif