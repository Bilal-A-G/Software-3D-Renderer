#pragma once
#include "../Scenes/Scene.h"

inline std::vector<TESLA::Scene*> scenes;
extern void SetUp(std::vector<TESLA::Scene*>& scenes);

void Init();
void Update(float deltaTime);
void Render();
void Shutdown();