#ifndef RT_HPP
#define RT_HPP

#define GLFW_INCLUDE_VULKAN
#include "../glfw/include/GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>

typedef struct s_queueFamilyIndices {
    std::optional<uint32_t>         graphicsFamily;
    std::optional<uint32_t>         presentFamily;

    [[nodiscard]] bool isComplete() const
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
} t_queueFamilyIndices;

typedef struct s_swapChainSupportDetails {
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
} t_swapChainSupportDetails;

class Application
{
    const int Width = 800;
    const int Height = 600;
    const int MaxFramesInFlight = 2;

    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    public:
        void run();

    private:
        GLFWwindow                  *m_window;
        VkInstance                  m_instance;
        VkDebugUtilsMessengerEXT    m_debugMessenger;
        VkSurfaceKHR                m_surface;

        VkPhysicalDevice            m_physicalDevice = VK_NULL_HANDLE;
        VkDevice                    m_device;

        VkQueue                     m_graphicsQueue;
        VkQueue                     m_presentQueue;

        VkSwapchainKHR              m_swapChain;
        std::vector<VkImage>        m_swapChainImages;
        VkFormat                    m_swapChainImageFormat;
        VkExtent2D                  m_swapChainExtent;
        std::vector<VkImageView>    m_swapChainImageViews;
        std::vector<VkFramebuffer>  m_swapChainFramebuffers;

        VkRenderPass                m_renderPass;
        VkPipelineLayout            m_pipelineLayout;
        VkPipeline                  m_graphicsPipeline;

        VkCommandPool               m_commandPool;
        VkCommandBuffer             m_commandBuffer;

        VkSemaphore                 m_imageAvailableSemaphore;
        VkSemaphore                 m_renderFinishedSemaphore;
        VkFence                     m_inFlightFence;


    static VkResult CreateDebugUtilsMessengerEXT(
                VkInstance instance,
                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                const VkAllocationCallbacks* pAllocator,
                VkDebugUtilsMessengerEXT* pDebugMessenger);
        static void DestroyDebugUtilsMessengerEXT(
                VkInstance instance,
                VkDebugUtilsMessengerEXT debugMessenger,
                const VkAllocationCallbacks* pAllocator);
        void initGlfw();
        void initVulkan();
        void mainLoop();
        void cleanup();
        void createInstance();
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions() const;
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        t_queueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void createLogicalDevice();
        void createSurface();
        void createSwapChain();
        void createRenderPass();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffer();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createSyncObjects();
        void drawFrame();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData)
        {
            std::cerr << messageSeverity << " " << messageType <<" validation layer: " << pCallbackData->pMessage << std::endl;
            if (pUserData != nullptr)
            {
                std::cerr << "Userdata:" << (char*)pUserData << std::endl;
            }
            return VK_FALSE;
        }

    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    t_swapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    void createImageViews();

    static std::vector<char> readFile(const std::string &filename);

    void createGraphicsPipeline();

    VkShaderModule createShaderModule(const std::vector<char> &code);
};

#endif