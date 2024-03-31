#include <string>

namespace STL {

    //read functions

    void read_STL(const std::string& filename, const std::string& mode);




    class Point {
    private:
        double x;
        double y;
        double z;
    public:
        Point() :x(0), y(0), z(0) {};
        Point(const Point&);
        Point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {};
        ~Point() {};

        void setX(double _x) { x = _x; }
        void setY(double _y) { y = _y; }
        void setZ(double _z) { z = _z; }
        void setPoint_from_array(double[2][4]);

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }


        void print()const;
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

        void setNx(double x) { nx = x; }
        void setNy(double y) { ny = y; }
        void setNz(double z) { nz = z; }

    };

    class Line {
        Vector dirv;
        Point p;
    public:
        Line() :dirv(Vector()), p(Point()) {};
        Line(Vector v1, Point p0) :dirv(v1), p(p0) {};
        ~Line() {};
        Vector getDirv()const { return dirv; };
        void setDirv(Vector n1, Vector n2);//vektorialis szorzat

        void setPoint_from_array(double[2][4], const Point&);

        void setDirv(Vector dirv);
        Vector getNormal()const;//visszadja az egyenes normalvektorat de csak 2D ben mivel a z koordinata mindig 0
        void setPoint(const Point p0);
        Point getPoint()const { return p; };


        void print()const;


    };




    class Facet {
    private:
        Vector n;
        Point v1;
        Point v2;
        Point v3;

    public:
        Facet(Vector n, Point v1, Point v2, Point v3) : n(n), v1(v1), v2(v2), v3(v3) {};
        ~Facet() {};

        Vector getNormal() const { return n; }
        Point getVertex1() const { return v1; }
        Point getVertex2() const { return v2; }
        Point getVertex3() const { return v3; }
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
    };

    //Fuggvenyek
    Line faceIntersection(Facet const& plane, Cutter const& cutter_plane);
    void solve_two_equations(double[2][4]);

    Point lineIntersection(Line const& l1, Line const& l2);
};