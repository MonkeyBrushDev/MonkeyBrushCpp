#ifndef __MB_BUFFER_ATTRIBUTE__
#define __MB_BUFFER_ATTRIBUTE__

#include <mb/api.h>

#include <vector>
namespace mb
{
  class IBufferAttribute
  {
  public:
    virtual void setArray( const std::vector<void*>& arr ) = 0;
    virtual unsigned int getCount( void ) const = 0;
    unsigned int getSize( void ) const
    {
      return this->_size;
    }
    virtual void reset( unsigned int count ) = 0;
    virtual void* getRawData( void ) = 0;
    virtual const void* getRawData( void ) const = 0;
    template< typename T>
    const T getX( unsigned int idx )
    {
      unsigned int size = getCount( );
      if ( size < 1 )
      {
        throw;
      }
      return static_cast< T* >( getRawData() )[ idx * _size ];
    }
    template< typename T>
    const T setX( unsigned int idx, T value )
    {
      if ( _size < 1 )
      {
        throw;
      }
      static_cast< T* >( getRawData() )[ idx * _size ] = value;
    }
    template< typename T>
    const T getY( unsigned int idx )
    {
      if ( _size < 2 )
      {
        throw;
      }
      return static_cast< T* >( getRawData() )[ idx * _size + 1 ];
    }
    template< typename T>
    const T setY( unsigned int idx, T value )
    {
      if ( _size < 2 )
      {
        throw;
      }
      static_cast< T* >( getRawData() )[ idx * _size + 1] = value;
    }
    template< typename T>
    const T getZ( unsigned int idx )
    {
      if ( _size < 3 )
      {
        throw;
      }
      return static_cast< T* >( getRawData() )[ idx * _size + 2 ];
    }
    template< typename T>
    const T setZ( unsigned int idx, T value )
    {
      if ( _size < 3 )
      {
        throw;
      }
      static_cast< T* >( getRawData() )[ idx * _size + 2 ] = value;
    }
    template< typename T>
    const T& getW( unsigned int idx ) const
    {
      if ( _size < 4 )
      {
        throw;
      }
      return static_cast< T* >( getRawData() )[ idx * _size + 3 ];
    }
    template< typename T>
    const T setW( unsigned int idx, T value )
    {
      if ( _size < 4 )
      {
        throw;
      }
      
      static_cast< T* >( getRawData() )[ idx * _size + 3 ] = value;
    }
    template<typename T>
    const std::vector<T> getXY(unsigned int idx ) const
    {
      if ( _size < 2 )
      {
        throw;
      }

      idx *= _size;

      auto data = static_cast<T*>(getRawData());

      std::vector<T> ret = {
        data.at( idx ),
        data.at( idx + 1)
      };

      return ret;
    }
    template< typename T>
    const T setXY( unsigned int idx, T xValue, T yValue )
    {
      if ( _size < 2 )
      {
        throw;
      }

      idx *= this->_size;

      static_cast< T* >( getRawData() )[ idx ] = xValue;
      static_cast< T* >( getRawData() )[ idx + 1 ] = yValue;
    }
  protected:
    unsigned int _size;
    //unsigned int _count;
  };
  template< typename T >
  class BufferAttribute: public IBufferAttribute
  {
  public:
    BufferAttribute( unsigned int count, unsigned int size )
    {
      _size = size;
      reset( count );
    }
    BufferAttribute( const std::vector<T>& arr, unsigned int size )
    {
      _size = size;
      //setArray( arr );
      this->_data = arr;
    }
  private:
    /*template <typename E>
    void wrapArrayInVector( E *sourceArray, size_t arraySize, std::vector<E, std::allocator<E> > &targetVector ) {
      typename std::_Vector_base<E, std::allocator<E> >::_Vector_impl *vectorPtr =
        (typename std::_Vector_base<E, std::allocator<E> >::_Vector_impl *)((void *) &targetVector);
      vectorPtr->_M_start = sourceArray;
      vectorPtr->_M_finish = vectorPtr->_M_end_of_storage = vectorPtr->_M_start + arraySize;
    }*/
  protected:
    virtual void setArray( const std::vector<void*>& arr )
    {
      //wrapArrayInVector( arr.data( ), arr.size( ), arr);
    }
  public:
    virtual void reset( unsigned int count ) override
    {
      _data.resize( count * _size );
    }
    virtual unsigned int getCount( void ) const
    {
      return _data.size( ) / _size;
    }
    virtual void* getRawData( void ) override
    {
      return _data.data( );
    }
    virtual const void* getRawData( void ) const override
    {
      return _data.data( );
    }
  protected:
    std::vector< T > _data;  };
  /*class IBufferAttribute
  {
  public:
    template< typename T >
    std::vector<T> array( void )
    {
      return static_cast<T*>( rawData( ) );
    }
    virtual unsigned int size() const = 0;
    virtual const void* rawData( void ) const = 0;
    template< typename T >
    T getX( unsigned int idx )
    {
      if (size( ) < 1)
      {
        throw;
      }
      return static_cast< T >( _data.at( idx ));
    }
  };
  template <typename T>
  class BufferAttribute: public IBufferAttribute
  {
  public:
    BufferAttribute( void )
    {
    }
    BufferAttribute( std::vector<T> arr, unsigned int size )
      : IBufferAttribute( )
    {
      this->_data = arr;
      this->_size = size;
    }
    virtual const void* rawData() const override;
    virtual unsigned int count();
  protected:
    std::vector<T> _data;
    unsigned int _size;
  };*/

  using IntBufferAttribute = BufferAttribute< int >;
  using UintBufferAttribute = BufferAttribute< unsigned int >;
  using FloatBufferAttribute = BufferAttribute< float >;
}

#endif /* __MB_BUFFER_ATTRIBUTE__ */