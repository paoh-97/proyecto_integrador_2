#include <stdio.h>
#include <stdlib.h>

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

int main() {
    struct Zona zonas[ZONAS]; 
    cargarDatos(zonas); 
    mostrarContaminacion(zonas); 
    predecirContaminacion(zonas);  
    generarAlertas(zonas);  
    recomendaciones(zonas); 
    guardarDatos(zonas); 

    return 0;
}

void cargarDatos(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("Ingrese el nombre de la zona %d: ", i + 1);
        scanf("%s", zonas[i].nombre); 
        printf("Ingrese los niveles de contaminantes actuales para la zona %s:\n", zonas[i].nombre);
        printf("CO2: ");
        scanf("%f", &zonas[i].contaminacion_actual[0]);
        printf("SO2: ");
        scanf("%f", &zonas[i].contaminacion_actual[1]);
        printf("NO2: ");
        scanf("%f", &zonas[i].contaminacion_actual[2]);
        printf("PM2.5: ");
        scanf("%f", &zonas[i].contaminacion_actual[3]);

        for (int j = 0; j < DIAS; j++) {
            printf("Día %d (CO2, SO2, NO2, PM2.5): ", j + 1);
            scanf("%f %f %f %f", &zonas[i].contaminacion_historica[j][0],
                                  &zonas[i].contaminacion_historica[j][1],
                                  &zonas[i].contaminacion_historica[j][2],
                                  &zonas[i].contaminacion_historica[j][3]);
        }

        printf("Ingrese la temperatura actual (°C): ");
        scanf("%f", &zonas[i].temperatura_actual);
        printf("Ingrese la velocidad del viento actual (km/h): ");
        scanf("%f", &zonas[i].viento_actual);
        printf("Ingrese el nivel de humedad actual (%%): ");
        scanf("%f", &zonas[i].humedad_actual);
    }
}

void mostrarContaminacion(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("Contaminación actual:\n");
        printf("CO2: %.2f\n", zonas[i].contaminacion_actual[0]);
        printf("SO2: %.2f\n", zonas[i].contaminacion_actual[1]);
        printf("NO2: %.2f\n", zonas[i].contaminacion_actual[2]);
        printf("PM2.5: %.2f\n", zonas[i].contaminacion_actual[3]);
    }
}

void predecirContaminacion(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nPredicción de contaminación para la zona %s en las proximas 24 horas:\n", zonas[i].nombre);
        float prediccion[4] = {0.0, 0.0, 0.0, 0.0};
        for (int j = DIAS - 5; j < DIAS; j++) {
            prediccion[0] += zonas[i].contaminacion_historica[j][0];
            prediccion[1] += zonas[i].contaminacion_historica[j][1];
            prediccion[2] += zonas[i].contaminacion_historica[j][2];
            prediccion[3] += zonas[i].contaminacion_historica[j][3];
        }

        for (int k = 0; k < 4; k++) {
            prediccion[k] /= 5.0;
        }

        prediccion[0] += zonas[i].temperatura_actual * 0.1 - zonas[i].viento_actual * 0.05;  
        prediccion[1] += zonas[i].humedad_actual * 0.05; 

        printf("Predicción CO2: %.2f\n", prediccion[0]);
        printf("Predicción SO2: %.2f\n", prediccion[1]);
        printf("Predicción NO2: %.2f\n", prediccion[2]);
        printf("Predicción PM2.5: %.2f\n", prediccion[3]);
    }
}

void generarAlertas(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nAlertas para la zona %s:\n", zonas[i].nombre);
        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("[ALERTA] El nivel de CO2 supera el limite\n");
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("[ALERTA] El nivel de SO2 supera el limite\n");
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("[ALERTA] El nivel de NO2 supera el limite\n");
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("[ALERTA] El nivel de PM2.5 supera el limite\n");
        }
    }
}

void recomendaciones(struct Zona zonas[ZONAS]) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nRecomendaciones para la zona %s:\n", zonas[i].nombre);
        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("Reducir tráfico vehicular\n");
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("Cerrar temporalmente industrias\n");
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("Limitar actividades al aire libre\n");
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("Suspender actividades al aire libre\n");
        }
    }
}

void guardarDatos(struct Zona zonas[ZONAS]) {
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar los datos.\n");
        return;
    }

    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "\nZona: %s\n", zonas[i].nombre);
        fprintf(archivo, "Contaminacion actual:\n");
        fprintf(archivo, "CO2: %.2f\n", zonas[i].contaminacion_actual[0]);
        fprintf(archivo, "SO2: %.2f\n", zonas[i].contaminacion_actual[1]);
        fprintf(archivo, "NO2: %.2f\n", zonas[i].contaminacion_actual[2]);
        fprintf(archivo, "PM2.5: %.2f\n", zonas[i].contaminacion_actual[3]);

        fprintf(archivo, "Contaminacion historica:\n");
        for (int j = 0; j < DIAS; j++) {
            fprintf(archivo, "Día %d: CO2=%.2f, SO2=%.2f, NO2=%.2f, PM2.5=%.2f\n", 
                    j+1, zonas[i].contaminacion_historica[j][0], zonas[i].contaminacion_historica[j][1],
                    zonas[i].contaminacion_historica[j][2], zonas[i].contaminacion_historica[j][3]);
        }
    }

    fclose(archivo);
    printf("Los datos han sido guardados en el archivo reporte_contaminacion.txt.\n");
}