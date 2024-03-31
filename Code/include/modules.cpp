#include"modules.h"
#include <iostream>
#include <fstream>
#include <string>
namespace STL {

    //Read functions
    void read_STL(const std::string& filename, const std::string& mode) {
        if (mode == "binary")
        {

        }
        else//Read file in text format
        {
            std::ifstream stl_file(filename);
            if (!stl_file) {
                std::cerr << "Could not open file " << filename << std::endl;
                return;
            }

            std::string line;
            while (std::getline(stl_file, line)) {
                std::cout << line << std::endl;
            }

            stl_file.close();

        }
    }




    //Construktorok
    Vector::Vector(Vector const& other) {
        this->nx = other.getNx();
        this->ny = other.getNy();
        this->nz = other.getNz();
    }
    Point::Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    };


    //Setterek

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
    };
    void Line::setDirv(Vector n1, Vector n2) {
        this->dirv = Vector(n1.getNy() * n2.getNz() - n1.getNz() * n2.getNy(),
            n1.getNz() * n2.getNx() - n1.getNx() * n2.getNz(),
            n1.getNx() * n2.getNy() - n1.getNy() * n2.getNx());
    }
    void Line::setDirv(Vector dirv) {
        this->dirv = dirv;
    }


    void Line::print()const {
        std::cout << "Point: (" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")" << std::endl;
        std::cout << "Direction Vector: (" << dirv.getNx() << ", " << dirv.getNy() << ", " << dirv.getNz() << ")" << std::endl;
    }

    void Point::print()const {
        std::cout << "Point: (" << getX() << ", " << getY() << ",Konstans:  " << getZ() << ")" << std::endl;
    }



    // getterek


    // Ez a függvény visszaadja a Line objektum normálvektorát.
    Vector Line::getNormal() const {
        // A normálvektor a irányvektor x és y komponenseinek felcserélésével és az új x komponens negálásával kapható.
        return Vector(this->dirv.getNy(), -1 * (this->dirv.getNx()), 0);
    }
    //függvenyek
    Line faceIntersection(Facet const& f1, Cutter const& cutter_plane) {

        Line solution;
        Vector v = f1.getNormal();
        Point p0 = f1.getVertex1();

        Point pc = cutter_plane.getPoint();//itt mindig a 3. pontot vesszuk az lesz amit mozgatunk 
        Vector n = cutter_plane.getNormal();

        double array_to_solve[2][4] = { v.getNx(),v.getNy(), v.getNz(),(p0.getX() * v.getNx()) + (p0.getY() * v.getNy()) + (p0.getZ() * v.getNz()),
                                      {n.getNx(),n.getNy(), n.getNz(),(pc.getX() * n.getNx()) + (pc.getY() * n.getNy()) + (pc.getZ() * n.getNz())} };

        solve_two_equations(array_to_solve);
        // Output the array using cout
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << array_to_solve[i][j] << " ";
            }
            std::cout << std::endl;
        }
        solution.setPoint(p0);//a szabad parameter erteket beallitom
        solution.setPoint_from_array(array_to_solve, p0);// a megoldas pontjat kiszedem a tombbol
        solution.setDirv(v, n);// a ket vektor kereszt szorzata lesz az iranyvektor
        return solution;

    }


    void solve_two_equations(double t[2][4]) {
        // normalizáljuk az első sor első nem nulla elemét
        bool normalized = false; //ha normalizátuk akkor true ra állítjuk 
        for (int j = 0; j < 3 && !normalized; j++) {
            if (fabs(t[0][j]) > 1e-6) { // ha nem nulla az elem akkor normalizáljuk
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
            if (fabs(t[0][j]) > 1e-6) { // Use the first non-zero element for elimination.
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
            if (fabs(t[1][j]) > 1e-6) {
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

        //kinulázzuk az összes vegyes felett az értékeket.
        for (int i = 0; i < 3; i++) {
            if (fabs(t[1][i]) > 1e-6 && t[1][i] == 1) { // If not already zero
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



}