#include <stdio.h>

int main() {
    char operador;
    double num1, num2, resultado;
    printf("Ingrese un operador (+, -, *, /): ");
    scanf("%c", &operador);

    printf("Ingrese dos números: ");
    scanf("%lf %lf", &num1, &num2);

    switch (operador) {
        case '+':
            resultado = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, resultado);
            break;

        case '-':
            resultado = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, resultado);
            break;

        case '*':
            resultado = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, resultado);
            break;

        case '/':
            if (num2 = 0) {
                resultado = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, resultado);
            } else {
                printf("Error: División por cero no permitida.\n");
            }
            break;

        default:
            printf("Error: Operador no válido.\n");
            break;
    }

    return 0;
}