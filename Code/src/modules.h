#pragma once
#include <string>
#include <iostream>
#include <vector>
namespace STL {

    const double PI = 3.14159265358979323846;
    class Point {
    private:
        double x;
        double y;
        double z;
        double angle;
    public:
        Point() :x(0), y(0), z(0), angle(0) {};
        Point(const Point&);
        Point(double _x, double _y, double _z, double a = 0) :x(_x), y(_y), z(_z), angle(a) {};
        ~Point() {};

        void setX(double _x) { x = _x; }
        void setY(double _y) { y = _y; }
        void setZ(double _z) { z = _z; }
        void setAngle(const Point&);
        void setPoint_from_array(double[2][4]);

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }

        double getAngle()const { return angle; };
        void print()const;

        //operators 
        friend std::istream& operator>>(std::istream& input, Point& p);
        bool operator==(const Point& p);
    };

    class Vector {
    private:
        double nx;
        double ny;
        double nz;
    public:
        Vector() :nx(0), ny(0), nz(0) {};
        Vector(double x, double y, double z) :nx(x), ny(y), nz(z) {};
        Vector(Vector const&);
        ~Vector() {};
        double getNx() const { return nx; }
        double getNy() const { return ny; }
        double getNz() const { return nz; }
        void normalize();
        double getMagnitude() const;

        //operatorok
        friend std::istream& operator>>(std::istream& input, Vector& v);
        bool operator==(const Vector& p);

        void print()const;


    };


    class Cutter {
    private:
        Vector n;
        Point p;
    public:
        Cutter(Vector _n, Point _p) : n(_n), p(_p) {};
        ~Cutter() {};

        Vector getNormal() const { return n; }
        Point getPoint() const { return p; };
        void setZ(double x) { p.setZ(x); };
    };


    class Facet {
    private:
        Vector n;
        Point v1;
        Point v2;
        Point v3;
        unsigned id[3];// ez tarolja az azonositojat egy feluletnek
        static unsigned id_cnt;
    public:
        Facet() :n(Vector()), v1(Point()), v2(Point()), v3(Point()) { id[0] = 0;id[1] = 0; id[2] = 0; };
        Facet(Vector n, Point v1, Point v2, Point v3) : n(n), v1(v1), v2(v2), v3(v3) { id[0] = 0;id[1] = 0; id[2] = 0; };
        ~Facet() {};

        Vector getNormal() const { return n; }
        Point getVertex1() const { return v1; }
        Point getVertex2() const { return v2; }
        Point getVertex3() const { return v3; }

        unsigned  getID(unsigned i)const { return id[i]; };
        void set_id();
        static void inc_ID() { id_cnt++; };
        double getMinX()const;
        double getMinY()const;
        double getMinZ()const;//megadja a legkisebb a koordinatat

        double getMaxX()const;
        double getMaxY()const;
        double getMaxZ()const;//megadja a legnagyobb a koordinatat


        void print()const;
    };

    class Line {
        Vector dirv;
        Point p;
        unsigned id[3];
    public:
        Line() :dirv(Vector()), p(Point()) { id[0] = 0;id[1] = 0; id[2] = 0; };
        Line(Vector v1, Point p0) :dirv(v1), p(p0) { id[0] = 0;id[1] = 0; id[2] = 0; };
        Line(const Line&);

        ~Line() {};
        Vector getDirv()const { return dirv; };

        unsigned  getID(unsigned i)const { return id[i]; };
        void setID(const Facet&);

        void setDirv(Vector n1, Vector n2);//vektorialis szorzat

        void setPoint_from_array(double[2][4], const Point&);

        void setDirv(Vector dirv);
        Vector getNormal() const { return Vector(this->dirv.getNy(), -1 * (this->dirv.getNx()), 0); };
        void setPoint(const Point p0);
        Point getPoint()const { return p; };


        bool operator==(const Line& p);
        void print()const;


    };



    //Functions
    double dotProduct(Vector v1, Vector v2);
    Vector crossProduct(const Vector& n1, const Vector& n2);
    Vector determineNormal(const Point& p1, const Point& p2, const Point& p3);
    void solve_two_equations(double[2][4]);
    Line faceIntersection(Facet const& plane, Cutter const& cutter_plane);
    Point lineIntersection(Line const& l1, Line const& l2);


    std::vector<Facet> read_STL(const std::string& filename, const std::string& mode);
    std::vector<Line> generate_Lines(std::vector<Facet>const& facets);
    std::vector<Point> generate_Points(std::vector<Line>const& lines);
    void generate_Id(std::vector<Facet>& facets);

    void write_gcode(std::vector<Point>const&);
    Point find_origin(std::vector<Point>const&, const unsigned);

    Vector operator-(const Point& p1, const Point& p2);
    Vector operator-(const Vector& v1, const Vector& v2);

    bool cmp(const Point&, const Point&);
    bool check_neighbour(const Facet&, const Facet&);

    bool check_ID(const Line&, const Line&);

}