#pragma once
#include <cstddef>
#include <type_traits>
#include <iterator>

namespace ql
{

template<typename T, std::size_t N>
class Array
{
public:

  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = value_type*;
  using const_iterator = const value_type*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  constexpr reference operator[]( size_type i ) { return m_data[i]; }
  constexpr const_reference operator[]( size_type i ) const { return m_data[i]; }

  constexpr reference at( size_type i ) { return m_data[i]; }
  constexpr const_reference at( size_type i ) const { return m_data[i]; }

  constexpr reference front() { return m_data[0]; }
  constexpr reference back() { return m_data[N - 1]; }

  constexpr const_reference front() const { return m_data[0]; }
  constexpr const_reference back() const { return m_data[N - 1]; }

  constexpr pointer data() { return m_data; }
  constexpr const_pointer data() const { return m_data; }

  constexpr bool empty() const { return begin() == end(); }
  constexpr size_type size() const { return N; }

  constexpr iterator begin() { return m_data; }
  constexpr iterator end() { return m_data + N; }

  constexpr reverse_iterator rbegin() { return m_data[N - 1]; }
  constexpr reverse_iterator rend() { return --m_data; }

  constexpr const_reverse_iterator crbegin() const { return m_data[N - 1]; }
  constexpr const_reverse_iterator rcend() const { return --m_data; }

  constexpr const_iterator begin() const { return m_data; }
  constexpr const_iterator end() const { return m_data + N; }

  constexpr const_iterator cbegin() const { return m_data; }
  constexpr const_iterator cend() const { return m_data + N; }

  // size_type max_size() const;
  // constexpr void fill( const T& value );
  // constexpr void swap( Array& other );

  T m_data[N];

};

template<typename T, typename... Ts>
Array( T, Ts... ) -> Array<T, 1 + sizeof...( Ts )>;

template<typename T, std::size_t N>
constexpr auto to_array( T( &array )[N] )
{
  Array<std::decay_t<T>, N> tmp;
  copy( &array[0], &array[N - 1], tmp.data() );
  return tmp;
}

}
