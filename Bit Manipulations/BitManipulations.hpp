//
//  BitManipulations.hpp
//  Practice1
//
//  Created by taher benisa on 11/13/20.
//  Copyright © 2020 taher benisa. All rights reserved.
//

#ifndef BitManipulations_hpp
#define BitManipulations_hpp



#include <stdio.h>
#include "string"
#include <iostream>
#include <vector>


unsigned int Swap2Bits1( unsigned int& num, int bit1, int bit2 );
unsigned int Swap2Bits2( unsigned int& num, int bit1, int bit2 );



    int computeXOR1( int number );
    int computeXOR2( int number );

    int CountSetBits(int n);

    int Update_Bits_1(int n, int m, int beginPos, int endPos);
    int Update_Bits_2(int n, int m, int beginPos, int endPos);

    // from Ritchi book
    unsigned int getBits2(unsigned int x, int p, int n);
    // Mine
    unsigned int getBits1(unsigned int x, int p, int n);

    // Generates 01010101010, See PrintNumHavingAltBitPattern1(int n)
    unsigned int setEvenBits_mine(unsigned int n);
    // Generates 10101010101, See PrintNumHavingAltBitPattern1(int n)
    unsigned int SetOddBits_geek(unsigned int n);
    unsigned int SetOddBits_mine(unsigned int n);

    unsigned char Clear_Bits_From_MSB_To_ithBit(unsigned char, int pos);

    // Use this function to do both SetEvenBits and SetEvenBits()
    // Call SetEvenBits() to set even bits and,
    // Call SetOddBits() to set odd bits or,
    // Call ~SetEvenBits() to set odd bits

    std::vector<int> generateAlternateBits1(int n); // Mine
    void             generateAlternateBits2(int n);

    bool Are_Bits_Alternating(unsigned int n);
    bool Are_ALL_Bits_Alternating2(unsigned int n);

    int ConsecutiveBits1(unsigned int number);
    int ConsecutiveBits2(unsigned int number);

    bool     BigIndianLittleIndian(void);
    uint32_t ChangeEndianness_1(uint32_t u32Value);
    uint32_t ChangeEndianness_2(uint32_t u32Value);

    bool PowerOfTwo(unsigned int n);

    long multiplyWithShift(short x, short y);
    long int DivideWithoutUsingDivision_1(int x, int y);
    int      DivideWithoutUsingDivision_2(int a, int b) ;

    int printDuplicatesInBigDataSet(unsigned int* a, int size);

    void OnesLeftZerosRight(int* array, int size);

    unsigned int ReverseBits1(unsigned int n);
    void         ReverseBits2(unsigned int &n);
    unsigned int ReverseBits3(unsigned int n);

    int  rotateBitsLeft_1(int n, int shiftleft);
    void RotateBitsLeft_2(int &n, int shiftleft);
    void rotateBitsLeft_3(unsigned int &n, int shiftleft);

    // Swap of bits, niblles, bytes

    std::byte     Swap_EvenOdd_Bits_Byte(std::byte x);
    unsigned int  Swap_2Bits_Nibble(unsigned int number);
    unsigned int  Swap_Bytes_In_Integer(unsigned int number);
    unsigned int  Swap_Halfword_In_Integer(unsigned int number);
    void          SwapNumbers_NotUsingtemp(int &x, int &y);
    unsigned char Swap_Nibbles_In_Byte(unsigned char x);
    unsigned int  Swap_Nibbles_In_Integer(unsigned int x);
    unsigned int  Swap_EvenOdd_Bits_Integer(unsigned int n);
    int           SwapRangeOfBits(unsigned int x, unsigned int p1, unsigned int p2, unsigned int n);
    unsigned char swap2Bits(unsigned char data, int bit1, int bit2);
    unsigned char swap2BitsMySolution(unsigned char data, unsigned char bit1, unsigned char bit2);


    int  Compute_Sign_of_Integer_1(int number);
    int  Compute_Sign_of_Integer_2(int number);
    bool CheckOppositeSign(int number, int b);

    int is_number_odd_or_even( int number );

    int is_char_lower_or_upper( char character );

    // similar functions:
    int longestSubsequenceOf1s_afterFlipping_1bit_util( int integer );
    int longestSubsequenceOf1s_afterFlipping_1bit( int integer );
    int longestContiguousOnes_afterFlipping_oneBit( std::vector<int> input );
    int flipBit_to_Win( int integer );
    int longestSubstringOf1s_afterRemoving_1bit_1( std::string s );
    int longestSubstringOf1s_afterRemoving_1bit_2( std::string str );

// Binary strings stuff
    int  CountNegative_1( std::string str );
    int  CountPositive_1( std::string str );
    std::vector<int>  Edges( std::string str );
    void Draw_Square_Wave( std::string str );
    
    // A pulse is defined as: an edge_up followed by an edge_down. !!!: order is very important
    // !!!: My best solution
    int  CountPositive_2      ( std::vector<int> serial_data );
    int  CountNegative_2      ( std::vector<int> serial_data );
    void numOf_Neg_Pos_Pulses ( std::vector<int> topograhpy );

    int FirstPositiveEdge_2( std::vector<int> serial_data );
    int FirstPositiveEdge_1( std::vector<int> serial_data );
    int FirstPositiveEdge_3( std::vector<int> serial_data );
    
// move it to bitManipulation
    int Find_MaxForm(std::vector<std::string>& strs, int m, int n);

    int EqualLengths_of_Zeros_Ones_1( std::vector<int>& nums );
    int findEqualLengths_of_Zeros_Ones_2( std::vector<int> &nums );

    char trailingZeros_1( char number );
    char trailingZeros_2( char number );
    int  leadingZeros_1 ( int  number );
    
    int  Equal_Sum_and_XOR( int number );   //??
    void XORnumbers( int number );
    
    unsigned int Toggle_Oddbits_1( unsigned int number );
    unsigned int Toggle_Oddbits_2( unsigned int number );


void move_zeros_to_left(std::vector<int>& a);

std::vector<int> ZeroOneTwo3(std::vector<int> v) ;
std::string ZeroOneTwo4(std::string s);   // The best

// Leading j bits (MSB) of 16-bit number:
unsigned short LeadingBits( unsigned short &x, int j );
// Trailing j bits (LSB) of 16-bit number:
unsigned short TrailingBits( unsigned short &x, int j );
// Middle bits btween i and j bits:
unsigned short MiddleBits( unsigned short &x, int i, int j );

// Do not use. We do not want to change outside function
// Returns 15 for x=0: it is OK. Leading 0s for 0 is undefined
int Leading0s( unsigned short x );

// Returns 15 for x=0: it is OK. Leading 0s for 0 is undefined
int Trailing0s( unsigned short x );

int PatternCount( std::string str );

#endif /* BitManipulations_hpp */


