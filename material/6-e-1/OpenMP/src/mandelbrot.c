#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timing.h"

int divergence(int limit, double radius, double *x, double *y) {
  double u = 0.0;
  double v = 0.0;
  double u2 = u * u;
  double v2 = v * v;
  int k;
  for (k = 1; k < limit && u2 + v2 < radius; k++) {
    v = 2 * u * v + *y;
    u = u2 - v2 + *x;
    u2 = u * u;
    v2 = v * v;
  };
  *x = u;
  *y = v;
  return k;
}

void to_rgb(double* r, double *g, double *b, int rgb) {
  *r = ((rgb >> 16) & 0xFF) / 255.0;
  *g = ((rgb >>  8) & 0xFF) / 255.0;
  *b = ((rgb >>  0) & 0xFF) / 255.0;
}

double clamp(double x) {
  if (x < 0) {
    return 0;
  } else if (x > 1) {
    return 1;
  } else {
    return x;
  }
}

int from_rgb(double r, double g, double b) {
  return
    ((int)(clamp(r) * 255) << 16) |
    ((int)(clamp(g) * 255) << 8) |
    ((int)(clamp(b) * 255));
}

double cubic (double x0, double x1,
              double y0, double y1,
              double m0, double m1,
              double x) {
  double h = x1 - x0;
  double t = (x - x0) / h;
  double h_00 = (1.0 + 2.0*t) * pow(1.0 - t, 2.0);
  double h_10 = t * pow(1.0 - t, 2.0);
  double h_01 = pow(t, 2.0) * (3.0 - 2.0 * t);
  double h_11 = pow(t, 2.0) * (t - 1.0);
  return y0 * h_00 + h * m0 * h_10 + y1 * h_01 + h * m1 * h_11;
}

double interp (double x0, double x1,
               double y0, double y1,
               double mr0, double mg0,double mb0,
               double mr1, double mg1, double mb1,
               double x) {
  double r0, g0, b0;
  to_rgb(&r0, &g0, &b0, y0);
  double r1, g1, b1;
  to_rgb(&r1, &g1, &b1, y1);

  return from_rgb(cubic(x0,x1, r0,r1, mr0,mr1, x),
                  cubic(x0,x1, g0,g1, mg0,mg1, x),
                  cubic(x0,x1, b0,b1, mb0,mb1, x));
}

int mk_palette (int points, int ix) {
  double p = (double)ix / (double)points;

  double p0 = 0.0;
  double p1 = 0.16;
  double p2 = 0.42;
  double p3 = 0.6425;
  double p4 = 0.8575;
  double p5 = 1.0;

  int c0 = 0x000764;
  int c1 = 0x206bcb;
  int c2 = 0xedffff;
  int c3 = 0xffaa00;
  int c4 = 0x000200;
  int c5 = c0;

  double mr0 = 0.7843138, mg0 = 2.4509804, mb0 = 2.52451;
  double mr1 = 1.93816,   mg1 = 2.341629,  mb1 = 1.6544118;
  double mr2 = 1.7046283, mg2 = 0.0,       mb2 = 0.0;
  double mr3 = 0.0,       mg3 = -2.281211, mb3 = 0.0;
  double mr4 = 0.0,       mg4 = 0.0,       mb4 = 0.0;
  double mr5 = mr0,       mg5 = mg0,       mb5 = mb0;

  if (p <= p1) {
    return interp(p0,p1, c0,c1, mr0,mg0,mb0, mr1,mg1,mb1, p);
  } else if (p <= p2) {
    return interp(p1,p2, c1,c2, mr1,mg1,mb1, mr2,mg2,mb2, p);
  } else if (p <= p3) {
    return interp(p2,p3, c2,c3, mr2,mg2,mb2, mr3,mg3,mb3, p);
  } else if (p <= p4) {
    return interp(p3,p4, c3,c4, mr3,mg3,mb3, mr4,mg4,mb4, p);
  } else {
    return interp(p4,p5, c4,c5, mr4,mg4,mb4, mr5,mg5,mb5, p);
  }
}

int escape_to_colour(int limit, int points, double x, double y, int n) {
  if (n == limit) {
    return 0; // Black.
  } else {
    double smooth = log2(log2(sqrt(x*x+y*y)));
    double scale = 256;
    double shift = 1664;
    int ix = sqrt(n + 1 - smooth) * scale + shift;
    return mk_palette(points, ix % points);
  }
}

// Write pixel values to file in the PPM image format - you can open
// this in most image viewers (or probably a browser).
void ppm_to_file(const char *filename, int *pixels, int height, int width) {
  FILE *file = fopen(filename, "wb");
  assert(file != NULL);

  fprintf(file, "P6\n%d %d\n255\n", width, height);

  for (int i = 0; i < height*width; i++) {
    unsigned char pixel[3];
    pixel[0] = pixels[i]>>16;
    pixel[1] = pixels[i]>>8;
    pixel[2] = pixels[i]>>0;
    fwrite(pixel, 1, 3, file);
  }

  fclose(file);
}

int main(int argc, char** argv) {
  assert(argc == 6 || argc == 9);

  const char *output_fname = argv[1];
  int imgw = atoi(argv[2]);
  int imgh = atoi(argv[3]);
  int limit = atoi(argv[4]);
  double radius = strtod(argv[5], NULL);

  double xcentre = -0.7;
  double ycentre = 0;
  double width = 3.67;

  if (argc == 9) {
    xcentre = strtod(argv[6], NULL);
    ycentre = strtod(argv[7], NULL);
    width = strtod(argv[8], NULL);
  }

  double aspect_ratio = imgw / imgh;
  double xmin = xcentre - width/2.0;
  double ymin = ycentre - (1/aspect_ratio)*width/2.0;
  double xmax = xcentre + width/2.0;
  double ymax = ycentre + (1/aspect_ratio)*width/2.0;

  double sizex = xmax - xmin;
  double sizey = ymax - ymin;

  int *pixels = malloc(imgw * imgh * sizeof(int));
  int points = 2048; // For colour palette.

  for (int i = 0; i < imgh; i++) {
    for (int j = 0; j < imgw; j++) {
      double x = xmin + (j*sizex) / imgw;
      double y = ymin + (i*sizey) / imgh;
      int n = divergence(limit, radius, &x, &y);
      int pixel = escape_to_colour(limit, points, x, y, n);
      pixels[i*imgw+j] = pixel;
    }
  }

  ppm_to_file(output_fname, pixels, imgh, imgw);
}
