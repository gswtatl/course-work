#include <fstream>

int main() {
    FILE *graphics = popen("gnuplot -persistent", "w");
    fprintf(graphics, "set multiplot layout 1,3\n");
    fprintf(graphics, "set title 'Первый график'\n");
    fprintf(graphics, "plot 'data1.txt' using 1:2 with lines\n");
    fprintf(graphics, "set title 'Второй график'\n");
    fprintf(graphics, "plot 'data2.txt' using 1:2 with lines\n");
    fprintf(graphics, "set title 'Третий график'\n");
    fprintf(graphics, "plot 'data3.txt' using 1:2 with lines\n");
    fprintf(graphics, "unset multiplot\n");
    pclose(graphics);
}