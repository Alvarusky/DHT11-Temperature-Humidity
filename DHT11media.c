#include <wiringPi.h>
#include <stdio.h>
#include "DHT11.h"
#include <stdlib.h>
#include <stdint.h>

char a_fecha[20];
#include "f_fecha.h"


int main()
{
        FILE *file1;
        int counter=0;
        float temperatura=0,humedad=0;
        struct dht11 resultado;
        char directorio[100]= "/home/pi/Programas/AlvaroJr/DHT11_resultados.txt";
        int MAX_COUNTER= 1800;
        float temperatura_mx = 0,humedad_mx = 0;
        float temperatura_min = 1000, humedad_min = 1000;

        file1 = fopen(directorio, "w+");

        fprintf(file1,"Alvaro de Miguel wiringPi DHT11 Temperature test program\n" );
        fputs("Humedad(min:med;max) Temperatura(min;med;max)\n", file1);
        fclose(file1);

        if ( wiringPiSetup() == -1 )
               exit( 1 );

        while ( 1 )
        {

                resultado = read_dht11_dat();

                if ( resultado.humedad > 1 && resultado.temperatura > 1)
                {
                        humedad =+ resultado.humedad;
                        temperatura =+ resultado.temperatura;
//                      printf(" Humedad = %d Temperatura :  %d \n", resultado.humedad, resultado.temperatura);
                        delay( 1000 );
                        counter++;

                }
                if (counter== MAX_COUNTER)
                {
                        temperatura=temperatura/counter;
                        humedad=humedad/counter;
                        if (temperatura_mx < temperatura)
                        {
                                temperatura_mx = temperatura;
                        }
                        if (humedad_mx < humedad)
                        {
                                humedad_mx = humedad;
                        }
                        if (temperatura_min > temperatura)
                        {
                                temperatura_min = temperatura;
                        }
                        if(humedad_min > humedad)
                        {
                                humedad_min= humedad;
                        }
//                      printf(" Humedad(min/media/max): %.2f/%.2f/%.2f Temperatura(min/media/max): %.2f/%.2f/%.2f \n", humedad_min, humedad, humedad_mx, temperatura_min, temperatura, temperatura_mx);

                        file1 = fopen(directorio, "a+");
                        fprintf(file1,"%s %.2f/%.2f/%.2f/%.2f/%.2f/%.2f\n",  (char*)f_fecha(),humedad_min, humedad, humedad_mx, temperatura_min, temperatura, temperatura_mx);
                        fclose(file1);

                        counter = 0;
                        temperatura = 0;
                        humedad = 0;
                }

        }


        return(0);
        fclose(file1);
}
