#include <algorithm>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <initializer_list>
#include <string>

#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <fmt/core.h>
#include <json/json.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <cstdlib>
#include <internal_use_only/config.hpp>
#include <iostream>

#include "calc.hpp"
#include "financial_manager.hpp"
// #include "shape.h"
#include "shape.hpp"
int main() {
    // 测试数据
    vector< ThreeDShape* > items = { new ThreeDAnyShape( 23, 92 ), new ThreeDAnyShape( 31, 57 ),
                                     new ThreeDAnyShape( 29, 49 ), new ThreeDAnyShape( 44, 68 ),
                                     new ThreeDAnyShape( 53, 60 ), new ThreeDAnyShape( 38, 43 ),
                                     new ThreeDAnyShape( 63, 67 ), new ThreeDAnyShape( 85, 84 ),
                                     new ThreeDAnyShape( 89, 87 ), new ThreeDAnyShape( 82, 72 ) };

    Container container( 165 );
    auto selected = container.selectOptimal( items );

    cout << "最优方案: ";
    for ( bool sel : selected ) {
        cout << sel << " ";
    }
    cout << endl;

    // 释放内存
    for ( auto item : items )
        delete item;

    return 0;
}

// int main() {
//     srand( time( nullptr ) );
//     Person Wang( 100000 );
//     Wang.addInvest( new Saving( 50000 ) );
//     Wang.addInvest( new Fund( 20000 ) );
//     cout << Wang.settle() << endl;
//     return 0;
// }

// int main() {
//     {
//         Color c( 100 );
//         Point p1( 2, 3, c );
//         Point p2( p1 );
//         Point p3;
//     }
//     {
//         Color c( 100 );
//         Point p1( 2, 3, c );
//         Point p2( p1 );
//         Point p3;
//         Circle c1( p1, 3 );
//         Circle c2( c1 );
//         c2 = c1;
//     }
//     {
//         Point p1( 2, 3, Color( 100 ) );
//         p1.draw();
//     }
//     return 0;
// }
//
// int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
//     Calculator calc;
//     std::string exp;
//     while ( true ) {
//         std::cout << "输入表达式:";
//         std::getline( std::cin, exp );
//         std::cout << calc.doIt( exp ) << std::endl;
//     }
//     return 0;
// }

// #include "circular_list.hpp"
// int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
//     int n, m;
//     std::cout << "输入人数n及报数值m:";
//     std::cin >> n >> m;
//     CircularList< int > cl;
//     for ( int i = 1; i <= n; i++ ) {
//         cl.push_back( i );
//     }
//     auto p = cl.head();
//     while ( cl.head() != cl.tail() ) {
//         for ( int i = 1; i < m; i++ ) {
//             p = p->next;
//         }
//         std::cout << p->data << " out!" << std::endl;
//         auto next = p->next;
//         cl.erase_at( p );
//         p = next;
//     }
//     std::cout << "winner is:" << cl.head()->data << std::endl;
//     return 0;
// }

// #include "calc.hpp"
// #include "haff.hpp"

// int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
//     auto ifs = std::ifstream{ "/home/pkj/workspace/Project/c_c++/c_cpp_learn/src/intro/haffman.txt" };
//     map< char, int > char_map;
//     HaffmanTree haff;
//     if ( ifs.is_open() ) {
//         std::string line;
//         while ( std::getline( ifs, line ) ) {
//             for ( auto c : line | views::filter( []( char c ) { return c != ' '; } ) )
//                 char_map[ c ]++;
//         }
//         ifs.close();
//     }
//     else {
//         cerr << "open file failed" << endl;
//     }
//     for ( auto [ c, w ] : char_map ) {
//         haff.add_node( w, c );
//     }
//     haff.build();
//     std::map< char, string > code_map;
//     haff.get_code_map( code_map );
//     auto ofs = std::ofstream{ "/home/pkj/workspace/Project/c_c++/c_cpp_learn/src/intro/haffman_code.txt" };
//     if ( ofs.is_open() ) {
//         for ( auto const& e : code_map ) {
//             ofs << e.second;
//             cout << e.first << ":" << e.second << std::endl;
//         }
//         ofs.close();
//     }
//     else {
//         cerr << "open file failed" << endl;
//     }
//     return 0;
// }

template < typename T > class MyVector {
    T* m_arr          = nullptr;
    size_t m_size     = 0;
    size_t m_capacity = 0;

public:
    MyVector() = default;
    MyVector( std::initializer_list< T > init_list ) {
        for ( auto& item : init_list ) {
            push_back( item );
        }
    }
    MyVector( const MyVector& rhs ) {
        m_size = m_capacity = rhs.m_size;
        m_arr               = new T[ m_capacity ];
        for ( size_t i = 0; i < m_size; i++ ) {
            m_arr[ i ] = rhs.m_arr[ i ];
        }
    }
    MyVector( MyVector&& rhs ) noexcept {
        m_size     = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_arr      = rhs.m_arr;
        rhs.m_size = rhs.m_capacity = 0;
        rhs.m_arr                   = nullptr;
    }
    ~MyVector() {
        delete[] m_arr;
    }
    MyVector& operator=( const MyVector& rhs ) {
        if ( this == &rhs ) {
            return *this;
        }
        delete[] m_arr;
        m_size = m_capacity = rhs.m_size;
        m_arr               = new T[ m_capacity ];
        for ( int i = 0; i < m_size; i++ ) {
            m_arr[ i ] = rhs.m_arr[ i ];
        }
        return *this;
    }
    MyVector& operator=( MyVector&& rhs ) noexcept {
        if ( this == &rhs ) {
            return *this;
        }
        delete[] m_arr;
        m_size     = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_arr      = rhs.m_arr;
        rhs.m_size = rhs.m_capacity = 0;
        rhs.m_arr                   = nullptr;
        return *this;
    }

    size_t size() {
        return m_size;
    }
    T& operator[]( size_t i ) {
        return m_arr[ i ];
    }
    T& at( size_t i ) {
        if ( i >= m_size ) {
            throw std::out_of_range( "index out of range" );
        }
        return m_arr[ i ];
    }
    T& front() {
        if ( m_size == 0 ) {
            throw std::out_of_range( "my_vector is empty" );
        }
        return m_arr[ 0 ];
    }
    T& back() {
        if ( m_size == 0 ) {
            throw std::out_of_range( "my_vector is empty" );
        }
        return m_arr[ m_size - 1 ];
    }
    void push_back( const T& value ) {
        if ( m_size == m_capacity ) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            T* new_arr          = new T[ new_capacity ];
            for ( size_t i = 0; i < m_size; i++ ) {
                new_arr[ i ] = m_arr[ i ];
            }
            delete[] m_arr;
            m_arr = new_arr;
            std::cout << "reallocating when push_back:" << value << ",before cap=" << m_capacity
                      << ",after cap=" << new_capacity << std::endl;
            m_capacity = new_capacity;
        }
        m_arr[ m_size++ ] = value;
    }
    T& pop_back() {
        if ( m_size == 0 ) {
            throw std::out_of_range( "my_vector is empty" );
        }
        return m_arr[ --m_size ];
    }
    void insert( size_t i, const T& value ) {
        if ( i > m_size ) {
            throw std::out_of_range( "index out of range" );
        }
        if ( m_size == m_capacity ) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            T* new_arr          = new T[ new_capacity ];
            for ( size_t j = 0; j < i; j++ ) {
                new_arr[ j ] = m_arr[ j ];
            }
            new_arr[ i ] = value;
            for ( size_t j = i; j < m_size; j++ ) {
                new_arr[ j + 1 ] = m_arr[ j ];
            }
            delete[] m_arr;
            m_arr = new_arr;
            std::cout << "reallocating when insert:" << value << ",before cap=" << m_capacity
                      << ",after cap=" << new_capacity << std::endl;
            m_capacity = new_capacity;
            m_size++;
        }
        else {
            for ( size_t j = m_size; j > i; j-- ) {
                m_arr[ j ] = m_arr[ j - 1 ];
            }
            m_arr[ i ] = value;
            m_size++;
        }
    }
    void erase( size_t i ) {
        if ( i >= m_size ) {
            throw std::out_of_range( "index out of range" );
        }
        for ( size_t j = i; j < m_size - 1; j++ ) {
            m_arr[ j ] = m_arr[ j + 1 ];
        }
        m_size--;
    }
    void clear() {
        m_size = 0;
    }
};

void hello_world( int a, int b ) {
    std::cout << "hello world" << std::endl;
    std::cout << "a=" << a << ",b=" << b << std::endl;
}

/// \brief This is the brief description
///
/// Here's a \b bold , \e italic and \p typewriter word!
/// \param foo Doc for foo
/// \param bar Doc for bar
/// \param baz Doc for a parameter that does not actually exist
/// \details Here are some details
/// \warning Watch Out!
/// \note This is a note
/// \note This is another note
/// \returns Doc for return value
// int test( int foo, std::string bar );
//
// int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
//     int some_value = 10;
//     MyVector< std::string > str_vec{ "", "world" };
//     std::cout << "content of str_vec:";
//     for ( size_t i = 0; i < str_vec.size(); i++ ) {
//         std::cout << str_vec[ i ] << " ";
//     }
//     std::cout << std::endl;
//     MyVector< std::string > str_vec1 = str_vec;
//     std::cout << "content of str_vec1:";
//     for ( size_t i = 0; i < str_vec1.size(); i++ ) {
//         std::cout << str_vec1[ i ] << " ";
//     }
//     std::cout << std::endl;
//     MyVector< std::complex< double > > complex_vec{ { 1.2, 0.0 }, { 2.2, 0.2 } };
//     complex_vec.push_back( { 3.2, 0.3 } );
//     complex_vec.push_back( { 4.2, 0.4 } );
//     std::cout << "content of complex_vec:";
//     for ( size_t i = 0; i < complex_vec.size(); i++ ) {
//         std::cout << complex_vec[ i ] << " ";
//     }
//     std::cout << std::endl;
//     MyVector< std::complex< double > > complex_vec1 = complex_vec;
//     std::cout << "content of complex_vec1:";
//     for ( size_t i = 0; i < complex_vec1.size(); i++ ) {
//         std::cout << complex_vec1[ i ] << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }

// int main( [[maybe_unused]] int argc, [[maybe_unused]] char* argv[] ) {
//     spdlog::set_level( spdlog::level::debug );
//     spdlog::info( "hello world" );
//     spdlog::debug( "hello world" );
//     dbg( "hello world" );
//     std::cout << cv::getBuildInformation() << std::endl;
//     std::map< int, int >  myMap;
//     myMap.insert( { 1, 2 } );
//     CLI::App app{ fmt::format( "{} version {}", c_cpp_learn::cmake::project_name,
//                                c_cpp_learn::cmake::project_version ) };
//     bool show_version = false;
//     app.add_flag( "-v,--version", show_version, "show version" );
//     CLI11_PARSE( app, argc, argv );
//     if ( show_version ) {
//         std::cout << fmt::format( "{} version {}", app.get_display_name( true ), app.version() ) << "\n";
//         return EXIT_SUCCESS;
//     }
//     return EXIT_SUCCESS;
// }
