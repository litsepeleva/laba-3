#include <stdio.h>
#include <stdlib.h>
void stroki(int** matrix, int n, int m) {
    for (int j=0; j<m; j++) {
        int temp = matrix[0][j];
        matrix[0][j] = matrix[n-1][j];
        matrix[n-1][j] = temp;
    }
}
void calculate(int** matrix, int n, int m, double* s) {
    for (int i=0; i<n; i++) {
        double sum = 0;
        for (int j=0; j<m; j++) {
            double val = (double)matrix[i][j];
            sum += 1 - val / 6.0 + (val * val) / 6.0;
        }
        s[i] = 5 + sum;
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <имя файла>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка\n");
        return 1;
    }
     int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2) {
        printf("Ошибка\n");
        fclose(file);
        return 1;
    }
    int** matrix = malloc(n * sizeof(int*));
    if (!matrix) {
        printf("Ошибка\n");
        fclose(file);
        return 1;
    }
    for (int i=0; i<n; i++) {
        matrix[i] = malloc(m * sizeof(int));
        if (!matrix[i]) {
            printf("Ошибка\n");
            for (int k=0; k<i; k++) free(matrix[k]);
            free(matrix);
            fclose(file);
            return 1;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка\n");
                for (int k=0; k<n; k++) free(matrix[k]);
                free(matrix);
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    stroki(matrix, n, m);
    double* s = malloc(n * sizeof(double));
    if (!s) {
        printf("Ошибка\n");
        for (int k=0; k<n; k++) free(matrix[k]);
        free(matrix);
        return 1;
    }
    calculate(matrix, n, m, s);
    printf("Обновленная матрица:\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Суммa для каждой строки:\n");
    for (int i=0; i<n; i++) {
        printf("s[%d] = %.3lf\n", i, s[i]);
    }
    for (int i=0; i<n; i++) free(matrix[i]);
    free(matrix);
    free(s);
    return 0;
}
