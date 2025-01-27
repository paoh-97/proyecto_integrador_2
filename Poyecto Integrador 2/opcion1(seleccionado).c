#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZONAS 5
#define DIAS 30
#define LIMITE_CO2 100
#define LIMITE_SO2 50
#define LIMITE_NO2 60
#define LIMITE_PM25 25

struct Zona {
    char nombre[30];
    float contaminacion_actual[4]; 
    float contaminacion_historica[DIAS][4]; 
    float temperatura_actual;
    float viento_actual;
    float humedad_actual;
};

void cargarDatos(struct Zona zonas[ZONAS]);
void mostrarContaminacion(struct Zona zonas[ZONAS]);
void predecirContaminacion(struct Zona zonas[ZONAS]);
void generarAlertas(struct Zona zonas[ZONAS]);
void recomendaciones(struct Zona zonas[ZONAS]);
void guardarDatos(struct Zona zonas[ZONAS]);
void calcularPromediosHistoricos(struct Zona zonas[ZONAS]);
void ingresarDatosContaminacion(struct Zona zonas[ZONAS]);
void menu(struct Zona zonas[ZONAS]);

int main() {
    struct Zona zonas[ZONAS]; 
    cargarDatos(zonas); 
    
    menu(zonas); 

    return 0;
}

void cargarDatos(struct Zona zonas[ZONAS]) {
    char *nombresZonas[ZONAS] = {"Centro Historico", "La Mariscal", "Cotogchoa", "Rumiñahui", "San Juan"};
    
    float contaminacion_historica[ZONAS][DIAS][4] = {
        {{50.0, 30.0, 40.0, 20.0}, {55.0, 32.0, 43.0, 22.0}, {60.0, 35.0, 45.0, 25.0},
         {58.0, 33.0, 42.0, 23.0}, {57.0, 34.0, 44.0, 21.0}, {61.0, 36.0, 46.0, 26.0},
         {62.0, 37.0, 47.0, 27.0}, {63.0, 38.0, 48.0, 28.0}, {64.0, 39.0, 49.0, 29.0},
         {65.0, 40.0, 50.0, 30.0}, {66.0, 41.0, 51.0, 31.0}, {67.0, 42.0, 52.0, 32.0},
         {68.0, 43.0, 53.0, 33.0}, {69.0, 44.0, 54.0, 34.0}, {70.0, 45.0, 55.0, 35.0},
         {71.0, 46.0, 56.0, 36.0}, {72.0, 47.0, 57.0, 37.0}, {73.0, 48.0, 58.0, 38.0},
         {74.0, 49.0, 59.0, 39.0}, {75.0, 50.0, 60.0, 40.0}, {76.0, 51.0, 61.0, 41.0},
         {77.0, 52.0, 62.0, 42.0}, {78.0, 53.0, 63.0, 43.0}, {79.0, 54.0, 64.0, 44.0},
         {80.0, 55.0, 65.0, 45.0}, {81.0, 56.0, 66.0, 46.0}, {82.0, 57.0, 67.0, 47.0},
         {83.0, 58.0, 68.0, 48.0}, {84.0, 59.0, 69.0, 49.0}, {85.0, 60.0, 70.0, 50.0}},  // Centro Historico
        
        {{45.0, 25.0, 30.0, 15.0}, {50.0, 28.0, 35.0, 17.0}, {55.0, 32.0, 40.0, 20.0},
         {53.0, 31.0, 38.0, 19.0}, {52.0, 30.0, 37.0, 18.0}, {56.0, 33.0, 42.0, 21.0},
         {58.0, 35.0, 44.0, 22.0}, {59.0, 36.0, 45.0, 23.0}, {60.0, 37.0, 46.0, 24.0},
         {61.0, 38.0, 47.0, 25.0}, {62.0, 39.0, 48.0, 26.0}, {63.0, 40.0, 49.0, 27.0},
         {64.0, 41.0, 50.0, 28.0}, {65.0, 42.0, 51.0, 29.0}, {66.0, 43.0, 52.0, 30.0},
         {67.0, 44.0, 53.0, 31.0}, {68.0, 45.0, 54.0, 32.0}, {69.0, 46.0, 55.0, 33.0},
         {70.0, 47.0, 56.0, 34.0}, {71.0, 48.0, 57.0, 35.0}, {72.0, 49.0, 58.0, 36.0},
         {73.0, 50.0, 59.0, 37.0}, {74.0, 51.0, 60.0, 38.0}, {75.0, 52.0, 61.0, 39.0},
         {76.0, 53.0, 62.0, 40.0}, {77.0, 54.0, 63.0, 41.0}, {78.0, 55.0, 64.0, 42.0},
         {79.0, 56.0, 65.0, 43.0}, {80.0, 57.0, 66.0, 44.0}, {81.0, 58.0, 67.0, 45.0}},  // La Mariscal

        {{48.0, 28.0, 35.0, 18.0}, {52.0, 31.0, 39.0, 20.0}, {57.0, 33.0, 42.0, 23.0},
        {59.0, 35.0, 44.0, 25.0}, {60.0, 36.0, 45.0, 26.0}, {61.0, 37.0, 46.0, 27.0},
        {63.0, 38.0, 47.0, 28.0}, {64.0, 39.0, 48.0, 29.0}, {66.0, 41.0, 50.0, 30.0},
        {67.0, 42.0, 51.0, 31.0}, {69.0, 43.0, 52.0, 33.0}, {70.0, 44.0, 53.0, 34.0},
        {72.0, 45.0, 54.0, 35.0}, {73.0, 46.0, 55.0, 36.0}, {74.0, 47.0, 56.0, 37.0},
        {75.0, 48.0, 57.0, 38.0}, {77.0, 49.0, 58.0, 39.0}, {78.0, 50.0, 59.0, 40.0},
        {79.0, 51.0, 60.0, 41.0}, {80.0, 52.0, 61.0, 42.0}, {81.0, 53.0, 62.0, 43.0},
        {82.0, 54.0, 63.0, 44.0}, {83.0, 55.0, 64.0, 45.0}, {84.0, 56.0, 65.0, 46.0},
        {85.0, 57.0, 66.0, 47.0}, {86.0, 58.0, 67.0, 48.0}, {87.0, 59.0, 68.0, 49.0},
        {88.0, 60.0, 69.0, 50.0}, {89.0, 61.0, 70.0, 51.0}, {30.0, 62.0, 71.0, 52.0}}, //Cotogchoa

        {{42.0, 24.0, 38.0, 16.0}, {47.0, 27.0, 41.0, 18.0}, {53.0, 30.0, 44.0, 21.0},
        {55.0, 31.0, 45.0, 22.0}, {57.0, 33.0, 46.0, 23.0}, {59.0, 34.0, 48.0, 24.0},
        {61.0, 35.0, 49.0, 25.0}, {62.0, 36.0, 50.0, 26.0}, {64.0, 37.0, 51.0, 27.0},
        {65.0, 38.0, 52.0, 28.0}, {66.0, 39.0, 53.0, 29.0}, {67.0, 40.0, 54.0, 30.0},
        {69.0, 41.0, 55.0, 31.0}, {71.0, 42.0, 56.0, 32.0}, {72.0, 43.0, 57.0, 33.0},
        {73.0, 44.0, 58.0, 34.0}, {75.0, 45.0, 59.0, 35.0}, {76.0, 46.0, 60.0, 36.0},
        {78.0, 47.0, 61.0, 37.0}, {79.0, 48.0, 62.0, 38.0}, {80.0, 49.0, 63.0, 39.0},
        {81.0, 50.0, 64.0, 40.0}, {82.0, 51.0, 65.0, 41.0}, {83.0, 52.0, 66.0, 42.0},
        {84.0, 53.0, 67.0, 43.0}, {85.0, 54.0, 68.0, 44.0}, {86.0, 55.0, 69.0, 45.0}}, //Rumiñahui

        {{51.0, 29.0, 37.0, 19.0}, {56.0, 32.0, 40.0, 21.0}, {61.0, 36.0, 43.0, 24.0},
        {63.0, 37.0, 44.0, 25.0}, {65.0, 38.0, 45.0, 26.0}, {67.0, 39.0, 46.0, 27.0},
        {68.0, 40.0, 47.0, 28.0}, {69.0, 41.0, 48.0, 29.0}, {70.0, 42.0, 49.0, 30.0},
        {71.0, 43.0, 50.0, 31.0}, {72.0, 44.0, 51.0, 32.0}, {73.0, 45.0, 52.0, 33.0},
        {74.0, 46.0, 53.0, 34.0}, {75.0, 47.0, 54.0, 35.0}, {76.0, 48.0, 55.0, 36.0},
        {77.0, 49.0, 56.0, 37.0}, {78.0, 50.0, 57.0, 38.0}, {79.0, 51.0, 58.0, 39.0},
        {80.0, 52.0, 59.0, 40.0}, {81.0, 53.0, 60.0, 41.0}, {82.0, 54.0, 61.0, 42.0},
        {83.0, 55.0, 62.0, 43.0}, {84.0, 56.0, 63.0, 44.0}, {85.0, 57.0, 64.0, 45.0},
        {86.0, 58.0, 65.0, 46.0}, {87.0, 59.0, 66.0, 47.0}, {88.0, 60.0, 67.0, 48.0}}, //San Juan
        
    };

    for (int i = 0; i < ZONAS; i++) {
        strcpy(zonas[i].nombre, nombresZonas[i]);

        for (int j = 0; j < DIAS; j++) {
            zonas[i].contaminacion_historica[j][0] = contaminacion_historica[i][j][0];
            zonas[i].contaminacion_historica[j][1] = contaminacion_historica[i][j][1];
            zonas[i].contaminacion_historica[j][2] = contaminacion_historica[i][j][2];
            zonas[i].contaminacion_historica[j][3] = contaminacion_historica[i][j][3];
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

void ingresarDatosContaminacion(struct Zona zonas[ZONAS]) {
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

void predecirContaminacion(struct Zona zonas[ZONAS]) {
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

void menu(struct Zona zonas[ZONAS]) {
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


void mostrarContaminacion(struct Zona zonas[ZONAS]) {
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

void generarAlertas(struct Zona zonas[ZONAS]) {
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

void recomendaciones(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nRecomendaciones para la zona: %s\n", zonas[i].nombre);
        
        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("Evitar actividades al aire libre.\n");
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("Recomendamos el uso de mascarillas.\n");
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("Evitar areas con trafico intenso.\n");
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("Consultar con un profesional de la salud.\n");
        }
    }
}

void guardarDatos(struct Zona zonas[ZONAS]) {
    FILE *archivo = fopen("report_contaminacion.txt", "w");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar los datos.\n");
        return;
    }

    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "Zona: %s\n", zonas[i].nombre);
        fprintf(archivo, "Contaminacion CO2: %.2f ppm\n", zonas[i].contaminacion_actual[0]);
        fprintf(archivo, "Contaminacion SO2: %.2f ppm\n", zonas[i].contaminacion_actual[1]);
        fprintf(archivo, "Contaminacion NO2: %.2f ppm\n", zonas[i].contaminacion_actual[2]);
        fprintf(archivo, "Contaminacion PM2.5: %.2f µg/m³\n", zonas[i].contaminacion_actual[3]);
        fprintf(archivo, "Temperatura Actual: %.2f °C\n", zonas[i].temperatura_actual);
        fprintf(archivo, "Velocidad del Viento: %.2f km/h\n", zonas[i].viento_actual);
        fprintf(archivo, "Humedad Actual: %.2f %%\n", zonas[i].humedad_actual);
        fprintf(archivo, "---------------------------------------\n");
    }

    fclose(archivo);
    printf("Los datos se han guardado correctamente en el archivo 'report_contaminacion.txt'.\n");
} 
