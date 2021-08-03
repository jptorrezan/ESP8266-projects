/*
    *
    *
    * Static - No blinking. Just plain old static light.
    * Blink - Normal blinking. 50% on/off time.
    * Breath - Does the "standby-breathing" of well known i-Devices. Fixed Speed.
    * Color Wipe - Lights all LEDs after each other up. Then turns them in that order off. Repeat.
    * Color Wipe Inverse - Same as Color Wipe, except swaps on/off colors.
    * Color Wipe Reverse - Lights all LEDs after each other up. Then turns them in reverse order off. Repeat.
    * Color Wipe Reverse Inverse - Same as Color Wipe Reverse, except swaps on/off colors.
    * Color Wipe Random - Turns all LEDs after each other to a random color. Then starts over with another color.
    * Random Color - Lights all LEDs in one random color up. Then switches them to the next random color.
    * Single Dynamic - Lights every LED in a random color. Changes one random LED after the other to a random color.
    * Multi Dynamic - Lights every LED in a random color. Changes all LED at the same time to new random colors.
    * Rainbow - Cycles all LEDs at once through a rainbow.
    * Rainbow Cycle - Cycles a rainbow over the entire string of LEDs.
    * Scan - Runs a single pixel back and forth.
    * Dual Scan - Runs two pixel back and forth in opposite directions.
    * Fade - Fades the LEDs on and (almost) off again.
    * Theater Chase - Theatre-style crawling lights. Inspired by the Adafruit examples.
    * Theater Chase Rainbow - Theatre-style crawling lights with rainbow effect. Inspired by the Adafruit examples.
    * Running Lights - Running lights effect with smooth sine transition.
    * Twinkle - Blink several LEDs on, reset, repeat.
    * Twinkle Random - Blink several LEDs in random colors on, reset, repeat.
    * Twinkle Fade - Blink several LEDs on, fading out.
    * Twinkle Fade Random - Blink several LEDs in random colors on, fading out.
    * Sparkle - Blinks one LED at a time.
    * Flash Sparkle - Lights all LEDs in the selected color. Flashes single white pixels randomly.
    * Hyper Sparkle - Like flash sparkle. With more flash.
    * Strobe - Classic Strobe effect.
    * Strobe Rainbow - Classic Strobe effect. Cycling through the rainbow.
    * Multi Strobe - Strobe effect with different strobe count and pause, controlled by speed setting.
    * Blink Rainbow - Classic Blink effect. Cycling through the rainbow.
    * Chase White - Color running on white.
    * Chase Color - White running on color.
    * Chase Random - White running followed by random color.
    * Chase Rainbow - White running on rainbow.
    * Chase Flash - White flashes running on color.
    * Chase Flash Random - White flashes running, followed by random color.
    * Chase Rainbow White - Rainbow running on white.
    * Chase Blackout - Black running on color.
    * Chase Blackout Rainbow - Black running on rainbow.
    * Color Sweep Random - Random color introduced alternating from start and end of strip.
    * Running Color - Alternating color/white pixels running.
    * Running Red Blue - Alternating red/blue pixels running.
    * Running Random - Random colored pixels running.
    * Larson Scanner - K.I.T.T.
    * Comet - Firing comets from one end.
    * Fireworks - Firework sparks.
    * Fireworks Random - Random colored firework sparks.
    * Merry Christmas - Alternating green/red pixels running.
    * Fire Flicker - Fire flickering effect. Like in harsh wind.
    * Fire Flicker (soft) - Fire flickering effect. Runs slower/softer.
    * Fire Flicker (intense) - Fire flickering effect. More range of color.
    * Circus Combustus - Alternating white/red/black pixels running.
    * Halloween - Alternating orange/purple pixels running.
    * Bicolor Chase - Two LEDs running on a background color.
    * Tricolor Chase - Alternating three color pixels running.
    * TwinkleFOX - Lights fading in and out randomly.
    * thru 63. Custom - Up to eight user created custom effects.


defines in src/WS2812FX.h

#define FX_MODE_STATIC                   0
#define FX_MODE_BLINK                    1
#define FX_MODE_BREATH                   2
#define FX_MODE_COLOR_WIPE               3
#define FX_MODE_COLOR_WIPE_INV           4 
#define FX_MODE_COLOR_WIPE_REV           5
#define FX_MODE_COLOR_WIPE_REV_INV       6
#define FX_MODE_COLOR_WIPE_RANDOM        7
#define FX_MODE_RANDOM_COLOR             8
#define FX_MODE_SINGLE_DYNAMIC           9
#define FX_MODE_MULTI_DYNAMIC           10
#define FX_MODE_RAINBOW                 11
#define FX_MODE_RAINBOW_CYCLE           12
#define FX_MODE_SCAN                    13
#define FX_MODE_DUAL_SCAN               14
#define FX_MODE_FADE                    15
#define FX_MODE_THEATER_CHASE           16
#define FX_MODE_THEATER_CHASE_RAINBOW   17
#define FX_MODE_RUNNING_LIGHTS          18
#define FX_MODE_TWINKLE                 19
#define FX_MODE_TWINKLE_RANDOM          20
#define FX_MODE_TWINKLE_FADE            21
#define FX_MODE_TWINKLE_FADE_RANDOM     22
#define FX_MODE_SPARKLE                 23
#define FX_MODE_FLASH_SPARKLE           24
#define FX_MODE_HYPER_SPARKLE           25
#define FX_MODE_STROBE                  26
#define FX_MODE_STROBE_RAINBOW          27
#define FX_MODE_MULTI_STROBE            28
#define FX_MODE_BLINK_RAINBOW           29
#define FX_MODE_CHASE_WHITE             30
#define FX_MODE_CHASE_COLOR             31
#define FX_MODE_CHASE_RANDOM            32
#define FX_MODE_CHASE_RAINBOW           33
#define FX_MODE_CHASE_FLASH             34
#define FX_MODE_CHASE_FLASH_RANDOM      35
#define FX_MODE_CHASE_RAINBOW_WHITE     36
#define FX_MODE_CHASE_BLACKOUT          37
#define FX_MODE_CHASE_BLACKOUT_RAINBOW  38
#define FX_MODE_COLOR_SWEEP_RANDOM      39
#define FX_MODE_RUNNING_COLOR           40
#define FX_MODE_RUNNING_RED_BLUE        41
#define FX_MODE_RUNNING_RANDOM          42
#define FX_MODE_LARSON_SCANNER          43
#define FX_MODE_COMET                   44
#define FX_MODE_FIREWORKS               45
#define FX_MODE_FIREWORKS_RANDOM        46
#define FX_MODE_MERRY_CHRISTMAS         47
#define FX_MODE_FIRE_FLICKER            48
#define FX_MODE_FIRE_FLICKER_SOFT       49
#define FX_MODE_FIRE_FLICKER_INTENSE    50
#define FX_MODE_CIRCUS_COMBUSTUS        51
#define FX_MODE_HALLOWEEN               52
#define FX_MODE_BICOLOR_CHASE           53
#define FX_MODE_TRICOLOR_CHASE          54
#define FX_MODE_TWINKLEFOX              55
#define FX_MODE_CUSTOM                  56  // keep this for backward compatiblity
#define FX_MODE_CUSTOM_0                56  // custom modes need to go at the end
#define FX_MODE_CUSTOM_1                57
#define FX_MODE_CUSTOM_2                58
#define FX_MODE_CUSTOM_3                59
#define FX_MODE_CUSTOM_4                60
#define FX_MODE_CUSTOM_5                61
#define FX_MODE_CUSTOM_6                62
#define FX_MODE_CUSTOM_7                63

//colors
#define RED        (uint32_t)0xFF0000
#define GREEN      (uint32_t)0x00FF00
#define BLUE       (uint32_t)0x0000FF
#define WHITE      (uint32_t)0xFFFFFF
#define BLACK      (uint32_t)0x000000
#define YELLOW     (uint32_t)0xFFFF00
#define CYAN       (uint32_t)0x00FFFF
#define MAGENTA    (uint32_t)0xFF00FF
#define PURPLE     (uint32_t)0x400080
#define ORANGE     (uint32_t)0xFF3000
#define PINK       (uint32_t)0xFF1493
#define GRAY       (uint32_t)0x101010
#define ULTRAWHITE (uint32_t)0xFFFFFFFF

*/
