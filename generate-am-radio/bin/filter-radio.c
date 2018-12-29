#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

float level_with_fading (float level, long t, float fast_period, float medium_period, float long_period, float extralong_period) {
  return level
         + 0.4 * level * sin(t / extralong_period)
         + 0.3 * level * sin(t / long_period)
         + 0.2 * level * sin(t / medium_period)
         + 0.1 * level * sin(t / fast_period);
}

int main (int argc, char *argv[]) {

  // Randomize from frequency value
  srand(atof(argv[3]));

  // Signal component levels
  // Payload signal
  float signal_level_mkv = 10.0;
  if (argc > 4) {
    signal_level_mkv = (float) atoi(argv[4]);
  }
  float signal_fading_fast_period = rand() % 1000 + 300,
        signal_fading_medium_period = rand() % 15000 + 17500,
        signal_fading_long_period = rand() % 40000 + 60000,
        signal_fading_extralong_period = rand() % 200000 + 150000;

  // Payload signal echo
  float echo_level_mkv = 0.3,
        echo_fading_fast_period = rand() % 2000 + 1500,
        echo_fading_medium_period = rand() % 7000 + 4000,
        echo_fading_long_period = rand() % 50000 + 25000,
        echo_fading_extralong_period = rand() % 200000 + 150000;
  const int echo_size_samples = 1000;

  // Background signal
  float bg_signal_level_mkv = 0.2,
        bg_signal_fading_fast_period = rand() % 2000 + 1500,
        bg_signal_fading_medium_period = rand() % 7000 + 4000,
        bg_signal_fading_long_period = rand() % 50000 + 25000,
        bg_signal_fading_extralong_period = rand() % 200000 + 150000;

  // Interference noise
  float interference_level_mkv = 0.02,
        interference_freq_factor = rand() % 1000 / 1000.0 * 3.0 + 1.0,
        interference_fading_fast_period = rand() % 2000 + 1500,
        interference_fading_medium_period = rand() % 7000 + 4000,
        interference_fading_long_period = rand() % 50000 + 25000,
        interference_fading_extralong_period = rand() % 200000 + 150000;

  // White (or brown) noise
  float noise_level_mkv = 0.1;

  // Vars
  // Signal component values
  float signal,
        echo,
        bg_signal,
        noise, noise_src,
        interference;

  // Current levels
  float signal_cur_level,
        echo_cur_level,
        bg_signal_cur_level,
        noise_cur_level,
        interference_cur_level;
  float common_cur_level, common_signal_src;

  // Other vars
  float output, prev_output;

  // Time counter
  long t = 0;

  // Signal source
  FILE *f, *bg_f;
  f = fopen(argv[1], "r");
  bg_f = fopen(argv[2], "r");

  // Echo source
  float echo_buffer[echo_size_samples];
  memset(echo_buffer, 0, echo_size_samples);

  while (!feof(f)) {

    // Signals
    signal = fgetc(f);
    echo = echo_buffer[t % echo_size_samples];
    bg_signal = fgetc(bg_f);
    interference = 100 + 100 * sin(t / interference_freq_factor);
    noise_src = rand() % 256;
    noise = 0.5 * noise + 0.5 * noise_src;

    // Current levels
    signal_cur_level       = level_with_fading(signal_level_mkv, t, signal_fading_fast_period, signal_fading_medium_period, signal_fading_long_period, signal_fading_extralong_period);
    echo_cur_level         = level_with_fading(echo_level_mkv, t, echo_fading_fast_period, echo_fading_medium_period, echo_fading_long_period, echo_fading_extralong_period);
    bg_signal_cur_level    = level_with_fading(bg_signal_level_mkv, t, bg_signal_fading_fast_period, bg_signal_fading_medium_period, bg_signal_fading_long_period, bg_signal_fading_extralong_period);
    noise_cur_level        = noise_level_mkv;
    interference_cur_level = level_with_fading(interference_level_mkv, t, interference_fading_fast_period, interference_fading_medium_period, interference_fading_long_period, interference_fading_extralong_period);

    // Common level
    common_cur_level = signal_cur_level + echo_cur_level + bg_signal_cur_level + noise_cur_level + interference_cur_level;

    // Common signal
    common_signal_src = signal * signal_cur_level + echo * echo_cur_level + bg_signal * bg_signal_cur_level + noise * noise_cur_level + interference * interference_cur_level;

    // Output with AGC
    output = common_signal_src / common_cur_level;
    printf("%c", (char)(0.5 * output + 0.5 * prev_output));

    echo_buffer[t % echo_size_samples] = signal;
    prev_output = output;

    t++;
  }

  fclose(f);
  fclose(bg_f);
  return 0;
}
