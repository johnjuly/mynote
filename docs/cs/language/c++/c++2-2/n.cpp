// BubblePanel.cpp
#include "BubblePanel.h"
#include <wx/dcbuffer.h>  // 用于双缓冲

BubblePanel::BubblePanel(wxWindow* parent)
    : wxPanel(parent),
      animTimer(this),
      rng(std::random_device{}())  // 初始化随机数引擎
{
    // 启用双缓冲防止闪烁
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // 绑定事件
    Bind(wxEVT_PAINT, &BubblePanel::OnPaint, this);
    Bind(wxEVT_TIMER, &BubblePanel::OnAnimTimer, this);
    Bind(wxEVT_SIZE, &BubblePanel::OnSize, this);  // 绑定尺寸变化事件

    // 初始生成泡泡
    GenerateBubbles();
}

// 生成泡泡（根据当前面板尺寸）
void BubblePanel::GenerateBubbles() {
    bubbles.clear();
    wxSize size = GetClientSize();

    // 初始化随机分布
    std::uniform_int_distribution<int>
        xDist(0, size.x),          // X坐标分布
        yDist(0, size.y),          // Y坐标分布
        speedDist(-3, 3),          // 速度范围
        radDist(15, 30);           // 半径范围

    // 生成5个泡泡
    for(int i = 0; i < 5; ++i) {
        bubbles.push_back({
            wxPoint(xDist(rng), yDist(rng)),  // 随机位置
            wxPoint(speedDist(rng), speedDist(rng)), // 随机速度
            radDist(rng)                      // 随机半径
        });
    }
}

// 绘制泡泡
void BubblePanel::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);  // 使用双缓冲
    dc.Clear();  // 清空背景

    // 设置渐变画刷
    wxColour startColor(100, 181, 246, 180);  // 半透明蓝色
    wxColour endColor(255, 255, 255, 50);     // 半透明白色

    for(const auto& b : bubbles) {
        // 创建径向渐变
        wxGraphicsContext* gc = dc.GetGraphicsContext();
        wxGraphicsBrush brush = gc->CreateRadialGradientBrush(
            b.pos.x, b.pos.y,                   // 圆心
            0,                                   // 内圆半径
            b.pos.x, b.pos.y, b.radius*1.5,      // 外圆位置和半径
            startColor, endColor);

        gc->SetBrush(brush);
        gc->DrawEllipse(b.pos.x - b.radius,      // 左上X
                       b.pos.y - b.radius,      // 左上Y
                       b.radius*2,              // 宽度
                       b.radius*2);             // 高度
    }
}

// 动画帧更新
void BubblePanel::OnAnimTimer(wxTimerEvent&) {
    wxSize size = GetClientSize();
    std::uniform_real_distribution<float> accDist(-0.3f, 0.3f);  // 随机加速度

    for(auto& b : bubbles) {
        // 添加随机加速度
        b.speed.x += accDist(rng);
        b.speed.y += accDist(rng);

        // 应用速度衰减（模拟空气阻力）
        b.speed *= 0.98f;

        // 更新位置
        b.pos += b.speed;

        // 边界碰撞检测（考虑半径）
        if(b.pos.x - b.radius < 0) {          // 左边界
            b.pos.x = b.radius;
            b.speed.x *= -0.8f;              // 速度反转并衰减
        }
        else if(b.pos.x + b.radius > size.x) { // 右边界
            b.pos.x = size.x - b.radius;
            b.speed.x *= -0.8f;
        }

        if(b.pos.y - b.radius < 0) {          // 上边界
            b.pos.y = b.radius;
            b.speed.y *= -0.8f;
        }
        else if(b.pos.y + b.radius > size.y) { // 下边界
            b.pos.y = size.y - b.radius;
            b.speed.y *= -0.8f;
        }
    }
    Refresh();  // 请求重绘
}

// 窗口尺寸变化处理
void BubblePanel::OnSize(wxSizeEvent& event) {
    GenerateBubbles();  // 重新生成泡泡
    Refresh();          // 立即刷新
    event.Skip();       // 传递事件
}

void BubblePanel::StartAnimation() {
    animTimer.Start(30); // 约33 FPS
}

void BubblePanel::StopAnimation() {
    animTimer.Stop();
}
