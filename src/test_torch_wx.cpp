#include "test_torch.h"

namespace fs = std::filesystem;

int main(int argc, char **argv){
    ros::init(argc, argv, "test_torch");
    ros::NodeHandle nh;
    ros::Rate rate(100);

    // Load the PyTorch model
    fs::path current_path = fs::current_path();
    std::string model_relative_path = "src/test_torch/Model/test_model.pt";
    fs::path model_absolute_path = current_path / model_relative_path;

    std::string model_path = model_absolute_path.string();
    torch::jit::script::Module RL_model = torch::jit::load(model_path);
    std::cout << "RL module Loaded!\n" << std::endl;

    Eigen::VectorXd obs(10);    // double type
    Eigen::VectorXf float_obs(10);  // double type

    while (ros::ok()){
        obs.setRandom();
        float_obs = obs.cast<float>();  // float type
        std::cout << "Input vector: " << float_obs << std::endl;

        torch::Tensor input_tensor = torch::from_blob(float_obs.data(), {1, 10}, torch::kFloat32).clone();

        std::cout << "Input tensor: " << input_tensor << std::endl;

        // Run inference (model needs float type)
        torch::jit::IValue outputs = RL_model.forward({input_tensor});

        // Extract output tensor
        torch::Tensor output_tensor = outputs.toTuple()->elements()[0].toTensor();

        // Print output tensor
        std::cout << "Output tensor: " << output_tensor << std::endl;

        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}