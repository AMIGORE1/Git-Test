#include "visual.h"

static bool WorldToScreen(Vector3 pos, Vector2& screen, const Matrix4x4& matrix, int windowWidth, int windowHeight)
{
    Vector4 clipCoords = matrix * Vector4{ pos.x, pos.y, pos.z, 1.0f };

    if (clipCoords.w < 0.1f)
        return false;

    Vector3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2.0f * NDC.x) + (windowWidth / 2.0f);
    screen.y = -(windowHeight / 2.0f * NDC.y) + (windowHeight / 2.0f);
    return true;
}

void vis::Update() {
    Esp();
}

void vis::Esp() {
    auto& em = EntityManager::Get();
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    ImGuiIO& io = ImGui::GetIO();
    int W = static_cast<int>(io.DisplaySize.x);
    int H = static_cast<int>(io.DisplaySize.y);
    Matrix4x4* viewMatrix = reinterpret_cast<Matrix4x4*>(offs::ViewMatrix);

    for (const auto& ent : em.GetEntities()) {
        if (ent.isAlive) continue;
        Vector3 footWorldPos = ent.pos;
        Vector3 headWorldPos = ent.headPos;

        Vector2 screenFoot, screenHead;
        if (!WorldToScreen(footWorldPos, screenFoot, *viewMatrix, W, H)) continue;
        if (!WorldToScreen(headWorldPos, screenHead, *viewMatrix, W, H)) continue;

        float boxHeight = screenFoot.y - screenHead.y;
        if (boxHeight <= 0) continue;
        float boxWidth = boxHeight / 2.0f;

        ImVec2 topLeft(screenHead.x - (boxWidth / 2.0f), screenHead.y);
        ImVec2 bottomRight(screenHead.x + (boxWidth / 2.0f), screenFoot.y);
        ImU32 boxColor = IM_COL32(0, 255, 0, 255);
        drawList->AddRect(topLeft, bottomRight, boxColor, 3.0f, 0, 1.0f);
    }
}