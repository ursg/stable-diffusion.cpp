#ifndef __STABLE_DIFFUSION_H__
#define __STABLE_DIFFUSION_H__

#include <memory>
#include <vector>

enum SDLogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

enum RNGType {
    STD_DEFAULT_RNG,
    CUDA_RNG
};

enum SampleMethod {
    EULAR_A,
};

class StableDiffusionGGML;

class StableDiffusion {
   private:
    std::shared_ptr<StableDiffusionGGML> sd;

   public:
    StableDiffusion(int n_threads = -1,
                    bool vae_decode_only = false,
                    bool free_params_immediately = false,
                    RNGType rng_type = STD_DEFAULT_RNG);
    bool load_from_file(const std::string& file_path);
    std::vector<uint8_t> txt2img(
        const std::string& prompt,
        const std::string& negative_prompt,
        float cfg_scale,
        int width,
        int height,
        SampleMethod sample_method,
        int sample_steps,
        int64_t seed);
    std::vector<uint8_t> img2img(
        const std::vector<uint8_t>& init_img,
        const std::string& prompt,
        const std::string& negative_prompt,
        float cfg_scale,
        int width,
        int height,
        SampleMethod sample_method,
        int sample_steps,
        float strength,
        int64_t seed);
};

void set_sd_log_level(SDLogLevel level);
std::string sd_get_system_info();

#endif  // __STABLE_DIFFUSION_H__