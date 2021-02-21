#include <stdio.h>
#include <stdint.h>

#include <raylib.h>

#include "librocket/sync.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include "scene_state_machine.hpp"
#include "scenes/game_scene/scene_game.hpp"
#include "scenes/splash_scene/scene_splash_screen.hpp"


#define MIN_INTERVAL (1.0 / 100.0)
#define MAX_LATENCY   0.5

const int screenWidth = 1024;
const int screenHeight = 600;
const Color BACKGROUND = {12, 12, 12};

enum Dir {UP, DOWN, LEFT, RIGHT};

SceneStateMachine sceneStateMachine;

ma_result result;
ma_decoder decoder;
ma_device_config deviceConfig;
ma_device device;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_bool32 isLooping = MA_TRUE;

    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    /*
    A decoder is a data source which means you can seemlessly plug it into the ma_data_source API. We can therefore take advantage
    of the "loop" parameter of ma_data_source_read_pcm_frames() to handle looping for us.
    */
    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL, isLooping);

    (void)pInput;
}

int SetupMiniAudio(char* filename)
{
    result = ma_decoder_init_file(filename, NULL, &decoder);
    if (result != MA_SUCCESS) {
        return -2;
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&decoder);
        return -3;
    }

    return 0;
}

int Main()
{
    sync_device *rocket = sync_create_device("sync");
    sync_tcp_connect(rocket, "localhost", 1338);

    /* Rocket tracks */
    const sync_track *clear_r = sync_get_track(rocket, "color:clear.r");
    const sync_track *clear_g = sync_get_track(rocket, "color:clear.g");
    const sync_track *clear_b = sync_get_track(rocket, "color:clear.b");
    const sync_track *cam_rot = sync_get_track(rocket, "camera:rot.y");
    const sync_track *cam_dist = sync_get_track(rocket, "camera:dist");

    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(sceneStateMachine); //1
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();

    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen); //2
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);

    splashScreen->SetSwitchToScene(gameSceneID);
    sceneStateMachine.SwitchTo(splashScreenID);

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return -4;
    }

    /* Main game loop */
    while (!WindowShouldClose()) {    // Detect window close button or ESC key

        //if (sync_update(rocket, (int)floor(row), &bass_cb, (void *)&stream))
            //sync_tcp_connect(rocket, "localhost", SYNC_DEFAULT_PORT);

        sceneStateMachine.ProcessInput();
        sceneStateMachine.Update(GetFrameTime());

        /* Draw */
        BeginDrawing();
            sceneStateMachine.Draw();
            //ClearBackground(BACKGROUND);
            //DrawText("GAME OVER..", screenWidth / 3.0, screenHeight / 2.0, 68, WHITE);
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return 0;
}


int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT); // Use before InitWindow()
    InitWindow(screenWidth, screenHeight, "Friday warm beer pong");
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second

    SetupMiniAudio("resources/shit_loop.mp3");
    Main();

    return 0;
}
