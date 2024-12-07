//
// Created by ebaup on 07.12.24.
//

#include "ODERightHandSide.h"

double ODERightHandSide::value(double y, double t) const{
  if(f){
    return (*f)(y,t);
  }else{
    throw std::runtime_error("Function pointer is null");
  }
}
