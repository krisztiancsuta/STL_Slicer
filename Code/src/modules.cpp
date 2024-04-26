#include "modules.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector> //dinamikus memoriafoglalasra jo 
#include <sstream>
#include <algorithm>
#include <iomanip> 
#include <cmath>

namespace STL {

    double epsilon = 1e-10;
    //READ FUNCTIONS
    std::vector<Facet> read_STL(const std::string& filename, const std::string& mode) {

        std::vector<Facet> facets; //letrehozok egy vektort amibe a facet-ek lesznek ez fog dinimaikusan novekedni

        if (mode == "binary")
        {

        }
        else//Read file in text format
        {
            std::ifstream stl_file(filename);
            if (!stl_file.is_open()) {
                std::cerr << "Could not open file " << filename << std::endl;
                return facets;
            }

            std::string line;
            while (std::getline(stl_file, line)) { // beolvassa az elso sort
                Vector n;
                Point verteces[3];

                if (line.find("facet normal") != std::string::npos) {
                    //
                    //std::istringstream sin(line.substr(line.find("facet normal") + 12)); // Initialize with the part after "facet normal"
                    //sin >> n; // overloaded >> operator
                    std::getline(stl_file, line); // Skip "outer loop"
                    for (int i = 0; i < 3; i++) {
                        std::getline(stl_file, line); // Read vertex
                        std::istringstream sin(line.substr(line.find("vertex") + 6)); // Initialize with the part after "facet normal"
                        sin >> verteces[i];
                    }
                    std::getline(stl_file, line); // Skip "endloop"
                    std::getline(stl_file, line); // Skip "endfacet"


                    n = determineNormal(verteces[0], verteces[1], verteces[2]);
                    Facet facet(n, verteces[0], verteces[1], verteces[2]);

                    facets.push_back(facet);
                }

            }

            stl_file.close();

        }
        return facets;
    }

    void generate_Id(std::vector<Facet>& facets) {


        for (unsigned i = 0; i < facets.size(); i++)
        {

            facets[i].set_id();// beallitja mindig az aktualis ID
            //vegig megyek az osszes lapon es megnezem van e kozos 2 pontja
            for (unsigned j = i + 1; j < facets.size(); j++)
            {
                if (check_neighbour(facets[i], facets[j])) {
                    facets[j].set_id();
                    facets[i].set_id();
                    facets[j].inc_ID();
                }

            }

        }

    }
    std::vector<Line> generate_Lines(std::vector<Facet>const& facets) {
        //Kiszamoljuk az összes vonalat amit a cutter plannel elvagunk minden z szinten
        //cutter plane z koordinatajat beallitjuk a legkisebb z koordinataju pontra a síkokbol
        std::vector<Line> lines; // ezek a vonalak lesznek majd amikre a linesintersetction kell futtatni
        double zmin = 0.0;
        double zmax = 0.0;
        // slicerhez allitja be h milyen magassagba kezdje el szeletelnni 
        for (unsigned i = 0; i < facets.size(); i++)
        {
            double min = facets[i].getMinZ();
            double max = facets[i].getMaxZ();
            if (zmin - min > epsilon)
                zmin = min;
            if (zmax < max)
                zmax = max;
        };
        Cutter slicer(Vector(0.0, 0.0, 1.0), Point(0, 0, zmin)); // csak a z tengely menten lehet szeletelni

        for (double i = zmin; i <= zmax; i = i + 0.2, slicer.setZ(i))// 0.2 mm ert lepkedunk felfele slicerrel
        {
            for (unsigned j = 0; j < facets.size(); j++)
            {
                Line line_to_push = faceIntersection(facets[j], slicer);
                //megnezzuk hogy a line_to_push nullvektor e
                if (std::fabs(line_to_push.getDirv().getNx()) < epsilon &&
                    std::fabs(line_to_push.getDirv().getNy()) < epsilon &&
                    std::fabs(line_to_push.getDirv().getNz()) < epsilon) {
                }
                else if (std::find(lines.begin(), lines.end(), line_to_push) == lines.end())
                    lines.push_back(line_to_push);
            }
            //TODO: ha tul meredek egy sik es nincs benne a metszesvonal az alakzatban akkor azt se rakja bele
        }
        std::cout << "Lines Done" << std::endl;
        return lines;
    }



    std::vector<Point> generate_Points(std::vector<Line> const& lines) {
        std::vector<Point> points;

        for (unsigned i = 0; i < lines.size();i++)
        {

            for (unsigned j = i + 1; j < lines.size(); j++)
            {

                if (check_ID(lines[i], lines[j]) && (lines[i].getPoint().getZ() == lines[j].getPoint().getZ())) {

                    double dotproduct = dotProduct(lines[i].getDirv(), lines[j].getDirv());
                    double magnitude = lines[i].getDirv().getMagnitude() * lines[j].getDirv().getMagnitude();

                    Point point_to_push = lineIntersection(lines[i], lines[j]);

                    if (std::fabs(magnitude - dotproduct) < epsilon || magnitude == -1 * dotproduct) {}
                    else if (std::find(points.begin(), points.end(), point_to_push) == points.end())
                        points.push_back(point_to_push);
                }

            }

        }
        int x = 0;
        Point origin = find_origin(points, 0);
        for (unsigned i = 0; i < points.size(); i++)
        {
            if (points[i].getZ() != origin.getZ())
                origin = find_origin(points, i);
            points[i].setAngle(origin);
        }

        //Rendezzük a pontokat növekvő szög szerint szintenként
        std::sort(points.begin(), points.end(), cmp);

        return points;
    }

    bool cmp(const Point& a, const Point& b) {
        if (a.getZ() < b.getZ()) {
            return true;
        }
        else if (a.getZ() == b.getZ()) {
            return a.getAngle() < b.getAngle();
        }
        else {
            return false;
        }
    }
    void write_gcode(std::vector<Point>const& points) {
        std::ofstream gcode("Generated.gcode");
        if (gcode.fail())
            std::cout << "Error writing file" << std::endl;

        std::string start = "G28;Home\nG1 Z20 F6000;Move the platform down 20mm\n";
        std::string stop = "G28 X0 Y0;";
        gcode << start << std::endl;
        for (unsigned i = 0; i < points.size(); i++)
        {
            gcode << "G1 F1500 X" << points[i].getX() << " Y" << points[i].getY() << " Z" << points[i].getZ() << " E" << i << std::endl;
            //std::cout << "G1 F1500 X" << points[i].getX() << " Y" << points[i].getY() << " Z" << points[i].getZ() << " E" << i << std::endl;
        }
        gcode << stop << std::endl;

    }

    double Facet::getMinZ()const {
        double t[3] = { v1.getZ(),v2.getZ(), v3.getZ() };
        double min = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (min > t[i])
                min = t[i];
        }
        return min;
    }
    double Facet::getMaxZ()const {
        double t[3] = { v1.getZ(),v2.getZ(), v3.getZ() };
        double max = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (max < t[i])
                max = t[i];
        }
        return max;
    }

    double Facet::getMinX()const {
        double t[3] = { v1.getX(),v2.getX(), v3.getX() };
        double min = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (min > t[i])
                min = t[i];
        }
        return min;
    }
    double Facet::getMaxX()const {
        double t[3] = { v1.getX(),v2.getX(), v3.getX() };
        double max = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (max < t[i])
                max = t[i];
        }
        return max;
    }
    double Facet::getMinY()const {
        double t[3] = { v1.getY(),v2.getY(), v3.getY() };
        double min = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (min > t[i])
                min = t[i];
        }
        return min;
    }
    double Facet::getMaxY()const {
        double t[3] = { v1.getY(),v2.getY(), v3.getY() };
        double max = t[0];
        for (unsigned i = 1; i < 3; i++)
        {
            if (max < t[i])
                max = t[i];
        }
        return max;
    }

    void Point::setAngle(const Point& reference) {
        Vector v((reference.x - this->x), (reference.y - this->y), 0); // Create a 2D vector and calculate the polar angle
        double res = std::atan2(v.getNy(), v.getNx());

        while (res < 0)
            res += (2 * PI);

        if (res >= (2 * PI))
            res -= (2 * PI);

        this->angle = res;
    }
    //OPERATORS
    std::istream& operator>>(std::istream& input, Point& p) {
        p.angle = 0;
        input >> p.x >> p.y >> p.z; // Read the values into the point
        return input;
    }
    std::istream& operator>>(std::istream& input, Vector& v) {

        input >> v.nx >> v.ny >> v.nz; // beolvassa a pontba az ertekeket
        return input;
    }
    bool Point::operator==(const Point& p) {
        return (std::fabs(p.x - this->x) < epsilon && std::fabs(p.y - this->y) < epsilon && std::fabs(p.z - this->z) < epsilon);
    }
    bool Line::operator==(const Line& l) {
        return (l.getPoint() == this->getPoint() && l.getDirv() == this->getDirv());
    }
    bool Vector::operator==(const Vector& p) {
        return (std::fabs(p.nx - this->nx) < epsilon && std::fabs(p.ny - this->nx) < epsilon && std::fabs(p.nz - this->nz) < epsilon);
    }

    Vector operator-(const Point& p1, const Point& p2) {
        return Vector(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ() - p2.getZ());
    }

    Vector operator-(const Vector& v1, const Vector& v2) {
        return Vector(v1.getNx() - v2.getNx(), v1.getNy() - v2.getNy(), v1.getNz() - v2.getNz());
    }

    //CONSTRUCTORS

    Line::Line(const Line& other) {
        this->dirv = other.dirv;
        this->p = other.p;
        memcpy(this->id, other.id, sizeof(id));
    }
    Vector::Vector(Vector const& other) {
        this->nx = other.getNx();
        this->ny = other.getNy();
        this->nz = other.getNz();
    }
    Point::Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->angle = other.angle;
    }


    bool check_ID(const Line& l1, const Line& l2) {
        for (unsigned i = 0; i < 3; i++)
        {
            for (unsigned j = 0; j < 3; j++)
            {
                if (l1.getID(i) == l2.getID(j))
                    return true;
            }

        }
        return false;

    }
    //SETTERS

    void Line::setID(const Facet& face) {
        this->id[0] = face.getID(0);
        this->id[1] = face.getID(1);
        this->id[2] = face.getID(2);
    }

    void Facet::set_id() {
        bool k = true;

        for (unsigned i = 0;i < 3;i++) {
            if (id[i] == id_cnt)
            {
                k = false;
            }

            if ((id[i] == 0 && k)) {
                id[i] = id_cnt;
                k = false;
            }
        }


    }

    void Line::setPoint_from_array(double t[2][4], const Point& p) {
        //Kivalasztom azt a pontot amihez vezeregyes tartozik a tombben
        if (t[0][0] == 1) {
            this->p.setX(t[0][3] - (t[0][1]) * p.getY());
            if (t[1][2] == 1)
                this->p.setZ(t[1][3]);
            return;
        }
        if (t[0][1] == 1) {
            this->p.setY(t[0][3] - (t[0][0]) * p.getX());
            if (t[1][2] == 1)
                this->p.setZ(t[1][3]);
            return;
        }
        if (t[1][0] == 1) {
            this->p.setX(t[1][3] - (t[1][1]) * p.getY());
            if (t[0][2] == 1)
                this->p.setZ(t[0][3]);
            return;
        }
        if (t[1][1] == 1) {
            this->p.setY(t[1][3] - (t[1][0]) * p.getX());
            if (t[0][2] == 1)
                this->p.setZ(t[0][3]);
            return;
        }
    }

    void Point::setPoint_from_array(double t[2][4]) {
        //Kivalasztom azt az erteket amihez vezeregyes tartozik a tombben
        if (t[0][0] == 1) {
            this->x = t[0][3];
            this->y = t[1][3];
            return;
        }
        if (t[0][1] == 1) {
            this->y = t[0][3];
            this->x = t[1][3];
            return;
        }
    }
    void Line::setPoint(const Point p) {
        this->p = p;
    }
    void Line::setDirv(Vector n1, Vector n2) {
        this->dirv = Vector(n1.getNy() * n2.getNz() - n1.getNz() * n2.getNy(),
            n1.getNz() * n2.getNx() - n1.getNx() * n2.getNz(),
            n1.getNx() * n2.getNy() - n1.getNy() * n2.getNx());
    }
    void Line::setDirv(Vector dirv) {
        this->dirv = dirv;
    }

    //PRINTS
    void Line::print()const {
        std::cout << "Point: (" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")" << std::endl;
        std::cout << "Direction Vector: (" << dirv.getNx() << ", " << dirv.getNy() << ", " << dirv.getNz() << ")" << std::endl;
        std::cout << "Id:" << id[0] << " " << id[1] << " " << id[2] << std::endl;
    }
    void Point::print()const {
        std::cout << "Point: (" << getX() << ", " << getY() << ", " << getZ() << ")" << "Angle: " << getAngle() << std::endl;
    }
    void Vector::print()const {
        std::cout << "Normal: (" << getNx() << ", " << getNy() << ", " << getNz() << ")" << std::endl;
    }
    void Facet::print()const {
        this->n.print();
        this->v1.print();
        this->v2.print();
        this->v3.print();
        std::cout << "Id:" << id[0] << " " << id[1] << " " << id[2] << std::endl;
        std::cout << std::endl;
    }

    //FUNCTIONS
    void solve_two_equations(double t[2][4]) {
        // normalizáljuk az első sor első nem nulla elemét
        bool normalized = false; //ha normalizátuk akkor true ra állítjuk 
        for (int j = 0; j < 3 && !normalized; j++) {
            if (std::fabs(t[0][j]) > epsilon) { // ha nem nulla az elem akkor normalizáljuk
                double norm = t[0][j];
                for (int k = 0; k < 4; k++) {
                    t[0][k] /= norm;
                }
                normalized = true; // ha sikerült normalizálni akkor kilépünk a ciklusból
            }
        }

        if (!normalized) {
            //TODO?:throw hibauzenet
            return;
        }

        // Eliminate the first non-zero element of the second row based on the normalized first row.
        normalized = false;
        for (int j = 0; j < 3 && !normalized; j++) {
            if (std::fabs(t[0][j]) > epsilon) { // Use the first non-zero element for elimination.
                double factor = t[1][j] / t[0][j];
                for (int k = 0; k < 4; k++) {
                    t[1][k] -= factor * t[0][k];
                }
                normalized = true;
            }
        }

        if (!normalized) {
            //TODO?:throw hibauzenet
            return;
        }


        // Normalize the second row based on its leading non-zero coefficient after elimination.
        normalized = false;
        for (int j = 0; j < 3 && !normalized; j++) {
            if (std::fabs(t[1][j]) > epsilon) {
                double norm = t[1][j];
                for (int k = 0; k < 4; k++) {
                    t[1][k] /= norm;
                }
                normalized = true;
            }
        }
        if (!normalized) {
            //TODO?:throw hibauzenet
            return;
        }

        //kinulázzuk az összes vezeregyes felett az értékeket.
        for (int i = 0; i < 3; i++) {
            if (std::fabs(t[1][i]) > epsilon && t[1][i] == 1) {
                double factor = t[0][i];
                for (int j = 0; j < 4; j++) {
                    t[0][j] -= factor * t[1][j];
                }

            }
        }

        /*
        // Output the final matrix
        printf("Final matrix:\n");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%10.3f ", t[i][j]);
            }
            printf("\n");
        }
        */
    }

    Line faceIntersection(Facet const& f1, Cutter const& cutter_plane) {

        Line solution;
        Vector v = f1.getNormal();
        Point p0 = f1.getVertex1();


        Point pc = cutter_plane.getPoint();//itt mindig a 3. pontot vesszuk az lesz amit mozgatunk 
        Vector n = cutter_plane.getNormal();
        if (f1.getMinZ() - pc.getZ() <= epsilon && epsilon <= (f1.getMaxZ() - pc.getZ())) {
            double array_to_solve[2][4] = { { v.getNx(),v.getNy(), v.getNz(),(p0.getX() * v.getNx()) + (p0.getY() * v.getNy()) + (p0.getZ() * v.getNz())},
                                      {n.getNx(),n.getNy(), n.getNz(),(pc.getX() * n.getNx()) + (pc.getY() * n.getNy()) + (pc.getZ() * n.getNz())} };

            solve_two_equations(array_to_solve);
            /*
            // Output the array using cout
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << array_to_solve[i][j] << " ";
                }
                std::cout << std::endl;
            }
            */
            solution.setPoint(p0);//a szabad parameter erteket beallitom
            solution.setPoint_from_array(array_to_solve, p0);// a megoldas pontjat kiszedem a tombbol
            solution.setDirv(v, n);// a ket vektor kereszt szorzata lesz az iranyvektor
        }
        solution.setID(f1);
        return solution;

    }

    Point lineIntersection(Line const& l1, Line const& l2) {
        Point solution;
        Vector n1 = l1.getNormal();
        Point p1 = l1.getPoint();

        Vector n2 = l2.getNormal();
        Point p2 = l2.getPoint();

        double array_to_solve[2][4] = { { n1.getNx(), n1.getNy(),0, n1.getNx() * p1.getX() + n1.getNy() * p1.getY() },
                                        {n2.getNx(), n2.getNy(),0, n2.getNx() * p2.getX() + n2.getNy() * p2.getY()} };

        solve_two_equations(array_to_solve);

        solution.setZ(p1.getZ());
        solution.setPoint_from_array(array_to_solve);


        return solution;
    }

    Point find_origin(std::vector<Point>const& points, const unsigned offset) {
        //megkeresi a legkisebb x y koordinataju pontot ez lesz az origin
        double minx = points[offset].getX();
        double miny = points[offset].getY();
        double minz = points[offset].getZ();
        for (unsigned i = 0 + offset; i < points.size(); i++)
        {
            if (points[i].getX() < minx && points[i].getZ() == minz)
                minx = points[i].getX();
            if (points[i].getY() < miny && points[i].getZ() == minz)
                miny = points[i].getY();
            if (points[i].getZ() < minz && points[i].getZ() == minz)
                minz = points[i].getZ();
        }

        return Point(minx, miny, minz, 0);
    }

    Vector determineNormal(const Point& p1, const Point& p2, const Point& p3) {
        Vector v1 = p2 - p1;
        Vector v2 = p3 - p1;
        Vector normal = crossProduct(v1, v2);
        normal.normalize();
        return normal;
    }

    void Vector::normalize() {
        double length = std::sqrt(nx * nx + ny * ny + nz * nz);
        if (length != 0.0) {
            nx /= length;
            ny /= length;
            nz /= length;
        }
    }
    Vector crossProduct(const Vector& n1, const Vector& n2) {
        return Vector(n1.getNy() * n2.getNz() - n1.getNz() * n2.getNy(),
            n1.getNz() * n2.getNx() - n1.getNx() * n2.getNz(),
            n1.getNx() * n2.getNy() - n1.getNy() * n2.getNx());
    }

    double Vector::getMagnitude()const { return std::sqrt(nx * nx + ny * ny + nz * nz); }
    double dotProduct(Vector v1, Vector v2) { return v1.getNx() * v2.getNx() + v1.getNy() * v2.getNy() + v1.getNz() * v2.getNz(); }


    bool check_neighbour(const Facet& f1, const Facet& f2) {
        int similarPoints = 0;
        Point p1[3] = { f1.getVertex1(),f1.getVertex2(),f1.getVertex3() };
        Point p2[3] = { f2.getVertex1(),f2.getVertex2(),f2.getVertex3() };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (p1[i] == p2[j]) {
                    similarPoints++;
                }
            }
        }
        return similarPoints >= 2;

    }
    unsigned Facet::id_cnt = 1;
}