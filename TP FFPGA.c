#include "sys/alt_stdio.h"
#include <system.h>
#include <io.h>

// Definition des adresses de base des composants
#define yassinAES_BASEADDR YASSIN_AES_0_BASE
#define PERF_CNTR_BASE 0x12345678 // Remplacez par l'adresse de base du compteur de performances

// Declaration des variables globales
unsigned int res[4];

// Declaration des fonctions
void PERF_BEGIN(unsigned int base_addr, unsigned int counter);
void PERF_END(unsigned int base_addr, unsigned int counter);
unsigned int perf_get_section_time(unsigned int base_addr, unsigned int counter);

// Fonction principale
int main()
{
    alt_putstr("Hello from Nios II!\n");
    alt_putstr("Load KEY!\n");
    IOWR_32DIRECT(yassinAES_BASEADDR, 0x00, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 1 * 0x04, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 2 * 0x04, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 3 * 0x04, 0x11111111);
    alt_putstr("Load data!\n");
    IOWR_32DIRECT(yassinAES_BASEADDR, 4 * 0x04, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 5 * 0x04, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 6 * 0x04, 0x11111111);
    IOWR_32DIRECT(yassinAES_BASEADDR, 7 * 0x04, 0x11111111);
    alt_putstr("retrive output!\n");

    PERF_BEGIN(PERF_CNTR_BASE, 1); // D�but de la mesure de performance

    printf("template0 0x%X \n", IORD_32DIRECT(yassinAES_BASEADDR, 8 * 0x04));
    printf("template1 0x%X \n", IORD_32DIRECT(yassinAES_BASEADDR, 9 * 0x04));
    printf("template2 0x%X \n", IORD_32DIRECT(yassinAES_BASEADDR, 10 * 0x04));
    printf("template3 0x%X \n", IORD_32DIRECT(yassinAES_BASEADDR, 11 * 0x04));
    printf("template3 0x%X 0x%X 0x%X 0x%X\n",
        IORD_32DIRECT(yassinAES_BASEADDR, 11 * 0x04),
        IORD_32DIRECT(yassinAES_BASEADDR, 10 * 0x04),
        IORD_32DIRECT(yassinAES_BASEADDR, 9 * 0x04),
        IORD_32DIRECT(yassinAES_BASEADDR, 8 * 0x04));

    PERF_END(PERF_CNTR_BASE, 1); // Fin de la mesure de performance

    unsigned int section_time = perf_get_section_time(PERF_CNTR_BASE, 1);
    printf("Temps de la section mesuree : %u cycles\n", section_time);

    alt_putstr("Hello from Nios II!\n");

    while (1)
    {
    }

    return 0;
}

// Fonctions de mesure de performance
void PERF_BEGIN(unsigned int base_addr, unsigned int counter)
{
    // Assurez-vous que le compteur est reinitialise en premier
    IOWR_32DIRECT(base_addr, counter * 0x04, 0);

    // Commencez la mesure de performance en activant le compteur
    IOWR_32DIRECT(base_addr, counter * 0x04 + 1, 1);
}
// Fonctions de mesure de performance 
void PERF_END(unsigned int base_addr, unsigned int counter)
{
    // Arretez la mesure de performance en desactivant le compteur 
    IOWR_32DIRECT(base_addr, counter * 0x04 + 1, 0);
}
 // Fonctions de mesure de performance 
unsigned int perf_get_section_time(unsigned int base_addr, unsigned int counter)
{
    // Lisez la valeur actuelle du compteur 
    unsigned int counter_value = IORD_32DIRECT(base_addr, counter * 0x04);

    // Retournez la valeur du compteur, qui represente le temps ecoule pendant la section mesuree
    return counter_value;
}
