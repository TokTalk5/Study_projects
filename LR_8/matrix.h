#include <QString>
#include <vector>

template <class number>
class matrix
{
protected:
    int n = 3;
    std::vector<std::vector<number>> M = {{2, 4, 3},{5, 7, 8},{6, 9, 1}};
    std::vector<std::vector<number>> delRowColumn(std::vector<std::vector<number>> source, int index_1, int index_2);
    number det(std::vector<std::vector<number>> source);

public:

    number getDimension();
    number getElement(int i, int j);

    void setDimension(int d1);
    void setElement(number el, int i, int j);

    std::vector<std::vector<number>> getMatrix();
    number getDet();

    void trans();

    number rank();
};


template <class number>
number matrix<number>::getElement(int i, int j){
    return M[i][j];
}


template <class number>
number matrix<number>::getDimension(){
    return this->n;
}


template <class number>
void matrix<number>::setDimension(int d1){ // DONE!
    this->n = d1;

    M.resize(d1);
    for (int i = 0; i < d1; i++) M[i].resize(d1);

}


template <class number>
void matrix<number>::setElement(number el, int i, int j){
    M[i][j] = el;
}


template <class number>
std::vector<std::vector<number>> matrix<number>::getMatrix(){
    return M;
}


template <class number>
std::vector<std::vector<number>> matrix<number>::delRowColumn(std::vector<std::vector<number>> source, int i, int j){
    std::vector<std::vector<number>> mass;
    mass = source;

    int si = 0;
    for (auto ele = mass.begin(); ele != mass.end(); ele++){
        if (si == i){
            mass.erase(ele);
            break;
        }
        si++;
    }

    si = 0;
    for (int sj = 0; sj < mass.size(); sj++){
        for (auto ele = mass[sj].begin(); ele != mass[sj].end(); ele++){
            if (si == j){
                mass[sj].erase(ele);
                break;
            }
            si++;
        }
    }
    return mass;
}


template <class number>
number matrix<number>::det(std::vector<std::vector<number>> source){
    std::vector<std::vector<number>> mass;


    int i = 0, k = 1;
    number d = 0; // перегружать еще и оператор присваивания?

    if (source.size() == 1){
        d = source[0][0];
        return d;
    }

    if (source.size() == 2){
        d = source[0][0] * source[1][1] - (source[1][0] * source[0][1]);
        return d;
    }

    if (source.size() > 2){
        for (i = 0; i < source.size(); i++){

            mass = delRowColumn(source, i, 0);
            d = d + (number)k * source[i][0] * det(mass);
            k = -k;
        }
    }
    return d;
}


template <class number>
number matrix<number>::getDet(){
    return det(M);
}


template <class number>
void matrix<number>::trans(){

    std::vector<std::vector<number>> buff = this->M;
    this->setDimension(this->m, this->n);

    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->m; j++){
            M[i][j] = buff[j][i];
        }
    }
}

template <class number>
number matrix<number>::rank(){ // допустим это работает
    number r = 0;
    int q = 1;

    while (q <= this->n)
    {
        std::vector<number> standart;

        std::vector<std::vector<number>> B;
        standart.resize(q);
        for(int w = 0; w < q; w++) B.push_back(standart);

        for(int a = 0; a < (n - (q - 1)); a++){
            for(int b = 0; b < (n - (q - 1)); b++){
                for(int c = 0; c < q; c++){
                    for(int d = 0; d < q; d++){
                        B[c][d] = M[a+c][b+d];
                    }
                }
                if(!(det(B) == 0)) r = q;
            }
        }
    q++;
    }
    return r;
}

