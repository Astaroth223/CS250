#include <iostream>
#include <vector>
#include <random>
#include <cstdint>  // For uint32_t

// Function declarations
void populateImage(std::vector<std::vector<uint32_t>>& image);
void calculateHistograms(const std::vector<std::vector<uint32_t>>& image,
                         std::vector<int>& redHist,
                         std::vector<int>& greenHist,
                         std::vector<int>& blueHist);
void displayHistogram(const std::vector<int>& hist, const std::string& color);

int main() {
    // Define the size of our "image" (10x10 pixels)
    const int ROWS = 10;
    const int COLS = 10;

    // 2D vector to hold pixel color values
    // pixels stored as a 32-bit unsigned integer (uint32_t)
    std::vector<std::vector<uint32_t>> image_data(ROWS, std::vector<uint32_t>(COLS));

    // Fill image with random RGB color values
    std::cout << "Generating random pixel colors...\n";
    populateImage(image_data);

    // Create three histograms: one for red, one for green, one for blue
    std::vector<int> redHistogram(256, 0);    // 256 possible values (0–255)
    std::vector<int> greenHistogram(256, 0);
    std::vector<int> blueHistogram(256, 0);

    // Analyze the image to count how often each color value appears
    std::cout << "Calculating color histograms...\n";
    calculateHistograms(image_data, redHistogram, greenHistogram, blueHistogram);

    // Show the results
    std::cout << "\n=== Color Histograms ===\n";
    displayHistogram(redHistogram, "Red");
    displayHistogram(greenHistogram, "Green");
    displayHistogram(blueHistogram, "Blue");

    std::cout << "\nDone!\n";
    return 0;
}

    // helper functions
    void populateImage(std::vector<std::vector<uint32_t>>& image) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 255);

    for (auto& row : image) {
        for (auto& pixel : row) {
            uint8_t red = dist(gen);
            uint8_t green = dist(gen);
            uint8_t blue = dist(gen);

            pixel = (red << 16) | (green << 8) | blue;
        }
    }
}

void calculateHistograms(const std::vector<std::vector<uint32_t>>& image,
                         std::vector<int>& redHist,
                         std::vector<int>& greenHist,
                         std::vector<int>& blueHist) {
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            uint8_t red = (pixel >> 16) & 0xFF;
            uint8_t green = (pixel >> 8) & 0xFF;
            uint8_t blue = pixel & 0xFF;

            redHist[red]++;
            greenHist[green]++;
            blueHist[blue]++;
        }
    }
}

void displayHistogram(const std::vector<int>& hist, const std::string& color) {
    std::cout << color << " Histogram:\n";
    for (int i = 0; i < 256; ++i) {
        if (hist[i] > 0) {
            std::cout << "[" << i << "]: " << hist[i] << "\n";
        }
    }
    std::cout << std::endl;
}

