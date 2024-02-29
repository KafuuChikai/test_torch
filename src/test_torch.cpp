#include "test_torch.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "test_torch");
    ros::NodeHandle nh;
    ros::Rate rate(1);

    // Load the PyTorch model
    std::string model_path = "/home/wx/catkin_ws/src/quarotor_feedback_controller/Model/Hover_target/PPO66.pt";
    torch::jit::script::Module RL_model = torch::jit::load(model_path);
    std::cout << "RL module Loaded!\n" << std::endl;

    Eigen::VectorXd obs_(10);
    Eigen::VectorXf float_obs_(10);

    while (ros::ok()){
        obs.setRandom();
        float_obs = obs.cast<float>();
        std::cout << "Input vector: " << float_obs << std::endl;

        torch::Tensor input_tensor = torch::from_blob(float_obs.data(), {1, 10}, torch::kFloat32).clone();

        std::cout << "Input tensor: " << input_tensor << std::endl;

        // Run inference
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