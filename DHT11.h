#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS      85
#define DHTPIN          7

int dht11_dat[5] = { 0, 0, 0, 0, 0};

struct dht11
        {
                int humedad;
                int temperatura;
        };

struct dht11 read_dht11_dat()
{
        uint8_t laststate       = HIGH;
        uint8_t counter         = 0;
        uint8_t j               = 0, i;
        float   f;
        struct dht11 a;

        dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

//Inicializando la entrada digital
        pinMode( DHTPIN, OUTPUT );
        digitalWrite( DHTPIN, LOW );
        delay( 18 );
        digitalWrite( DHTPIN, HIGH );
        delayMicroseconds( 40 );

//Entrada digital
        pinMode( DHTPIN, INPUT );

        for ( i = 0; i < MAXTIMINGS; i++ )
        {
                counter = 0;
//              printf("Last state antes:  %d",laststate);
                while ( digitalRead( DHTPIN ) == laststate )
                {
//                      printf("%d",laststate);
                        counter++;
                        delayMicroseconds( 1 );
                        if ( counter == 255 )
                        {
                                break;
                        }
                }
                laststate = digitalRead( DHTPIN );
//              printf("     Last state despues: %d  \n",laststate );
                if ( counter == 255 )
                        break;

                if ( (i >= 4) && (i % 2 == 0) )
                {
//                      printf("\rAlvaro:  dht11_dat:  %d, %d ,%d, %d", dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
                        dht11_dat[j / 8] <<= 1;
                        if ( counter > 16 )
                                dht11_dat[j / 8] |= 1;
                        j++;
                }
        }

        if ( (j >= 40) &&
             (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
        {
                f = dht11_dat[2] * 9. / 5. + 32;  //convertir la temperatura a grados farenheit

//              printf( "Humidity = %d %% Temperature = %d C (%.1f F)\n", dht11_dat[0], dht11_dat[2], f );

                a.humedad= dht11_dat[0];
                a.temperatura= dht11_dat[2];

        } else  {
//              printf( "Data not good, skip\n" );
        }

        return(a);

}
