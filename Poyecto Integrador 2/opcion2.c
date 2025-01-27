#include <stdio.h>
#include <string.h>

#define ZONAS 5
#define DIAS 30
#define LIMITE_CO2 100
#define LIMITE_SO2 50
#define LIMITE_NO2 60
#define LIMITE_PM25 25

typedef struct Zona {
    char nombre[30];
    float contaminacion_actual[4]; 
    float contaminacion_historica[DIAS][4]; 
    float temperatura_actual;
    float viento_actual;
    float humedad_actual;
} Zona;

void cargarDatos(Zona *zonas);
void mostrarContaminacion(Zona *zonas);
void predecirContaminacion(Zona *zonas);
void generarAlertas(Zona *zonas);
void recomendaciones(Zona *zonas);
void guardarDatos(Zona *zonas);
void ingresarDatosContaminacion(Zona *zonas);
void menu(Zona *zonas);

int main() {
    Zona zonas[ZONAS]; 
    cargarDatos(zonas);
    menu(zonas); 
    return 0;
}

void cargarDatos(Zona *zonas) {
    char *nombresZonas[ZONAS] = {"Centro Historico", "La Mariscal", "Cotogchoa", "Rumiñahui", "San Juan"};
    
    float contaminacion_historica[ZONAS][DIAS][4] = {
        {{50.0, 30.0, 40.0, 20.0}, {55.0, 32.0, 43.0, 22.0}, {60.0, 35.0, 45.0, 25.0}, },
        {{45.0, 25.0, 30.0, 15.0}, {50.0, 28.0, 35.0, 17.0}, },
        {{48.0, 28.0, 35.0, 18.0}, {52.0, 31.0, 39.0, 20.0}, },
        {{42.0, 24.0, 38.0, 16.0}, {47.0, 27.0, 41.0, 18.0}, },
        {{51.0, 29.0, 37.0, 19.0}, {56.0, 32.0, 40.0, 21.0}, },
    };

    for (int i = 0; i < ZONAS; i++) {
        strcpy(zonas[i].nombre, nombresZonas[i]);

        for (int j = 0; j < DIAS; j++) {
            for (int k = 0; k < 4; k++) {
                zonas[i].contaminacion_historica[j][k] = contaminacion_historica[i][j][k];
            }
        }

 
        zonas[i].contaminacion_actual[0] = 0.0;
        zonas[i].contaminacion_actual[1] = 0.0;
        zonas[i].contaminacion_actual[2] = 0.0;
        zonas[i].contaminacion_actual[3] = 0.0;

        zonas[i].temperatura_actual = 0.0;
        zonas[i].viento_actual = 0.0;
        zonas[i].humedad_actual = 0.0;
    }
}

void ingresarDatosContaminacion(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("¿Desea ingresar los datos de contaminacion para la zona: %s? (s/n): ", zonas[i].nombre);
        char respuesta;
        scanf(" %c", &respuesta);

        if (respuesta == 's' || respuesta == 'S') {
            printf("Ingrese los datos de contaminacion para la zona: %s\n", zonas[i].nombre);

            printf("CO2 (ppm): ");
            scanf("%f", &zonas[i].contaminacion_actual[0]);
            printf("SO2 (ppm): ");
            scanf("%f", &zonas[i].contaminacion_actual[1]);
            printf("NO2 (ppm): ");
            scanf("%f", &zonas[i].contaminacion_actual[2]);
            printf("PM2.5 (µg/m³): ");
            scanf("%f", &zonas[i].contaminacion_actual[3]);

            printf("Temperatura Actual (°C): ");
            scanf("%f", &zonas[i].temperatura_actual);
            printf("Velocidad del Viento Actual (km/h): ");
            scanf("%f", &zonas[i].viento_actual);
            printf("Humedad Actual (%%): ");
            scanf("%f", &zonas[i].humedad_actual);

            printf("\n");
        } else {
            printf("Usando los datos historicos para la prediccion de la zona: %s\n", zonas[i].nombre);
        }
    }
}

void predecirContaminacion(Zona *zonas) {
    printf("\nPrediccion de Contaminacion para los Proximos Dias:\n");
    for (int i = 0; i < ZONAS; i++) {
        float promedio[4] = {0};

        if (zonas[i].contaminacion_actual[0] == 0 && zonas[i].contaminacion_actual[1] == 0 && 
            zonas[i].contaminacion_actual[2] == 0 && zonas[i].contaminacion_actual[3] == 0) {

            for (int j = 0; j < DIAS; j++) {
                promedio[0] += zonas[i].contaminacion_historica[j][0];
                promedio[1] += zonas[i].contaminacion_historica[j][1];
                promedio[2] += zonas[i].contaminacion_historica[j][2];
                promedio[3] += zonas[i].contaminacion_historica[j][3];
            }

            promedio[0] /= DIAS;
            promedio[1] /= DIAS;
            promedio[2] /= DIAS;
            promedio[3] /= DIAS;
        } else {
            promedio[0] = zonas[i].contaminacion_actual[0];
            promedio[1] = zonas[i].contaminacion_actual[1];
            promedio[2] = zonas[i].contaminacion_actual[2];
            promedio[3] = zonas[i].contaminacion_actual[3];
        }

        float factor_climatico = 1.0 + (zonas[i].temperatura_actual - 22) * 0.01 + 
                                 (zonas[i].viento_actual - 5) * 0.02 + 
                                 (zonas[i].humedad_actual - 60) * 0.005;

        printf("\nZona: %s\n", zonas[i].nombre);
        printf("Prediccion de CO2: %.2f, SO2: %.2f, NO2: %.2f, PM2.5: %.2f\n", 
            promedio[0] * factor_climatico, promedio[1] * factor_climatico, 
            promedio[2] * factor_climatico, promedio[3] * factor_climatico);
    }
}

void menu(Zona *zonas) {
    int opcion;
    do {
        printf("\nMenu:\n");
        printf("1. Ingresar Datos de Contaminacion\n");
        printf("2. Mostrar Contaminacion Actual\n");
        printf("3. Predecir Contaminacion\n");
        printf("4. Generar Alertas\n");
        printf("5. Recomendaciones\n");
        printf("6. Guardar Datos\n"); 
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatosContaminacion(zonas);
                break;
            case 2:
                mostrarContaminacion(zonas);
                break;
            case 3:
                predecirContaminacion(zonas);
                break;
            case 4:
                generarAlertas(zonas);
                break;
            case 5:
                recomendaciones(zonas);
                break;
            case 6: 
                guardarDatos(zonas);
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (1);
}

void mostrarContaminacion(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("Contaminacion CO2: %.2f ppm\n", zonas[i].contaminacion_actual[0]);
        printf("Contaminacion SO2: %.2f ppm\n", zonas[i].contaminacion_actual[1]);
        printf("Contaminacion NO2: %.2f ppm\n", zonas[i].contaminacion_actual[2]);
        printf("Contaminacion PM2.5: %.2f µg/m³\n", zonas[i].contaminacion_actual[3]);
        printf("Temperatura Actual: %.2f °C\n", zonas[i].temperatura_actual);
        printf("Velocidad del Viento: %.2f km/h\n", zonas[i].viento_actual);
        printf("Humedad Actual: %.2f %%\n", zonas[i].humedad_actual);
    }
}

void generarAlertas(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nAlertas para la zona: %s\n", zonas[i].nombre);

        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("¡Alerta! Niveles de CO2 elevados.\n");
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("¡Alerta! Niveles de SO2 elevados.\n");
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("¡Alerta! Niveles de NO2 elevados.\n");
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("¡Alerta! Niveles de PM2.5 elevados.\n");
        }
    }
}

void recomendaciones(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nRecomendaciones para la zona: %s\n", zonas[i].nombre);

        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("Evitar actividades al aire libre por altos niveles de CO2.\n");
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("Reducir actividades al aire libre en caso de alta presencia de SO2.\n");
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("Tomar precauciones por los altos niveles de NO2 en el aire.\n");
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("Es recomendable usar mascarillas debido a los niveles elevados de PM2.5.\n");
        }
    }
}

void guardarDatos(Zona *zonas) {
    FILE *file = fopen("datos_contaminacion.txt", "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo para guardar los datos.\n");
        return;
    }
    
    for (int i = 0; i < ZONAS; i++) {
        fprintf(file, "Zona: %s\n", zonas[i].nombre);
        fprintf(file, "Contaminacion CO2: %.2f ppm\n", zonas[i].contaminacion_actual[0]);
        fprintf(file, "Contaminacion SO2: %.2f ppm\n", zonas[i].contaminacion_actual[1]);
        fprintf(file, "Contaminacion NO2: %.2f ppm\n", zonas[i].contaminacion_actual[2]);
        fprintf(file, "Contaminacion PM2.5: %.2f µg/m³\n", zonas[i].contaminacion_actual[3]);
        fprintf(file, "Temperatura: %.2f °C\n", zonas[i].temperatura_actual);
        fprintf(file, "Viento: %.2f km/h\n", zonas[i].viento_actual);
        fprintf(file, "Humedad: %.2f %%\n", zonas[i].humedad_actual);
    }

    fclose(file);
    printf("Datos guardados con éxito.\n");
}
