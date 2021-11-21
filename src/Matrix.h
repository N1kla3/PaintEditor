//
// Created by kolya on 11/8/2021.
//

#pragma once

#include <vector>
#include <iostream>

template<class T>
class matrix{
public:
    size_t ROW,COL;
    std::vector<std::vector<T>> mat;
    matrix(size_t N, size_t M, int populate = 0){
        this->ROW = N;
        this->COL = M;
        this->mat = std::vector<std::vector<T>> (ROW,std::vector<T> (COL,populate));
    }
    matrix(size_t N, int populate = 0){
        this->ROW = N;
        this->COL = N;
        this->mat = std::vector<std::vector<T>> (ROW,std::vector<T> (COL,populate));
    }

    /*
     * size of top vector is Row
     * size of in-vector is column
     * all in-vectors should be of the same size
     */
    constexpr matrix(std::vector<std::vector<T>>&& inmat)
    {
        if (inmat.empty()) throw std::exception("vector is empty - matrix");
        ROW = inmat.size();
        COL = inmat[0].size();
        mat = std::move(inmat);
    }

    void init()
    {
        for(int i = 0; i < ROW; ++i){
            for(int j = 0; j < COL; ++j){
                std::cin  >> this->mat[i][j];
            }
        }
    }
    void display()
    {
        for(int i = 0; i < ROW; ++i){
            for(int j = 0; j < COL; ++j){
                std::cout << this->mat[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    matrix<T> operator*(const matrix<T> &rhs) const
    {
        if(this->COL != rhs.ROW){
            throw std::exception("MATRIX MULTIPLICATION CANNOT HAPPEN WITH THE GIVEN MATRICES");
        }
        matrix<T> result(this->ROW,rhs.COL);
        for(int _i = 0; _i < this->ROW; _i++)
        {
            for(int _j = 0; _j < rhs.COL; _j++)
            {
                result.mat[_i][_j] = 0;
                for(int _k = 0; _k < this->COL; ++_k)
                {
                    result.mat[_i][_j]+=(this->mat[_i][_k]*rhs.mat[_k][_j]);
                }
            }
        }
        return result;
    }
    matrix<T> power(int n)
    {
        if(n == 0)return matrix<T>(this->ROW, this->COL,1);
        if(n == 1)return *this;
        matrix p = power(n/2);
        p = p*p;
        if(n%2)p = p*(*this);
        return p;
    }
};