#pragma once

namespace Parameters {
	static constexpr float g = -9.81;
	static constexpr float physics_scale = 30.f; //30 pixels = 1 meter
	static constexpr float physics_scale_inv = 1.0f / physics_scale;
	static constexpr int game_width = 800;
	static constexpr int game_height = 600;
	static constexpr float time_step = 1.0f / 60.0f;
	static constexpr int sub_step_count = 4;
	constexpr float pi = 3.14159265358979323846f;
}

