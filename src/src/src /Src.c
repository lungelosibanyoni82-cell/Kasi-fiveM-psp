
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdio.h>

PSP_MODULE_INFO("Kasi FiveM PSP", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf

int main(void) {
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    int x = 16, y = 8;
    SceCtrlData pad;
    unsigned int oldButtons = 0;

    while (1) {
        sceCtrlReadBufferPositive(&pad, 1);

        if (pad.Buttons & PSP_CTRL_UP && y > 2) y--;
        if (pad.Buttons & PSP_CTRL_DOWN && y < 17) y++;
        if (pad.Buttons & PSP_CTRL_LEFT && x > 1) x--;
        if (pad.Buttons & PSP_CTRL_RIGHT && x < 30) x++;

        if ((pad.Buttons & PSP_CTRL_START) &&
            !(oldButtons & PSP_CTRL_START)) break;

        oldButtons = pad.Buttons;

        pspDebugScreenSetXY(0, 0);
        printf("KASI FIVEM - PSP EDITION\n");
        printf("D-pad: Move | START: Quit\n\n");

        for (int row = 0; row < 20; row++) {
            for (int col = 0; col < 32; col++) {
                if (row == 0 || row == 19 ||
                    col == 0 || col == 31) printf("#");
                else if (row == 5 && col > 3 && col < 12) printf("=");
                else if (row == 13 && col > 19 && col < 28) printf("=");
                else if (row == 9 && col == 7) printf("S");
                else if (row == 4 && col == 24) printf("P");
                else if (row == y && col == x) printf("@");
                else printf(" ");
            }
            printf("\n");
        }

        printf("\n@ You  S Spaza  P Police station\n");
        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
