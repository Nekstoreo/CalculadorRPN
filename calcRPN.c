#include <stdio.h>
#include <math.h>

double stack[8];
int top = -1;

void push(double value)
{
    if (top < 8 - 1)
    {
        for (int i = top; i >= 0; i--)
        {
            stack[i + 1] = stack[i];
        }
        stack[0] = value;
        top++;
    }
    else
    {
        printf("La pila esta llena. No se pueden agregar mas elementos.\n");
    }
}

double pop()
{
    if (top >= 0)
    {
        double value = stack[0];
        for (int i = 0; i < top; i++)
        {
            stack[i] = stack[i + 1];
        }
        stack[top] = 0.0;
        top--;
        return value;
    }
    else
    {
        printf("La pila esta vacia.\n");
        return NAN;
    }
}

void clear_stack()
{
    for (int i = 0; i < 8; i++)
    {
        stack[i] = 0.0;
    }
    top = -1;
}

void printStack()
{
    printf("Pila:\n");
    for (int i = 8 - 1; i >= 0; i--)
    {
        printf("%d) %.5f\n", i + 1, stack[i]);
    }
}

void popFirst()
{
    if (top >= 0)
    {
        for (int i = 0; i < top; i++)
        {
            stack[i] = stack[i + 1];
        }
        stack[top] = 0.0;
        top--;
    }
    else
    {
        printf("La pila esta vacia.\n");
    }
}

int main() {
    char opcion;
    double num1;

    while (1) {
        
        printStack();
        printf("\nMenu:\n");
        printf("1. Agregar numero a la pila\n");
        printf("2. Realizar operacion\n");
        printf("3. Limpiar pila\n");
        printf("4. Eliminar primer elemento de la pila\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case '1':
                printf("Ingrese un numero: ");
                scanf("%lf", &num1);
                push(num1);
                break;
            case '2':
                if (top >= 1) {
                    printf("Ingrese la operacion (+, -, *, /, p (potencia), r (raiz), s (seno), c (coseno), t (tangente)): ");
                    scanf(" %c", &opcion);
                    double resultado;
                    num1 = pop();
                    switch (opcion) {
                        case '+':
                            resultado = num1 + pop();
                            break;
                        case '-':
                            resultado = num1 - pop();
                            break;
                        case '*':
                            resultado = num1 * pop();
                            break;
                        case '/':
                            double num2 = pop();
                            if (num2 == 0) {
                                printf("No se puede dividir entre cero.\n");
                                push(num2);
                                push(num1); 
                                continue;
                            }
                            resultado = num1 / num2;
                            break;
                        case 'p':
                            resultado = pow(num1, pop());
                            break;
                        case 'r':
                            if (num1 < 0) {
                                printf("No se puede calcular la raiz cuadrada de un numero negativo.\n");
                                push(num1); // Devuelve el valor a la pila
                                continue;
                            }
                            resultado = sqrt(num1);
                            break;
                        case 's':
                            resultado = sin(num1 * M_PI / 180);
                            break;
                        case 'c':
                            resultado = cos(num1 * M_PI / 180);
                            break;
                        case 't':
                            if (num1 == 90 || num1 == 270) {
                                printf("No se puede calcular la tangente de 90 o 270 grados.\n");
                                push(num1); // Devuelve el valor a la pila
                                continue;
                            }
                            resultado = tan(num1 * M_PI / 180);
                            break;
                        default:
                            printf("Operacion no valida.\n");
                            push(num1); // Devuelve el valor a la pila
                            continue;
                    }
                    push(resultado);
                } else {
                    printf("Se necesitan al menos dos numeros en la pila para realizar una operacion.\n");
                }
                break;
            case '3':
                clear_stack();
                break;
            case '4':
                popFirst();
                break;
            case '0':
                printf("Saliendo del programa.\n");
                return 0;
            default:
                printf("Opcion no valida.\n");
        }
    }
    return 0;
}