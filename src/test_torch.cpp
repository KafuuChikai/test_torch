#include "test_torch.h"

namespace fs = std::filesystem;

int main(int argc, char **argv){
    ros::init(argc, argv, "test_torch");
    ros::NodeHandle nh;
    ros::Rate rate(2000);
    ros::Publisher nn_pub;
    std_msgs::Bool hz_test;
    nn_pub = nh.advertise<std_msgs::Bool>("/test", 10);
    hz_test.data = 1;

    // Load the PyTorch model
    fs::path current_path = fs::current_path();
    // std::string model_relative_path = "src/test_torch/Model/test_model.pt";
    std::string model_relative_path = "src/test_torch/Model/bpnn_test.pt";
    fs::path model_absolute_path = current_path / model_relative_path;

    std::string model_path = model_absolute_path.string();
    torch::jit::script::Module nn_model = torch::jit::load(model_path);
    // std::cout << "RL module Loaded!\n" << std::endl;

    Eigen::VectorXd obs(15);    // double type
    Eigen::VectorXf float_obs(15);  // double type

    double dataset[15] = {-2.5,-1.5,-0.8999999999999999,
                          -6.0,-2.0,0.0,
                          0.0,0.0,0.021815177933981113,
                          -0.05176682900616987,-0.0668506193060422,9.935041240132362,
                          0.3372690239911232,-0.3197741439636147,0.0397553322282329};

    while (ros::ok()){
        // obs.setRandom();
        int i;
        for (int i = 0; i < 15; i++)
        {
            obs[i] = dataset[i];
        }
        float_obs = obs.cast<float>();  // float type
        // std::cout << "Input vector: " << float_obs << std::endl;
                
        torch::Tensor input_tensor = torch::from_blob(float_obs.data(), {1, 15}, torch::kFloat32).clone();

        // std::cout << "Input tensor: " << input_tensor << std::endl;

        // Run inference (model needs float type)
        torch::jit::IValue outputs = nn_model.forward({input_tensor});

        // Extract output tensor
        // torch::Tensor output_tensor = outputs.toTuple()->elements()[0].toTensor();

        // Print output tensor
        // std::cout << "Output tensor: " << output_tensor << std::endl;
        std::cout << "Output tensor: " << outputs << std::endl;

        nn_pub.publish(hz_test);

        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}