//
//  Vectors.hpp
//  Practice1
//
//  Created by Taher Benisa on 9/1/22.
//  Copyright © 2022 taher benisa. All rights reserved.
//

#ifndef Vectors_hpp
#define Vectors_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

// Print a vector
void printVector(std::vector<int>& nums);
void printVector(std::ostream& out, std::vector<int>& nums);
template<class T> void printVectorTemplate( std::vector<T>& nums );
template<class T> T GetMax (T a, T b);

// Print a vectorS
void printVectors(std::vector<std::vector<int>>& nums);

void assigingVectors(std::vector<int>& a, std::vector<int>& b);

template<class T> void printVectorTemplate( std::vector<T>& nums )
{
   int size = static_cast<T>(nums.size());
    std::cout << "[";
    for( int i = 0; i < size; ++i ) {
        if( i < size-1 ) {
            std::cout << nums[i] << ", ";
        }
        else {
            std::cout << nums[i];
        }
    }
    std::cout << "]";
    std::cout  << std::endl;
}

#endif /* Vectors_hpp */

//template <class T> inline int MAX_TMPL(T a, T b) {return a >= b ? a : b;}
/*  Stroustrup explains the issue in his book "Programming Principles and Practice Using C++:
    As usual, the benefits have corresponding weaknesses. For templates, the main problem is that the
    flexibility and performance come at the cost of poor separation between the "inside" of a template
    (its definition) and its interface (its declaration).
    When compiling a use of a template, the compiler "looks into" the template and also into the template
    argument types. It does do to get the information to generate optimal code. To have all the information
    available, current compilers tend to require that a template must be fully defined whenever it is used.
    That includes all of its member functions and all template functions called from those. Consequently,
    template writers tend to place template definition in header files. That is not actually required by the
    standard, but until improved implementations are widely available, we recommend that you do so for your own
    templates: place the definition of any template that is to be used in more than one translation unit in a header file.
 */
/*  it's important for us to realize that the template is not class definition yet. It's a set of instructions to the compiler about how to generate the class definition. A particular realization of a template is called an instantiation or a specialization.
 Unless we have a compiler that has implemented the new export keyword, placing the template member functions in a separate implementation file won't work. Because the templates are not functions, they can't be compiled separately.
 */
