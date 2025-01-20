#include <stdio.h>
#include <stdlib.h>

#define NUM_ZONAS 5
#define LIMITE_CO2 50.0  
#define LIMITE_SO2 20.0  
#define LIMITE_NO2 30.0  
#define LIMITE_PM25 25.0 

struct Zona {
    char nombre[50];
    float nivelesCO2[5];  
    float nivelesSO2[5];  
    float nivelesNO2[5];  
    float nivelesPM25[5]; 
    float prediccionCO2;  
    float prediccionSO2;  
    float prediccionNO2;  
    float prediccionPM25; 
    float temperatura;    
    float viento;         
    float humedad;        
};

struct Zona zonas[NUM_ZONAS];

void monitorearContaminacion(struct Zona* zona) {
    printf("Zona: %s\n", (*zona).nombre);
    printf("Nivel de contaminacion actual de CO2: %.2f\n", (*zona).nivelesCO2[4]);
    printf("Nivel de contaminacion actual de SO2: %.2f\n", (*zona).nivelesSO2[4]);
    printf("Nivel de contaminacion actual de NO2: %.2f\n", (*zona).nivelesNO2[4]);
    printf("Nivel de contaminacion actual de PM2.5: %.2f\n", (*zona).nivelesPM25[4]);
}

void predecirContaminacion(struct Zona* zona) {  
    float prediccionCO2 = 0.0;
    float prediccionSO2 = 0.0;
    float prediccionNO2 = 0.0;
    float prediccionPM25 = 0.0;
    float peso = 0.0;
    float ajusteClimatico = 1.0;

    for (int i = 0; i < 5; i++) {
        prediccionCO2 += (*zona).nivelesCO2[i] * (5 - i);
        prediccionSO2 += (*zona).nivelesSO2[i] * (5 - i);
        prediccionNO2 += (*zona).nivelesNO2[i] * (5 - i);
        prediccionPM25 += (*zona).nivelesPM25[i] * (5 - i);
        peso += (5 - i);
    }
    prediccionCO2 /= peso;
    prediccionSO2 /= peso;
    prediccionNO2 /= peso;
    prediccionPM25 /= peso;

    if ((*zona).temperatura > 30.0) {
        ajusteClimatico += 0.1;
    } else if ((*zona).temperatura < 10.0) { 
        ajusteClimatico -= 0.1;
    }

    if ((*zona).viento < 3.0) { 
        ajusteClimatico += 0.1;
    } else if ((*zona).viento > 10.0) { 
        ajusteClimatico -= 0.1;
    }

    if ((*zona).humedad > 80.0) { 
        ajusteClimatico += 0.05;
    } else if ((*zona).humedad < 30.0) { 
        ajusteClimatico -= 0.05;
    }

    (*zona).prediccionCO2 = prediccionCO2 * ajusteClimatico;
    (*zona).prediccionSO2 = prediccionSO2 * ajusteClimatico;
    (*zona).prediccionNO2 = prediccionNO2 * ajusteClimatico;
    (*zona).prediccionPM25 = prediccionPM25 * ajusteClimatico;
}

void alertaPreventiva(struct Zona* zona) {
    if ((*zona).prediccionCO2 > LIMITE_CO2) {
        printf("¡ALERTA! El nivel de CO2 excede el limite.\n");
    }
    if ((*zona).prediccionSO2 > LIMITE_SO2) {
        printf("¡ALERTA! El nivel de SO2 excede el limite.\n");
    }
    if ((*zona).prediccionNO2 > LIMITE_NO2) {
        printf("¡ALERTA! El nivel de NO2 excede el limite.\n");
    }
    if ((*zona).prediccionPM25 > LIMITE_PM25) {
        printf("¡ALERTA! El nivel de PM2.5 excede el limite.\n");
    }
}

void generarRecomendaciones(struct Zona* zona) {
    int recomendacionGenerada = 0; 

    if ((*zona).nivelesCO2[4] > LIMITE_CO2 || (*zona).prediccionCO2 > LIMITE_CO2) {
        printf("Recomendacion: Reducir el trafico vehicular en la zona debido a altos niveles de CO2.\n");
        recomendacionGenerada = 1;
    }
    if ((*zona).nivelesSO2[4] > LIMITE_SO2 || (*zona).prediccionSO2 > LIMITE_SO2) {
        printf("Recomendacion: Suspender actividades industriales temporales debido a altos niveles de SO2.\n");
        recomendacionGenerada = 1;
    }
    if ((*zona).nivelesPM25[4] > LIMITE_PM25 || (*zona).prediccionPM25 > LIMITE_PM25) {
        printf("Recomendacion: Suspender actividades al aire libre debido a altos niveles de PM2.5.\n");
        recomendacionGenerada = 1;
    }

    if (recomendacionGenerada == 0) {
        printf("No hay recomendaciones, los niveles de contaminacion son aceptables.\n");
    }
}

void exportarDatos(struct Zona* zona) {
    FILE* archivo = fopen("reportes.txt", "w");  
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "Zona: %s\n", (*zona).nombre);
    fprintf(archivo, "Niveles de los ultimos 5 dias:\n");
    for (int i = 0; i < 5; i++) {
        fprintf(archivo, "Dia %d - CO2: %.2f, SO2: %.2f, NO2: %.2f, PM2.5: %.2f\n", i+1, (*zona).nivelesCO2[i], (*zona).nivelesSO2[i], (*zona).nivelesNO2[i], (*zona).nivelesPM25[i]);
    }
    fprintf(archivo, "Predicciones futuras:\n");
    fprintf(archivo, "CO2: %.2f\n", (*zona).prediccionCO2);
    fprintf(archivo, "SO2: %.2f\n", (*zona).prediccionSO2);
    fprintf(archivo, "NO2: %.2f\n", (*zona).prediccionNO2);
    fprintf(archivo, "PM2.5: %.2f\n", (*zona).prediccionPM25);
    fclose(archivo);
}

int main() {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Ingrese el nombre de la zona %d: ", i + 1);
        scanf("%s", zonas[i].nombre);

        printf("Ingrese los niveles de contaminacion de los ultimos 5 dias:\n");
        for (int j = 0; j < 5; j++) {
            printf("Dia %d\n", j + 1);
            printf("CO2: ");
            scanf("%f", &zonas[i].nivelesCO2[j]);
            printf("SO2: ");
            scanf("%f", &zonas[i].nivelesSO2[j]);
            printf("NO2: ");
            scanf("%f", &zonas[i].nivelesNO2[j]);
            printf("PM2.5: ");
            scanf("%f", &zonas[i].nivelesPM25[j]);
        }

        printf("Ingrese la temperatura actual en °C: ");
        scanf("%f", &zonas[i].temperatura);
        printf("Ingrese la velocidad del viento actual en m/s: ");
        scanf("%f", &zonas[i].viento);
        printf("Ingrese el nivel de humedad actual en %%: ");
        scanf("%f", &zonas[i].humedad);

        monitorearContaminacion(&zonas[i]);
        predecirContaminacion(&zonas[i]);  
        printf("Prediccion de contaminacion futura:\n");
        printf("CO2: %.2f\n", zonas[i].prediccionCO2);
        printf("SO2: %.2f\n", zonas[i].prediccionSO2);
        printf("NO2: %.2f\n", zonas[i].prediccionNO2);
        printf("PM2.5: %.2f\n", zonas[i].prediccionPM25);

        alertaPreventiva(&zonas[i]);

        generarRecomendaciones(&zonas[i]);

        exportarDatos(&zonas[i]);
    }

    return 0;
}
