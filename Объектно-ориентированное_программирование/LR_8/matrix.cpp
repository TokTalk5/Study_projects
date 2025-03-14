#include "matrix.h"

template <class number>
class Matrix : public matrix<number>
{
public:
    //Matrix();
    int getDimension();
    void setDimension(int d1);
};


template <class number>
int Matrix<number>::getDimension(){
    return (matrix<number>::getDimension().first);
}

template <class number>
void Matrix<number>::setDimension(int d1){
    return (matrix<number>::setDimension(d1,d1));
}
