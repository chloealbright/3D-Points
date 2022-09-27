/*
Name: Chloe Albright 
Project 1, Description: 
The class Points3D represent a sequence of 3D points where a sequence 
can be any size(an empty sequence has a size of 0), coordinates are of 
type int or double, and since the Points3D size can be arbitrary, 
pointers are used here.
*/
#ifndef CSCI335_HOMEWORK1_POINTS3D_H_
#define CSCI335_HOMEWORK1_POINTS3D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

/**
class Points3D uses the Big 5(: default constructor, destructor, copy constructor, copy assignment,
move constructor, move assignment) in order to create and represent 3D point sequences.
*/
template<typename Object>
class Points3D {
  public:

    //citing source: Big 5 01_335 Slide pg55-62

    /** Zero-parameter constructor i.e Default constructor
     @post sets sequence and size for created object
    */
    Points3D(){
        sequence_ = nullptr; // another way would be: sequence_ = new std::array<Object,3>[0];
        size_ = 0; 
    }// end zero parameter instructor

    /** Copy-constructor.
    @param rhs 
    @post copies referenced Points3D
    */
    Points3D(const Points3D &rhs){
        size_ = rhs.size_; //set new size
        sequence_ = new std::array<Object, 3>[size_]; //create new object of same size
        
        for(size_t i = 0; i < rhs.size_; i++){ //fill in a copy of the items in their respective pos
           sequence_[i] = rhs.sequence_[i];
        }
    }//end copy constructor

    /** Copy-assignment.
    @returns creates a deep copy of @param rhs
    (Deep copy: the variables are independent of each other.
    Needed because private member *sequence is a pointer,
    therefore dependent).
    */
    Points3D& operator=(const Points3D &rhs){
        Points3D copy = rhs;
        std::swap(*this, copy); // *this referenced from the STL
        //swaps vals but still in the sequence
        return *this; //return copy 
    }//end copy assignment

    /** Move-constructor.
    @post Moves @param rhs.sequence_ such that
    it's no longer in it's original position.
    */
    Points3D(Points3D &&rhs) : sequence_{rhs.sequence_}, size_{rhs.size_}{//initiating from header
        rhs.size_ = 0;
        rhs.sequence_ = nullptr;//empty current content pos and move to next pos
    }//end move constructor 

    /** Move-assignment.
     @param rhs  std::swap() for all variables.
    */
    Points3D& operator=(Points3D &&rhs){
        std::swap(sequence_, rhs.sequence_); 
        std::swap(size_, rhs.size_);
        return *this; //return from swap
    }//end move assignment

    /** Destructor
    @post handles dangling pointers by deletion and de-allocation*/
    ~Points3D(){
        delete[] sequence_;
        sequence_ = nullptr;
    }//end destructor

    // End of big-five.


    /** One parameter constructor.
    @post creates a 3D point objecy of size 1
    */
    Points3D(const std::array<Object, 3>& item) {
        size_ = 1; 
        sequence_ = new std::array<Object, 3>(item);       
    }//end one parameter constructor
    
    /** size_t is a getter function
    @returns size_ 
    */
    size_t size() const {
        return size_;
    }//end size_t

    /** operator[]
    @param location: an index to a location in the sequence.
    @returns the point at @location.
     const version.
     abort() if out-of-range.
    */
    const std::array<Object, 3>& operator[](size_t location) const{
        //index starts at 0 so >= out of range if equal to size_
        if(location >= size_){ 
            std::abort();
        }
        return sequence_[location];  
    }//end operator

    /**  
      operator+
      @param c1: A sequence.
      @param c2: A second sequence.
      @return their sum. If the sequences are not of the same size, append the
      result with the remaining part of the larger sequence.
    */
    friend Points3D operator+(const Points3D &c1, const Points3D &c2){
        //allocate for a new array in heap 
        //when we create new objects goes to heap
       
        //size is bigger of the 2 arrays 
        //w.e is leftover, include in new array 
        //add 2 rando size arrays 
        Points3D<double> sum;
        /*
        case1: if sequences are both empty i.e size 0        
        */
        //note: can try with bool
        if(c1.size_&&c2.size_==0){
            std::abort();
        }

        /*
        case2: if sequence size c1==c2
        then sum size & sequence will be equal to input size & sequence        
        */
        if(c1.size_ == c2.size_){
            sum.size_ = c1.size_;
            sum.sequence_= new std::array<Object, 3>[sum.size_];
            //use size_t type to work on double
            for(size_t i = 0; i < sum.size_; i++){
                //add the 3D points [size][index]
                sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
                sum.sequence_[i][2] = c1.sequence_[i][2] + c2.sequence_[i][2];
            }
            
        }
            
        /* case 3: if one sequence is larger than the other.
        whichever sequence size is larger gets the sum size */
        if(c1.size_ > c2.size_){
            sum.size_ = c1.size_;
            sum.sequence_= new std::array<Object, 3>[sum.size_];
            for(size_t i = 0; i < c2.size_; i++){
                sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
                sum.sequence_[i][2] = c1.sequence_[i][2] + c2.sequence_[i][2];

            }
            for(size_t i = c2.size_; i < sum.size_; i++){
                sum.sequence_[i][0] = c1.sequence_[i][0];
                sum.sequence_[i][1] = c1.sequence_[i][1];
                sum.sequence_[i][2] = c1.sequence_[i][2];
            }           
        }
        else if(c2.size_ > c1.size_){
            sum.size_ = c2.size_;
            sum.sequence_= new std::array<Object, 3>[sum.size_];
            for(size_t i = 0; i < c1.size_; i++){
                sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
                sum.sequence_[i][2] = c1.sequence_[i][2] + c2.sequence_[i][2];

            }
            for(size_t i = c1.size_; i < sum.size_; i++){
                sum.sequence_[i][0] = c2.sequence_[i][0];
                sum.sequence_[i][1] = c2.sequence_[i][1];
                sum.sequence_[i][2] = c2.sequence_[i][2];
            }                
        }
        /* alternative for testing: 
        bool size_unequal = (c1.size_ > c2.size_ || c2.size_ > c1.size_ );
        if(size_unequal){           
        }*/

        return sum;
    }//end operator+

    /** Overloading the << operator.
    @post prints stream
    */
    friend std::ostream &operator<<(std::ostream &out, const Points3D &some_points) {
        if(some_points.size_==0){
            out<<"()"<<std::endl;
            return out;
        }
        for(size_t i = 0; i < some_points.size_; i++){
            out<<"("<<some_points[i][0]<<", "<<some_points[i][1]<<", "<<some_points[i][2]<<") ";
        }
        out<<std::endl;
        return out;
    }//end overloading operator

    /** Overloading the Input >> operator.
    @param in, @param some_points
    @post Read a chain from an input stream (e.g., standard input).
    */
    friend std::istream &operator>>(std::istream &in, Points3D &some_points) {
        //referenced from class lecture 
       if(some_points.sequence_ != nullptr){
           delete[] some_points.sequence_;
           some_points.sequence_=nullptr;
       }

       in>>some_points.size_;
       /*alternative for testing:
       if(some_points.sequence_ != nullptr){          
           some_points.sequence_= new std::array<Object, 3>[some_points.size_];
           for(size_t i = 0; some_points.size_ > i; i++){
                for(size_t j = 0; j < 3; j++){
                    delete[] some_points.sequence_[i][j]; //i=size pos, index contents
                }
           } 
       }*/
       some_points.sequence_= new std::array<Object, 3>[some_points.size_];
       for(size_t i = 0; some_points.size_ > i; i++){
           for(size_t j = 0; j < 3; j++){
               in>>some_points.sequence_[i][j]; //i=size pos, index contents
           }
       } 
       std::cout<<std::endl;
       return in;
    }//end >> overloading operator

  private:
    // Sequence of points.
    std::array<Object, 3> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif 
