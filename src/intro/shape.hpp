#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

using namespace std;

// Shape 基类
class Shape {
public:
    [[nodiscard]] virtual double area() const   = 0;
    [[nodiscard]] virtual double volume() const = 0;
    virtual ~Shape()                            = default;
};

// Point类
class Point {
private:
    double x, y;

public:
    explicit Point( double x = 0, double y = 0 ) : x( x ), y( y ) {}
    [[nodiscard]] double distanceTo( const Point& other ) const {
        return sqrt( pow( x - other.x, 2 ) + pow( y - other.y, 2 ) );
    }
};

// 线类
class Line : public Shape {
private:
    Point start, end;

public:
    Line( const Point& s, const Point& e ) : start( s ), end( e ) {}
    [[nodiscard]] double length() const {
        return start.distanceTo( end );
    }
    [[nodiscard]] double area() const override {
        return 0;
    }
    [[nodiscard]] double volume() const override {
        return 0;
    }
    bool operator<( const Line& other ) const {
        return length() < other.length();
    }
};

// 2D Shape 基类
class TwoDShape : public Shape {
public:
    [[nodiscard]] double area() const override = 0;
    [[nodiscard]] double volume() const override {
        return 0;
    }
    bool operator<( const TwoDShape& other ) const {
        return area() < other.area();
    }
};

// 圆类
class Circle : public TwoDShape {
private:
    Point center;
    double radius;

public:
    Circle( const Point& c, double r ) : center( c ), radius( r ) {}
    [[nodiscard]] double area() const override {
        return M_PI * radius * radius;
    }
};

// 三角形类
class Triangle : public TwoDShape {
private:
    Point a, b, c;

public:
    Triangle( const Point& a, const Point& b, const Point& c ) : a( a ), b( b ), c( c ) {}
    [[nodiscard]] double area() const override {
        double ab = a.distanceTo( b );
        double bc = b.distanceTo( c );
        double ca = c.distanceTo( a );
        double s  = ( ab + bc + ca ) / 2;
        return sqrt( s * ( s - ab ) * ( s - bc ) * ( s - ca ) );
    }
};

// 矩形类
class Rectangle : public TwoDShape {
private:
    Point topLeft;
    double width, height;

public:
    Rectangle( const Point& tl, double w, double h ) : topLeft( tl ), width( w ), height( h ) {}
    [[nodiscard]] double area() const override {
        return width * height;
    }
};

// 3D Shape 基类
class ThreeDShape : public Shape {
public:
    [[nodiscard]] virtual double value() const = 0;
    bool operator<( const ThreeDShape& other ) const {
        return volume() < other.volume();
    }
};

// 为了求出最优方案，添加的任意形状类
class ThreeDAnyShape : public ThreeDShape {
private:
    double m_value;
    double m_volume;

public:
    ThreeDAnyShape( double volume, double value ) : m_value( value ), m_volume( volume ) {}
    [[nodiscard]] double area() const override {
        // 不关心面积
        return 0;
    }
    [[nodiscard]] double volume() const override {
        return m_volume;
    }
    [[nodiscard]] double value() const override {
        return m_value;
    }
};

// 圆柱体类
class Cylinder : public ThreeDShape {
private:
    double radius, height, m_value;

public:
    Cylinder( double r, double h, double v ) : radius( r ), height( h ), m_value( v ) {}
    [[nodiscard]] double area() const override {
        return 2 * M_PI * radius * ( radius + height );
    }
    [[nodiscard]] double volume() const override {
        return M_PI * radius * radius * height;
    }
    [[nodiscard]] double value() const override {
        return m_value;
    }
};

// 长方体类
class Cuboid : public ThreeDShape {
private:
    double length, width, height, m_value;

public:
    Cuboid( double l, double w, double h, double v ) : length( l ), width( w ), height( h ), m_value( v ) {}
    [[nodiscard]] double area() const override {
        return 2 * ( length * width + width * height + height * length );
    }
    [[nodiscard]] double volume() const override {
        return length * width * height;
    }
    [[nodiscard]] double value() const override {
        return m_value;
    }
};

// 圆锥类
class Cone : public ThreeDShape {
private:
    double radius, height, m_value;

public:
    Cone( double r, double h, double v ) : radius( r ), height( h ), m_value( v ) {}
    [[nodiscard]] double area() const override {
        return M_PI * radius * ( radius + sqrt( height * height + radius * radius ) );
    }
    [[nodiscard]] double volume() const override {
        return ( 1.0 / 3.0 ) * M_PI * radius * radius * height;
    }
    [[nodiscard]] double value() const override {
        return m_value;
    }
};

// 容器类
class Container {
private:
    double capacity;
    vector< ThreeDShape* > items;

    void clearItems() {
        for ( auto item : items )
            delete item;
        items.clear();
    }

public:
    explicit Container( double cap ) : capacity( cap ) {}
    ~Container() = default;

    void addItem( ThreeDShape* item ) {
        items.push_back( item );
    }

    void sortByVolume() {
        sort( items.begin(), items.end(), []( ThreeDShape* a, ThreeDShape* b ) { return *a < *b; } );
    }

    vector< bool > selectOptimal( const vector< ThreeDShape* >& allItems ) {
        size_t n = allItems.size();
        vector< int > volumes, values;
        for ( auto item : allItems ) {
            volumes.push_back( static_cast< int >( item->volume() ) );
            values.push_back( static_cast< int >( item->value() ) );
        }

        int cap = static_cast< int >( capacity );
        vector< vector< int > > dp( n + 1, vector< int >( cap + 1, 0 ) );

        for ( size_t i = 1; i <= n; ++i ) {
            for ( size_t w = 0; w <= cap; ++w ) {
                if ( volumes[ i - 1 ] > w ) {
                    dp[ i ][ w ] = dp[ i - 1 ][ w ];
                }
                else {
                    dp[ i ][ w ] = max( dp[ i - 1 ][ w ], dp[ i - 1 ][ w - volumes[ i - 1 ] ] + values[ i - 1 ] );
                }
            }
        }

        vector< bool > selected( n, false );
        int w = cap;
        for ( int i = n; i >= 1; --i ) {
            if ( dp[ i ][ w ] != dp[ i - 1 ][ w ] ) {
                selected[ i - 1 ] = true;
                w -= volumes[ i - 1 ];
            }
        }

        clearItems();
        for ( int i = 0; i < n; ++i ) {
            if ( selected[ i ] ) {
                items.push_back( allItems[ i ] );
            }
        }

        return selected;
    }
};
