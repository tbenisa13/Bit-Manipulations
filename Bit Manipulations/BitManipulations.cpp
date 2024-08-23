//
//  BitManipulations.cpp
//  Practice1
//
//  Created by taher benisa on 11/13/20.
//  Copyright © 2020 taher benisa. All rights reserved.
//

#include "BitManipulations.hpp"
#include "NumberConversions.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::array;
using std::byte;
using std::endl;
using std::istream;
using std::ostream;


enum BIG_LITTLE_INDIAN {BIG_INDIAN = 0, LITTLE_INDIAN = 1};


int XNOR(int n1, int n2)
{
    int i = 0, xnor = 0;
    while ( n1 > 0 )
    {
        if ((n1 & 1) == (n2 & 1))
            xnor |= (1 << i++);

        n1 >>= 1; n2 >>= 1;
    }

    return xnor;
}

// XOR a number n: ???: Useless
int computeXOR1(int n)
{
    int i = 1;
    int res = 0;
    while(i <= n)
    {
        n ^= i;
        if(n == 0) {
            cout << "i = " << i  << " res = " << n << endl;
            return i;
        }
        i++;
     }
                
    return i;
}

// Method to calculate xor
int computeXOR2(int n)
{
    // If n is a multiple of 4
    if (n % 4 == 0)
        return n;

    // If n%4 gives remainder 1
    if (n % 4 == 1)
        return 1;

    // If n%4 gives remainder 2
    if (n % 4 == 2)
        return n + 1;

    // If n%4 gives remainder 3
    return 0;
}

int Compute_Sign_of_Integer_1(int number)
{
    int sign = (number > 0) - (number < 0); // check the sign of the number
    return sign;
}

int Compute_Sign_of_Integer_2(int number)
{
    return number >> 31 & 1;
}

bool CheckOppositeSign(int a, int b)
{
    return ((a ^ b) < 0); // 1 if a and b have opposite signs;
}

int Update_Bits_1(int n, int m, int startBit, int endBit)
{
    unsigned int mask0 = ~0;    // 0xFFFFFFFF
    int mask1 = ~0;             // -1
    int x = mask1 - ((1<<startBit) - 1);
    //cout << "x = " << x << endl;
    int mask2 =  ~1   ;     // -2
    unsigned int mask3 =  ~1   ;    // 0xFFFFFFFF - 1

    int i = startBit;   //2
    int mask = 0;
    while(i <= endBit)  // <= means inclusive, including bits 2-6
    {
        mask |= 1 << i; // Set bits 2-6
        i++;
    }
    
    n  = n & ~mask; // Clear bits 2-6 in n
    
    int res = n | (m << startBit);
    
    return res;
}

// !!!: 09/12/2020: this worked the first time I tried it. I am really surprised but proud of getting it right first time
int Update_Bits_2(int n, int m, int beginPos, int endPos)
{
    int right =  (1 << beginPos) - 1;       // beginPos = 4
    int left  = ~((1 << (endPos + 1)) - 1);  // endPos = 6
    int mask = left | right;                 // Create mask= ...111110000011
    
    return (n & mask) | (m << beginPos);
}

// from = 3, to = 4 inclusive
unsigned int getBits1(unsigned int number, int fromBit, int toBit) {
    unsigned int mask = ~(~0 << (toBit - fromBit + 1)); // 00000011
    
    return (number >> fromBit) & mask;
}

// from Ritchi book: p=4, n=3. n is index from 1, that is why n-1 below
// Needs work
unsigned int getBits2(unsigned int number, int fromBit, int toBit) {
    //unsigned int c = ~(~0 << toBit);  c = 0b00000000000000000000000001111111, toBit=7    //return d & c;
    return (number >> (fromBit - toBit + 1)) & ~(~0 << toBit);    // !!!: ???
}

// Given a number, the task is to set all odd bits of a number. Positions of bits are counted from
// LSB (least significant bit) to MSB (Most significant bit). !!!: Position of LSB is considered as 1.
// Works, but SetOddBits(n) is better: simpler and faster
unsigned int SetOddBits_geek(unsigned int number)
{
    int count = 0;
 
    // res for store 010101.. number
    int res = 0;
 
    // generate number form of 010101.....till
    for (int temp = number; temp > 0; temp >>= 1) {
 
        // if bit is odd, then generate number, and or itwith res
        // !!!: Note, position of LSB is considered as 1.
        if (count % 2 == 0)
            res |= (1 << count);
 
        count++;
    }
 
    return (number | res); 
}

// does not work
unsigned int SetOddBits_mine(unsigned int n)
{
    return n | 0x55555555;  // oddmask = 0x55555555: 0101
}

// does not work
unsigned int setEvenBits_mine(unsigned int n)
{
    return n | 0xAAAAAAAA;  // evenmask = 0xAAAAAAAA: 1010
}

int CountSetBits(int n)
{
    //int r = n;
    int count = 0;
    //    n   & (n - 1) = result
    // 010111 & 010110  = 010110 => count = 1
    // 010110 & 010101  = 010100 => count = 2
    // 010100 & 010011  = 010000 => count = 3
    // 010000 & 001111  = 000000 => count = 4
    while(n > 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

unsigned char Clear_Bits_From_MSB_To_ithBit(unsigned char number, int pos)
{
    return 0xFF >> (8 - pos);    // nice. great idea
}


// From internet: Implementation to print numbers in the range 1 to n having bits in alternate
// pattern function to print numbers in the range (1 to n) having bits in alternate pattern
// My work: this works for both 10 0r 01
vector<int> generateAlternateBits1(int n)
{
    // n = 110010 :
                // r = 101010 = 42
                // r = 010101 = 21
                // r = 001010 = 10
                // r = 000101 = 5
                // r = 000010 = 2
                // r = 000001 = 1
    vector<int> result;
    int number = 1;
    while(number <= n) {
        result.push_back(number);                       // Add number to result
        // Generate next number from current one:
        // Shift 'this number' left 1, and add one to it, only if 'this number' is even
        number = (number << 1) + (number % 2 == 0);     //
        //number = (number << 1) + !(number & 1);     // this also works √√√
        
        // generate next number having all bits '1's bit pattern: 1, 11, 111, 1111, 11111
        // number = (number << 1) ^ 1;
     }

    return result;
}

// Too complicated
void generateAlternateBits2(int n)
{
    // first number having bits in alternate pattern
    int curr_num = 1;

    // display
   // cout << curr_num << " ";

    // loop until n < curr_num
    while (1) {

        // generate next number having alternate bit pattern
        curr_num <<= 1; // x2,

        // if true then break
        if (n < curr_num)
            break;

        // display
        //cout << curr_num << " ";

        // generate next number having alternate bit pattern
        curr_num = ((curr_num) << 1) ^ 1;   // 2<<1 = 4 => 100^1 = 101

        // if true then break
        if (n < curr_num)
            break;

        // display
        //cout << curr_num << " ";
    }
}

// Implement a function that checks if given number contains 2 or more consecutive 1s.
// If it does, the function should return 1. Otherwise, it should return 0.
int ConsecutiveBits1(unsigned int number)
{
    int one_bit_count = 0;
    
    while( number > 0) {
        if((number & 1) == 1) {
            one_bit_count++;
            if( one_bit_count > 1 ) {   // or: one_bit_count >= 2;
                return 1;               // count = 2
            }
        }
        else if( (number & 1) == 0 ) {
            one_bit_count = 0;         // Important!!!:
        }
        
        number >>= 1;
    }
    
    return 0;
}

int ConsecutiveBits2(unsigned int number)
{
    while( number > 0) {
        if( (number & 1) && ((number >> 1) & 1) ) {
                return 1;               // count = 2
        }
        
        number >>= 1;
    }
    
    return 0;
}

/*  Big-endian systems store the most significant byte of a word at the smallest memory address and the least significant byte at the largest. A little-endian system, in contrast, stores the least-significant byte at the smallest address.  */
bool BigIndianLittleIndian(void)
{
    //              D C B A
    int testInt = 0x44434241;
    char *pByte = reinterpret_cast<char *>(&testInt);   // => This is also OK, using reinterpret_cast

    for(int i = 0; i < sizeof(int); i++)
    {
        cout << "index = " << i << ", "<< *(pByte + i) << endl; // *(pByte + i) = pByte[i] = *pByte++
    }
    if( *pByte == 'A')
        return BIG_INDIAN;
    else
        return LITTLE_INDIAN;
}

//Function to change the endianess
uint32_t ChangeEndianness_1(uint32_t u32Value)
{
    uint32_t u32Result = 0;
    u32Result |= (u32Value & 0x000000FF) << 24;
    u32Result |= (u32Value & 0x0000FF00) << 8;
    u32Result |= (u32Value & 0x00FF0000) >> 8;
    u32Result |= (u32Value & 0xFF000000) >> 24;
    
    return u32Result;
}

//Function to change the endianess. Slower than version 1
uint32_t ChangeEndianness_2(uint32_t u32Value)
{
    char* p1 = (char* )(&u32Value);
    char* p2 = p1 + 3;  // sizeof(uint32_t) = 4;
    while(p1 < p2) {
        // swap bytes
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
        ++p1;
        --p2;
    }
    
    return u32Value;
}

/* Geeksforgeeks: Swap all the pair of bits in a byte. Before swapping: 11-10-11-01 After swapping: 11-01-11-10
Examples:
    Input  : 00000010           Input  : 00000100
    Output : 00000001           Output : 00001000
 */
// Surprised and impressed it worked first time
byte Swap_EvenOdd_Bits_Byte(byte Byte)
{
    //  Odd bits mask = 0xAA     Even bits mask = 0x55
    return (Byte & byte(0xAA)) >> 1 | (Byte & byte(0x55)) << 1;
}

unsigned int Swap_EvenOdd_Bits_Integer(unsigned int n)
{
    //           Odd bits mask             Even bits mask
    return (n & 0xAAAAAAAA) >> 1 | (n & 0x55555555) << 1;
}

// 00111001
// 11000110
unsigned int Swap_2Bits_Nibble(unsigned int number) {
    number = (((number & 0xcccccccc) >> 2) | ((number & 0x33333333) << 2));
    return number;
}

unsigned char Swap_Nibbles_In_Byte(unsigned char c) {
    // !!!: Notice it is easier to swap nibbles in a byte
    return static_cast<unsigned char>((c >> 4) | (c << 4));
    /*c = c >> 4 | c << 4;  // Warning: Implicit conversion loses integer precision: 'int' to 'unsigned char'
    return  c;*/

}

unsigned int Swap_Nibbles_In_Integer(unsigned int n) {
    unsigned int oddNibble  = n & 0xF0F0F0F0;
    unsigned int evenNibble = n & 0x0F0F0F0F;
    return (oddNibble >> 4) | (evenNibble << 4);
}

unsigned int Swap_Bytes_In_Integer(unsigned int number) {
    number = ((number & 0xFF00FF00) >> 8) | ((number & 0x00FF00FF) << 8);
    return number;
}

unsigned int Swap_Halfword_In_Integer(unsigned int number) {
    number = number >> 16 | number << 16;
    return number;
}



//  Given a number x and two positions (from the right side) in the binary representation of x,
//  write a function that swaps n bits at given two positions and returns the result.
//  It is also given that the two sets of bits do not overlap.
int SwapRangeOfBits(unsigned int number, unsigned int pos1, unsigned int pos2, unsigned int range) {
    int result = 0;
    unsigned int mask1 = 0;
    unsigned int mask2 = 0;
    unsigned int shift1 = 0;
    unsigned int shift2 = 0;

    unsigned int z = pos1;      // 0b00101111; // 1, 5, 3
                                // mask = 0b11101110
                                //  &   = 0b00101110
    mask1 =  (1 << range) - 1;  // Creates all ones 11, 111, 1111,...
    shift1 = ((number >> pos1) & mask1) << pos2;
    shift2 = ((number >> pos2) & mask1) << pos1;
    result = shift1 | shift2;
    
    return result;
}

// Submitted Leetcode
// Runtime 0 ms Beats 100% Memory 5.7 MB MB Beats 99.4%
// !!!: does not work
bool Are_Bits_Alternating(unsigned int number) {
    bool one_has_been_seen = false;
    bool zero_has_been_seen  = false;

    while(number > 0) {   // if you used number>0, you would check only first alternating pattern from right
        // is current bit a '1'
        if( number & 1 ) {
            // current bit is 1
            if( one_has_been_seen ) {
                // two 1s in a raw 0110, return false
                return false;
            }
            
            // keep a '1 has been seen' flag true
            one_has_been_seen = true;
            // rest a '0 has been seen' flag to false
            zero_has_been_seen = false;
        }
        // is current bit a '0'
        else if( number & 0 ) {
            if(zero_has_been_seen) {
                // two 0s in a raw 1001, return false
                return false;
            }
            
            one_has_been_seen = false;
            zero_has_been_seen = true;
        }
        
        number >>= 1;
    }
    
    return true;
}

// !!!: Pay attention to ALL bits
bool Are_ALL_Bits_Alternating2( unsigned int n )
{
    return n == 0x55555555 || n == 0xAAAAAAAA;
}

unsigned int Swap2Bits1( unsigned int& num, int bit1, int bit2 ) {
    int x = (num >> bit1) & 1;     // x = 0 or 1
    int y = (num >> bit2) & 1;     // y = 0 or 1
    
    // Xor z (x ^ y) with number @ j to produce x. same for y.
    num ^= (x ^ y) << bit2;   // num = num ^ (((num >> i) & 1) ^ ((num >> j) & 1) << j);
    num ^= (x ^ y) << bit1;
    
    return  num;;
}

// !!!: √√√ I think simplier and more improtantly is easier to understand
unsigned int Swap2Bits2( unsigned int& num, int bit1, int bit2 ) {
    int x = (num >> bit1) & 1;
    int y = (num >> bit2) & 1;
    
    // !!!: only whent the 2 bits are different, swap them
    if( x != y ) {
        num ^= 1 << bit1;
        num ^= 1 << bit2;
    }
    
    return  num;;
}

unsigned char swap2Bits(unsigned char number, int bit1, int bit2)
{
    unsigned char result = 0;

    // Get 1st bit from data
    unsigned char bit_1 = (number >> bit1) & 1;

    // Get 2nd bit from data
    unsigned char bit_2 = (number >> bit2) & 1;

    // Get XOR of bit_1 and bit_2
    unsigned char xorBit1Bit2 = bit_1 ^ bit_2;

    result = (unsigned char )( number ^ (xorBit1Bit2 << bit1 | xorBit1Bit2 << bit2) );
 
    return result;
}

// !!!: Too complicated
unsigned char swap2BitsMySolution(unsigned char data, unsigned char bit1, unsigned char bit2)
{
    unsigned char result = 0;

    // Get 1st bit from data
    bool bit_1 = (data >> bit1) & 1;

    // Get 2nd bit from data
    bool bit_2 = (data >> bit2) & 1;

    // My solution:
    result = bit_1 ? (unsigned char)(data | 1<<bit2) : (data & ~(1<<bit2));
    result = bit_2? (unsigned char)(result | 1<<bit1) : (result & ~(1<<bit1));
 
    return result;
}

bool PowerOfTwo(unsigned int n)
{
    while ((n % 2) == 0)    // while n is even
        if ((n /= 2) == 1)  // if n/2 equals 1
            return 1;

    return 0;
}

long multiplyWithShift(short x, short y)
{
    long res = 0;
    int counter = 0;
    while( x > 0 ) {
        if (x & 1) {
            res += y << counter;
        }
        
        x >>= 1;
        counter++;
    }

    return res;
}

// you could return int instead of double. can not use int because of corner case when
// dividend and/or divisor are equal to INT_MIN = -2147483648. in this case, you must return
// 2147483648 which is outside the range of int (-2147483648...2147483647)
long int DivideWithoutUsingDivision_1(int dividend, int divisor)
{
    // sorry, you can not divide by 0
    if( divisor == 0 ) {
        throw std::runtime_error("Math error: Attempted to divide by Zero\n");
    }
    
    // handle corner case first
    if( dividend == INT_MIN ) {
        if( divisor == 1) {
            return INT_MIN;
        }
        if( divisor == -1) {
            // !!!: very important corner case
            return (unsigned int)(-INT_MIN);
            /* or, you can do this, it works as well:
             unsigned int temp = dividend * -1;
            return (temp);*/
        }
        if( divisor == INT_MIN ) {
            return 1;
        }
    }

    long int div = 0;
    int sign = 1;
    
    // handle first number's sign
    if( dividend < 0 ) {
        // update sign
        sign *= -1;
        
        // make dividend positive.
        // pay attention to the special case where dividend = INT_MIN
        dividend *= -1;
    }
    
    // handle first number's sign
    if( divisor < 0 ) {
        sign *= -1;
        divisor *= -1;
    }

    // now, do the division without division operator
    while( dividend >= divisor ) {
        dividend -= divisor;
        div++;
    }
    
    // at this point, we have correct division sign
    return div * sign;
}

// does not work for: a = INT_MIN, b = -1
int DivideWithoutUsingDivision_2(int a, int b) {
    int count = 0;
    int sum = b;
    while (sum <= a) {
        sum += b;
        count++;
    }
    return count;
}

// 16.0 in Interview book. Good work by ME
int printDuplicatesInBigDataSet(unsigned int* a, int size)
{
    // I have 4KB of memory = 4Kbyte * 1024 bytes/Kbyte * 8 bits/byte = 32768 bits.
    // For numbers (1...32000), N = 32000. Each bit represents a number:
    // I need 32000 bits or 32000/8 = 4000 bytes to represent these numbers.
    // So, 32768 bits of memory is grater than 32000 numbers. 1 bit for each number. √√√
    
    unsigned char memory[4*1024] = {0};  // Allocate memory bytes
    int byteIndex = 0;
    int bitIndex  = 0;
    int count = 0;  // used for illustration
    cout << endl << endl << "duplicate number: " <<  endl;
    
    // Traversal of bits in memory
    for(int i=0; i<size; i++)
    {
        byteIndex = (a[i] - 1) / 8;     // -1 because, N = 1......32000
        bitIndex  = (a[i] - 1) % 8;     // bitIndex = 0...7
        
        // Is number in bigset
        if( memory[byteIndex] & 1 << bitIndex ) {
            cout << a[i] << ", ";   // Found: Number's bit in memory is set
            count++;
        }
        else {
            // Not Found: Number's bit in memory is not set, set its bit in memory
            memory[byteIndex] |= 1 << bitIndex;
        }
    }

    return count;
}

void OnesLeftZerosRight(int* array, int size)
{
    int lastSwap = 0;
    for(int i=0; i < size; i++)
    {
        if(array[i] == 0)
        {
            for(int j = lastSwap + 1; j < size; j++)
            {
                if(array[j] == 1)
                {
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    lastSwap = j;   // for effeciency
                    break;
                }
            }
        }
      //  lastSwap = i;
    }
}

unsigned int ReverseBits1( unsigned int number )
{
    int result = 0; // Must be initialized to zero

    // from i = 0 -> 31, check ith bit for a 1 => ( != 0)
    for(int i = 0; i < WORD_BIT; i++) {
        if( (number & (1 << i))) {
            result |= 1 << ((WORD_BIT - 1) - i);
        }
    }

   return result;
}

void ReverseBits2(unsigned int& n)
{
    if( n == 0 || n == INT_MAX )
       return;
       
    int result = 0; // Must be initialized to zero
    
    // from i = 0...31, check ith bit for a 1 and put it at (intsize - 1) - i
    for(int i = 0; i < WORD_BIT; i++) {
            result |= ((n >> i) & 1) << ((WORD_BIT - 1) - i);
    }

    // only difference from ReverseBits() above
    n = result;
}

// !!!: Best in my opnion
unsigned int ReverseBits3( unsigned int n )
{
    unsigned int result = 0;
    unsigned int size = WORD_BIT;
    while( size )
    {
        result <<= 1;       // !!!: Critical: Shift result FIRST to make a space for new bit.
        result |= n & 1;    // bit0 = 0 or 1

        n >>= 1;
        size--;
    }

    return result;
}

// rotate bits left
int rotateBitsLeft_1(int n, int shiftleft)
{
    int result = 0;
    int INT_SIZE = WORD_BIT;
 
    // 01101001 << 3 = 01001 011
    // !!!: first, shift right all bits from (INT_SIZE - shiftleft) to INT_SIZE
    for( int i = INT_SIZE - shiftleft; i < INT_SIZE; i++ ) {
            result |= ((n >> i) & 1) << (i - (INT_SIZE - shiftleft));
    }
    
    // !!!:  second, shift n left by shiftleft bits
    result |= n << shiftleft;
    
    return result;
}

// Is clearer than RotateBitsLeft_1()
void RotateBitsLeft_2( int& n, int shiftleft )
{
    int result = 0;    // OR int result = n;
    
    for(int i = WORD_BIT - 1; i >= (WORD_BIT - shiftleft); i--) {
        result <<= 1;
        result |= (n >> i) & 1;
    }
    result |= (n << shiftleft);

    n = result;
}

// !!!: Even faster than previous versions √√√√√
void rotateBitsLeft_3(unsigned int& n, int rotateleft)
{
    n = (n >> (WORD_BIT - rotateleft)) | (n << rotateleft);
}

void SwapNumbers_NotUsingtemp( int& x, int& y )
{
    int t = x ^ y;
    x = t ^ x;      // x = x ^ y ^ x = y.   x^x=0 and 0^y=y;
    y = t ^ y;      // y = x ^ y ^ y = x
}

// count trailing zero bits for a number.
// if number is 1101000, then c will be 3
// my solution. it works
char trailingZeros_1( char number )
{
    int count = 0;
    int i = 0;
    while( i < CHAR_BIT ) {
        if (number & 1) {
            return count;
        }

        count++;

        number >>= 1;
        i++;
    }
    
    return count;
}

// eficient version, but harder to understand
char trailingZeros_2( char number)
{
    //                n = 01101000 (base 2), then count will be 3
    //            n - 1 = 01100111
    //      n ^ (n - 1) = 00001111  // this step can be used to flip trailing 0s to 1s
    // n ^ (n - 1) >> 1 = 00000111

    int count = 0;
    
    if( number )
    {
        // !!!: very interesting. set number's trailing 0s to 1s and zero rest
        number = (number ^ (number - 1)) >> 1;
        for (count = 0; number; count++)
        {
            number >>= 1;
        }
    }
    else
    {
         count = CHAR_BIT * sizeof( number );
    }
     
     return count;
 }

// my solution.
int leadingZeros_1( int number )
{
     int last_bit_mask = 1 << (WORD_BIT - 1);
     int zero_count = 0;
     
    // count trailing 0s: if last (31st) bit is 0, increment zero count.
    // zero count can't be greater than WORD_BIT, therefore, "zero_count < WORD_BIT" is checked
     while( zero_count < WORD_BIT && (number & last_bit_mask) == 0)
     {
         zero_count++ ;
         number <<= 1;
     }
    
    // at this point, either we reached end or fir 1 was found, or both
     return zero_count;
}

int is_number_odd_or_even( int number )
{
    return  number & 1;     // odd == 1 and even == 0
}

int is_char_lower_or_upper( char character )
{
    return (97 <= character && character <= 122) ? 0 : 1;
}

// !!!: ************************                                        **************************
// !!!: ************************    CountNegative and Positive Pulses   **************************
// !!!: ************************                                        **************************
// !!!: This is real cool. I am impressed with myself
/*  Given a binary string, write an algorithm to find THE NUMBER of patterns of form 1[0]1 
    where [0] represents any number of zeroes (minimum requirement is one 0) there should not
    be any other character except 0 in the [0] sequence.*/
// !!!: Aukward but works
int CountNegative_1(string str)
{
    enum { LOW, HIGH };
    int  negative_pulses = 0;
    bool prev_level      = LOW;
    bool edge_down       = false;
    
    for( char curr_level: str ) {
        
        if( curr_level == '1' ) {
            if( edge_down ) {
                negative_pulses++;     // found a negative pulses
                edge_down = false;     // reset high to low to LO
            }
            
            prev_level = HIGH;
        }
        
        // look for the a transition from HIGH to LOW
        if( prev_level == HIGH && curr_level == '0' && !edge_down) {
            edge_down = true;
        }
    }
    
    return negative_pulses;
}

// !!!: √√√ My solution: is Better and clearer
int CountNegative_2( vector<int> data )
{
    enum { LOW, HIGH };
    size_t bits       = data.size();
    int    bit        = 0;
    int    neg_pulses = 0;
    bool   edge_down  = false;

    while( bit < bits - 1 ) {
        // find the falling edge
        if( data[bit] == HIGH && data[bit+1] == LOW ) {
            edge_down = true;       // we have an edge_down
        }
        
        // find the rising edge
        if( data[bit] == LOW && data[bit+1] == HIGH && edge_down == true ) {
            neg_pulses++;
        }

        bit++;
    }

    return neg_pulses;
}

int CountPositive_1( string str )
{
    int pulse_count = 0;
    enum { LOW = '0', HIGH = '1' };
    
    int  prev_level = HIGH;
    bool pos_edge   = false;
    
    for( char curr_level : str ) {
        if( curr_level == LOW ) {
            if( pos_edge ) {
                pulse_count++;                    // found pattern
                pos_edge = false;     // reset high to low to LO
            }
            
            prev_level = LOW;
        }
        
        // look for the a transition from HIGH to LOW
        if( prev_level == LOW && curr_level == HIGH && !pos_edge) {
            pos_edge = true;      // else if(oneseen){ would also work. if(oneseen){ would also work.
        }                                       // else if(c == '0' && oneseen){ would also work.
    }
    
    return pulse_count;
}

// A pulse is defined as: an edge_up followed by an edge_down. !!!: order is very important
// !!!: My best solution
int CountPositive_2( vector<int> data )
{
    size_t bits       = data.size();
    int    bit        = 0;
    int    pos_pulses = 0;
    bool   edge_up    = false;

    while( bit < bits - 1 ) {
        // find the rising edge
        if( data[bit] == 0 && data[bit+1] == 1  ) {
            edge_up = true;     // we have an edge_up, since right bit > current bit
        }
        
        // find the falling edge
        if( data[bit] == 1 && data[bit+1] == 0 && edge_up == true ) {
                pos_pulses++;   // we have a pulse, since we have an edge_down and we had seen an edge_up
        }
        // disregard the 2 conditions where: serial_data[bit] and serial_data[bit+1] are the same.
        // They are Don't care conditions. the level stays the same: 0 or 1. no need to process these 2 conditons
        
        bit++;
    }
    
    return pos_pulses;
}

vector<int> Edges( string str )
{
    vector<int> result(2);
    int neg_edges = 0;
    int pos_edges = 0;
    int prev_level = str[0];
    
    // count lows and highs
    for( int level=1; level < str.size(); level++ ) {
        if( str[level] == '0' ) {
            if( prev_level == '1' ) {
                // high to low transition ;
                neg_edges++;
            }
            prev_level = '0';
        }
            
        if( str[level] == '1' ) {
            if( prev_level == '0') {
                // low to high transition ;
                pos_edges++;
            }
            prev_level = '1';
        }
    }
    
    // return negative and positive edges
    result[0] = neg_edges;
    result[1] = pos_edges;
    return      result;
}

void numOf_Neg_Pos_Pulses( vector<int> topograhpy )
{
    if( topograhpy.size() < 2) {
        cout << "   No Positive or Negative Pulses";
    }
    
    int    location  = 0;
    int    peaks     = 0;
    int    valleys   = 0;
    bool   edge_up   = false;
    bool   edge_down = false;

    while( location < topograhpy.size() - 1 ) {
        // chaeck if next location is higher than current location
        if( topograhpy[location+1] > topograhpy[location] ) {
            edge_up   = true;       // upward transitioin
            if( edge_down == true )  {
                valleys++;
            }
            edge_down = false;
        }
        
        if( topograhpy[location+1] < topograhpy[location] ) {
            edge_down = true;       // going down
            if( edge_up == true )  {
                peaks++;
            }
            edge_up   = false;
        }
        
        location++;
    }

    // just for illustration: to tell if we are up or down or flat, when there are no peaks or valleys
    if( peaks == 0 && valleys == 0 ) {
        cout << "\n   Result = No Positive or Negative Pulses, ";
        if( edge_up ) {
            cout << "\n            Just One Edge Up";
        }
        if( edge_down ) {
            cout << "\n             Just One Edge Down";
        }
        if( !edge_up && !edge_down ) {
            cout << "\n            No Edges at all";
        }
        return;
    }
    
    cout << "\n   Result = "<< peaks << " Positive Pulses and " << valleys << " Negative Pulses\n";
    return;
}

// !!!: /////////////////   PULSES  ////////////////////
//
//  Given a SORTED array containing only numbers 0 and 1, the task is to find the transition point efficiently.
//  The transition point is the point where “0” ends and “1” begins.
//  A transition point is the index of the first ‘1’ appearing in the array.


// Run time is O(n)
int FirstPositiveEdge_1( vector<int> serial_data )
{
    size_t bits = serial_data.size();

    for( int bit = 0; bit < bits - 1; ++bit ) {
        // find the rising edge
        if( serial_data[bit] == 0 && serial_data[bit+1] == 1  ) {
            return bit + 1;
        }
    }
    
    return -1;
}
    
/* Given an array of sorted numbers containing only 0s and 1s, find the transition point.
   A transition point is the index of the first ‘1’ appearing in the array*/
// !!!: taken advantage of SORTED array. O(log n) √√√
int FirstPositiveEdge_2( vector<int> array )
{
    int size = static_cast<int>(array.size());
    int left  = 0;
    int right = size - 1;
    
    int count = 0;
    while( left <= right ) {
        count++;
        int mid  = (left + right) / 2;
        
        if( array[mid] == 0 ) {         // handle 0
            left = mid + 1;             // go right
        }
        
        if( array[mid] == 1 )  {        // handle 1
            if( mid == 0 ) {            // corner case first
                cout << "\n   Count = " << count;
                return -1;              // reached left end and no transition was found: all 11111s
            }
            
            if ( array[mid-1] == 0 ) {  // is 0 is left of this 1?
                cout << "\n   Count = " << count;
                return  mid;            // A. yes, found a transition. return middle index
            }

            right = mid - 1;            // B. no, go left
        }
    }
    
    cout << "\n   Count = " << count;
   return -1;                   // no transitions: all 0s, or all 1s
}

// !!!: Very similar to version 2 √√√
// !!!: I think it is a little clearer
int FirstPositiveEdge_3( vector<int> a )
{
    int size = static_cast<int>(a.size());
    int left  = 0;
    int right = size - 1;
    
    int count = 0;
    while( left <= right ) {
        count++;
        int mid  = (left + right) / 2;
        
        // Handle Corner case first: eithier all zeros or all ones
        if( mid == 0 || mid == a.size()-1 ) {
            cout << "\n   Count = " << count;
            return -1;              // reached left end and no transition was found: all 11111s
        }

        if( a[mid] == 0 ) {         // handle 0
            if( a[mid+1] == 1 ) {   // is 1 left of this 0?
                cout << "\n   Count = " << count;
                return mid+1;
            }
            left = mid + 1;         // go right
        }
        
        if( a[mid] == 1 )  {        // handle 1
            if ( a[mid-1] == 0 ) {  // is 0 left of this 1?
                cout << "\n   Count = " << count;
                return  mid;            // A. yes, found a transition. return middle index
            }

            right = mid - 1;            // B. no, go left
        }
    }
    
    cout << "\n   Count = " << count;
   return -1;                   // no transitions: all 0s, or all 1s
}



// -_- = one valley
// _-_ = one pulse
void Draw_Square_Wave( string str )
{
    for( char curr_level: str ) {
        if( curr_level == '1' ) {
            cout << '-';
        }
        if( curr_level == '0' ) {
            cout << '_';
        }                                       // else if(c == '0' && oneseen){ would also work.
    }
}

// !!!: ////////////////   Longest Substring Of 1s After Removing One Element   ////////////////
// !!!: VERY IMPORTANT: in all these functions, pay attention to the passed parameter: array, string or integer
/*
 Medium. Longest Subarray of 1's After Deleting One Element (0 or 1).
 Given a BINARY array nums, you should delete one element from it. Return the size of the
 longest non-empty subarray containing only 1's in the resulting array. Return 0 if there is no such subarray.
 Handle edge cases: If all elements in the array are 1, return the length of the array minus 1. If all elements are 0, return 0, as there will be no contiguous 1's after deletion.
 Example 1:
Input: nums = [1,1,0,1]
 Output: 3
 Explanation: After deleting the number in position 2, [1,1,1] contains 3
 numbers with value of 1's.

 Example 2:
 Input: nums = [0,1,1,1,0,1,1,0,1]
 Output: 5
 Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1]
 longest subarray with value of 1's is [1,1,1,1,1].

 Example 3:
 Input: nums = [1,1,1]
 Output: 2
 Explanation: You must delete one element.

 Example 4:
 Input: nums = [1,1,0,0,1,1,1,0,1]
 Output: 4

 Example 5:
 Input: nums = [0,0,0]
 Output: 0
 */
/* Leetcode Runtime: 36 ms, faster than 66.77% of C++ online submissions for Longest Subarray of 1's After Deleting One Element.
   Memory Usage: 36.5 MB, less than 39.37% of C++ online submissions.*/
// !!!: √√√. passing a string
int longestSubstringOf1s_afterRemoving_1bit_1( string str )
{
    int curr_count = 0;      // current  1s sum
    int prev_count = 0;      // previous 1s sum
    int max_count  = 0;      // maximum  1s sum

    int i = 0;
    for( char c : str ) {
        // handle '1'
        if( c == '1' ) {
          curr_count++;
        }

        // handle '0' or end of string
        if( c == '0' || i == str.length() - 1 ) { // c == '0' || end of string
            // 1. determine max sum based on current and previous sums
            if( (curr_count + prev_count) > max_count ) {
                max_count = prev_count + curr_count;
            }

            // 2. save current sum, and reset it to 0
            prev_count = curr_count;  // !!!: for 2 adjacent 0s, prev count becomes = 0;
            
            curr_count = 0;
        }

        i++;
    }

    // 1) corner case: string is all 1s. after removing 1 bit from it, we get max count - 1
    if( max_count == str.size() ) {
        return max_count - 1;
    }

    return max_count;
 }

// using zero flag as extra variable
int longestSubstringOf1s_afterRemoving_1bit_2( string str )
{
    int prevCount = 0;      // left count of 1s
    int currCount = 0;      // right count of 1s
    int maxCount  = 0;      // maximum count of 1s
    
    bool prevZero = false;  // !!!: good idea, using zero flag as extra variable for efficincy √√√

    int i = 0;
    for( char c : str ) {
        // handle '1'
        if( c == '1' ) {
            currCount++;
            
            prevZero = false;
        }

        // handle '0' and end of string
        if( c == '0' || i == str.length() - 1 ) { // c == '0' || end of string
        
            // 1) only at first 0, we determine max sum based on current and previous sums
            if( !prevZero ) {
                // do this only if you have only a one 0
                if( (prevCount + currCount) > maxCount ) {
                     maxCount = prevCount + currCount;
                }
            }

            // 2. always save current sum, then reset it to 0,
            //    wether, 0 or more in a row have been seen
            prevCount = currCount;
            currCount = 0;

            prevZero = true;
        }

         i++;
    }

    // 1) corner case: string is all 1s. after removing 1 bit, we get max count - 1
    if( maxCount == str.size() ) {
        return maxCount - 1;
    }

    return maxCount;
 }

// !!!: ////////////////  Longest Subsequence Of 1s After 'FLIPPING' 1 Bit   ////////////////
// !!!: ////////////////
// taking advantage of my longestSubstringOf1s_afterRemoving_1bit() function
int longestSubsequenceOf1s_afterFlipping_1bit_util( int integer )
{
    string str = DecimalToBinary_mine( integer );
     
    return longestSubstringOf1s_afterRemoving_1bit_1( str ) + 1;
}

/*  Flip Bit to Win: You have an integer and you can flip exactly one bit. Write code to
    find the length of the longest sequence of 1 s you could create.
    EXAMPLE
    Input: 1775 (or: 11011101111)
    Output: 8 */
// !!!!: Optimal Algorithm: MUST READ
// To reduce the space usage, note that we don't need to hang on to the length of each sequence the entire
// time. We only need it long enough to compare each 1s sequence to the immediately preceding 1s sequence.
// Therefore, we can just walk through the integer doing this, tracking the current 1s sequence length and the
// previous 1s sequence length. When we see a zero, update previousLength:
// my function, passing integer. !!!: works √√
int longestSubsequenceOf1s_afterFlipping_1bit( int integer )
{
    // 1) if all 1s, this is already the longest sequence
    if( ~integer == 0 ) {
        // yes, return max bits for integer
        return sizeof(integer) * 8 - 1;
    }
    
    int currCount = 0;
    int prevCount = 0;
    int maxCount  = 0;

    // 2) must check all bits
    int i = 0;  // to keep track of last bit
    while( i < 32 ) {
        // 0000000111011011, 6     0000011011101111, 8
        // 2.1) current bit is 1: increment current count
        if( (integer & 1) == 1 ) {
            ++currCount;
        }
        
        // 2.2) current bit is 0 or reached last bit:
        //      add prev and current counts and save it as max count, if it is > max count.
        if( (integer & 1) == 0 || i == 31 ) {
            
            if( (prevCount + currCount) > maxCount ) {
                maxCount = prevCount + currCount;
            }

            prevCount = currCount;
            
            currCount = 0;      // start a new count
        }

        integer >>= 1;
        i++;
    }
    
    return maxCount + 1;
}

// From: https://tutorialhorizon.com/algorithms/maximum-contiguous-ones-after-one-flip-allowed/
// !!!: Interesting
int longestContiguousOnes_afterFlipping_oneBit( vector<int> input )
{
    int left = 0;
    int right = 0;
    int flip = 0;
    int max = 0;

    while( right< input.size() ) {
        if( input[right] == 1 )
            right++;
        else{
            if(flip<1) {
                flip++;
                right++;
            }
            else{
                if(input[left++]==0)
                    flip--;
            }
        }
        max = std::max(max, (right-left));
    }
    return max;
}

// From Cracking the Interview Code. !!!: best in performance √√√.
// similar to: "int longestSubsequenceOf1s_AfterFlipping_0_to_1( int integer )".
int flipBit_to_Win( int bits )
{
    // if all 1s, this is already the longest sequence
    if(~bits == 0) {
        return sizeof( bits ) * 8 - 1;
    }
    
    int currCount = 0;
    int prevCount = 0;
    int maxCount  = 1;   // integer can always have a sequence of at least a 1
    
    while( bits != 0 ) {
        if( (bits & 1) == 1 ) {
            ++currCount;    // current bit is 1
        }
        else if( (bits & 1) == 0 ) {
            // current bit is 0
            // update prev count to 0 (if next bit is 0), or to curr count (if next bit 0)
            if( (bits & 2) == 0 ) {  // corner case: 2 adjacent 0s
                prevCount = 0;
            }
            else {
                prevCount = currCount;
            }
            
            currCount = 0;
        }
        
        // wiki:
        maxCount = std::max( prevCount + currCount + 1, maxCount );
        // mine: does not work
        //maxCount = std::max( prevCount + currCount, maxCount );
        
        bits >>= 1;
    }
    
    // wiki:
    return maxCount;
    // mine: does not work
    //return maxCount +1;

}

// !!!: ////////////////   ////////////////
// !!!: ////////////////


// Unnecessary complicated. O(N2). See version 2
int EqualLengths_of_Zeros_Ones_1( vector<int> &a )
{
    int maxcount = 0;

    for( int left = 0; left < a.size()-1; left++ ) {
        int zerocount = 0;
        int onecount = 0;
        
        for( int right = left; right < a.size (); right++ ) {
            if( a[right] == 1 ) {
              onecount++;
            }
            else if( a[right] == 0 ) {
              zerocount++;
            }

            if( zerocount == onecount ) {
                if( (zerocount + onecount) > maxcount ) {
                    maxcount = zerocount + onecount;
                }
            }
        }
    }

    return maxcount;
}

// Much simpler than version 1. O(N)
int findEqualLengths_of_Zeros_Ones_2( vector<int> &nums )
{
    int zerocount = 0;
    int onecount = 0;

    for( int i = 0; i < nums.size(); i++ ) {
        if( nums[i] == 1 ) {
          onecount++;
        }
        else if( nums[i] == 0 ) {
          zerocount++;
        }
    }

    // interesting and makes sense
    return std::min(zerocount, onecount) * 2; // 2, becausse count of 0 & 1 = 2
}

// toggle odd bits until number is zero
unsigned int Toggle_Oddbits_1( unsigned int n )
{
    unsigned int mask = 0, count = 0;

    for( unsigned int temp = n; temp > 0; temp >>= 1 ) {
        if( count % 2 == 1 ) {      // Odd count
            mask |= (1 << count);
        }
        count++;
    }
    return n ^ mask;
}

unsigned int Toggle_Oddbits_2( unsigned int n)
{
    return  n ^ 0xAAAAAAAA;
}

// Given a positive integer n, find count of positive integers i such that 0 <= i <= n and n+i = n^i.
// program to print count of values such that n+i = n^i.
// Function to count number of values less than equal to n that satisfy the given condition
int Equal_Sum_and_XOR (int n)
{
    int countV = 0;

    // Traverse all numbers from 0 to n and increment result only when given condition is satisfied.
    for( int i=0; i <= n; i++ ) {
        if( (n + i ) == (n ^ i) ) {
            cout << "   i = " << i << ":\tn + i = " << (n+i) << ",\t\tn ^ i = " << (n ^ i) << "\n";
            countV++;
        }
    }

    return countV;
}


// XOR a number n
void XORnumbers(int n)
{
    int i = 0;
    int res = 0;
    while( i <= n )
    {
        /*cout << res << " XOR " << i << " = " ;
        res ^= i;
        cout << res << endl;*/
        cout << "   " << n << " XOR " << i << " = " << (n^i) << endl;
        i++;
    }
}


/* You are given an array of binary strings strs and two integers m and n. Return the size of the largest subset of strs such that there are at most m '0's and n '1's in the subset.
   A set x is a subset of a set y if all elements of x are also elements of y.
   Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
   Output: 4
   Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
  Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
  {"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.*/
int Find_MaxForm(vector<string>& strs, int m, int n) {
    int zerosCount = 0;
    int onesCount = 0;
    int strcCount = 0;
    
    for( string str : strs ) {
        for(char c : str) {
            // A or B
            if(zerosCount > m || onesCount > n) {
                break;
            }
            if(c == '0')
                zerosCount++;
            else
                onesCount++;
        }
        
        // A && B
        if(zerosCount <= m && onesCount <= n) {
            strcCount++;    // if you get here, break statment above is not executed
        }
        
        zerosCount = 0;
        onesCount  = 0;
    }
    
    return strcCount;
}

// https://www.educative.io/blog/top-cpp-coding-interview-questions#data-structs
/*  Move All Zeros to the Beginning of the Array
 Problem Statement:  “Given an integer array, move all elements that are 0 to the left while maintaining
    the order of other elements in the array. The array must be modified in-place.  ”
 Hints:
    Use reader/writer indexes
    You cannot use a simple chronological sort as elements other than zeros must maintain their position.
 */
void move_zeros_to_left(vector<int>& a)
{
    int write_index = static_cast<int>(a.size()) - 1;
    int read_index = write_index;

    while( read_index >= 0 ) {
        if(a[read_index] != 0) {
          a[write_index] = a[read_index];
          write_index--;
        }

        read_index--;
  }

  while(write_index >= 0) {
    a[write_index] = 0;
    write_index--;
  }
}

// The best: vector version
vector<int> ZeroOneTwo3(vector<int> v) {
    vector<int> result(v.size());   // = {0};
    int lastZero = 0;
    int lastOne  = 0;
    unsigned long lastTwo = v.size() - 1;

    // 2,1,0,0,2 -> 0,0,0,0,2 -> 0,1,0,0,2 ->
    for(int i=0; i < v.size(); i++) {
        if(v[i] == 2) {
            result[lastTwo--] = 2;
        }
        else if(v[i] == 1) {
            result[lastOne] = 1;
            lastOne++;
        }
        else {  // v[i] == 0
            // move zero to right place and move 1 right 1 position if you have to
            if(result[lastZero] == 1)  {
                result[lastOne] = 1;
            }
            result[lastZero] = 0;
            lastZero++;
            lastOne++;  // Must be updated here, not in if() above
        }
    }
    
    return result;
}

// The best: string version
string ZeroOneTwo4(string s)
{
    string result ("");
    //result.resize(s.size());        // Very important!!!

    int index0 = 0;                 // Index of last ZERO written to result
    int index1 = 0;                 // Index of last ONE written to result
    unsigned long index2 = s.size() - 1; // Index of last TWO written to result
    
    for(char c : s) {
        if(c == '0') {
            if(result[index0] == '1') {
                result[index1] = '1';
            }
            result[index0] = '0';
            index0++;                // Pay attention to next 2 lines
            index1++;
        }
        if(c == '1') {
            result[index1] = '1';
            index1++;
        }
        if(c == '2') {
            result[index2] = '2';
            index2--;
        }
    }
    
    return result;
}

int N = sizeof(unsigned short) * 8;
// Leading j bits (MSB) of 16-bit number:
unsigned short LeadingBits( unsigned short &x, int j ) {
    return x >> (N - j);
    //return (x >> (N-j)) & ((1<<j) - 1);
}
// Trailing j bits (LSB) of 16-bit number:
unsigned short TrailingBits( unsigned short &x, int j ) {
    return  x & ((1<<j) - 1);
}
// Middle bits btween i and j bits:
unsigned short MiddleBits( unsigned short &x, int i, int j ) {
    return  (x >> i) & ((1<<(j-i+1)) - 1);
}

// Do not use. We do not want to change outside function
// Returns 15 for x=0: it is OK. Leading 0s for 0 is undefined
int Leading0s( unsigned short x )
{
    int ones_count = 1;
    while( x >>= 1 ) { ++ones_count; }
    return N - ones_count;  // return zeros_count = N - ones_count */
    // OR
    /* int ones_count = 0;
    while( x ) { ++ones_count; x >>= 1; }
    return N - ones_count;  // return zeros_count = N - ones_count */

}

// Returns 15 for x=0: it is OK. Leading 0s for 0 is undefined
int Trailing0s( unsigned short x )
{
    int count = 1;
    while( x <<= 1 ) { ++count; }
    return N-count;
}

/*  Given a binary string, write an algorithm to find the number of patterns of form 1[0]1 where [0]
    represents any number of zeroes (minimum requirement is one 0) there should not be any other character
    except 0 in the [0] sequence.   */
int PatternCount( string str )
{
    int count = 0;
    bool edge_up = false, edge_down = false;
    
    for( int i=0; i<str.size()-1; ++i ) {
        
        if( str[i] == '1' ) {
            if( str[i+1] == '0' ) {     // Find edge down, when going from 1 to 0
                edge_down = true;
            }
        }
        
        if( str[i] == '0' ) {
            if( str[i+1] == '1' ) {     // Find edge up, when going from 0 to 1
                edge_up = true;
                if( edge_down ) {
                    count++;
                }
            }
        }
    }
    
    return count;
}


/*  Check if all bits can be made same by flipping two consecutive bits
    Difficulty Level : Expert
    Last Updated : 06 Apr, 2021
    Given a binary string, the task is to find whether all the digits of the string can be made equal
    i.e either 0 or 1 by flipping two consecutive bits any number of times.
 
    Examples: Input: 01011   (1-indexed)
    Output: YES
    Explanation: Flip 2nd and 3rd bit -> 00111,
                 again flipping 1'st and 2'nd bit -> 11111

    Input: 100011
    Output: NO
    Explanation: No number of moves can ever equalize all elements of the array.
 */
