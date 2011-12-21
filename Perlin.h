#ifndef PERLIN_H
#define PERLIN_H

#define X_NOISE_GEN 1619
#define Y_NOISE_GEN 31337
#define OCTAVE_NOISE_GEN 3463
#define SEED_NOISE_GEN 13397

class Perlin
{
private:
    int seed;
    int octaves;
    double persistance;
    double zoom;

    static double noise(int x, int y, int octave)
    {
        int n = int n = (X_NOISE_GEN * x + Y_NOISE_GEN * y + OCTAVE_NOISE_GEN * octave + SEED_NOISE_GEN * seed) & 0x7fffffff;;
        n=(n>>13)^n;
        return 1.0 - ( (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff ) / 1073741824.0;
    }


    static double interpolate(double a,double b,double x)
    {
        double ft = x * 3.1415927;
        double f = (1 - cos(ft)) * .5;
        return  a * (1 - f) + b*f;
    }
    static double interpolated_noise(double x,double y,int octave) {
        int int_x = (int)floor(x);
        double frac_x = x - (int_x + 0.0);

        int int_y = (int)floor(y);
        double frac_y = y - (int_y + 0.0);

        double v1=noise(int_x, int_y, octave);
        double v2=noise(int_x+1, int_y, octave);
        double v3=noise(int_x, int_y+1, octave);
        double v4=noise(int_x+1, int_y+1, octave);

        double i1=interpolate(v1, v2, frac_x);
        double i2=interpolate(v3, v4, frac_x);

        return interpolate(i1,i2,frac_y);
    }

public:

    double n(int x, int y) //Short for noise; will be used a lot, shortened for brevity
    {
        double total = 0;

        for(int i = 0; i < octaves; i++)
        {
            double frequency = Math.pow(2, i) * zoom;
            double amplitude = Math.pow(persistance, i);
            total = total + interpolated_noise(x * frequency, y * frequency, i) * amplitude;
        }

        return total;
    }

    Perlin(int _octaves, double _persistance, double _zoom, int _seed)
    {
        octaves = _octaves;
        persistance = _persistance;
        zoom = _zoom;
        seed = _seed;
    }
}
