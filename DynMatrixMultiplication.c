#include <stdio.h>
#include <stdlib.h>

int** input_matrix(int *rm, int *cm) {
    printf("Rows: ");
    scanf("%d", rm);
    printf("Columns: ");
    scanf("%d", cm);

    int **matrix = (int **)malloc(*rm * sizeof(int *));
    for (int i = 0; i < *rm; i++) {
        matrix[i] = (int *)malloc(*cm * sizeof(int));
    }

    printf("Enter values for the matrix:\n");
    for (int i = 0; i < *rm; i++) {
        for (int j = 0; j < *cm; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    return matrix;
}

int** matrix_multiply(int **m1, int rm1, int cm1, int **m2, int rm2, int cm2) {
    if (cm1 != rm2) {
        fprintf(stderr, "ERROR: CANNOT MULTIPLY\n");
        return NULL;
    }

    int **result = (int **)malloc(rm1 * sizeof(int *));
    for (int i = 0; i < rm1; i++) {
        result[i] = (int *)malloc(cm2 * sizeof(int));
    }

    for (int i = 0; i < rm1; i++) {
        for (int j = 0; j < cm2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cm1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

void output_matrix(int **m, int rm, int cm) {
    for (int i = 0; i < rm; i++) {
        for (int j = 0; j < cm; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int **m1, **m2, **m3;
    int rm1, cm1, rm2, cm2;

    m1 = input_matrix(&rm1, &cm1);
    m2 = input_matrix(&rm2, &cm2);

    if (m1 && m2) {
        if (cm1 == rm2) {
            m3 = matrix_multiply(m1, rm1, cm1, m2, rm2, cm2);

            if (m3) {
                printf("Matrix 1:\n");
                output_matrix(m1, rm1, cm1);
                printf("Matrix 2:\n");
                output_matrix(m2, rm2, cm2);
                printf("Product (Matrix 3):\n");
                output_matrix(m3, rm1, cm2);

                // Free allocated memory
                for (int i = 0; i < rm1; i++) {
                    free(m1[i]);
                }
                free(m1);
                for (int i = 0; i < rm2; i++) {
                    free(m2[i]);
                }
                free(m2);
                for (int i = 0; i < rm1; i++) {
                    free(m3[i]);
                }
                free(m3);

                return 0;
            } else {
                printf("Error allocating memory for the result matrix.\n");
            }
        } else {
            printf("Error in dimensions. Matrix 1 columns must match Matrix 2 rows.\n");
        }
    } else {
        printf("Error allocating memory for matrices.\n");
    }

    return -1;
}

