#include <functional> // for std::function

// Define function types for drawing operations
using DrawFunction = std::function<void(int32_t, int32_t, int32_t, int32_t, uint32_t)>;

class ProgressBar {
public:
    ProgressBar() {}

    // colors are in 5:6:5 format, to convert you can use http://greekgeeks.net/#maker-tools_convertColor
    ProgressBar(DrawFunction drawFunc, DrawFunction fillFunc, 
                int startX = 0, int startY = 0, int width = 100, int height = 10, int borderWidth = 1, 
                uint32_t activeColor = 0xB7E0, uint32_t inactiveColor = 0x7BEF, uint32_t borderColor = 0xFFFF)
        : drawRect(drawFunc), fillRect(fillFunc), x(startX), y(startY), width(width), height(height), borderWidth(borderWidth), 
          activeColor(activeColor), inactiveColor(inactiveColor), borderColor(borderColor), progress(0) {}

    void updateProgress(int newProgress) {
        previousProgress = progress;
        progress = newProgress;
        draw();
    }

private:
    DrawFunction drawRect, fillRect;
    int x, y, width, height, borderWidth;
    uint32_t activeColor, inactiveColor, borderColor;
    int progress; // Progress percentage
    int previousProgress;

    // Method to draw the progress bar
    void draw() const {
        // Draw border
        if (borderWidth > 0) {
            drawRect(x, y, width, height, borderColor);
        }
        if (previousProgress == 0 | previousProgress > progress) {
            // Draw inactive part
            fillRect(x + borderWidth, y + borderWidth, width - 2 * borderWidth, height - 2 * borderWidth, inactiveColor);
        }
        // Draw active part (based on progress)
        int activeWidth = static_cast<int>((width - 2 * borderWidth) * (progress / 100.0));
        fillRect(x + borderWidth, y + borderWidth, borderWidth + activeWidth, height - 2 * borderWidth, activeColor);
    }
};
