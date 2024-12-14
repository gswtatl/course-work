#include <cmath>
#include <iostream>
#include <fstream>

struct Power {
    double T, dt, k0, U0, m, f0, h, c, tgdelta; 
};
Power arr[3];

FILE* input_file = fopen("C:/Users/gswtatl/Downloads/programming/course_work/input.txt", "r");
FILE* output_file = fopen("C:/Users/gswtatl/Downloads/programming/course_work/output.txt", "w");
double U = 0, k = 0, f = 0, Pa;

void read_data(Power arr[]) {
    for (int i = 0; i < 3; i++) {
        fscanf(input_file, "%lf%lf%lf%lf%lf%lf%lf%lf%lf",
               &arr[i].T, &arr[i].dt, &arr[i].k0,
               &arr[i].U0, &arr[i].m, &arr[i].f0,
               &arr[i].h, &arr[i].c, &arr[i].tgdelta);
    }
}

void count_k(float t, double T, double k0, double m) {
    if (0 <= t && t <= T / 2) {
        k = k0 * (1 + m * t);
    }
    else k = k0 * (1 + m * (T / 2));
}

void count_U(float t, double T, double U0) {
    if (0 <= t && t <= T / 4) {
        U = U0 * (1 - exp(-k * t));
    }
    else if (T / 4 <= t && t <= T / 2) {
        U = U0 * (1 - exp(-k * (T / 2)));
    }
    else U = U0 * (1 - exp(-k * (T / 2))) * exp(-k * (t - T / 2));
}

void count_f(float t, double T, double f0, double h) {
    if (0 <= t && t <= T / 4) {
       f = f0 * (1 + h * t);
    }
    else if (T / 4 <= t && t <= (3 * T / 4)) {
        f = f0 * (1 + h * (T / 4));
    }
    else f = f0 * (1 + h * (T / 4)) - f0 * exp(-h * (t - (3 * T / 4)));
}

int main() {
    read_data(arr);

    for (int i = 0; i < 3; i++) {
        fprintf(output_file, "Для %i-го варианта:\n", i + 1);
        for (float t = 0; t <= arr[i].T; t += arr[i].dt) {
            count_k(t, arr[i].T, arr[i].k0, arr[i].m);
            count_U(t, arr[i].T, arr[i].U0);
            count_f(t, arr[i].T, arr[i].f0, arr[i].h);
            Pa = pow(U, 2) * 2 * M_PI * f * arr[i].c * arr[i].tgdelta;
            fprintf(output_file, "t = %3.1f: k = %3.3lf, U = %lf, f = %lf, Pa = %lf\n", t, k, U, f, Pa);
        }
    }

    fclose(input_file);
    fclose(output_file);
}