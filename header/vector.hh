#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include<cmath>
#include<exception>
#include<string>
#include<utility>

#include<normal_iterator.hh>

class indexOutOfBoundsException : public std::exception{
private:
  std::string msg;

public:
  indexOutOfBoundsException( unsigned long long idx ){
    msg = "Index ";
    msg += idx;
    msg += " out of bounds!";
  }
  virtual const char* what() const noexcept{
    return msg.data();
  }
};

template<class T>
class vector{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef const value_type* const_pointer;
  typedef normal_iterator<value_type, vector> iterator;
  typedef unsigned long size_type;

private:
  size_type mSize;
  size_type mCapacity;
  unsigned char* mData;
  static const unsigned int datasize = sizeof( value_type );
  const float goldenRatio = 1.4;

  void reallocateTo( size_type size ){
    unsigned char* bfr;

    mCapacity = size;
    bfr = new unsigned char[( mCapacity * datasize )];

    // copy data to new buffer
    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      bfr[i] = mData[i];
    }

    delete[] mData;
    mData = bfr;
  }

public:
  /*!
   * @brief default ctor, initialize capacity to 1
   */
  vector():
    vector( 1 ){
  }

  /*!
   * @brief ctor, initialize with givin capacity
   *
   * @param capacity  the value the capacity will be initialized to
   */
  vector( size_type capacity ):
    mSize( 0 ),
    mCapacity( capacity ),
    mData( new unsigned char[( mCapacity * datasize )] ){
  }

  /*!
   * @brief ctor, initialize with count copies of val
   *
   * @param val    data to be copied
   *
   * @param count  the number of copies of val to be made
   */
  vector( const_reference val, size_type count ):
    vector( count ){

    while( count-- ){
      push_back( val );
    }
  }

  /*!
   * @brief copy ctor, copy other
   *
   * @param other  vector to copy data from
   */
  vector( const vector& other ):
    mSize( other.mSize ),
    mCapacity( mSize + 5 ),
    mData( new unsigned char[( mCapacity * datasize )] ){

    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      mData[i] = other.mData[i];
    }
  }

  /*!
   * @brief move ctor, move other to this vector
   *
   * @param other  vector to be moved here
   */
  vector( vector&& other ):
    mSize( other.mSize ),
    mCapacity( other.mCapacity ),
    mData( other.mData ){

    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
  }

  /*!
   * @brief copy array of elements
   *
   * @param other  array to copy values from
   *
   * @param size   the number of elements in other
   */
  vector( pointer other, size_type size ):
    mSize( size ),
    mCapacity( mSize + 5 ),
    mData( new unsigned char[( mCapacity * datasize )] ){

    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      mData[i] = other[i];
    }
  }

  /*!
   * @brief copy ctor, copy elements from an arbitrary container
   *
   * @param first  first element to be copied
   *
   * @param last   one past the end of the container to be copied from
   */
  template<class inputIter>
  vector( inputIter first, inputIter last ){
    for( ; first != last; ++first ){
      push_back( *first );
    }
  }

  /*!
   * @brief dtor
   *
   * all data is cleared, destructors ran, and memory freed
   */
  virtual ~vector(){
    clear();
    delete[] mData;
  }

  /*!
   * @brief copy assignment, copy data from other
   *
   * @param other  vector from which data will be copied
   *
   * @return reference to this vector
   */
  vector& operator=( const vector& other ){
    if( mData == other.mData ){
      return *this;
    }

    if( mCapacity < other.mSize ){
      delete[] mData;
      
      mCapacity = other.mSize;
      mData = new unsigned char[( mCapacity * datasize )];
    }

    mSize = other.mSize;
    for( size_type i = 0; i < ( mSize * datasize ); ++i ){
      mData[i] = other.mData[i];
    }

    return *this;
  }

  /*!
   * @brief move assignment, move data from other
   *
   * @param other  vector from which data will be moved
   *
   * @return reference to this vector
   */
  vector& operator=( vector&& other ){
    mSize = other.mSize;
    mCapacity = other.mCapacity;
    mData = other.mData;
    
    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
    
    return *this;
  }

  /*!
   * @brief indexed getter, get element at index idx
   *
   * @param idx  index into vector, from which data will be returned
   *
   * @return reference to data located at index idx
   */
  reference operator[]( size_type idx ){
    if( idx >= mSize ){
      throw indexOutOfBoundsException( idx );
    }

    return ( reference )( *( mData + ( idx * datasize ) ) );
  }

  /*!
   * @brief indexed const getter, get const element at index idx
   *
   * @param idx  index into vector, from which const data will be returned
   *
   * @return const reference to data located at index idx
   */
  const_reference operator[]( size_type idx ) const{
    return ( *this )[idx];
  }

  /*!
   * @brief first element getter
   *
   * @return reference to first element
   */
  reference front(){
    return ( *this )[0];
  }

  /*!
   * @brief last element getter
   *
   * @return reference to last element
   */
  reference back(){
    return ( *this )[mSize - 1];
  }
  
  /*!
   * @brief add data to the end
   *
   * @param data  data to be copied at the end of vector
   */
  //uses copy constructor to store incoming data;
  void push_back( const_reference data ){
    if( mSize + 1 > mCapacity ){
      reallocateTo( std::ceil( mCapacity * goldenRatio ) );
    }

    new ( ( pointer )( mData + ( mSize * datasize ) ) ) value_type( data );
    ++mSize;
  }
  /*!
   * @brief construct new object at the end of vector
   *
   * @param args  arguments to be passed to ctor of new object
   */
  //forwards arguments to constructor
  template<class ...Args>
  void emplace_back( Args&&... args ){
    if( mSize + 1 > mCapacity ){
      reallocateTo( std::ceil( mCapacity * goldenRatio ) );
    }

    //use placement new to call ctor
    new( ( pointer )( mData + ( mSize * datasize ) ) ) value_type( std::forward<Args>( args )... );
    ++mSize;
  }

  /*!
   * @brief removes and destructs element at end of vector
   */
  void pop_back(){
    --mSize;
    //call dtor
    ( ( pointer )( mData + ( mSize * datasize ) ) )->~value_type();
  }

  /*!
   * @brief removes and destructs all elements in vector
   */
  void clear(){
    while( mSize > 0 ){
      pop_back();
    }
  }

  /*!
   * @brief get whether the vector is empty
   *
   * @return vector size equal to zero
   */
  bool empty() const{
    return mSize == 0;
  }

  /*!
   * @brief get current vector size
   *
   * @return count of currently stored elements
   */
  size_type size() const{
    return mSize;
  }

  /*!
   * @brief get current vector capacity
   *
   * @return number of elements that can be stored before a resize is necessary
   */
  size_type capacity() const{
    return mCapacity;
  }

  /*!
   * @brief request vector to be a certain size
   *
   * @param count  new size
   *
   * @param value  the value to use in filling additional elements
   */
  void resize( size_type count, value_type value = value_type() ){
    while( mSize < count ){
      push_back( value );
    }
    while( mSize > count ){
      pop_back();
    }
  }

  /*!
   * @brief request vector capacity be a certain size
   *
   * @param cap  new capacity
   */
  void reserve( size_type cap ){
    if( mCapacity < cap ){
      reallocateTo( cap );
    }
  }

  /*!
   * @brief get iterator to beginning
   *
   * @return iterator to the first element of the vector
   */
  iterator begin(){
    return Iterator( 0 );
  }

  /*!
   * @brief get const iterator to beginning
   *
   * @return const iterator to the first element of the vector
   */
  const iterator cbegin() const{
    return begin();
  }

  /*!
   * @brief get iterator to end
   *
   * @return iterator to the last element of the vector
   */
  iterator end(){
    return Iterator( mSize );
  }

  /*!
   * @brief get const iterator to end
   *
   * @return const iterator to the last element of the vector
   */
  const iterator cend() const{
    return end();
  }

  /*!
   * @brief get general iterator
   *
   * @param idx  index iterator will point to
   *
   * @return iterator pointing to element at index idx
   */
  iterator Iterator( size_type idx ){
    return iterator( pointer( mData + ( idx * datasize ) ) );
  }
};

#endif

