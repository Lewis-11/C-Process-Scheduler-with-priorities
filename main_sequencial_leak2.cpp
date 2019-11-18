#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;
//Global variables
double g = 6.674e-5;
double t = 0.1;
double dmin = 5;
int width = 200;
int height = 200;
double mass = 1000;
double sdm = 50;

//Asteroids Class
class Asteroid {
public:
    double xcoord = 0;
    double ycoord = 0;
    double xforce = 0;
    double yforce = 0;
    double xspeed = 0;
    double yspeed = 0;
    double xacc = 0;
    double yacc = 0;
    double mass = 0;
};

//Planets Class
class Planet {
public:
    double xcoord = 0;
    double ycoord = 0;
    double mass = 0;
};

//Initialize planets and asteroids
void create_bodies(Asteroid* asteroids, Planet* planets, int n_asteroids, int n_planets, int seed) {
    ofstream conf;
    conf.open("init_conf.txt", fstream::app);
    default_random_engine re{seed};
    uniform_real_distribution<double> xdist{0.0, std::nextafter(width, std :: numeric_limits<double>::max())};
    uniform_real_distribution<double> ydist{0.0, std::nextafter(height, std :: numeric_limits<double>::max())};
    normal_distribution<double> mdist{mass, sdm};
    conf << fixed << setprecision(3);
    //Create the asteroids
    for (int i = 0; i < n_asteroids ; ++i) {
        asteroids[i].xcoord = xdist(re);
        asteroids[i].ycoord = ydist(re);
        asteroids[i].mass = mdist(re);
        conf << asteroids[i].xcoord << " " << asteroids[i].ycoord << " " << asteroids[i].mass << " " << endl;
    }

    //Create the planets
    for (int i = 0; i < n_planets ; ++i) {
        if (i%4 == 0) {
            planets[i].xcoord = 0;
            planets[i].ycoord = ydist(re);
            planets[i].mass = mdist(re)*10;
        }
        else if (i%4 == 1) {
            planets[i].xcoord = xdist(re);
            planets[i].ycoord = 0;
            planets[i].mass = mdist(re)*10;
        }
        else if (i%4 == 2) {
            planets[i].xcoord = width;
            planets[i].ycoord = ydist(re);
            planets[i].mass = mdist(re)*10;
        }
        else if (i%4 == 3) {
            planets[i].xcoord = xdist(re);
            planets[i].ycoord = height;
            planets[i].mass = mdist(re)*10;
        }
        conf << planets[i].xcoord << " " << planets[i].ycoord << " " << planets[i].mass << " " << endl;
    }
    conf.unsetf(ios::fixed);
    conf.close();
}

//Function that creates the configuration file
int create_conf_file(int num, int* init) {
    ofstream conf;
    conf.open("init_conf.txt");
    for (int i = 0; i < num-1; ++i) {
        conf << init[i] << " ";
    }
    conf << endl;
    conf.close();
    return 0;
}

//Functions to calculate the distance between two bodies
double distance(Asteroid a, Asteroid b){
    return sqrt(pow(a.xcoord - b.xcoord, 2) + pow(a.ycoord - b.ycoord, 2));

}
double distance(Asteroid a, Planet b){
    return sqrt(pow(a.xcoord - b.xcoord, 2) + pow(a.ycoord - b.ycoord, 2));
}

//Functions to calculate the angle formed by two bodies
double angle(Asteroid a, Asteroid b) {
    double slope = ((a.ycoord - b.ycoord) / (a.xcoord - b.xcoord));
    if(slope > 1) slope = 1;
    if(slope < -1) slope = -1;
    double alpha = atan(slope);
    return alpha;
}
double angle(Asteroid a, Planet b) {
    double slope = ((a.ycoord - b.ycoord) / (a.xcoord - b.xcoord));
    if(slope > 1) slope = 1;
    if(slope < -1) slope = -1;
    double alpha = atan(slope);
    return alpha;
}

//Functions to calculate the attraction force of two bodies
double attraction_force(Asteroid a, Asteroid b, bool yaxis){
    double r_force = ((g*a.mass*b.mass)/pow(distance(a, b), 2));
    if (yaxis) r_force = r_force * sin(angle(a, b));
    else r_force = r_force * cos(angle(a, b));
    if(r_force > 100) return 100;
    else return r_force;
}
double attraction_force(Asteroid a, Planet b, bool yaxis){
    double r_force = ((g*a.mass*b.mass)/pow(distance(a, b), 2));
    if (yaxis) r_force = r_force * sin(angle(a, b));
    else r_force = r_force * cos(angle(a, b));
    if(r_force > 100) return 100;
    else return r_force;
}

//Function to calculate acceleration of an asteroid
void ast_acceleration(Asteroid* a, int num){
    for (int i = 0; i < num; ++i) {
        a[i].xacc = (1/a[i].mass)*a[i].xforce;
        a[i].yacc = (1/a[i].mass)*a[i].yforce;
    }
}

//Function to calculate speed of an asteroid
void speed_asteroids(Asteroid* a, int num) {
    for (int i = 0; i < num; ++i) {
        a[i].xspeed = a[i].xspeed + a[i].xacc*t;
        a[i].yspeed = a[i].yspeed + a[i].yacc*t;
    }
}

//Function to calculate position of an asteroid
//Using same iteration in the for loop to calculate rebounds with the borders
void pos_asteroids(Asteroid* a, int num) {
    double temp_x;
    double temp_y;
    for (int i = 0; i < num; ++i) {
        temp_x = a[i].xcoord + a[i].xspeed*t;
        temp_y = a[i].ycoord + a[i].yspeed*t;
        //Checking rebounds against walls
        if (temp_x <= 0) {
            a[i].xcoord = dmin;
            a[i].xspeed = -a[i].xspeed;
        }
        else if (temp_x >= width) {
            a[i].xcoord = width - dmin;
            a[i].xspeed = -a[i].xspeed;
        }
        else a[i].xcoord = temp_x;
        if (temp_y <= 0) {
            a[i].ycoord = dmin;
            a[i].yspeed = -a[i].yspeed;
        }
        else if (temp_y >= height) {
            a[i].ycoord = height - dmin;
            a[i].yspeed = -a[i].yspeed;
        }
        else a[i].ycoord = temp_y;
    }
}

//Function to write the output data into a file
void output_file(Asteroid* a, int num){
    ofstream out;
    out.open("out1.txt", ios::out | ios::trunc);
    out << fixed << setprecision(3);
    for (int i = 0; i < num; ++i) {
        out << a[i].xcoord << " " << a[i].ycoord << " " << a[i].xspeed << " " << a[i].yspeed << " " << a[i].mass << endl;
    }
    out.close();
}

int main(int argc, char **argv) {
    //Initialize the clock
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    //Checking parameters are valid
    int *param = new int[argc-1];
    for (int i = 1; i < argc; ++i) {
        param[i-1] = atoi(argv[i]);
        if (param[i-1] < 0){
            cout << "nasteroids-seq: Wrong arguments." << endl;
            cout << "Correct use: nasteroids-seq num_asteroids num_iterations num_planets seed." << endl;
            cout << "Values must be positive." << endl;
            return -1;
        }
    }

    //Creating the initial configuration file and initializing asteroids and planets
    create_conf_file(argc, param);
    auto asteroids = new Asteroid[param[0]];
    auto planets = new Planet[param[2]];
    create_bodies(asteroids, planets, param[0], param[2], param[3]);

    //Program iterates to calculate the positions of the asteroids
    double calc_xforce = 0;
    double calc_yforce = 0;
    for(int k = param[1]; k > 0; --k) {
        //Reset attraction forces
        for (int i = 0; i < param[0]; ++i) {
            asteroids[i].xforce = 0;
            asteroids[i].yforce = 0;
        }
        //Attraction force between asteroids is calculated
        for (int i = 0; i < param[0]-1; ++i) {
            for (int j = i+1; j < param[0]; ++j) {
                if (distance(asteroids[i], asteroids[j]) > dmin) {
                    calc_xforce = attraction_force(asteroids[i], asteroids[j], false);
                    calc_yforce = attraction_force(asteroids[i], asteroids[j], true);
                    asteroids[i].xforce += calc_xforce;
                    asteroids[i].yforce += calc_yforce;
                    asteroids[j].xforce -= calc_xforce;
                    asteroids[j].yforce -= calc_yforce;
                }
            }
        }
        //Attraction force between asteroids and planets is calculated
        for (int i = 0; i < param[0]; ++i) {
            for (int j = 0; j < param[2]; ++j) {
                asteroids[i].xforce += attraction_force(asteroids[i], planets[j], false);
                asteroids[i].yforce += attraction_force(asteroids[i], planets[j], true);
            }
        }
        //New positions for the asteroids are calculated
        ast_acceleration(asteroids, param[0]);
        speed_asteroids(asteroids, param[0]);
        pos_asteroids(asteroids, param[0]);

        //Rebounds between asteroids are calculated
        double temp;
        for (int i = 0; i < param[0]-1; ++i) {
            for (int j = i + 1; j < param[0]; ++j) {
                if (distance(asteroids[i], asteroids[j]) <= dmin) {
                    temp = asteroids[i].xspeed;
                    asteroids[i].xspeed = asteroids[j].xspeed;
                    asteroids[j].xspeed = temp;
                    temp = asteroids[i].yspeed;
                    asteroids[i].yspeed = asteroids[j].yspeed;
                    asteroids[j].yspeed = temp;
                    break;
                }
            }
        }
    }
    output_file(asteroids, param[0]);
    auto t2 = high_resolution_clock::now();
    auto diff = duration_cast<microseconds>(t2-t1);
    cout << setprecision(3);
    cout << "Time: " << diff.count() << endl;
    return 0;
}