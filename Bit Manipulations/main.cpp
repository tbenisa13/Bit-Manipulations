//
//  main.cpp
//  Bit Manipulations
//
//  Created by Taher Benisa on 5/6/24.
//

#include <iostream>
#include "BitManipulations.hpp"
#include "NumberConversions.hpp"
#include "Vectors.hpp"


using std::cout;
using std::string;
using std::hex;
using std::dec;
using std::bitset;
using std::endl;
using std::vector;
using std::byte;

// GIT
int main(int argc, const char * argv[]) {
    {
        string str = "1110001001101";   // "0110001001101"
        cout << "Number of Patterns of form 1[0]1 for str[] = " << str << endl;
        int result = PatternCount( str );
        cout << "Answer: " << result;
    }

    {
        unsigned int number = 0b0010110100;
        int bit1 = 4;
        int bit2 = 5;
        cout << "1) Swap bits i = " << bit1 << " and j = " << bit2 << " for\n          number = " << number << " = ";
        cout << DecimalToBinary_mine( number );
        
        unsigned int result = Swap2Bits1( number, bit1, bit2) ;
        cout << "\n          Result = " << result << " = ";
        cout << DecimalToBinary_mine( result );
        
        cout  << "\n\n2) Now Swap back the 2 bits, you should get the number back: ";
        bit1 = 5;
        bit2 = 4;
        result = Swap2Bits2( number, bit1, bit2) ;
        cout << "\n          Result = " << result << " = ";
        cout << DecimalToBinary_mine( result );
    }
    
    {
        unsigned short x = 0b1100001110000011;  // 16 bits => 50051
        int j = 1; // number of leftmost bits
        cout << "\n\nLeading  n-bits (MSB bits) for " << bitset<16>(x) << " = " << LeadingBits ( x, j );
        cout << "\nTrailing n-bits (LSB bits) for "   << bitset<16>(x) << " = " << TrailingBits( x, j );
        
        const int i = 5;
        const int j1 = 10;  // !!!: j1 must be >= i
        cout << "\n\nMiddle n-bits (" << i << " ... " << j1              << ") for: " << bitset<16>(x);
        unsigned short int result =  MiddleBits( x, i, j1 );
        cout << "\n    Distracted bits = " << bitset<j1-i+1>(result) << " (" << result <<")";
        
        // Trailing 0s
        x = (unsigned short int) 0b0000000000000001;
        cout << "\nLeading  0s Count for " << bitset<16>(x) << " = " << Leading0s ( x );
        x = (unsigned short int) 0b1000000000000000;
        cout << "\nTrailing 0s Count for " << bitset<16>(x) << " = " << Trailing0s( x );
    }
    {
        int n = 0b10000;
        cout << "\n\nEqual_Sum_and_XOR for n = " << n << ": \n";
        Equal_Sum_and_XOR( n );
        
        cout << "\n\nXOR Numbers for " << n << ": " << endl;
        // n = 16;
        XORnumbers( n );
    }
    {
        unsigned int n = 0b110110110110;
        cout << hex << Toggle_Oddbits_1(n) << "\n";
        cout << hex << Toggle_Oddbits_2(n) << "\n\n";
    }
    
    // !!!: ///////////////////      Bits and Pieces     ///////////////////
    // !!!: ///////////////////      Swap 2 Bits         ///////////////////
    {
        unsigned char data = 0b10100000;
        unsigned char bit1 = 7, bit2 = 0;
        cout << "\n\nSwap bits " << bit1 << " and " << bit2 << "       = " << bitset<8>(data) << endl;
        unsigned char result = swap2Bits(data, bit1, bit2);
        cout << "After swapping the bits = " << hex << bitset<8>(result)  << endl << endl;
        //cout << "After swapping the bits = " << hex << (unsigned)result << endl << endl;
        
        cout << "My Swap bits " << bit1 << " and " << bit2 << "    = " << bitset<8>(data) << endl;
        unsigned char result1 = swap2BitsMySolution(data, bit1, bit2);
        cout << "After swapping the bits = " << hex << bitset<8>(result1);
        //cout << "After swapping the bits, data value is: " << hex << (unsigned)result1 << endl;
    }
    
    // !!!: ///////////////////      Swap Nibbles in a Byte    ///////////////////
    {
        unsigned char byte = 0xEF;
        cout << "\n\nSwap Nibbles in Byte = 0x" << hex << static_cast<unsigned int>(byte);
        unsigned char newbyte = Swap_Nibbles_In_Byte(byte);
        cout << "\nSwapped Nibbles      = 0x" << (unsigned int)newbyte << endl;
    }
    {
        unsigned char c = 0xBA;
        cout << "\n\t\t\t\t    c = " << hex << (unsigned int)(c) << endl;
        // return value promoted from 'unsigned char' to 'int'
        int result = Swap_Nibbles_In_Byte(c);
        cout << "Swap Nibbles in Bytes = " << result << endl;
    }
    {
        unsigned int n = 0xABCDEF;
        cout << "\n\t\t\t\t\t  n = " << n << endl;
        unsigned int result = Swap_Nibbles_In_Integer(n);
        cout << "Swapped nibbles in word = " << result << endl;
    }
    {
        std::byte b = byte(0b1110111);
        cout << "\nSwap Even and Odd Bits in a Byte: " << bitset<8>(int(b)) << endl;
        byte result = Swap_EvenOdd_Bits_Byte(b);
        // cout << int(result) << endl;
        cout << "                          result: " << bitset<8>(int(result))  << endl;
    }
    {
        unsigned int number = 0b111001;
        cout << "\nn                        = " << bitset<8>(number) << endl;
        unsigned int result1 = Swap_EvenOdd_Bits_Integer(number);
        cout << "Swaped Even and Odd Bits = " << bitset<8>(result1)  << endl << endl;
    }
    {
        unsigned int number = 0b111001;
        cout << "\nn                       = " << bitset<8>(number) << endl;
        unsigned int result2 = Swap_2Bits_Nibble(number);
        cout << "Swaped 2 Bits of Nibble = " << bitset<8>(result2)  << endl << endl;
    }
    {
        unsigned int number = 0x12ABCDEF;
        cout << hex << "number = " << number << endl;
        unsigned int result3 = Swap_Bytes_In_Integer(number);
        cout << "Swaped Bytes of Integer = " << result3 << endl;
    }
    {
        unsigned int number = 0x12ABCDEF;
        unsigned int result4 = Swap_Halfword_In_Integer(number);
        cout << "Swaped Half-Word of Integer = " << result4 << endl;
    }
    {
        unsigned int integer = 0b00101111;
        int fromPos          = 1;
        int toPos            = 5;
        int range            = 3;
        cout << "Given a number = " << bitset<8>(integer) << ", Swap " << range << " bits from " << fromPos << " to " << toPos << endl;
        int res = SwapRangeOfBits(integer, fromPos, toPos, range);
        cout << "        Result = " << bitset<8>(res) << endl;
    }
    {
        int x = 5;
        int y = 7;
        cout << "Before SwapNumbers(): " << x << " and " << y <<endl;
        SwapNumbers_NotUsingtemp(x, y);
        cout << "After SwapNumbers(): " << x << " and " << y <<endl<< endl;
    }
    {
        int number = 0b10001;
        bitset<32> x(number);
        // all are legal and set bit0
        x[0] = 1;       // ok
        x[0] = 2;       // ok
        x[0] = true;    // ok
        
        cout << "\nDoes number (" << bitset<16>(number) << ") contain 2 or more consecutive 1s: ";
        int result = ConsecutiveBits1( number );
        cout << (result? "\n   1) Yes" : "\n   1) No");
        result =  ConsecutiveBits2( number );
        cout << (result? "\n   2) Yes" : "\n   2) No");
    }
    {
        char character = 'A';
        int lower_upper = is_char_lower_or_upper( character );
        cout << "\nIs '" << character << "' Lower or Upper?" << (lower_upper == 0? " Lower" : " Upper");
    }
    
    // !!!:  /////////////////     Equal Length Of Zeros Ones     ////////////////
    {
        vector<int> nums = {1, 1, 1, 1, 1, 1, 1, 1};
        printVector(cout << "\n\nFind Equal Length Of Zeros and Ones: ", nums);
        int result = EqualLengths_of_Zeros_Ones_1(nums);
        cout << "\n1)   result = " << result << endl;
        
        result = findEqualLengths_of_Zeros_Ones_2(nums);
        cout << "2)   result = " << result << endl;
    }
    {
        short x = 5, y = 11;
        long result = multiplyWithShift(x, y);
        cout << "Multiple by Shifting = " << result << endl;
    }
    
    // !!!: ////////////////////////     Compute Sign of Integer     ////////////////////////////
    {
        int number = -3;
        int sign = Compute_Sign_of_Integer_1(number);
        cout << "\n1) Sign of Integer " << number << " is " << (sign? "Positive" : "Negative");
        
        sign = Compute_Sign_of_Integer_2(number);
        cout << "\n2) Sign of Integer " << number << " is " << (sign? "Negative" : "Positive") << endl;
    }
    
    
    
    // !!!: ////////////////////////      Ones Left Zeros Right      ////////////////////////////
    {
        //int zerosones[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int zerosones[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        //int zerosones[20] = {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1};
        int arraySize = 20;
        //int array[10] = {0,0,0,0,0,1,0,0,0,0};
        //int zerosones[20] = {0,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1};  //important case
        //int zerosones[10] = {1,1,1,1,1,1,1,1,1,1};
        //int zerosones[10] = {0,0,0,0,0,1,1,1,1,1};
        //int zerosones[10] = {1,1,1,1,1,0,0,0,0,0};
        //int zerosones[10] = {0,1,0,1,0,1,0,1,0,1};
        //int zerosones[1] = {1};
        cout << "OnesLeftZerosRight():\n\t";
        for(int i=0; i < arraySize; i++)
            cout << zerosones[i];
        //cout << "a[" << i << "] = " << array[i] << endl;
        
        OnesLeftZerosRight(zerosones, arraySize);
        
        cout << endl << "\t";
        for(int i=0; i < arraySize; i++)
            cout << zerosones[i];
        
    }
    
    // !!!: /////////////////         Count Odds and Even Bits      ////////////////////////
    {
        int number = 1103;
        int odd_even = is_number_odd_or_even(number);
        cout << "\nIs " << number << " Odd or Even?" << (odd_even == 0? " Even" : " Odd");
    }
    {
        unsigned int integer = 0b101; //0b101;    //b10101010101010101010101010101010
        //cout << "\nn                     = " << bitset<8>(number) << endl;
        
        bool result = Are_Bits_Alternating(integer);
        cout << "\n\nDoes number = " << bitset<32>(integer) << " Have ALL Alternating Bits (1) = " << (result?"yes":"no")  << endl;
        
        bool result1 = Are_ALL_Bits_Alternating2(integer);
        cout << "Does number = " << bitset<32>(integer) << " Have ALL Alternating Bits (2) = " << (result1?"yes":"no")  << endl;
    }
    {
        int number = 50;
        cout << dec << "\n1) Generate Number Having Alt Bit Pattern My implementation: \n" << "   Number = " << number << ", Result: " << endl;
        vector<int> result = generateAlternateBits1(number);
        for(int i : result) { cout << "\t\t\t\t\t\t" << i << "  = "; print_DecimalToBinary(i); cout << endl; }
        
        cout << "\n2) Generate Number Having Alt Bit Pattern: \n" << "   Number = " << number << ", Result: ";
        generateAlternateBits2(number);
        for(int i : result) {
            cout << "\n\t\t\t\t\t\t" << i << "  = " << DecimalToBinary_mine(i);
        }
        {
            int n = 0b01101101;
            int result = CountSetBits(n);
            cout << "\nSetBits(" << bitset<32>(n) << ") = " << bitset<32>(result) << endl;
        }
        {
            unsigned int number = 0b0111111110000;
            int frombit = 7;
            int tobit   = 7;
            
            cout << "\nGetBits() Mine: mask from bits = "<< frombit << " to " << tobit << endl;
            cout << " number  = " << DecimalToBinary_mine(number) << endl;
            unsigned int r1 = getBits1(number, frombit, tobit);
            cout << " result = " <<  DecimalToBinary_mine(r1) << endl;
            
            cout << "\nGetBits() Ritchi: needs work" << endl;
            unsigned int r = getBits2(number, frombit, tobit);
            cout << " result = " <<  DecimalToBinary_mine(r) << endl;
        }
        
        // !!!:  /////////////////     Set Odd and Even Bits     ////////////////
        {
            unsigned int number = 0b00001010;    // Try 0b01010101, ob11
            cout << "\nSet EVEN Bits: n = " << bitset<32>(number);
            int res  = setEvenBits_mine(number);
            cout << "\n       My result = " << bitset<32>(res);
            
            cout << "\n\nSet ODD Bits:  n = " << bitset<32>(number);
            res = SetOddBits_mine(number);
            cout << "\n       My result = " << bitset<32>(res);
            res  = SetOddBits_geek(number);
            cout << "\n     Geek result = " << bitset<32>(res);
            
            cout << "\n\nOdd & Even        = " << (bitset<32>(SetOddBits_mine(number)) & bitset<32>(setEvenBits_mine(number)) ) << endl;
        }
// !!!: //
// !!!: ////////////////  Longest Substring Of 1s After Removing One Element (0)  ////////////////
// !!!: //
        {
            // 110111000111111100 = 7 // 11110111111 = 10 // 1111000111111 = 6 (tricky)
            // [1,1,1] = 2             // [1,1,0,1] = 3    // [0,1,1,1,0,1,1,0,1] = 5 //  [1,1,0,0,1,1,1,0,1] = 4
            // [0,0,0] = 0
            string str = "110011101"; // "11101101"; 1101 = 3, 110011101 = 4, 011101101 = 5
            cout << "\n\n1) Longest Substring of 1's After Removing 1 Element in string = \"" << str << "\":" << endl;
            int max_bit_count = longestSubstringOf1s_afterRemoving_1bit_1(str);
            cout << dec << "     my result = " << max_bit_count;
            
            cout << "\n2) Longest Substring of 1's After Removing 1 Element in string = \"" << str << "\":" << endl;
            max_bit_count = longestSubstringOf1s_afterRemoving_1bit_2(str);
            cout << dec << "     my result = " << max_bit_count << endl;
// !!!: //
// !!!: ////////////////  Longest Subsequence Of 1s After Flipping 0 to 1   ////////////////
            // needs serious work
            int integer = 0b1110010;//0xFFFFFFFF ;
            cout << "\n1) Longest Subsequence Of 1s After Flipping 1 Element in integer = " << integer << ":\n     my result = " << bitset<32>(integer);
            // makes use of longestSubstringOf1s_AfterRemoving1Element( str ) above
            max_bit_count = longestSubsequenceOf1s_afterFlipping_1bit( integer );
            cout<< " = " << max_bit_count;
            
            vector<int> bits = { 1, 1, 1, 0, 0, 1, 0};
            max_bit_count = longestContiguousOnes_afterFlipping_oneBit( bits );
            
            // from Cracking the Interview Code. !!!: does not work with 2 or more consicutavie 0s
            cout << "\n2) Flip a Bit to Win, from wiki:\n     wiki result = " << bitset<32>(integer);
            max_bit_count = flipBit_to_Win( integer );
            cout<< " = " << max_bit_count;
        }
        
        // !!!: /////////////////////////      Clear Bits From MSB To ithBit    ////////////////////
        {
            unsigned char byte = 0b10011101;
            int pos = 4;
            cout << "\nClear Bits From MSB to ith-bit " << pos <<" for number = " << bitset<8>(byte) << endl;
            unsigned char result = Clear_Bits_From_MSB_To_ithBit(byte, pos);
            cout << bitset<8>( result) << endl;
        }
        
        
        // !!!: ///////////////////////////   XOR   ///////////////////////////////////////
        {
            unsigned int number = 6;
            cout << "Number        = " << bitset<32>(number) << endl;
            int XORres = computeXOR1(number);
            cout << "computeXOR1() = " << bitset<32>(XORres) << endl;
            
            XORres = computeXOR2(number);
            cout << "computeXOR2() = " << XORres << endl << endl;
        }
        
        
        
// !!!: ////////////////////////////      Update Bits     //////////////////////////
    {
        int n = 0b11110101111;
        int m = 0b0;
        int beginBit = 4;
        int endBit   = 6;
        cout << "Update Bits with Range positions: " << beginBit << ", " << endBit << endl;
        cout << "Original bits      = " << bitset<11>(n) << endl;
        cout << "Insert bits        = " << bitset<3>(m);

        int newbits = Update_Bits_1(n, m, beginBit, endBit);
        cout << "\nUpdateBitsVersion1 = " << bitset<11>(newbits);

        int newbits1 = Update_Bits_2(n, m, beginBit, endBit);
        cout << "\nUpdateBitsVersion2 = " << bitset<11>(newbits1);
    }
        
// !!!: /////////////////////      Divide Without Using Division Operator       ///////////////////
    {
        int dividend = INT_MIN;     // INT_MIN = -2147483648
        int divisor  = -1;     // INT_MIN = -INT_MIN
        long int div1 = DivideWithoutUsingDivision_1( dividend, divisor );
        cout << "\n\n1) Divide Without Using Division " << dividend << "/" << divisor << " = " << div1;

        int div2 = DivideWithoutUsingDivision_2( dividend, divisor );
        cout << "\n2) Divide Without Using Division " << dividend << "/" << divisor << " = " << div2;
    }

// !!!: ////////////////////////      Big Indian Little Indian       ////////////////////////////
    {
        bool big_little_indian = BigIndianLittleIndian();
        cout << "\nIs System LITTLE_INDIAN or BIG_INDIAN? \nresult: " << ((big_little_indian)? "LITTLE_INDIAN" : "BIG_INDIAN") << endl;
    }

// !!!: ////////////////////////      Change End Ianness       ////////////////////////////
    {
        uint32_t u32CheckData  = 0x11223344;
        uint32_t u32ResultData =0;
        u32ResultData = ChangeEndianness_1(u32CheckData);  //swap the data
        printf("\nOriginal Integer = 0x%x\n",u32ResultData);
        u32CheckData = u32ResultData;
        u32ResultData = ChangeEndianness_1(u32CheckData);//again swap the data
        printf("1) Afetr Changing Endianness = 0x%x\n",u32ResultData);
        
        u32ResultData = ChangeEndianness_2(u32CheckData);//again swap the data
        printf("2) Afetr Changing Endianness = 0x%x\n",u32ResultData);
    }
        
// !!!: ////////////////////////      Reverse Bits       ////////////////////////////
    {
        //unsigned int bits = 0x1;
        //unsigned int bits = 0b00000000000000000000000000000001;
        unsigned int bits = 0b00000001000000001111111111111111;
        //unsigned int bits = 0b11110000000011110000111111110000;
        cout << "ReverseBits1(): Before reversing " << bitset<32>(bits) << endl;
        unsigned int revbits = ReverseBits1(bits);
        cout << "ReverseBits1(): After reversing  " << bitset<32>(revbits) << endl << endl;

        cout << "ReverseBits2(): Before reversing " << bitset<32>(bits) << endl;
        ReverseBits2(bits);
        cout << "ReverseBits2(): After reversing  "  << bitset<32>(bits) << endl << endl;

        cout << "ReverseBits3(): Before reversing " << bitset<32>(bits) << endl;
        unsigned int result = ReverseBits3(bits);
        cout << "ReverseBits3(): Before reversing " << bitset<32>(result) << dec ;
    }

// !!!: ////////////////////////      Rotate Bits Left       ////////////////////////////
    {
        //int bits = 0b11111111000000000000000000000000;
        int bits = 0xFF00FF;
        int no_of_left_rotations = 15;
        
        cout << "\n\nRotate Bits    \"" << bitset<32>(bits) << "\" Left by " << no_of_left_rotations;
        int result = rotateBitsLeft_1( bits, no_of_left_rotations );
        cout << "\n1) Rotated Bits " << bitset<32>(result);

        RotateBitsLeft_2( bits, no_of_left_rotations );
        cout << "\n2) Rotated Bits " << bitset<32>(result);

        unsigned int ubits = 0xFF0000FF;
        rotateBitsLeft_3(ubits, no_of_left_rotations);
        cout << "\n3) Rotated Bits " << bitset<32>(result);
    }
        
// !!!: /////////////////         Count Trailing ZEROS       ////////////////////////
    {
        int number = 0b00000010;
        int count = trailingZeros_1( number );
        cout << "\n\nTrailing ZEROS for Number " << bitset<8> (number) << ", is " << count;
        
        count = trailingZeros_2( number );
        cout << "\nTrailing ZEROS for Number " << bitset<8> (number) << ", is " << count;
    }


// !!!: ////////////////////////      Move Zeros to Left      ////////////////////////////
        {
            vector<int> a = {1, 10, 20, 0, 59, 63, 0, 88, 0};
            printVector(cout << "\n\nOriginal Array: ", a);
              
            move_zeros_to_left(a);
              
            printVector(cout << "\nAfter Moving Zeroes to Left: ", a);
        }
        
        
        
        
// !!!: ///////////////////     Print Duplicates in Big Data Set    //////////////////
            
            // I have 4KB of memory = 4Kbyte * 1024 bytes/Kbyte * 8 bits/byte = 32768 bits.
            unsigned int bigset[4*1024*8];
            int BIG_SET_SIZE = 4*1024*8;
            
            // Populate first 32000 of bigset[] = 1,2,3....,32000
            int index = 0;
            for(; index < 32000; index++) {
                bigset[index] = index + 1;
                //cout << bigset[index] << ", ";
            }
            cout << endl;
            int value= 32000;
            // Add duplicates for last 768 = 32768 - 32000
            for(; index < BIG_SET_SIZE; index++ ) {
                bigset[index] =  value--;  // OR, index + 1 OR something else
                //cout << bigset[index] << "' ";
            }
            
            // This function prints long list
            // int result1 = printDuplicatesInBigDataSet(bigset, BIG_SET_SIZE);
            // cout << "\nAs expected, Duplicate numbers = " << result1 << endl << endl;


        
        
    // !!!: ////////////////////////////      Zero One Two      ////////////////////
        {
            //vector<int> v = {0,2,2,1,1,1,2,1,2,1};
            //vector<int> v = {2,2,2,2,0,0,0,0,1,1};
            vector<int> v = {2,1,0,0,0,2,1};
            vector<int> result = ZeroOneTwo3(v);
            for(int i : result)
                cout << i;

            string s = "20101010101";
            string str = ZeroOneTwo4(s);
            for(char c : str) {
                cout << c ;
            }
        }

        
// !!!: /
// !!!: //////////      Find Zero-to-One Transition Point in SORTED Array       /////////////
// !!!: /
        {
            // array must be Sorted
            vector<int> serial_data = {0,0, 0,0,1}; //{1,1,1,1,1}; {0,0,0,0,0};
            cout << "\n\nOriginal array = ";
            printVector(serial_data);
            
            int transpoint = FirstPositiveEdge_1( serial_data );
            if( transpoint >= 0 ) {
               cout<<"1) Transition Point Occured at index "<< transpoint;
            }
            else{
               cout<<"\n3) Transition Point was Not Found";
            }

            transpoint = FirstPositiveEdge_2( serial_data );
            if( transpoint >= 0 ) {
               cout<<"\n2) Transition Point Occured at index "<< transpoint;
            }
            else{
               cout<<"\n2) Transition Point was Not Found";
            }

            transpoint = FirstPositiveEdge_3( serial_data );
            if( transpoint >= 0 ) {
               cout<<"\n3) Transition Point Occured at index "<< transpoint;
            }
            else{
               cout<<"\n3) Transition Point was Not Found";
            }
        }
        

// !!!: ////////////////////////   Square Wave Pattern   //////////////////////////////
//
            {
                string str = "001010100001101";   // 1001010001, 3
                cout << "\n\nDrawing the pattern " << str << "\n\t\t\t\t\t";
                Draw_Square_Wave( str );
                
                // !!!: 1) Count Negative pulses
                int result = CountNegative_1( str );
                cout << "\n1) Negative Pulses = " << result;
                
                // !!!: 1) Count Negative pulses
                vector<int> data = {0,0,1,0,1,0,1,0,0,0,0,1,1,0,1};
                result    = CountNegative_2( data );
                cout << "\n2) Negative Pulses = " << result;

                result    = CountPositive_1( str );
                cout << "\n\tPositive Pulses = " << result;

                vector<int> edges = Edges( str );
                cout << "\n\tNegative Edges  = " << edges[0] << "\n\tPositive Edges  = " << edges[1];
            }
            // !!!: ////////////////////     Pulses    //////////////////////////
            {
                vector<int> serial_data = {0,0,1,0,1,0,1,0,0,0,0,1,1,0,1};//{0,0,1,1,1};
                printVector( cout << "\n\nNumber Of Positive Pulses : ", serial_data );
                cout << "                    ";
                for( auto i: serial_data ) {
                    if( i == 1 ) cout << "-";
                    else                             cout << "_";
                }
                cout << "\n   Result = " << CountNegative_2( serial_data ) << " positive pulses";
                
                printVector( cout << "\n\nNumber Of Negative Pulses : ", serial_data );
                cout << "                    ";
                for( auto i: serial_data ) {
                    if( i == 1 ) cout << "-";
                    else                             cout << "_";
                }
                cout << "\n   Result = " << CountNegative_2( serial_data ) << " negative pulses";
                
                printVector( cout << "\n\nNumber Of Negative and Positive Pulses : ", serial_data );
                cout << "                    ";
                for( auto i: serial_data ) {
                    if( i == 1 ) cout << "-";
                    else                             cout << "_";
                }
                 numOf_Neg_Pos_Pulses( serial_data );

            }
                
        return 0;
    }
}
