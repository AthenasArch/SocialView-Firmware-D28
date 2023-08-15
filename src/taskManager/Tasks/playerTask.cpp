// #include "taskManager/Tasks/playerTask.h"
// #include "Peripheral/SdServerManager/sdServerManager.h" // Incluir o header da inicialização do SD
// #include "Audio.h"

// #define I2S_DOUT      17
// #define I2S_BCLK      0
// #define I2S_LRCK      18

// Audio audio;

// void playerTask_run(void* pvParameters) {

//     SystemStatus *systemStatus = (SystemStatus *)pvParameters;
//     static bool oldStatusPauseResum = 1;

//     if(systemStatus->machine.sdCard.status != SD_CARD_OK) { 
//         // Se o cartão SD não estiver pronto, retorne e tente novamente depois
//         Serial.println("Cartão SD não está pronto, tentando novamente mais tarde...");
//         vTaskDelay(1000); // Espera um pouco antes de tentar novamente
//         return;
//     } else {
//         Serial.println("Cartão SD foi iniciado com sucesso");
//     }
  
//     audio.setPinout(I2S_BCLK, I2S_LRCK, I2S_DOUT);
//     audio.connecttoFS(SD, "/music1.mp3");
//     audio.setVolume(16); // 0...21

//     for (;;) {
//         // audio.setVolume(10); // 0...21
//         if (oldStatusPauseResum != systemStatus->player.pauseResum){
//             oldStatusPauseResum = systemStatus->player.pauseResum;
//             audio.pauseResume();
//         }
//         audio.loop();
//     }
// }

// // Optional
// void audio_info(const char *info){
//     Serial.print("info        "); Serial.println(info);
// }

// void audio_id3data(const char *info){  // id3 metadata
//     Serial.print("id3data     "); Serial.println(info);
// }

// void audio_eof_mp3(const char *info){  // end of file
//     Serial.print("eof_mp3     "); Serial.println(info);
// }
